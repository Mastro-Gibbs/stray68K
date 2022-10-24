#include "emulator.h"

#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <stdlib.h>
#include <time.h>

#include "cpu.h"
#include "ram.h"

#define RAM_SIZE 0x00FFFFFF

#define SEPARATOR      '\n'
#define SIMHALT_SYMBOL '!'
#define ORG_SYMBOL     'o'
#define ORG_DEFAULT     0x00000000

#define TRUE        1
#define FALSE       0

struct EmulationMachine
{
    enum
    {
        EMULATE_STD = 0,
        EMULATE_SBS = 1
    } EmuType;

    enum
    {
        BEGIN_STATE     = 0,
        EXECUTION_STATE = 1,
        FINAL_STATE     = 2
    } State;

    struct
    {
        bit  descr;
        bit  quiet;
        bit  timer;
        char *path;
    } ExecArgs;

    struct
    {
        generic_u32_t size;
        regex_t       hex_rx;
        const char    *hex_regex;
    } Loader;

    struct
    {
        m68k_cpu *cpu;
        m68k_ram *ram;

        bit           sbs_print;
        generic_u32_t simhalt;
        generic_u32_t orgptr;
        generic_u32_t lwb;

        struct
        {
            struct termios oldt;
            struct termios newt;
        } Waiting;

        struct
        {
            struct timespec t_begin;
            struct timespec t_end;
            generic_u64_t   delta_t;
        } Timer;

    } Machine;

};



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

generic_u32_t _extract_ORG(char *filename)
{
    FILE   *fp;
    char   *line = NULL;
    char   *end  = NULL;
    size_t  len   = 0, read = 0;

    generic_u32_t value = ORG_DEFAULT;

    char org[9];

    fp = fopen(filename, "r");

    read = getline(&line, &len, fp);

    if (line[0] == ORG_SYMBOL)
    {
        if (read != 10)
            EMULATOR_ERROR("Error incomes while loading an invalid bytecode, line: 1. (Invalid ORG)")

        strncpy(org, line+1, 8);
        value = (generic_u32_t) strtol(org, &end, 16);
    }

    fclose(fp);

    return value;
}

generic_u8_t* _read_bytecode(struct EmulationMachine *es, char *filename)
{
    generic_u8_t *bytecode = NULL;

    FILE  *fp;
    fp = fopen(filename, "r");

    if (regcomp(&es->Loader.hex_rx, es->Loader.hex_regex, REG_EXTENDED) == 1)
        EMULATOR_ERROR("Could not compile regex %s", es->Loader.hex_regex)

    int  reti;
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        reti = regexec(&es->Loader.hex_rx, &ch, 0, NULL, 0);
        if (!reti)
        {
            es->Loader.size++;
        }
    }

    es->Loader.size = ((es->Loader.size - ((es->Machine.orgptr) ? 9 : 0)) / 2) + 1;

    fclose(fp);

    bytecode = calloc(es->Loader.size, sizeof (* bytecode));

    fp = fopen(filename, "r");

    char symbol[3];
    symbol[2] = '\0';

    generic_u32_t pos = 0,
                  validator = ((es->Machine.orgptr) ? 10 : 0);

    fseek(fp, validator, SEEK_SET);

    generic_u32_t meta_pc = es->Machine.orgptr;

    while((ch = fgetc(fp)) != EOF)
    {
        if (ch == SIMHALT_SYMBOL)
        {
            if (es->Machine.simhalt == 0) es->Machine.simhalt = meta_pc;
        }
        else if (ch != SEPARATOR)
        {
            symbol[0] = ch;
            symbol[1] = fgetc(fp);

            char *end = NULL;

            generic_u8_t val = strtol(symbol, &end, 16);

            bytecode[pos++] = (generic_u8_t) val;

            meta_pc += BYTE_SPAN;
        }
    }
    fclose(fp);

    return bytecode;
}

