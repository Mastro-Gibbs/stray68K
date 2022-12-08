#include "emulator.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cpu.h"
#include "ram.h"
#include "JSON.h"

#define SIMHALT_SYMBOL  0xAC
#define ORG_SYMBOL      'o'
#define ORG_DEFAULT     0x00000000

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

bit halt_compare(u8 *s1)
{
    u8 halt[8] = {0xAC, 0xAC, 0xFF, 0xFF, 0xFF, 0xFF, 0xAC, 0xAC};

    for (u16 i = 0; i < 8; i++)
        if (s1[i] != halt[i]) return FALSE;

    return TRUE;
}


/* LOADER */
bit _is_valid_file(struct EmulationMachine *em)
{
    FILE    *fp;

    const char* ldot = strrchr(em->ExecArgs.executable_path, '.');
    if (ldot != NULL)
    {
        size_t length = strlen("B68");
        if (strncmp(ldot + 1, "B68", length) != 0)
        {
            EMULATOR_ERROR("File extension not valid, be sure to pass '.B68' format.")
        }
    }

    fp = fopen(em->ExecArgs.executable_path, "r");

    if (fp == NULL)
        EMULATOR_ERROR("File not found, be sure to pass correct path.")

    fseek(fp, 0L, SEEK_END);
    if (ftell(fp) == 0L)
        EMULATOR_ERROR("Empty bin file.")

    fclose(fp);

    return 1;
}



FILE* open_file_and_extract_ORG(struct EmulationMachine *em)
{
    FILE *fp;

    s8  is_org = 0;
    u8  org[4];
    u32 value = ORG_DEFAULT;

    fp = fopen(em->ExecArgs.executable_path, "rb");

    if (fread(&is_org, 1, 1, fp) == 0)
        EMULATOR_ERROR("Error incomes while loading invalid binary");

    if (is_org == ORG_SYMBOL)
    {
        if (fread(org, ARRAY_SIZE(org), sizeof (*org), fp) == 0)
            EMULATOR_ERROR("Error incomes while loading binary");

        value = (org[0] << 24) | (org[1] << 16) | (org[2] << 8) | org[3];
    }
    else
        fseek(fp, 0, SEEK_SET);

    em->Machine.RuntimeData.org_pointer = value;
    em->Machine.cpu->pc                 = value;

    return fp;
}

void load_bytecode(struct EmulationMachine *em)
{
    FILE  *fp;

    u8  byte;
    u32 span = 0;

    fp = open_file_and_extract_ORG(em);

    while (fread(&byte, 1, 1, fp) != 0)
    {
        if (byte == SIMHALT_SYMBOL)
        {
            u8 sh[8] = {byte, 0, 0, 0, 0, 0, 0, 0};

            u16 i   = 1;
            u32 len = 1;

            for (; i < 8 && len != 0; i++)
                len = fread(&sh[i], 1, 1, fp);

            if (halt_compare(sh) && em->Machine.RuntimeData.simhalt == 0)
            {
                em->Machine.RuntimeData.simhalt = em->Machine.cpu->pc + span;
                continue;
            }
            else fseek(fp, ftell(fp) - ((!len) ? (i-2) : (i-1)),  SEEK_SET);
        }

        write_byte(em->Machine.cpu->pc + span, byte);
        span += BYTE_SPAN;
    }


    fclose(fp);

    em->Machine.RuntimeData.last_loaded_byte_index = em->Machine.cpu->pc + span;

    if (em->Machine.RuntimeData.simhalt == 0)
        em->Machine.RuntimeData.simhalt = em->Machine.RuntimeData.last_loaded_byte_index;

}



