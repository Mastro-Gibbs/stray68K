#include "ARCH.h"

#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define SEPARATOR      '\n'
#define SIMHALT_SYMBOL '!'
#define ORG_SYMBOL     'o'
#define ORG_DEFAULT     0x00000000


void  __load_bytecode__(char *filename);
bit   __is_halt__();
void  __turn_off__();


generic_u32_t loader_data_size = 0;
regex_t       hex_rx;
const char    *hex_regex = "[0-9a-fA-F!]+";


arch_t        ARCH;
generic_u32_t simhalt = 0;
generic_u32_t orgptr  = 0;


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

    fp = fopen(filename, "r");

    if (fp == NULL)
        ARCH_ERROR("File not found, be sure to pass correct path.")

    if ((read = getline(&line, &len, fp)) == -1)
        ARCH_ERROR("Empty file!")

    fclose(fp);

    return 1;
}

generic_u32_t _extract_ORG(char *filename)
{
    FILE   *fp;
    char   *line = NULL;
    char   *end  = NULL;
    size_t len   = 0;

    generic_u32_t value = ORG_DEFAULT;

    char org[9];

    fp = fopen(filename, "r");

    getline(&line, &len, fp);

    if (line[0] == ORG_SYMBOL)
    {
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

    while (validator--) fgetc(fp);

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

void __load_bytecode__(char *filename)
{
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

        free(bytecode);
        regfree(&hex_rx);

        _set_simhalt((generic_u32_t)(get_pc() + span));
    }
    else ARCH_ERROR("Error incomes while loading an invalid bytecode")
}



/* EMULATOR UTILS*/

struct ExecArgs
{
    bit  descr;
    bit  quiet;
    char *path;
};

struct ExecArgs parse_args(int argc, char **argv)
{
    if (argc < 3)
    {
        fputs(
        "stray68K: emulator for Motorola 68000.\n"
        "\n"
        "Options:\n"
        " -a [opts|args]   -Invoke assembler. See below.\n"
        " -e [path]        -Input executable file. To generate it use assembler options.\n"
        " -s [path]        -Like option '-e' but run executable file step by step.\n"
        " -[e|s] [path] -d -Like options '-e' and '-s' but prints opcode and mnemonic.\n"
        " -[e|s] [path] -q -Like options '-e' and '-s' but but avoid to print system status (quiet).\n"
        "\n"
        "Step by step mode options asked from stdin:\n"
        "   'c' -Print a snapshot of the cpu.\n"
        "   'm' -Print a snapshot of the ram, asks for start and end addresses to extract a ram slice.\n"
        "   'b' -Options c and m combined together.\n"
        "   'a' -Options b combined with auto ram slice printing.\n"
        "   's' -Skip current step.\n"
        "   't' -Full skip steps. The execution proceeds to the end.\n"
        "\n\n",
        stdout);

        ARCH_ERROR("Too few params")
    }

    _is_valid_file(argv[2]);

    struct ExecArgs ea;

    ea.path = argv[2];
    ea.descr = 0;
    ea.quiet = 0;

    for (generic_32_t i = 3; i < argc; i++)
    {
        if (strlen(argv[i]) >= 2)
        {
            if (argv[i][0] == '-' && argv[i][1] == 'd')
                ea.descr = 1;

            if (argv[i][0] == '-' && argv[i][1] == 'q')
                ea.quiet = 1;
        }
        else ARCH_ERROR("Invalid param");
    }

    if (ea.quiet && ea.descr)
        ARCH_ERROR("Cannot combine '-d' and '-q' options")

    return ea;
}

void _enable_single_char()
{
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void _disable_single_char()
{
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int _wait()
{
    char c;
    generic_u32_t mbegin, mend;

    fputs(
        "\n----------------------- Execution Options ------------------------\n"
        "[\033[01m\033[37mc\033[0m] \033[01m\033[37mcpu\033[0m | "
        "[\033[01m\033[37mm\033[0m] \033[01m\033[37mram\033[0m | "
        "[\033[01m\033[37mb\033[0m] \033[01m\033[37mboth\033[0m | "
        "[\033[01m\033[37ma\033[0m] \033[01m\033[37mauto\033[0m | "
        "[\033[01m\033[37ms\033[0m] \033[01m\033[37mskip\033[0m | "
        "[\033[01m\033[37mt\033[0m] \033[01m\033[37mfull skip\033[0m\n",
    stdout);

    fflush(stdout);
    fflush(stdin);

    _enable_single_char();
    c = getchar();
    _disable_single_char();

    if (c == 'c')
    {
        system("clear");
        ARCH.cpu->show();
        printf("\n");
    }
    else if (c == 'm')
    {
        printf("Enter start ram address: (hex) ");
        scanf("%X", &mbegin);
        printf("Enter final ram address: (hex) ");
        scanf("%X", &mend);
        system("clear");
        ARCH.ram->show(mbegin, (mend | 0x0000000F) + 0x11);
        printf("\n");
    }
    else if (c == 'b')
    {
        printf("Enter start ram address: (hex) ");
        scanf("%X", &mbegin);
        printf("Enter final ram address: (hex) ");
        scanf("%X", &mend);
        system("clear");
        ARCH.cpu->show();
        printf("\n");
        ARCH.ram->show(mbegin, (mend | 0x0000000F) + 0x1);
        printf("\n");
    }
    else if (c == 'a')
    {
        system("clear");
        ARCH.cpu->show();
        printf("\n");
        ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x21);
        printf("\n\n");
    }
    else if (c == 's')
    {
        system("clear");
        printf("Skip selected, the execution proceeds.\n");
    }
    else if (c == 't')
    {
        system("clear");
        printf("Full skip selected, the execution proceeds to the end.\n");
        return 0;
    }
    else
    {
        system("clear");
        printf("\nInvalid option or skip selected, the execution proceeds.\n");
    }

    return 1;
}

void printf_sstatus(char *state)
{
    system("clear");

    printf("\033[01m\033[37m%s", state);
    printf(":\033[0m\n\n");

    ARCH.cpu->show();
    printf("\n");
    ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x21);
    printf("\n");

    fflush(stdout);
}



/* EMULATOR */
int emulate(int argc,  char** argv)
{
    struct ExecArgs ea = parse_args(argc, argv);

    _begin();

    ARCH.load(ea.path);

    if (!ea.quiet)
        printf_sstatus("Initial system status");

    while(!ARCH.is_halt())
    {
        ARCH.cpu->exec(ea.descr);
    }

    if (!ea.quiet)
        printf_sstatus("Final system status");

    ARCH.turnoff();

    return (EXIT_SUCCESS);
}


int emulate_sbs(int argc, char **argv) // aka step-by-step
{
    bit print = 1;

    struct ExecArgs ea = parse_args(argc, argv);

    _begin();

    ARCH.load(ea.path);

    printf_sstatus("Initial system status");

    while(!ARCH.is_halt())
    {
        if (print) { print = _wait(); }

        ARCH.cpu->exec(ea.descr);
    }

    if (print) { _wait(); }

    printf_sstatus("Final system status");

    ARCH.turnoff();

    return (EXIT_SUCCESS);
}




