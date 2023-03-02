#include "emulator.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "cpu.h"
#include "ram.h"
#include "JSON.h"

#define SIMHALT_SYMBOL  0xAC
#define ORG_SYMBOL      'o'
#define ORG_DEFAULT     0x00000000

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

c_bool halt_compare(u8 *s1)
{
    u8 halt[8] = {0xAC, 0xAC, 0xFF, 0xFF, 0xFF, 0xFF, 0xAC, 0xAC};

    for (u16 i = 0; i < 8; i++)
        if (s1[i] != halt[i]) return c_false;

    return c_true;
}


/* LOADER */


u32 peek_ORG_from_file(struct EmulationMachine *emulator)
{
    FILE *fp;

    s8  is_org = 0;
    u8  org[4];
    u32 value = ORG_DEFAULT;

    fp = fopen(emulator->binary_path, "rb");

    if (fread(&is_org, 1, 1, fp) == 0)
        EMULATOR_ERROR("Error incomes while loading invalid binary");

    if (is_org == ORG_SYMBOL)
    {
        if (fread(org, ARRAY_SIZE(org), sizeof (*org), fp) == 0)
            EMULATOR_ERROR("Error incomes while loading binary");

        value = (org[0] << 24) | (org[1] << 16) | (org[2] << 8) | org[3];
    }

    fclose(fp);

    return value;
}


FILE* open_file_and_extract_ORG(struct EmulationMachine *emulator)
{
    FILE *fp;

    s8  is_org = 0;
    u8  org[4];
    u32 value = ORG_DEFAULT;

    fp = fopen(emulator->binary_path, "rb");

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

    emulator->Machine.RunTime.org_pointer = value;
    emulator->Machine.cpu.pc                 = value;

    return fp;
}

void load_bytecode(struct EmulationMachine *emulator)
{
    FILE  *fp;

    u8  byte;
    u32 span = 0;

    fp = open_file_and_extract_ORG(emulator);

    while (fread(&byte, 1, 1, fp) != 0)
    {
        if (byte == SIMHALT_SYMBOL)
        {
            u8 sh[8] = {byte, 0, 0, 0, 0, 0, 0, 0};

            u16 i   = 1;
            u32 len = 1;

            for (; i < 8 && len != 0; i++)
                len = fread(&sh[i], 1, 1, fp);

            if (halt_compare(sh) && emulator->Machine.RunTime.simhalt == 0)
            {
                emulator->Machine.RunTime.simhalt = emulator->Machine.cpu.pc + span;
                continue;
            }
            else fseek(fp, ftell(fp) - ((!len) ? (i-2) : (i-1)),  SEEK_SET);
        }

        write_byte(emulator, emulator->Machine.cpu.pc + span, byte);
        span += BYTE_SPAN;
    }


    fclose(fp);

    emulator->Machine.RunTime.last_loaded_byte_index = emulator->Machine.cpu.pc + span;

    if (emulator->Machine.RunTime.simhalt == 0)
        emulator->Machine.RunTime.simhalt = emulator->Machine.RunTime.last_loaded_byte_index;

}



struct EmulationMachine*
obtain_emulation_machine(const char *path)
{
    struct EmulationMachine *emulator = NULL;

    emulator = malloc(sizeof(* emulator));

    emulator->Machine.State = BEGIN_STATE;
    emulator->Machine.dump  = NULL;

    emulator->Machine.RunTime.operation_code = 0;
    emulator->Machine.RunTime.mnemonic       = NULL;

    emulator->Machine.RunTime.org_pointer = ORG_DEFAULT;
    emulator->Machine.RunTime.simhalt     = 0;
    emulator->Machine.RunTime.last_loaded_byte_index = 0;

    emulator->Machine.RunTime.STACK_BOTTOM_INDEX = 0x01000000;
    emulator->Machine.RunTime.JSR_CALL_COUNTER   = 0;

    emulator->Machine.RunTime.Chrono.dt = 0;

    emulator->Machine.IO.buffer  = NULL;
    emulator->Machine.IO.Type    = IO_UNDEF;

    emulator->binary_path = malloc(strlen(path) + 1);
    strcpy(emulator->binary_path, path);

    init_cpu(emulator);

    init_opcodes(emulator);

    init_ram(emulator);

    return emulator;
}




void begin_emulator(struct EmulationMachine* emulator)
{
    load_bytecode(emulator);

    emulator->Machine.State = EXECUTION_STATE;

    emit_dump(emulator);

    clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.RunTime.Chrono.t_begin);
}

void end_emulator(struct EmulationMachine* emulator)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.RunTime.Chrono.t_end);

    emulator->Machine.RunTime.Chrono.dt = (emulator->Machine.RunTime.Chrono.t_end.tv_sec - emulator->Machine.RunTime.Chrono.t_begin.tv_sec) * 1000000 +
                           (emulator->Machine.RunTime.Chrono.t_end.tv_nsec - emulator->Machine.RunTime.Chrono.t_begin.tv_nsec) / 1000;

    emulator->Machine.IO.Type = IO_UNDEF;
    emulator->Machine.State = FINAL_STATE;

    if (emulator->Machine.IO.buffer)
        free(emulator->Machine.IO.buffer);

    if (emulator->Machine.dump)
        free(emulator->Machine.dump);

    if (emulator->binary_path)
        free(emulator->binary_path);
    
    destroy_codes(emulator);

    free(emulator);
}


int is_last_istr(struct EmulationMachine* emulator)
{
    return (emulator->Machine.cpu.pc + WORD_SPAN) < emulator->Machine.RunTime.simhalt ? 0 : 1;
}


/* EMULATOR */
int emulate(struct EmulationMachine* emulator)
{
    if (emulator->Machine.cpu.pc < emulator->Machine.RunTime.simhalt)
    {
        if (execute_instruction(emulator) == RETURN_ERR)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.RunTime.Chrono.t_end);

            emulator->Machine.RunTime.Chrono.dt = (emulator->Machine.RunTime.Chrono.t_end.tv_sec - emulator->Machine.RunTime.Chrono.t_begin.tv_sec) * 1000000 +
                                   (emulator->Machine.RunTime.Chrono.t_end.tv_nsec - emulator->Machine.RunTime.Chrono.t_begin.tv_nsec) / 1000;

            emit_dump(emulator);

            return (RETURN_ERR);
        }

        return (RETURN_OK);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &emulator->Machine.RunTime.Chrono.t_end);

    emulator->Machine.RunTime.Chrono.dt = (emulator->Machine.RunTime.Chrono.t_end.tv_sec - emulator->Machine.RunTime.Chrono.t_begin.tv_sec) * 1000000 +
                                   (emulator->Machine.RunTime.Chrono.t_end.tv_nsec - emulator->Machine.RunTime.Chrono.t_begin.tv_nsec) / 1000;

    emulator->Machine.State = FINAL_STATE;

    emit_dump(emulator);

    return (RETURN_FINISH);
}



