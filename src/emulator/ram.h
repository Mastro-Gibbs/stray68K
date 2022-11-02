#ifndef __RAM_H__68000
#define __RAM_H__68000


#include "motorolatypes.h"
#include "utils.h"

#include <stdlib.h>


m68k_ram* init_ram(struct EmulationMachine *em);
m68k_ram* get_ram(void);
void      erase_ram(void);
void      destroy_ram(void);


/* MEMORY READ */
u8  read_byte(const u32 pointer);
u16 read_word(const u32 pointer);
u32 read_long(const u32 pointer);

/* MEMORY WRITE */
void write_byte(const u32 pointer, const u8  value);
void write_word(const u32 pointer, const u16 value);
void write_long(const u32 pointer, const u32 value);



#endif // __RAM_H__68000
