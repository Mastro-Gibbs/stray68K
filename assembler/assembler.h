#ifndef __ASSEMBLER_H_H__68000
#define __ASSEMBLER_H_H__68000

#include "clowncommon.h"
#include "semantic.h"

#define ERROR(message) do { fputs("Error: " message "\n", stderr); exit_code = EXIT_FAILURE;} while (0)



int assemble(int argc, char **argv);




#endif // __ASSEMBLER_H_H__68000
