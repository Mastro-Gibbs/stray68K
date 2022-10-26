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

    em->Loader.size = ((em->Loader.size - ((em->Machine.Data.orgptr) ? 9 : 0)) / 2) + 1;

    fclose(fp);

    bytecode = calloc(em->Loader.size, sizeof (* bytecode));

    fp = fopen(filename, "r");

    char symbol[3];
    symbol[2] = '\0';

    u32 pos = 0,
                  validator = ((em->Machine.Data.orgptr) ? 10 : 0);

    fseek(fp, validator, SEEK_SET);

    u32 meta_pc = em->Machine.Data.orgptr;

    while((ch = fgetc(fp)) != EOF)
    {
        if (ch == SIMHALT_SYMBOL)
        {
            if (em->Machine.Data.simhalt == 0) em->Machine.Data.simhalt = meta_pc;
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

    em->Machine.Data.orgptr = _extract_ORG(filename);
    em->Machine.cpu->pc = em->Machine.Data.orgptr;

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

        em->Machine.Data.lwb = em->Machine.cpu->pc + span;

        free(bytecode);
        regfree(&em->Loader.hex_rx);

        if (em->Machine.Data.simhalt == 0) em->Machine.Data.simhalt = em->Machine.Data.lwb;

    }
    else EMULATOR_ERROR("Error incomes while loading an invalid bytecode")
}



/* EMULATOR UTILS*/
void parse_args(struct EmulationMachine *em, int argc, char **argv)
{
    if (argc < 3)
    {
        fputs(
        "stray68K: emulator for Motorola 68000.\n"
        "\n"
        "Options:\n"
        " -a [opts|args]     -Invoke assembler. See below.\n"
        " -e [path]  [-q|-t] -Input executable file. To generate it use assembler options.\n"
        "                     [-q] mean quiet option.\n"
        "                     [-t] mean timer option.\n"
        "\n"
        " -s [path]  [-d]    -Like option '-e' but run executable file step by step (debug mode).\n"
        "                     [-d] mean descriptive opt.\n"
        "\n"
        "step-by-step mode options asked from stdin:\n"
        "   's' -Asks for offsets and print current stack.\n"
        "   'n' -Execute next istruction.\n"
        "   's' -Skip current step.\n"
        "   't' -Full skip steps. The execution proceeds to the end.\n"
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
    em->ExecArgs.JSON.timer  = FALSE;
    em->ExecArgs.JSON.menm   = FALSE;
    em->ExecArgs.JSON.ocode  = FALSE;

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
                if (i == (argc-1) || argv[i+1][0] == '-')
                    EMULATOR_ERROR("Must specify what to encode in JSON format (cpu, ram, time, mnemonic, code).");

                em->ExecArgs.JSON.enable = TRUE;

                u32 i_clone = i;
                for (u16 j = i_clone+1; j < argc; j++)
                {
                    if (strcmp(argv[j], "cpu") == 0)
                        em->ExecArgs.JSON.cpu = TRUE;
                    else if (strcmp(argv[j], "ram") == 0)
                        em->ExecArgs.JSON.ram = TRUE;
                    else if (strcmp(argv[j], "time") == 0)
                        em->ExecArgs.JSON.timer = TRUE;
                    else if (strcmp(argv[j], "mnemonic") == 0)
                        em->ExecArgs.JSON.menm = TRUE;
                    else if (strcmp(argv[j], "code") == 0)
                        em->ExecArgs.JSON.ocode = TRUE;
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

    if (em->EmuType == EMULATE_STD && em->ExecArgs.descr)
        EMULATOR_ERROR("Cannot use descriptive option (-d) in normal mode.")

    if (em->ExecArgs.descr && em->ExecArgs.quiet)
        EMULATOR_ERROR("Cannot combine '-d' and '-q' options.")

    if (em->ExecArgs.timer && em->ExecArgs.JSON.enable)
        EMULATOR_ERROR("Cannot combine '-t' and JSON encoder '-j' options.")
}

struct EmulationMachine obtain_emulation_machine(int argc, char **argv)
{
    struct EmulationMachine em;

    em.Machine.Data.orgptr  = ORG_DEFAULT;
    em.Machine.Data.simhalt = 0;
    em.Machine.Data.lwb     = 0;

    em.Loader.size = 0;
    em.Loader.hex_regex = "[0-9a-fA-F!]+";

    em.State = BEGIN_STATE;
    em.Machine.Data.sbs_debugger = FALSE;

    em.Machine.Timer.dt = 0;

    em.Machine.OpCode.code = 0;
    em.Machine.OpCode.mnemonic = NULL;

    if (argv[1][1] == 'e')
        em.EmuType = EMULATE_STD;
    else
    {
        em.Machine.Data.sbs_debugger = TRUE;
        em.EmuType = EMULATE_SBS;
    }

    parse_args(&em, argc, argv);

    return em;
}


/* EMULATOR */
int emulate(int argc, char** argv)
{
    struct EmulationMachine em = obtain_emulation_machine(argc, argv);

    em.Machine.cpu = init_cpu();
    em.Machine.ram = init_ram(RAM_SIZE);

    __load_bytecode__(&em);

    printf_sstatus(&em);

    em.State = EXECUTION_STATE;

    pre_set_runner(&em);

    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Timer.t_begin);
    while((em.Machine.cpu->pc != em.Machine.Data.simhalt || em.Machine.cpu->pc < em.Machine.Data.simhalt))
    {
        em.Machine.cpu->exec(&em);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Timer.t_end);

    em.Machine.Timer.dt = (em.Machine.Timer.t_end.tv_sec - em.Machine.Timer.t_begin.tv_sec) * 1000000 +
                               (em.Machine.Timer.t_end.tv_nsec - em.Machine.Timer.t_begin.tv_nsec) / 1000;

    em.State = FINAL_STATE;

    machine_waiter(&em);

    printf_sstatus(&em);

    destroy_cpu();
    destroy_ram();

    return (EXIT_SUCCESS);
}



