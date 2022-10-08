#ifndef __ASSEMBLER_H_H__68000
#define __ASSEMBLER_H_H__68000

#include "clowncommon.h"
#include "semantic.h"

#define ASSSEMBLER_ERROR(message) do { fputs("[\033[31m\033[01mASSEMBLER ERROR\033[0m] " message "\n", stderr); exit_code = EXIT_FAILURE;} while (0)



int assemble(int argc, char **argv);




#endif // __ASSEMBLER_H_H__68000
