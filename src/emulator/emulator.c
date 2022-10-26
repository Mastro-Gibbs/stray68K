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
bit _is_valid_file(char *filename)
{
    FILE    *fp;
    char    *line = NULL;
    size_t  len   = 0;
    ssize_t read;

    const char* ldot = strrchr(filename, '.');
    if (ldot != NULL)
    {
        size_t length = strlen("B68");
        if (strncmp(ldot + 1, "B68", length) != 0)
        {
            EMULATOR_ERROR("File extension not valid, be sure to pass '.B68' format.")
        }
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
        EMULATOR_ERROR("File not found, be sure to pass correct path.")

    read = getline(&line, &len, fp);
    if (read == -1)
        EMULATOR_ERROR("Empty file!")

    fclose(fp);

    return 1;
}

u32 _extract_ORG(char *filename)
{
    FILE   *fp;
    char   *line = NULL;
    char   *end  = NULL;
    size_t  len   = 0, read = 0;

    u32 value = ORG_DEFAULT;

    char org[9];

    fp = fopen(filename, "r");

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

u8* _read_bytecode(struct EmulationMachine *em, char *filename)
{
    u8 *bytecode = NULL;

    FILE  *fp;
    fp = fopen(filename, "r");

    if (regcomp(&em->Loader.hex_rx, em->Loader.hex_regex, REG_EXTENDED) == 1)
        EMULATOR_ERROR("Could not compile regex %s", em->Loader.hex_regex)

    int  reti;
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        reti = regexec(&em->Loader.hex_rx, &ch, 0, NULL, 0);
        if (!reti)
        {
            em->Loader.size++;
        }
    }

    em->Loader.size = ((em->Loader.size - ((em->Machine.ExecData.orgptr) ? 9 : 0)) / 2) + 1;

    fclose(fp);

    bytecode = calloc(em->Loader.size, sizeof (* bytecode));

    fp = fopen(filename, "r");

    char symbol[3];
    symbol[2] = '\0';

    u32 pos = 0,
                  validator = ((em->Machine.ExecData.orgptr) ? 10 : 0);

    fseek(fp, validator, SEEK_SET);

    u32 meta_pc = em->Machine.ExecData.orgptr;

    while((ch = fgetc(fp)) != EOF)
    {
        if (ch == SIMHALT_SYMBOL)
        {
            if (em->Machine.ExecData.simhalt == 0) em->Machine.ExecData.simhalt = meta_pc;
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

    return bytecode;
}

void __load_bytecode__(struct EmulationMachine *em)
{
    char *filename = em->ExecArgs.path;

    em->Machine.ExecData.orgptr = _extract_ORG(filename);
    em->Machine.cpu->pc = em->Machine.ExecData.orgptr;

    u8 *bytecode = _read_bytecode(em, filename);

    if (bytecode)
    {
        u32 span = 0;
        for (u32 iter = 0; iter < em->Loader.size; iter++)
        {
            u8 c = bytecode[iter];

            write_byte(em->Machine.cpu->pc + span, c);
            span += BYTE_SPAN;
        }

        em->Machine.ExecData.lwb = em->Machine.cpu->pc + span;

        free(bytecode);
        regfree(&em->Loader.hex_rx);

        if (em->Machine.ExecData.simhalt == 0) em->Machine.ExecData.simhalt = em->Machine.ExecData.lwb;

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
            " You cannot use JSON encoding option (-j) alone.\n"
            " You cannot use JSON chrono encoding (-j chrono) in step-by-step mode.\n"
            "\n"
            "**JSON encoding commands**\n"
            " [cpu]      -Mean cpu encoding.\n"
            " [ram]      -Mean ram encoding.\n"
            " [chrono]   -Mean chrono encoding (ns).\n"
            " [code]     -Mean operation code encoding (base 10).\n"
            " [mnemonic] -Mean mnemonic operation encoding.\n"
            " [concat]   -Perform JSON concat, must pass at least two listed above commands.\n"
            "\n"
            "**STEP-BY-STEP MODE's options asked from stdin**\n"
            " [s] -Asks for offsets and print current stack.\n"
            " [n] -Execute next istruction.\n"
            " [k] -Skip current step.\n"
            " [t] -Full skip steps. The execution proceeds to the end.\n"
            "\n\n",
        stdout);

        EMULATOR_ERROR("Too few params")
    }

    _is_valid_file(argv[2]);

    em->ExecArgs.path   = argv[2];
    em->ExecArgs.descr  = FALSE;
    em->ExecArgs.quiet  = FALSE;
    em->ExecArgs.timer  = FALSE;

    em->ExecArgs.JSON.enable = FALSE;
    em->ExecArgs.JSON.cpu    = FALSE;
    em->ExecArgs.JSON.ram    = FALSE;
    em->ExecArgs.JSON.chrono  = FALSE;
    em->ExecArgs.JSON.mnem   = FALSE;
    em->ExecArgs.JSON.ocode  = FALSE;
    em->ExecArgs.JSON.concat = FALSE;

    for (s32 i = 3; i < argc; i++)
    {
        if (strlen(argv[i]) == 2)
        {
            if (argv[i][0] == '-' && argv[i][1] == 'd')
                em->ExecArgs.descr = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 'q')
                em->ExecArgs.quiet = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 't')
                em->ExecArgs.timer = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 'j')
            {
                em->ExecArgs.JSON.enable = TRUE;

                u32 i_clone = i;
                for (u16 j = i_clone+1; j < argc; j++)
                {
                    if (strcmp(argv[j], "cpu") == 0)
                        em->ExecArgs.JSON.cpu = TRUE;
                    else if (strcmp(argv[j], "ram") == 0)
                        em->ExecArgs.JSON.ram = TRUE;
                    else if (strcmp(argv[j], "chrono") == 0)
                        em->ExecArgs.JSON.chrono = TRUE;
                    else if (strcmp(argv[j], "mnemonic") == 0)
                        em->ExecArgs.JSON.mnem = TRUE;
                    else if (strcmp(argv[j], "code") == 0)
                        em->ExecArgs.JSON.ocode = TRUE;
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

    if (em->EmuType == EMULATE_SBS && em->ExecArgs.quiet)
        EMULATOR_ERROR("Cannot use quiet option (-q) in step-by-step mode.")

    if (em->EmuType == EMULATE_SBS && em->ExecArgs.timer)
        EMULATOR_ERROR("Cannot use timer option (-t) in step-by-step mode.")

    if (em->EmuType == EMULATE_SBS && em->ExecArgs.JSON.chrono)
        EMULATOR_ERROR("Cannot use JSON timer encoding (-j chrono) in step-by-step mode.")

    if (em->EmuType == EMULATE_STD && em->ExecArgs.descr)
        EMULATOR_ERROR("Cannot use descriptive option (-d) in normal mode.")

    if (em->ExecArgs.descr && em->ExecArgs.quiet)
        EMULATOR_ERROR("Cannot combine '-d' and '-q' options.")

    if (em->ExecArgs.timer && em->ExecArgs.JSON.enable)
        EMULATOR_ERROR("Cannot combine '-t' and JSON encoder '-j' options.")

    if (em->ExecArgs.JSON.enable)
    {
        u8 c_c = 0;
        if (em->ExecArgs.JSON.cpu)   c_c++;
        if (em->ExecArgs.JSON.ram)   c_c++;
        if (em->ExecArgs.JSON.ocode) c_c++;
        if (em->ExecArgs.JSON.chrono) c_c++;
        if (em->ExecArgs.JSON.mnem)  c_c++;

        if (em->ExecArgs.JSON.concat && c_c < 2)
            EMULATOR_ERROR("To use 'concat' JSON util, must pass at least two formatter params.")

        if (em->ExecArgs.JSON.enable && c_c == 0)
            EMULATOR_ERROR("Cannot use JSON encoding option (-j) alone.")
    }
}

struct EmulationMachine obtain_emulation_machine(int argc, char **argv)
{
    struct EmulationMachine em;

    em.Machine.ExecData.orgptr  = ORG_DEFAULT;
    em.Machine.ExecData.simhalt = 0;
    em.Machine.ExecData.lwb     = 0;

    em.Loader.size = 0;
    em.Loader.hex_regex = "[0-9a-fA-F!]+";

    em.State = BEGIN_STATE;
    em.Machine.ExecData.sbs_debugger = FALSE;

    em.Machine.Chrono.dt = 0;

    em.Machine.OpCode.code = 0;
    em.Machine.OpCode.mnemonic = NULL;

    if (argv[1][1] == 'e')
        em.EmuType = EMULATE_STD;
    else
    {
        em.Machine.ExecData.sbs_debugger = TRUE;
        em.EmuType = EMULATE_SBS;
    }

    parse_args(&em, argc, argv);

    em.Machine.cpu = init_cpu(&em);

    if (em.State == PANIC_STATE)
    { PANIC(em.Machine.Exception.panic_cause); exit(EXIT_FAILURE); }

    em.Machine.ram = init_ram(&em, RAM_SIZE);

    if (em.State == PANIC_STATE)
    { PANIC(em.Machine.Exception.panic_cause); exit(EXIT_FAILURE); }

    return em;
}


/* EMULATOR */
int emulate(int argc, char** argv)
{
    struct EmulationMachine em = obtain_emulation_machine(argc, argv);
    preset_handler(&em);

    __load_bytecode__(&em);

    printf_sstatus(&em);

    em.State = EXECUTION_STATE;

    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_begin);
    while((em.Machine.cpu->pc != em.Machine.ExecData.simhalt || em.Machine.cpu->pc < em.Machine.ExecData.simhalt))
    {
        if (!em.Machine.cpu->exec(&em))
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

            em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                                   (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

            switch (em.State) {
                case PANIC_STATE:
                    PANIC(em.Machine.Exception.panic_cause)
                    break;
                case TRAP_STATE:
                    TRAPEXC(em.Machine.Exception.trap_cause)
                    break;
                default:
                    break;
            }

            em.State = FINAL_STATE;

            printf_sstatus(&em);

            return (EXIT_FAILURE);
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

    em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                           (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

    em.State = FINAL_STATE;

    machine_waiter(&em);

    printf_sstatus(&em);

    destroy_cpu();
    destroy_ram();

    return (EXIT_SUCCESS);
}