void __load_bytecode__(struct EmulationMachine *es)
{
    char *filename = es->ExecArgs.path;

    es->Machine.orgptr = _extract_ORG(filename);
    set_pc(es->Machine.orgptr);

    generic_u8_t *bytecode = _read_bytecode(es, filename);

    if (bytecode)
    {
        generic_u32_t span = 0;
        for (generic_u32_t iter = 0; iter < es->Loader.size; iter++)
        {
            generic_u8_t c = bytecode[iter];

            write_byte(get_pc() + span, c);
            span += BYTE_SPAN;
        }

        es->Machine.lwb = get_pc() + span;

        free(bytecode);
        regfree(&es->Loader.hex_rx);

        if (es->Machine.simhalt == 0) es->Machine.simhalt = es->Machine.lwb;

    }
    else EMULATOR_ERROR("Error incomes while loading an invalid bytecode")
}



/* EMULATOR UTILS*/
void parse_args(struct EmulationMachine *es, int argc, char **argv)
{
    if (argc < 3)
    {
        fputs(
        "stray68K: emulator for Motorola 68000.\n"
        "\n"
        "Options:\n"
        " -a [opts|args]     -Invoke assembler. See below.\n"
        " -e [path]  [-q|-t] -Input executable file. To generate it use assembler options. [-q] mean qiuet opt.\n"
        " -s [path]  [-d]    -Like option '-e' but run executable file step by step (debug mode). [-d] mean descriptive opt.\n"
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

    es->ExecArgs.path  = argv[2];
    es->ExecArgs.descr = FALSE;
    es->ExecArgs.quiet = FALSE;
    es->ExecArgs.timer = FALSE;

    for (generic_32_t i = 3; i < argc; i++)
    {
        if (strlen(argv[i]) >= 2)
        {
            if (argv[i][0] == '-' && argv[i][1] == 'd')
                es->ExecArgs.descr = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 'q')
                es->ExecArgs.quiet = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 't')
                es->ExecArgs.timer = TRUE;

            else EMULATOR_ERROR("Invalid param '%s' at position %d.", argv[i], i);
        }
    }

    if (es->EmuType == EMULATE_SBS && es->ExecArgs.quiet)
        EMULATOR_ERROR("Cannot use quiet option (-q) in step-by-step mode.")

    if (es->EmuType == EMULATE_SBS && es->ExecArgs.timer)
        EMULATOR_ERROR("Cannot use timer option (-t) in step-by-step mode.")

    if (es->EmuType == EMULATE_STD && es->ExecArgs.descr)
        EMULATOR_ERROR("Cannot use descriptive option (-d) in normal mode.")

    if (es->ExecArgs.descr && es->ExecArgs.quiet)
        EMULATOR_ERROR("Cannot combine '-d' and '-q' options.")
}

struct EmulationMachine obtain_emulation_state(int argc, char **argv)
{
    struct EmulationMachine es;

    es.Machine.orgptr  = ORG_DEFAULT;
    es.Machine.simhalt = 0;
    es.Machine.lwb     = 0;

    es.Loader.size = 0;
    es.Loader.hex_regex = "[0-9a-fA-F!]+";

    es.State = BEGIN_STATE;
    es.Machine.sbs_print = FALSE;

    es.Machine.Timer.delta_t = 0;

    if (argv[1][1] == 'e')
        es.EmuType = EMULATE_STD;
    else
    {
        es.Machine.sbs_print = TRUE;
        es.EmuType = EMULATE_SBS;
    }

    parse_args(&es, argc, argv);

    return es;
}

void printf_sstatus(struct EmulationMachine *es)
{
    if (!es->ExecArgs.quiet)
    {
        if (es->EmuType == EMULATE_SBS && es->Machine.sbs_print) system("clear");

        generic_u32_t _start = es->Machine.orgptr;
        generic_u32_t _end   = (es->Machine.lwb | 0x0000000F) + 0x11;
        generic_u32_t _ptr   = get_pc();
        char *pcptr_color    = "";
        char *halt_color     = "\033[37m";

        if (es->State == BEGIN_STATE)
        {
            printf("\033[01m\033[37mInitial State:\033[0m");
            pcptr_color = "\033[92m";
        }
        else if (es->State == EXECUTION_STATE)
        {
            printf("\033[01m\033[37mExecution State:\033[0m");
            _start = (_ptr & 0xFFFFFFF0) - 0x20;
            _end   = (_ptr | 0x0000000F) + 0x31;
            pcptr_color    = "\033[93m";

        }
        else if (es->State == FINAL_STATE)
        {
            printf("\033[01m\033[37mFinal State:\033[0m");
            pcptr_color    = "\033[91m";
            halt_color     = "\033[91m";
        }

        es->Machine.cpu->show();
        printf("\n");

        es->Machine.ram->show(_start, _end, _ptr, pcptr_color);
        printf("\n");

        printf("\033[01m\033[37mHalt\033[0m:     %s0x%X\033[0m\n", halt_color, es->Machine.simhalt);

        fflush(stdout);
    }

    if (es->State == FINAL_STATE && es->Machine.Timer.delta_t)
    {
        printf("\033[01m\033[37mTimer\033[0m: %.3fms -> %.3fs\n",
               (generic_f64_t) es->Machine.Timer.delta_t / (generic_f64_t) 1000,
               (generic_f64_t) es->Machine.Timer.delta_t / (generic_f64_t) 1000000);
    }
}

