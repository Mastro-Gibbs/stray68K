#ifndef __ASSEMBLER_H_H__68000
#define __ASSEMBLER_H_H__68000

#include "clowncommon.h"
#include "semantic.h"

#define ASSEMBLER_ERROR(message) do { fputs("[\033[31m\033[01mASSEMBLER ERROR\033[0m] " message "\n", stderr); exit_code = EXIT_FAILURE;} while (0)

#define FASSEMBLER_ERROR(fmt, ...) do { printf("[\033[31m\033[01mASSEMBLER ERROR\033[0m] "); printf (fmt, ##__VA_ARGS__); printf ("\n"); exit_code = EXIT_FAILURE;} while (0)


int assemble(int argc, char **argv);




#endif // __ASSEMBLER_H_H__68000
