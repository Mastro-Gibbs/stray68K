#ifndef __ARCH_H__68000
#define __ARCH_H__68000


#include <stdlib.h>
#include "cpu.h"
#include "memory.h"
#include "loader.h"


#define RAM_SIZE 0xFFFFFFFF


typedef struct __ARCH__68000
{
    cpu_t *cpu;
    ram_t *ram;

    void  (*load)    (char *filename);
    bit (*is_halt) ();
    void  (*turnoff) ();    
} arch_t;



int emulate(int argc, char **argv);

int emulate_sbs(int argc, char **argv);



#endif // __ARCH_H__68000