void _wait(struct EmulationMachine *es)
{
    if (es->Machine.sbs_print)
    {
        fputs(
            "\n---------------- Execution Options ----------------\n"
            "[\033[01m\033[37ms\033[0m] \033[01m\033[37mstack\033[0m | "
            "[\033[01m\033[37mn\033[0m] \033[01m\033[37mnext\033[0m | "
            "[\033[01m\033[37mk\033[0m] \033[01m\033[37mskip\033[0m | "
            "[\033[01m\033[37mt\033[0m] \033[01m\033[37mfull skip\033[0m\n",
        stdout);

        fflush(stdout);
        fflush(stdin);

        char opt;
        bit loop = TRUE;

        while (loop)
        {
            tcgetattr(STDIN_FILENO, &es->Machine.Waiting.oldt);
            es->Machine.Waiting.newt = es->Machine.Waiting.oldt;
            es->Machine.Waiting.newt.c_lflag &= ~(ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &es->Machine.Waiting.newt);

            opt = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &es->Machine.Waiting.oldt);

            switch (opt) {
                case 's': //stack;
                {
                    generic_u32_t _top = 0, _bottom = 0x00FFFFFF;

                    SBS_DEBUGGER("Insert stack top address: ");
                    scanf("%X", &_top);
                    SBS_DEBUGGER("Insert stack bottom address: ");
                    scanf("%X", &_bottom);

                    if (_bottom > RAM_SIZE || (((_bottom & 0x0000000F) + 1) % 4) != 0)
                    {
                        SBS_DEBUGGER("Invalid bottom index");
                    }
                    else
                    {
                        es->Machine.ram->stack(_top, _bottom);
                    }

                    break;
                }

                case 'n': //goto next istr, print cpu & ram
                {
                    printf_sstatus(es);

                    loop = FALSE;
                    break;
                }

                case 'k': //skip
                {
                    system("clear");
                    SBS_DEBUGGER("Skip selected, the execution proceeds.\n");

                    loop = FALSE;
                    break;
                }

                case 't': //terminate
                {
                    system("clear");
                    SBS_DEBUGGER("Full skip selected, the execution proceeds to the end.\n");

                    loop = FALSE;

                    es->Machine.sbs_print = FALSE;
                    es->ExecArgs.descr = FALSE;
                    break;
                }

                default: //catch \n and do nothing here
                { break; }
            }
        }
    }
}



/* EMULATOR */
int emulate(int argc, char** argv)
{
    struct EmulationMachine es = obtain_emulation_state(argc, argv);

    es.Machine.cpu = init_cpu();
    es.Machine.ram = init_ram(RAM_SIZE);

    __load_bytecode__(&es);

    printf_sstatus(&es);

    es.State = EXECUTION_STATE;

    clock_gettime(CLOCK_MONOTONIC_RAW, &es.Machine.Timer.t_begin);
    while((get_pc() != es.Machine.simhalt || get_pc() < es.Machine.simhalt))
    {
        _wait(&es);

        es.Machine.cpu->exec(es.ExecArgs.descr);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &es.Machine.Timer.t_end);

    es.Machine.Timer.delta_t = (es.Machine.Timer.t_end.tv_sec - es.Machine.Timer.t_begin.tv_sec) * 1000000 +
                               (es.Machine.Timer.t_end.tv_nsec - es.Machine.Timer.t_begin.tv_nsec) / 1000;

    es.State = FINAL_STATE;

    _wait(&es);

    printf_sstatus(&es);

    destroy_cpu();
    destroy_ram();

    return (EXIT_SUCCESS);
}



