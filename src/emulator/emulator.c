#include "emulator.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cpu.h"
#include "ram.h"

#define SIMHALT_SYMBOL  0xAC
#define ORG_SYMBOL      'o'
#define ORG_DEFAULT     0x00000000

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

bit halt_compare(u8 *s1)
{
    u8 halt[8] = {0xAC, 0xAC, 0xFF, 0xFF, 0xFF, 0xFF, 0xAC, 0xAC};

    for (u16 i = 0; i < 8; i++)
        if (s1[i] != halt[i]) return FALSE;

    return TRUE;
}


/* LOADER */
bit _is_valid_file(struct EmulationMachine *em)
{
    FILE    *fp;

    const char* ldot = strrchr(em->ExecArgs.executable_path, '.');
    if (ldot != NULL)
    {
        size_t length = strlen("B68");
        if (strncmp(ldot + 1, "B68", length) != 0)
        {
            EMULATOR_ERROR("File extension not valid, be sure to pass '.B68' format.")
        }
    }

    fp = fopen(em->ExecArgs.executable_path, "r");

    if (fp == NULL)
        EMULATOR_ERROR("File not found, be sure to pass correct path.")

    fseek(fp, 0L, SEEK_END);
    if (ftell(fp) == 0L)
        EMULATOR_ERROR("Empty bin file.")

    fclose(fp);

    return 1;
}



FILE* open_file_and_extract_ORG(struct EmulationMachine *em)
{
    FILE *fp;

    s8  is_org = 0;
    u8  org[4];
    u32 value = ORG_DEFAULT;

    fp = fopen(em->ExecArgs.executable_path, "rb");

    if (fread(&is_org, 1, 1, fp) == 0)
        EMULATOR_ERROR("Error incomes while loading invalid binary");

    if (is_org == ORG_SYMBOL)
    {
        if (fread(org, ARRAY_SIZE(org), sizeof (*org), fp) == 0)
            EMULATOR_ERROR("Error incomes while loading binary");

        value = (org[0] << 24) | (org[1] << 16) | (org[2] << 8) | org[3];
    }
    else
        fseek(fp, 0, SEEK_SET);

    em->Machine.RuntimeData.org_pointer = value;
    em->Machine.cpu->pc                 = value;

    return fp;
}

void load_bytecode(struct EmulationMachine *em)
{
    FILE  *fp;

    u8  byte;
    u32 span = 0;

    fp = open_file_and_extract_ORG(em);

    while (fread(&byte, 1, 1, fp) != 0)
    {
        if (byte == SIMHALT_SYMBOL)
        {
            u8 sh[8] = {byte, 0, 0, 0, 0, 0, 0, 0};

            u16 i   = 1;
            u32 len = 1;

            for (; i < 8 && len != 0; i++)
                len = fread(&sh[i], 1, 1, fp);

            if (halt_compare(sh) && em->Machine.RuntimeData.simhalt == 0)
            {
                em->Machine.RuntimeData.simhalt = em->Machine.cpu->pc + span;
                continue;
            }
            else fseek(fp, ftell(fp) - ((!len) ? (i-2) : (i-1)),  SEEK_SET);
        }

        write_byte(em->Machine.cpu->pc + span, byte);
        span += BYTE_SPAN;
    }


    fclose(fp);

    em->Machine.RuntimeData.last_loaded_byte_index = em->Machine.cpu->pc + span;

    if (em->Machine.RuntimeData.simhalt == 0)
        em->Machine.RuntimeData.simhalt = em->Machine.RuntimeData.last_loaded_byte_index;

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
            "\n"
            "**Emulator option**\n"
            " [-t] -Perform a chrono calculation and print it.\n"
            "       This option is prohibited in STEP-BY-STEP MODE.\n"
            "\n\n",
        stdout);

        EMULATOR_ERROR("Too few params")
    }

    em->ExecArgs.executable_path  = argv[2];
    em->ExecArgs.chrono_mode      = FALSE;

    _is_valid_file(em);

    for (s32 i = 3; i < argc; i++)
    {
        if (strlen(argv[i]) == 2)
        {
            if (argv[i][0] == '-' && argv[i][1] == 't')
                em->ExecArgs.chrono_mode = TRUE;
            else EMULATOR_ERROR("Invalid param '%s' at position %d.", argv[i], i);
        }
        else EMULATOR_ERROR("Invalid param '%s' at position %d.", argv[i], i);
    }

}


void __init(struct EmulationMachine *this)
{
    this->Machine.cpu = init_cpu(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        exit(EXIT_FAILURE);
    }

    init_opcodes(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        exit(EXIT_FAILURE);
    }

    this->Machine.ram = init_ram(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        exit(EXIT_FAILURE);
    }
}


void __turnoff()
{
    destroy_cpu();
    destroy_ram();
    destroy_codes();
}


struct EmulationMachine obtain_emulation_machine(int argc, char **argv)
{
    struct EmulationMachine em;

    em.Machine.State = BEGIN_STATE;

    em.Machine.RuntimeData.operation_code = 0;
    em.Machine.RuntimeData.mnemonic       = NULL;

    em.Machine.RuntimeData.org_pointer = ORG_DEFAULT;
    em.Machine.RuntimeData.simhalt     = 0;
    em.Machine.RuntimeData.last_loaded_byte_index = 0;

    em.Machine.RuntimeData.RAM_SIZE = 0x00FFFFFF;
    em.Machine.RuntimeData.STACK_BOTTOM_INDEX = 0x01000000;
    em.Machine.RuntimeData.JSR_CALL_COUNTER   = 0;

    em.Machine.Chrono.dt = 0;

    em.Machine.IO.buffer  = NULL;
    em.Machine.IO.Type    = IO_UNDEF;

    parse_args(&em, argc, argv);

    em.Machine.init    = __init;
    em.Machine.turnoff = __turnoff;

    return em;
}


/* EMULATOR */
int emulate(int argc, char** argv)
{
    struct EmulationMachine em = obtain_emulation_machine(argc, argv);
    em.Machine.init(&em);

    preset_hander(&em);

    load_bytecode(&em);

    em.Machine.State = EXECUTION_STATE;

    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_begin);
    while(em.Machine.cpu->pc < em.Machine.RuntimeData.simhalt)
    {
        if (em.Machine.cpu->exec(&em) == RETURN_ERR)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

            em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                                   (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

            switch (em.Machine.State) {
                case PANIC_STATE:
                {
                    PANIC(em.Machine.Exception.panic_cause)
                    break;
                }
                case TRAP_STATE:
                {
                    TRAPEXC(em.Machine.Exception.trap_cause)
                    break;
                }
                default:
                    break;
            }

            em.Machine.turnoff();

            return (EXIT_FAILURE);
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &em.Machine.Chrono.t_end);

    em.Machine.Chrono.dt = (em.Machine.Chrono.t_end.tv_sec - em.Machine.Chrono.t_begin.tv_sec) * 1000000 +
                           (em.Machine.Chrono.t_end.tv_nsec - em.Machine.Chrono.t_begin.tv_nsec) / 1000;

    if (em.ExecArgs.chrono_mode)
        fprintf(stdout, "Time: %.3fms -> %.3fs\n",
                (f64) em.Machine.Chrono.dt / (f64) 1000,
                (f64) em.Machine.Chrono.dt / (f64) 1000000);

    em.Machine.State = FINAL_STATE;

    em.Machine.turnoff();

    return (EXIT_SUCCESS);
}



