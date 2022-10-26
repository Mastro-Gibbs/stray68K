#ifndef __RAM_H__68000
#define __RAM_H__68000


#include "motorolatypes.h"
#include "utils.h"

#include <stdlib.h>


m68k_ram* init_ram(struct EmulationMachine *em, u32 size);
m68k_ram* get_ram();
void   erase();
void   destroy_ram();


/* MEMORY READ */
u8  read_byte(u32 pointer);
u16 read_word(u32 pointer);
u32 read_long(u32 pointer);

/* MEMORY WRITE */
void write_byte(u32 pointer, u8  value);
void write_word(u32 pointer, u16 value);
void write_long(u32 pointer, u32 value);



#endif // __RAM_H__68000
