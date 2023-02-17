#ifndef __RAM_H__68000
#define __RAM_H__68000


#include "motorolatypes.h"
#include "utils.h"

#include <stdlib.h>


void init_ram(struct EmulationMachine *emulator);
void erase_ram(struct EmulationMachine *emulator);


/* MEMORY READ */
u8  read_byte(struct EmulationMachine* emulator, const u32 pointer);
u16 read_word(struct EmulationMachine* emulator, const u32 pointer);
u32 read_long(struct EmulationMachine* emulator, const u32 pointer);

/* MEMORY WRITE */
void write_byte(struct EmulationMachine* emulator, const u32 pointer, const u8  value);
void write_word(struct EmulationMachine* emulator, const u32 pointer, const u16 value);
void write_long(struct EmulationMachine* emulator, const u32 pointer, const u32 value);


unsigned char* read_chunk(struct EmulationMachine* emulator, const unsigned int pointer, const unsigned int end);
unsigned char* read_stack(struct EmulationMachine* emulator, const unsigned int pointer);


#endif // __RAM_H__68000
