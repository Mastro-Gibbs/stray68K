#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "stray_m68k.h"

int usage(char *param)
{
    if (param)
        fprintf(stderr, "Unrecognised option %s.\n", param);

    fputs(
        "**stray68K** an emulator for Motorola 68000.\n"
        "\n"
        "**Modality**\n"
        " -Assembler:\n"
        "   <filepath> [options] -Invoke assembler. Be sure to pass a .X68 file.\n"
        " -Emulator:\n"
        "   <filepath> [options] -Be sure to pass a .68 file. To generate it use assembler options.\n"
        "\n"
        "**Emulator option**\n"
        " [-t] -Perform a chrono calculation and print it.\n"
        "       This option is prohibited in STEP-BY-STEP MODE.\n"
        "\n\n"
        "**Assembler** an assembler for the Motorola 68000. (thanks to Clownacy)\n"
        "\n"
        "**Options**\n"
        " -o [path] -Output file. Optional.\n"
        " -l [path] -Listing file. Optional.\n"
        " -s [path] -asm68k-style symbol file. Optional.\n"
        " -c        -Enable case-insensitive mode.\n"
        " -b        -Enable Bison's debug output.\n"
        " -d        -Allow EQU/SET to descope local labels.\n"
        , stdout);

    return (EXIT_FAILURE);
}


struct
{
    int (*handler)(int argc, char** argv);
} Runner;


int detect_format(const char* filepath)
{
    if (access(filepath, F_OK) != 0)
    {
        fputs("Be sure to pass an existing file.\n", stdout);
        return (EXIT_FAILURE);
    }

    const char* ldot = strrchr(filepath, '.');
    if (ldot != NULL)
    {
        size_t length = strlen("B68");
        if (strncmp(ldot + 1, "B68", length) == 0)
            Runner.handler = emulate;
        else
            Runner.handler = assemble;

        return (EXIT_SUCCESS);
    }
    else
    {
        fputs("Be sure to pass a '.X68' or '.B68' file.\n", stdout);
    }

    return (EXIT_FAILURE);
}

int parseargs(int argc, char **argv)
{
    int exit_code = EXIT_FAILURE;

    if (argc == 1) return usage(NULL);

    if (detect_format(argv[1]) == EXIT_SUCCESS)
        exit_code = Runner.handler(argc, argv);

    return (exit_code);
}



int main(int argc,  char** argv)
{
    return parseargs(argc, argv);
}

