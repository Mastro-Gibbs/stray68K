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
        "**Emulator options list**\n"
        " [-q] -STEP-BY-STEP mode.\n"
        "\n"
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
        " [concat]   -Perform JSON concat, must pass at least two listed above commands.\n"
        "\n"
        "**STEP-BY-STEP MODE's options asked from stdin**\n"
        " [s] -Asks for top address and print current stack.\n"
        " [r] -Asks for ram offsets and print selected ram chunck.\n"
        " [n] -Execute next istruction.\n"
        " [t] -Terminate the program. The execution proceeds to the end.\n"
        "\n\n"
        "**Assembler** an assembler for the Motorola 68000. (thanks to Clownacy)\n"
        "\n"
        "**Options**\n"
        " -o [path] -Output file, Optional.\n"
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
