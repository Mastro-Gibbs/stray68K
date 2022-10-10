#include <stdio.h>
#include "strayemu.h"
#include <string.h>


void usage()
{
    fputs(
        "stray68K: emulator for Motorola 68000.\n"
        "\n"
        "Options:\n"
        " -a [opts|args]   -Invoke assembler. See below.\n"
        " -e [path]        -Input executable file. To generate it use assembler options, must be .B68 file extesion.\n"
        " -s [path]        -Like option '-e' but run executable file step by step, must be .B68 file extesion.\n"
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
}


int main(int argc,  char** argv)
{
    int exit_code = EXIT_FAILURE;

    if (argc > 1)
    {
        if (strlen(argv[1]) == 2)
        {
            if (argv[1][0] == '-')
            {
                if (argv[1][1] == 'e')
                    exit_code = emulate(argc, argv);
                else if (argv[1][1] == 's')
                    exit_code = emulate_sbs(argc, argv);
                else if (argv[1][1] == 'a')
                    exit_code = assemble(argc, argv);
                else
                {
                    ARCH_ERROR("Unrecognised option %s", argv[1])
                    usage();
                }
            }
            else
                usage();
        }
        else
            usage();
    }
    else
        usage();

    return (exit_code);
}

