#include "ARCH.h"

#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <stdlib.h>

#include "cpu.h"
#include "ram.h"

#define RAM_SIZE 0x00FFFFFF

#define SEPARATOR      '\n'
#define SIMHALT_SYMBOL '!'
#define ORG_SYMBOL     'o'
#define ORG_DEFAULT     0x00000000

#define EMULATE_STD 0
#define EMULATE_SBS 1

#define BEGIN_STATE 0
#define EXEC_STATE  1
#define FINAL_STATE 2

#define TRUE        1
#define FALSE       0

struct EmulationState
{
    generic_u8_t state; //initial, execution, final
    generic_u8_t type;

    struct
    {
        bit  descr;
        bit  quiet;
        char *path;
    } ExecArgs;

    bit sbs_print;
};



typedef struct __ARCH__68000__
{
    m68k_cpu *cpu;
    m68k_ram *ram;

    void  (*load)    (struct EmulationState *state);
    bit   (*is_halt) ();
    void  (*turnoff) ();
} arch_t;




void  __load_bytecode__(struct EmulationState *state);
bit   __is_halt__();
void  __turn_off__();


generic_u32_t loader_data_size = 0;
regex_t       hex_rx;
const char    *hex_regex = "[0-9a-fA-F!]+";


arch_t        ARCH;
generic_u32_t simhalt = 0;
generic_u32_t orgptr  = 0;
generic_u32_t last_written_byte = 0;


static struct termios oldt, newt;


void _begin()
{
    ARCH.cpu = init_cpu();
    ARCH.ram = init_ram(RAM_SIZE);

    ARCH.load    = __load_bytecode__;
    ARCH.is_halt = __is_halt__;
    ARCH.turnoff = __turn_off__;
}

void __turn_off__()
{
    destroy_cpu();
    destroy_ram();
}


/* ORG */
void _set_ORG(generic_u32_t org) { orgptr = org; set_pc(orgptr); }


/* SIMHALT */
void _set_simhalt(generic_u32_t addr) { if (simhalt == 0) simhalt = addr; }

bit __is_halt__() { return (get_pc() != simhalt || get_pc() < simhalt) ? 0 : 1; }



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
            ARCH_ERROR("File extension not valid, be sure to pass '.B68' format.")
        }
    }

    fp = fopen(filename, "r");

    if (fp == NULL)
        ARCH_ERROR("File not found, be sure to pass correct path.")

    read = getline(&line, &len, fp);
    if (read == -1)
        ARCH_ERROR("Empty file!")

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
            ARCH_ERROR("Error incomes while loading an invalid bytecode, line: 1. (Invalid ORG)")

        strncpy(org, line+1, 8);
        value = (generic_u32_t) strtol(org, &end, 16);
    }

    fclose(fp);

    return value;
}

