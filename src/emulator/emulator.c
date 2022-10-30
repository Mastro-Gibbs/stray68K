#include "emulator.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cpu.h"
#include "ram.h"
#include "JSON.h"

#define SEPARATOR      '\n'
#define SIMHALT_SYMBOL '!'
#define ORG_SYMBOL     'o'
#define ORG_DEFAULT     0x00000000


/* LOADER */
bit _is_valid_file(struct EmulationMachine *em)
{
    FILE    *fp;
    char    *line = NULL;
    size_t  len   = 0;
    ssize_t read;

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

    read = getline(&line, &len, fp);
    if (read == -1)
        EMULATOR_ERROR("Empty file!")

    fclose(fp);

    return 1;
}

u32 _extract_ORG(struct EmulationMachine *em)
{
    FILE   *fp;
    char   *line = NULL;
    char   *end  = NULL;
    size_t  len   = 0, read = 0;

    u32 value = ORG_DEFAULT;

    char org[9];

    fp = fopen(em->ExecArgs.executable_path, "r");

    read = getline(&line, &len, fp);

    if (line[0] == ORG_SYMBOL)
    {
        if (read != 10)
            EMULATOR_ERROR("Error incomes while loading an invalid bytecode, line: 1. (Invalid ORG)")

        strncpy(org, line+1, 8);
        value = (u32) strtol(org, &end, 16);
    }

    fclose(fp);

    return value;
}

void load_bytecode(struct EmulationMachine *em)
{
    u32        size = 0;
    regex_t    hex_rx;
    const char *hex_regex = "[0-9a-fA-F!]+";

    em->Machine.RuntimeData.org_pointer = _extract_ORG(em);
    em->Machine.cpu->pc = em->Machine.RuntimeData.org_pointer;

    u8 *bytecode = NULL;

    FILE  *fp;
    fp = fopen(em->ExecArgs.executable_path, "r");

    if (regcomp(&hex_rx, hex_regex, REG_EXTENDED) == 1)
        EMULATOR_ERROR("Could not compile regex %s", hex_regex)

    int  reti;
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        reti = regexec(&hex_rx, &ch, 0, NULL, 0);
        if (!reti)
        {
            size++;
        }
    }

    size = ((size - ((em->Machine.RuntimeData.org_pointer) ? 9 : 0)) / 2) + 1;

    fclose(fp);

    bytecode = calloc(size, sizeof (* bytecode));

    fp = fopen(em->ExecArgs.executable_path, "r");

    char symbol[3];
    symbol[2] = '\0';

    u32 pos = 0,
        validator = ((em->Machine.RuntimeData.org_pointer) ? 10 : 0);

    fseek(fp, validator, SEEK_SET);

    u32 meta_pc = em->Machine.RuntimeData.org_pointer;

    while((ch = fgetc(fp)) != EOF)
    {
        if (ch == SIMHALT_SYMBOL)
        {
            if (em->Machine.RuntimeData.simhalt == 0) em->Machine.RuntimeData.simhalt = meta_pc;
        }
        else if (ch != SEPARATOR)
        {
            symbol[0] = ch;
            symbol[1] = fgetc(fp);

            char *end = NULL;

            u8 val = strtol(symbol, &end, 16);

            bytecode[pos++] = (u8) val;

            meta_pc += BYTE_SPAN;
        }
    }
    fclose(fp);

    if (bytecode)
    {
        u32 span = 0;
        for (u32 iter = 0; iter < size; iter++)
        {
            u8 c = bytecode[iter];

            write_byte(em->Machine.cpu->pc + span, c);
            span += BYTE_SPAN;
        }

        em->Machine.RuntimeData.last_loaded_byte_index = em->Machine.cpu->pc + span;

        free(bytecode);
        regfree(&hex_rx);

        if (em->Machine.RuntimeData.simhalt == 0) em->Machine.RuntimeData.simhalt = em->Machine.RuntimeData.last_loaded_byte_index;

    }
    else EMULATOR_ERROR("Error incomes while loading an invalid bytecode")
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

    em.Machine.cpu = init_cpu(&em);

    if (em.Machine.State == PANIC_STATE)
    {
        PANIC(em.Machine.Exception.panic_cause);

        if (em.ExecArgs.JSON.is_activated)
            emit_dump(&em);

        exit(EXIT_FAILURE);
    }

    init_codes(&em);

    if (em.Machine.State == PANIC_STATE)
    {
        PANIC(em.Machine.Exception.panic_cause);

        if (em.ExecArgs.JSON.is_activated)
            emit_dump(&em);

        exit(EXIT_FAILURE);
    }

    em.Machine.ram = init_ram(&em);

    if (em.Machine.State == PANIC_STATE)
    {
        PANIC(em.Machine.Exception.panic_cause);

        if (em.ExecArgs.JSON.is_activated)
            emit_dump(&em);

        exit(EXIT_FAILURE);
    }

    return em;
}


/* EMULATOR */
int emulate(int argc, char** argv)
{
    struct EmulationMachine em = obtain_emulation_machine(argc, argv);

    preset_hander(&em);

    load_bytecode(&em);

    emit_sys_status(&em);

    em.Machine.State = EXECUTION_STATE;

    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_begin);
    while((em.Machine.cpu->pc != em.Machine.RuntimeData.simhalt || em.Machine.cpu->pc < em.Machine.RuntimeData.simhalt))
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

            emit_sys_status(&em);

            destroy_cpu();
            destroy_ram();

            return (EXIT_FAILURE);
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

    em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                           (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

    em.Machine.State = FINAL_STATE;

    machine_waiter(&em);

    emit_sys_status(&em);

    destroy_cpu();
    destroy_ram();

    return (EXIT_SUCCESS);
}



