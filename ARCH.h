#ifndef __ARCH_H__68000
#define __ARCH_H__68000


#include <stdlib.h>
#include "cpu.h"
#include "memory.h"


#define RAM_SIZE 0x00FFFFFF


struct EmulationState;


typedef struct __ARCH__68000__
{
    cpu_t *cpu;
    ram_t *ram;

    void  (*load)    (struct EmulationState *state);
    bit   (*is_halt) ();
    void  (*turnoff) ();    
} arch_t;



int emulate(int argc, char **argv);



#endif // __ARCH_H__68000