generic_u8_t* _read_bytecode(char *filename, generic_u32_t *org)
{
    generic_u8_t *bytecode = NULL;

    FILE  *fp;
    fp = fopen(filename, "r");

    if (regcomp(&hex_rx, hex_regex, REG_EXTENDED) == 1)
        ARCH_ERROR("Could not compile regex %s", hex_regex)

    int  reti;
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        reti = regexec(&hex_rx, &ch, 0, NULL, 0);
        if (!reti)
        {
            loader_data_size++;
        }
    }

    loader_data_size = ((loader_data_size - ((*org) ? 9 : 0)) / 2) + 1;

    fclose(fp);

    bytecode = calloc(loader_data_size, sizeof (* bytecode));

    fp = fopen(filename, "r");

    char symbol[3];
    symbol[2] = '\0';

    generic_u32_t pos = 0,
                  validator = ((*org) ? 10 : 0);

    fseek(fp, validator, SEEK_SET);

    generic_u32_t meta_pc = *org;

    while((ch = fgetc(fp)) != EOF)
    {
        if (ch == SIMHALT_SYMBOL)
        {
            _set_simhalt(meta_pc);
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

void __load_bytecode__(struct EmulationState *state)
{
    char *filename = state->ExecArgs.path;

    generic_u32_t org = _extract_ORG(filename);
    _set_ORG(org);

    generic_u8_t *bytecode = _read_bytecode(filename, &org);

    if (bytecode)
    {
        generic_u32_t span = 0;
        for (generic_u32_t iter = 0; iter < loader_data_size; iter++)
        {
            generic_u8_t c = bytecode[iter];

            write_byte(get_pc() + span, c);
            span += BYTE_SPAN;
        }

        last_written_byte = get_pc() + span;

        free(bytecode);
        regfree(&hex_rx);

        _set_simhalt((generic_u32_t)(get_pc() + span));
    }
    else ARCH_ERROR("Error incomes while loading an invalid bytecode")
}



/* EMULATOR UTILS*/
void parse_args(struct EmulationState *state, int argc, char **argv)
{
    if (argc < 3)
    {
        fputs(
        "stray68K: emulator for Motorola 68000.\n"
        "\n"
        "Options:\n"
        " -a [opts|args]  -Invoke assembler. See below.\n"
        " -e [path]  [-q] -Input executable file. To generate it use assembler options. [-q] mean qiuet opt.\n"
        " -s [path]  [-d] -Like option '-e' but run executable file step by step (debug mode). [-d] mean descriptive opt.\n"
        "\n"
        "step-by-step mode options asked from stdin:\n"
        "   's' -Asks for offsets and print current stack.\n"
        "   'n' -Execute next istruction.\n"
        "   's' -Skip current step.\n"
        "   't' -Full skip steps. The execution proceeds to the end.\n"
        "\n\n",
        stdout);

        ARCH_ERROR("Too few params")
    }

    _is_valid_file(argv[2]);

    state->ExecArgs.path  = argv[2];
    state->ExecArgs.descr = FALSE;
    state->ExecArgs.quiet = FALSE;

    for (generic_32_t i = 3; i < argc; i++)
    {
        if (strlen(argv[i]) >= 2)
        {
            if (argv[i][0] == '-' && argv[i][1] == 'd')
                state->ExecArgs.descr = TRUE;

            else if (argv[i][0] == '-' && argv[i][1] == 'q')
                state->ExecArgs.quiet = TRUE;

            else ARCH_ERROR("Invalid param '%s' at position %d.", argv[i], i);
        }
    }

    if (state->type == EMULATE_SBS && state->ExecArgs.quiet)
        ARCH_ERROR("Cannot use quiet option (-q) in step-by-step mode.")

    if (state->type == EMULATE_STD && state->ExecArgs.descr)
        ARCH_ERROR("Cannot use descriptive option (-d) in normal mode.")

    if (state->ExecArgs.descr && state->ExecArgs.quiet)
        ARCH_ERROR("Cannot combine '-d' and '-q' options.")
}

struct EmulationState obtain_emulation_state(int argc, char **argv)
{
    struct EmulationState state;

    state.state = BEGIN_STATE;
    state.sbs_print = FALSE;

    if (argv[1][1] == 'e')
        state.type = EMULATE_STD;
    else
    {
        state.sbs_print = TRUE;
        state.type = EMULATE_SBS;
    }

    parse_args(&state, argc, argv);

    return state;
}

void printf_sstatus(struct EmulationState *state)
{
    if (!state->ExecArgs.quiet)
    {
        if (state->type == EMULATE_SBS && state->sbs_print) system("clear");

        generic_u32_t _start = orgptr;
        generic_u32_t _end   = (last_written_byte | 0x0000000F) + 0x11;
        generic_u32_t _ptr   = get_pc();
        char *pcptr_color    = "";
        char *halt_color     = "\033[37m";

        if (state->state == BEGIN_STATE)
        {
            printf("\033[01m\033[37mInitial State:\033[0m");
            pcptr_color = "\033[92m";
        }
        else if (state->state == EXEC_STATE)
        {
            printf("\033[01m\033[37mExecution State:\033[0m");
            _start = (_ptr & 0xFFFFFFF0) - 0x20;
            _end   = (_ptr | 0x0000000F) + 0x31;
            pcptr_color    = "\033[93m";

        }
        else if (state->state == FINAL_STATE)
        {
            printf("\033[01m\033[37mFinal State:\033[0m");
            pcptr_color    = "\033[91m";
            halt_color     = "\033[91m";
        }

        ARCH.cpu->show();
        printf("\n");

        ARCH.ram->show(_start, _end, _ptr, pcptr_color);
        printf("\n");

        printf("\033[01m\033[37mHalt\033[0m:     %s0x%X\033[0m\n", halt_color, simhalt);

        fflush(stdout);
    }
}

void _wait(struct EmulationState *state)
{
    if (state->sbs_print)
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
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            opt = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

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
                        ARCH.ram->stack(_top, _bottom);
                    }

                    break;
                }

                case 'n': //goto next istr, print cpu & ram
                {
                    printf_sstatus(state);

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

                    state->sbs_print      = FALSE;
                    state->ExecArgs.descr = FALSE;
                    break;
                }

                default: //catch \n and do nothing here
                { break; }
            }
        }
    }
}



/* EMULATOR */
int emulate_std(struct EmulationState *state)
{
    _begin();

    ARCH.load(state);

    printf_sstatus(state);

    state->state = EXEC_STATE;
    while(!ARCH.is_halt())
    {
        ARCH.cpu->exec(state->ExecArgs.descr);
    }
    state->state = FINAL_STATE;

    printf_sstatus(state);

    ARCH.turnoff();

    return (EXIT_SUCCESS);
}

int emulate_sbs(struct EmulationState *state) // aka step-by-step
{
    _begin();
    ARCH.load(state);

    printf_sstatus(state);
    state->state = EXEC_STATE;

    while(!ARCH.is_halt())
    {
        _wait(state);

        ARCH.cpu->exec(state->ExecArgs.descr);
    }

    state->state = FINAL_STATE;
    _wait(state);
    printf_sstatus(state);

    ARCH.turnoff();

    return (EXIT_SUCCESS);
}


int emulate(int argc, char** argv)
{
    struct EmulationState state = obtain_emulation_state(argc, argv);

    if (state.type == EMULATE_STD)
        return emulate_std(&state);
    else
        return emulate_sbs(&state);
}



