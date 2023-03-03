/**
 * Author: Stefano Fattore
 *
 * This header contains some protos to menage cpu struct (Read-Write regs, pc, stacks).
 *
 * Some protos are used to menage CC register.
 *
 *
 */

#ifndef __CPU_H__68000
#define __CPU_H__68000

#include "motorolatypes.h"
#include "handler.h"

#include <stdlib.h>

void init_cpu(struct EmulationMachine *emulator);
void reset_cpu(struct EmulationMachine* restrict emulator);


/* REGS */
u32  read_datareg(struct EmulationMachine* restrict emulator, const u32 reg);
void write_datareg(struct EmulationMachine* restrict emulator, const u32 reg, const u32 val, opsize* const size);

u32  read_addrreg(struct EmulationMachine* restrict emulator, const u32 reg);
void write_addrreg(struct EmulationMachine* restrict emulator, const u32 reg, const u32 val, opsize* const size);

void incr_addr_reg(struct EmulationMachine* restrict emulator, const u32 reg, const opsize size);
void decr_addr_reg(struct EmulationMachine* restrict emulator, const u32 reg, const opsize size);


/* STACKS */
u16 pop_word(struct EmulationMachine* restrict emulator);
u32 pop_long(struct EmulationMachine* restrict emulator);

void push_word(struct EmulationMachine* restrict emulator, const u16 word);
void push_long(struct EmulationMachine* restrict emulator, const u32 longword);


/* CONDITION CODES */
bit eval_cc(struct EmulationMachine* restrict emulator, const CCm cc);


/* PROGRAM COUNTER */
void set_pc(struct EmulationMachine* restrict emulator, const u32 pc);
u32 get_pc(struct EmulationMachine* restrict emulator);

#endif // __CPU_H__68000