/* EMULATOR UTILS*/
void parse_args(struct EmulationMachine *em, int argc, char **argv)
{
    if (argc < 3)
    {
        fputs(
            "**stray68K** an emulator for Motorola 68000.\n"
            "\n"
            "**Modality**\n"
            " -Assembler:\n"
            "   -a [opts|args] -Invoke assembler. See help.\n"
            " -Emulator:\n"
            "   -e [path] -STANDARD MODE. Input executable file. To generate it use assembler options.\n"
            "   -s [path] -STEP-BY-STEP MODE. Like option '-e' but run executable file step by step (debug mode).\n"
            "\n"
            "**Emulator options list**\n"
            " [-q] -Mean quiet output.\n"
            "       This option is prohibited in STEP-BY-STEP MODE.\n"
            " [-d] -Mean descriptive output.\n"
            "       This option is prohibited in STANDARD MODE.\n"
            " [-t] -Perform a chrono calculation and print it.\n"
            "       This option is prohibited in STEP-BY-STEP MODE.\n"
            " [-j] -Perform JSON machine encoding output.\n"
            "\n"
            " You cannot combine '-d' and '-q' options.\n"
            " You cannot combine '-j' and '-t' options.\n"
            " You cannot combine JSON encoding option 'dump' and 'concat'.\n"
            " You cannot use JSON encoding option (-j) alone.\n"
            " You cannot use JSON chrono encoding (-j chrono) in step-by-step mode.\n"
            "\n"
            "**JSON encoding commands**\n"
            " [cpu]    -Mean cpu encoding.\n"
            " [ram]    -Mean ram encoding.\n"
            " [chrono] -Mean chrono encoding (ns).\n"
            " [op]     -Mean op mnemonic and code encoding (base 10).\n"
            " [io]     -Show io operation in JSON format.\n"
            " [dump]   -Perform sys dump in JSON format.\n"
            " [concat] -Perform JSON concat, must pass at least two listed above commands.\n"
            "\n"
            "**STEP-BY-STEP MODE's options asked from stdin**\n"
            " [s] -Asks for top address and print current stack.\n"
            " [r] -Asks for ram offsets and print selected ram chunck.\n"
            " [n] -Execute next istruction.\n"
            " [t] -Terminate the program. The execution proceeds to the end.\n"
            "\n\n",
        stdout);

        EMULATOR_ERROR("Too few params")
    }

    em->ExecArgs.executable_path  = argv[2];
    em->ExecArgs.descriptive_mode = FALSE;
    em->ExecArgs.quiet_mode       = FALSE;
    em->ExecArgs.chrono_mode      = FALSE;

    em->ExecArgs.JSON.is_activated = FALSE;
    em->ExecArgs.JSON.cpu    = FALSE;
    em->ExecArgs.JSON.ram    = FALSE;
    em->ExecArgs.JSON.chrono = FALSE;
    em->ExecArgs.JSON.op     = FALSE;
    em->ExecArgs.JSON.dump   = FALSE;
    em->ExecArgs.JSON.io     = FALSE;
    em->ExecArgs.JSON.concat = FALSE;

    _is_valid_file(em);

    for (s32 i = 3; i < argc; i++)
    {
        if (strlen(argv[i]) == 2)
        {
            if (argv[i][0] == '-' && argv[i][1] == 'd')
                em->ExecArgs.descriptive_mode = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 'q')
                em->ExecArgs.quiet_mode = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 't')
                em->ExecArgs.chrono_mode = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 'j')
            {
                em->ExecArgs.JSON.is_activated = TRUE;

                u32 i_clone = i;
                for (u16 j = i_clone+1; j < argc; j++)
                {
                    if (strcmp(argv[j], "cpu") == 0)
                        em->ExecArgs.JSON.cpu = TRUE;
                    else if (strcmp(argv[j], "ram") == 0)
                        em->ExecArgs.JSON.ram = TRUE;
                    else if (strcmp(argv[j], "chrono") == 0)
                        em->ExecArgs.JSON.chrono = TRUE;
                    else if (strcmp(argv[j], "op") == 0)
                        em->ExecArgs.JSON.op = TRUE;
                    else if (strcmp(argv[j], "dump") == 0)
                        em->ExecArgs.JSON.dump = TRUE;
                    else if (strcmp(argv[j], "io") == 0)
                        em->ExecArgs.JSON.io = TRUE;
                    else if (strcmp(argv[j], "concat") == 0)
                        em->ExecArgs.JSON.concat = TRUE;
                    else if (argv[j][0] == '-')
                        break;
                    else
                        EMULATOR_ERROR("Invalid JSON formatter '%s' at position %d.", argv[j], j);

                    i++;
                }
            }
            else EMULATOR_ERROR("Invalid param '%s' at position %d.", argv[i], i);
        }
        else EMULATOR_ERROR("Invalid param '%s' at position %d.", argv[i], i);
    }

    if (em->EmuType == EMULATE_SBS && em->ExecArgs.quiet_mode)
        EMULATOR_ERROR("Cannot use quiet option (-q) in step-by-step mode.")

    if (em->EmuType == EMULATE_SBS && em->ExecArgs.chrono_mode)
        EMULATOR_ERROR("Cannot use timer option (-t) in step-by-step mode.")

    if (em->EmuType == EMULATE_SBS && em->ExecArgs.JSON.chrono)
        EMULATOR_ERROR("Cannot use JSON timer encoding (-j chrono) in step-by-step mode.")

    if (em->EmuType == EMULATE_STD && em->ExecArgs.descriptive_mode)
        EMULATOR_ERROR("Cannot use descriptive option (-d) in normal mode.")

    if (em->ExecArgs.descriptive_mode && em->ExecArgs.quiet_mode)
        EMULATOR_ERROR("Cannot combine '-d' and '-q' options.")

    if (em->ExecArgs.chrono_mode && em->ExecArgs.JSON.is_activated)
        EMULATOR_ERROR("Cannot combine '-t' and JSON encoder '-j' options.")

    if (em->ExecArgs.JSON.dump && em->ExecArgs.JSON.concat)
        EMULATOR_ERROR("Cannot combine JSON encoding option 'dump' and 'concat'.")

    if (em->ExecArgs.JSON.is_activated)
    {
        u8 c_c = 0;
        if (em->ExecArgs.JSON.cpu)    c_c++;
        if (em->ExecArgs.JSON.ram)    c_c++;
        if (em->ExecArgs.JSON.op)     c_c++;
        if (em->ExecArgs.JSON.chrono) c_c++;
        if (em->ExecArgs.JSON.dump)   c_c++;
        if (em->ExecArgs.JSON.io)     c_c++;

        if (em->ExecArgs.JSON.concat && c_c < 2)
            EMULATOR_ERROR("To use 'concat' JSON util, must pass at least two formatter params.")

        if (em->ExecArgs.JSON.is_activated && c_c == 0)
            EMULATOR_ERROR("Cannot use JSON encoding option (-j) alone.")
    }
}


