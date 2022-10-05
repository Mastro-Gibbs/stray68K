#include "ARCH.h"
#include <string.h>

void  __load_bytecode__(char *filename);
void  __set_simhalt__(generic_u32_t addr);
bit __is_halt__();
void  __turn_off__();


arch_t        ARCH;
generic_u32_t simhalt = 0;
generic_u32_t orgptr  = 0;



void begin()
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


void ORG(generic_u32_t org) { orgptr = org; set_pc(orgptr); }


/* LOADER */
bit is_valid_file(char *filename)
{
    FILE    *fp;
    char    *line = NULL;
    size_t  len   = 0;
    ssize_t read;

    fp = fopen(filename, "r");

    if (fp == NULL)
        { PANIC("[PANIC] File not found!\n"); }

    if ((read = getline(&line, &len, fp)) == -1)
        { PANIC("[PANIC] Empty file!\n"); }

    return 1;
}

generic_u32_t __extract_ORG__(char *filename)
{
    FILE    *fp;
    char    *line = NULL;
    size_t  len   = 0;

    char  org[9];
    char* end = NULL;
    long  value;

    fp = fopen(filename, "r");

    getline(&line, &len, fp);

    strncpy(org, line, 8);
    value = strtol(org, &end, 16);

    fclose(fp);

    return (generic_u32_t) value;
}

void  __load_bytecode__(char *filename)
{
    if (is_valid_file(filename))
    {
        generic_u32_t org = __extract_ORG__(filename);

        if (org != LOAD_ERROR)
        {
            ORG(org);

            generic_u32_t ram_ptr = load_executable(filename);

            __set_simhalt__(ram_ptr);
        }
        else { PANIC("[PANIC] Error incomes while loading an invalid bytecode\n"); }
    }
}



/* SIMHALT */
void __set_simhalt__(generic_u32_t addr) { simhalt = addr; write_long(addr, 0xFFFFFFFF); }

bit __is_halt__() { return (get_pc() != simhalt) ? 0 : 1; }




/* EMULATOR */
int emulate(int argc,  char** argv)
{
    bit describe_code = 0;

    if (argc < 3)
        return (EXIT_FAILURE);

    if (argc > 3 && strlen(argv[3]) == 2)
    {
        if (argv[3][0] == '-' && argv[3][1] == 'd')
            describe_code = 1;
        else
            fputs("Option not reconized.\n", stdout);
    }

    begin();

    ARCH.load(argv[2]);

    system("clear");
    printf("\033[01m\033[37mInitial system status:\033[0m\n\n");
    ARCH.cpu->show();
    printf("\n");
    ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x11);
    fflush(stdout);

    while(!ARCH.is_halt())
    {
        ARCH.cpu->exec(describe_code);
    }

    system("clear");
    printf("\033[01m\033[37mFinal system status:\033[0m\n\n");
    ARCH.cpu->show();
    printf("\n");
    ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x11);
    fflush(stdout);

    ARCH.turnoff();

    return (EXIT_SUCCESS);
}



int _wait_()
{
    char c;
    generic_u32_t mbegin, mend;

    fputs(
        "----------------------- Execution Options ------------------------\n"
        "[\033[01m\033[37mc\033[0m] \033[01m\033[37mcpu\033[0m | "
        "[\033[01m\033[37mm\033[0m] \033[01m\033[37mram\033[0m | "
        "[\033[01m\033[37mb\033[0m] \033[01m\033[37mboth\033[0m | "
        "[\033[01m\033[37ma\033[0m] \033[01m\033[37mauto\033[0m | "
        "[\033[01m\033[37ms\033[0m] \033[01m\033[37mskip\033[0m | "
        "[\033[01m\033[37mt\033[0m] \033[01m\033[37mfull skip\033[0m\n",
    stdout);

    fflush(stdout);
    fflush(stdin);

    scanf(" %c", &c);

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
        ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x11);
        printf("\n");
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


int emulate_sbs(int argc, char **argv) // aka step-by-step
{
    bit print = 1;
    bit describe_code = 0;

    if (argc < 3)
        return (EXIT_FAILURE);

    if (argc > 3 && strlen(argv[3]) == 2)
    {
        if (argv[3][0] == '-' && argv[3][1] == 'd')
            describe_code = 1;
        else
            fputs("Option not reconized.\n", stdout);
    }

    begin();

    ARCH.load(argv[2]);

    system("clear");
    printf("\033[01m\033[37mInitial system status:\033[0m\n\n");
    ARCH.cpu->show();
    printf("\n");
    ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x11);
    fflush(stdout);

    while(!ARCH.is_halt())
    {
        if (print) { print = _wait_(); }

        ARCH.cpu->exec(describe_code);
    }

    system("clear");
    printf("\033[01m\033[37mFinal system status:\033[0m\n\n");
    ARCH.cpu->show();
    printf("\n");
    ARCH.ram->show(orgptr, (simhalt | 0x0000000F) + 0x11);
    fflush(stdout);

    ARCH.turnoff();

    return (EXIT_SUCCESS);
}




