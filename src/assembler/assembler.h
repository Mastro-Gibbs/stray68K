#ifndef __ASSEMBLER_H_H__68000
#define __ASSEMBLER_H_H__68000

#include "clowncommon.h"
#include "semantic.h"

#define ASSEMBLER_ERROR(message) do { fputs("[ASSEMBLER ERROR] " message "\n", stderr); exit_code = EXIT_FAILURE;} while (0)

#define FASSEMBLER_ERROR(fmt, ...) do { printf("[ASSEMBLER ERROR] "); printf (fmt, ##__VA_ARGS__); printf ("\n"); exit_code = EXIT_FAILURE;} while (0)


int assemble(int argc, char **argv);




#endif // __ASSEMBLER_H_H__68000
