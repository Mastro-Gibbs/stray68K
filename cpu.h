#ifndef __CPU_H__68000
#define __CPU_H__68000

#include "opcode_handlers.h"

#include <stdlib.h>


typedef struct __cpu__
{
    generic_u32_t data_r[8];  // D0..D7 -> data registers

    generic_u32_t addr_r[7];  // A0..A6 -> address registers

    generic_u32_t  usp;        // aka A7 -> user stack pointer

    generic_u32_t  ssp;        // system stack pointer

    generic_u32_t  pc;         // program counter

    srflags sr;        // status register flags


    generic_u32_t (*exec) (bit describe_code); // runner

    void (*show)();

} cpu_t;


cpu_t* init_cpu();
void   reset_cpu();
void   destroy_cpu();

/* FLAGS */
bit get_carry();
void  set_carry(bit bit);

bit get_overflow();
void  set_overflow(bit bit);

bit get_zero();
void  set_zero(bit bit);

bit get_negative();
void  set_negative(bit bit);

bit get_extended();
void  set_extended(bit bit);

bit get_supervisor();
void  set_supervisor(bit bit);

bit get_trace();
void  set_trace(bit bit);


/* REGS */
generic_u32_t read_datareg(generic_u32_t reg);
void  write_datareg(generic_u32_t reg, generic_u32_t val, opsize *size);

generic_u32_t read_addrreg(generic_u32_t reg);
void  write_addrreg(generic_u32_t reg, generic_u32_t val, opsize *size);

void incr_addr_reg(generic_u32_t reg, opsize size);
void decr_addr_reg(generic_u32_t reg, opsize size);

srflags get_sr();
void set_sr(srflags bits);



/* STACKS */
generic_u16_t pop_word();
generic_u32_t pop_long();

void push_word(generic_u16_t word);
void push_long(generic_u32_t longword);

generic_u32_t get_stack_ptr();

void set_usp(generic_u32_t ptr);
generic_u32_t get_usp();


/* CONDITION CODES */
bit eval_cc(CCm cc);


/* PROGRAM COUNTER */
void set_pc(generic_u32_t pc);
void incr_pc(bit bits);
generic_u32_t get_pc();

#endif // __CPU_H__68000
