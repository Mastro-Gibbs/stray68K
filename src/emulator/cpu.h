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

m68k_cpu* init_cpu(struct EmulationMachine *em);
m68k_cpu* get_cpu(void);
void      reset_cpu(void);
void      destroy_cpu(void);


/* REGS */
u32 read_datareg(u32 reg);
void write_datareg(u32 reg, u32 val, opsize *size);

u32 read_addrreg(u32 reg);
void write_addrreg(u32 reg, u32 val, opsize *size);

void incr_addr_reg(u32 reg, opsize size);
void decr_addr_reg(u32 reg, opsize size);


/* STACKS */
u16 pop_word(void);
u32 pop_long(void);

void push_word(u16 word);
void push_long(u32 longword);


/* CONDITION CODES */
bit eval_cc(CCm cc);


/* PROGRAM COUNTER */
void set_pc(u32 pc);
u32 get_pc(void);

#endif // __CPU_H__68000
