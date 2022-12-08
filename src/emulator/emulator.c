#include "emulator.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cpu.h"
#include "ram.h"
#include "JSON.h"

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
void parse_args(struct EmulationMachine *em, char *path)
{
    em->ExecArgs.executable_path  = path;

    _is_valid_file(em);
}


void __init(struct EmulationMachine *this)
{
    this->Machine.cpu = init_cpu(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        emit_dump(this);

        exit(EXIT_FAILURE);
    }

    init_opcodes(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        emit_dump(this);

        exit(EXIT_FAILURE);
    }

    this->Machine.ram = init_ram(this);

    if (this->Machine.State == PANIC_STATE)
    {
        PANIC(this->Machine.Exception.panic_cause);

        emit_dump(this);

        exit(EXIT_FAILURE);
    }
}


void __turnoff()
{
    destroy_cpu();
    destroy_ram();
    destroy_codes();
}


struct EmulationMachine *emulator = NULL;

void obtain_emulation_machine(char *path)
{
    emulator = malloc(sizeof(* emulator));

    emulator->Machine.State = BEGIN_STATE;

    emulator->Machine.RuntimeData.operation_code = 0;
    emulator->Machine.RuntimeData.mnemonic       = NULL;

    emulator->Machine.RuntimeData.org_pointer = ORG_DEFAULT;
    emulator->Machine.RuntimeData.simhalt     = 0;
    emulator->Machine.RuntimeData.last_loaded_byte_index = 0;
    emulator->Machine.RuntimeData.sbs_printer_enabler    = FALSE;

    emulator->Machine.RuntimeData.RAM_SIZE = 0x00FFFFFF;
    emulator->Machine.RuntimeData.STACK_BOTTOM_INDEX = 0x01000000;
    emulator->Machine.RuntimeData.JSR_CALL_COUNTER   = 0;

    emulator->Machine.Chrono.dt = 0;

    emulator->Machine.IO.buffer  = NULL;
    emulator->Machine.IO.Type    = IO_UNDEF;

    emulator->Machine.RuntimeData.sbs_printer_enabler = TRUE;
    emulator->EmuType = EMULATE_SBS;

    parse_args(emulator, path);

    emulator->Machine.init    = __init;
    emulator->Machine.turnoff = __turnoff;

}




void begin_emulator(char *path)
{
    obtain_emulation_machine(path);
    emulator->Machine.init(emulator);

    preset_hander(emulator);

    load_bytecode(emulator);

    emulator->Machine.State = EXECUTION_STATE;

    emit_dump(emulator);

    clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.Chrono.t_begin);
}

void end_emulator()
{
    clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.Chrono.t_end);

    emulator->Machine.Chrono.dt = (emulator->Machine.Chrono.t_end.tv_sec - emulator->Machine.Chrono.t_begin.tv_sec) * 1000000 +
                           (emulator->Machine.Chrono.t_end.tv_nsec - emulator->Machine.Chrono.t_begin.tv_nsec) / 1000;

    emulator->Machine.State = FINAL_STATE;

    emit_dump(emulator);

    emulator->Machine.turnoff();

    free(emulator);
    emulator = NULL;
}


/* EMULATOR */
int emulate()
{
    if (emulator->Machine.cpu->pc < emulator->Machine.RuntimeData.simhalt)
    {
        if (emulator->Machine.cpu->exec(emulator) == RETURN_ERR)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.Chrono.t_end);

            emulator->Machine.Chrono.dt = (emulator->Machine.Chrono.t_end.tv_sec - emulator->Machine.Chrono.t_begin.tv_sec) * 1000000 +
                                   (emulator->Machine.Chrono.t_end.tv_nsec - emulator->Machine.Chrono.t_begin.tv_nsec) / 1000;

            switch (emulator->Machine.State) {
                case PANIC_STATE:
                {
                    PANIC(emulator->Machine.Exception.panic_cause)
                    break;
                }
                case TRAP_STATE:
                {
                    TRAPEXC(emulator->Machine.Exception.trap_cause)
                    break;
                }
                default:
                    break;
            }

            emulator->Machine.turnoff();

            return (RETURN_ERR);
        }

        return (RETURN_OK);
    }

    return (RETURN_ERR);
}



