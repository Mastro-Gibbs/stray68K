#include "ram.h"
#include "JSON.h"


void init_ram(struct EmulationMachine *emulator)
{
    emulator->Machine.ram.size = RAM_MAX_SIZE;
    erase_ram(emulator);
}

void erase_ram(struct EmulationMachine *emulator)
{
    for (u32 iter = 0; iter < emulator->Machine.ram.size; iter++)
        emulator->Machine.ram.self[iter] = 0x00;

}


/* MEMORY READ */
u8 read_byte(struct EmulationMachine* emulator, const u32 pointer)
{
    return emulator->Machine.ram.self[pointer];
}

u16 read_word(struct EmulationMachine* emulator, const u32 pointer)
{
    return (u16)((emulator->Machine.ram.self[pointer] << 8) + emulator->Machine.ram.self[pointer + 1]);
}

u32 read_long(struct EmulationMachine* emulator, const u32 pointer)
{
    return (u32)((emulator->Machine.ram.self[pointer] << 24) + (emulator->Machine.ram.self[pointer + 1] << 16) + 
                 (emulator->Machine.ram.self[pointer + 2] << 8) + emulator->Machine.ram.self[pointer + 3]);
}


unsigned char* read_chunk(struct EmulationMachine* emulator, const unsigned int pointer, const unsigned int end)
{
    u8 *read = malloc(sizeof (u8) * end+1);

    for (u32 iter = 0; iter < (end-pointer); iter++)
        read[iter] = emulator->Machine.ram.self[pointer + iter];

    read[end] = '\0';

    return read;
}

unsigned char* read_stack(struct EmulationMachine* emulator, const unsigned int pointer)
{
    u8 *read = malloc(sizeof (u8) * 41);

    for (u32 iter = 40; iter > 0; iter--)
        read[40 - iter] = emulator->Machine.ram.self[(pointer+4) - iter];

    read[40] = '\0';

    return read;
}


/* MEMORY WRITE */
void write_byte(struct EmulationMachine* emulator, const u32 pointer, const u8 value)
{
    emulator->Machine.ram.self[pointer] = value;
}

void write_word(struct EmulationMachine* emulator, const u32 pointer, const u16 value)
{
    emulator->Machine.ram.self[pointer]     = (u8)((value >> 8) & 0xFF);
    emulator->Machine.ram.self[pointer + 1] = (u8)(value & 0xFF);
}

void write_long(struct EmulationMachine* emulator, const u32 pointer, const u32 value)
{
    emulator->Machine.ram.self[pointer]     = (u8)((value >> 24) & 0xFF);
    emulator->Machine.ram.self[pointer + 1] = (u8)((value >> 16) & 0xFF);
    emulator->Machine.ram.self[pointer + 2] = (u8)((value >> 8)  & 0xFF);
    emulator->Machine.ram.self[pointer + 3] = (u8)(value & 0xFF);
}


