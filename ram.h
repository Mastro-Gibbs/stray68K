#ifndef __RAM_H__68000
#define __RAM_H__68000


#include "motorolatypes.h"
#include "utils.h"

#include <stdlib.h>


m68k_ram* init_ram(generic_u32_t size);
void   erase();
void   destroy_ram();


/* MEMORY READ */
generic_u8_t  read_byte(generic_u32_t pointer);
generic_u16_t read_word(generic_u32_t pointer);
generic_u32_t read_long(generic_u32_t pointer);

/* MEMORY WRITE */
void write_byte(generic_u32_t pointer, generic_u8_t  value);
void write_word(generic_u32_t pointer, generic_u16_t value);
void write_long(generic_u32_t pointer, generic_u32_t value);



#endif // __RAM_H__68000
