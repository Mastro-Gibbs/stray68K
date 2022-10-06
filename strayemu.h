#ifndef __STRAYEMU_H__68000
#define __STRAYEMU_H__68000

#include "ARCH.h"
#include "assembler/assembler.h"


/* EMULATOR */
int emulate(int argc,  char** argv);
int emulate_sbs(int argc, char **argv); // aka step-by-step

#endif // __STRAYEMU_H__68000