void __init(struct EmulationMachine *this)
{
    this->Machine.cpu = init_cpu(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        if (this->ExecArgs.JSON.is_activated)
            emit_dump(this);

        exit(EXIT_FAILURE);
    }

    init_opcodes(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        if (this->ExecArgs.JSON.is_activated)
            emit_dump(this);

        exit(EXIT_FAILURE);
    }

    this->Machine.ram = init_ram(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        if (this->ExecArgs.JSON.is_activated)
            emit_dump(this);

        exit(EXIT_FAILURE);
    }
}


void __turnoff()
{
    destroy_cpu();
    destroy_ram();
    destroy_codes();
}


struct EmulationMachine obtain_emulation_machine(int argc, char **argv)
{
    struct EmulationMachine em;

    em.Machine.State = BEGIN_STATE;

    em.Machine.RuntimeData.operation_code = 0;
    em.Machine.RuntimeData.mnemonic       = NULL;

    em.Machine.RuntimeData.org_pointer = ORG_DEFAULT;
    em.Machine.RuntimeData.simhalt     = 0;
    em.Machine.RuntimeData.last_loaded_byte_index = 0;
    em.Machine.RuntimeData.sbs_printer_enabler    = FALSE;

    em.Machine.RuntimeData.RAM_SIZE = 0x00FFFFFF;
    em.Machine.RuntimeData.STACK_BOTTOM_INDEX = 0x01000000;
    em.Machine.RuntimeData.JSR_CALL_COUNTER   = 0;

    em.Machine.Chrono.dt = 0;

    em.Machine.IO.buffer  = NULL;
    em.Machine.IO.Type    = IO_UNDEF;

    if (argv[1][1] == 'e')
        em.EmuType = EMULATE_STD;
    else
    {
        em.Machine.RuntimeData.sbs_printer_enabler = TRUE;
        em.EmuType = EMULATE_SBS;
    }

    parse_args(&em, argc, argv);

    em.Machine.init    = __init;
    em.Machine.turnoff = __turnoff;

    return em;
}


/* EMULATOR */
int emulate(int argc, char** argv)
{
    struct EmulationMachine em = obtain_emulation_machine(argc, argv);
    em.Machine.init(&em);

    preset_hander(&em);

    load_bytecode(&em);

    em.Machine.State = EXECUTION_STATE;

    emit_dump(&em);

    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_begin);
    while(em.Machine.cpu->pc < em.Machine.RuntimeData.simhalt)
    {
        if (em.Machine.cpu->exec(&em) == RETURN_ERR)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

            em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                                   (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

            switch (em.Machine.State) {
                case PANIC_STATE:
                {
                    PANIC(em.Machine.Exception.panic_cause)
                    break;
                }
                case TRAP_STATE:
                {
                    TRAPEXC(em.Machine.Exception.trap_cause)
                    break;
                }
                default:
                    break;
            }

            em.Machine.turnoff();

            return (EXIT_FAILURE);
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

    em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                           (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

    em.Machine.State = FINAL_STATE;

    emit_dump(&em);

    em.Machine.turnoff();

    return (EXIT_SUCCESS);
}



