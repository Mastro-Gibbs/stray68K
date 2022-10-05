#ifndef __MEMORY_H__68000
#define __MEMORY_H__68000


#include "motorolatypes.h"
#include "utils.h"

#include <stdlib.h>


typedef struct __memory__
{
    generic_u8_t *ram;
    generic_u32_t size;

    void (*show) (generic_u32_t _start, generic_u32_t _end);

} ram_t;


ram_t* init_ram(generic_u32_t size);
void   erase();
void   destroy_ram();


/* MEMORY READ */
generic_u8_t* read_chunk(generic_u32_t pointer, generic_u32_t length);

generic_u8_t  read_byte(generic_u32_t pointer);
generic_u16_t read_word(generic_u32_t pointer);
generic_u32_t read_long(generic_u32_t pointer);

/* MEMORY WRITE */
void write_chunk(generic_u32_t pointer, generic_u8_t *value, generic_u32_t size);

void write_byte(generic_u32_t pointer, generic_u8_t  value);
void write_word(generic_u32_t pointer, generic_u16_t value);
void write_long(generic_u32_t pointer, generic_u32_t value);



#endif // __MEMORY_H__68000
