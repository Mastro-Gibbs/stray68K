#include <stdio.h>
#include <string.h>

#include "stray_m68k.h"

int usage(char *param)
{
    if (param)
        fprintf(stderr, "Unrecognised option %s.\n", param);

    fputs(
        "stray68K: emulator for Motorola 68000.\n"
        "\n"
        "Options:\n"
        " -a [opts|args]     -Invoke assembler. See below.\n"
        " -e [path]  [-q|-t] -Input executable file. To generate it use assembler options.\n"
        "                     [-q] mean quiet option.\n"
        "                     [-q] mean timer option.\n"
        "\n"
        " -s [path]  [-d]    -Like option '-e' but run executable file step by step (debug mode).\n"
        "                     [-d] mean descriptive opt.\n"
        "\n"
        "step-by-step mode options asked from stdin:\n"
        "   's' -Asks for offsets and print current stack.\n"
        "   'n' -Execute next istruction.\n"
        "   's' -Skip current step.\n"
        "   't' -Full skip steps. The execution proceeds to the end.\n"
        "\n\n"
        "Assembler: an assembler for the Motorola 68000. (thanks to Clownacy)\n"
        "\n"
        "Options:\n"
        " -i [path] -Input file, must be .X68 file extesion.\n"
        " -o [path] -Output file, must be .B68 file extesion.\n"
        " -l [path] -Listing file. Optional.\n"
        " -s [path] -asm68k-style symbol file. Optional.\n"
        " -c        -Enable case-insensitive mode.\n"
        " -b        -Enable Bison's debug output.\n"
        " -d        -Allow EQU/SET to descope local labels.\n"
        , stdout);

    return (EXIT_FAILURE);
}


int run(int argc, char **argv)
{
    int exit_code = EXIT_FAILURE;

    if (argc == 1) return usage(NULL);

    if (strlen(argv[1]) != 2) return usage(argv[1]);

    if (argv[1][0] != '-') return usage(argv[1]);

    if (argv[1][1] == 'e' || argv[1][1] == 's')
        exit_code = emulate(argc, argv);
    else if (argv[1][1] == 'a')
        exit_code = assemble(argc, argv);
    else return usage(argv[1]);

    return (exit_code);
}


int main(int argc,  char** argv)
{
    return run(argc, argv);
}

