#ifndef __UTILS_H__68000
#define __UTILS_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "ram.h"
#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * MACRO used to raise a critical trap code.
 *
 */
#define TRAPEXC(...) do {                                               \
                        system("clear");                                \
                        m68k_cpu *cpu = init_cpu();                     \
                        cpu->show();                                    \
                        printf("\n[\033[01m\033[35mTRAP\033[0m] ");     \
                        printf("Raised trap exception: \n       \033[01m\033[37mcode\033[0m:     %d\n       \033[01m\033[37mmnemonic\033[0m: %s\n", ##__VA_ARGS__);\
                        fflush(stdout);                                 \
                        destroy_cpu();                                  \
                        destroy_ram();                                  \
                        exit(-1);                                       \
                    } while (0);


/*
 * MACRO used to turn system into PANIC mode aka something that the sys don't know how to handle it.
 *
 */
#define PANIC(fmt, ...) do {                                           \
                            system("clear");                           \
                            m68k_cpu *cpu = init_cpu();                \
                            cpu->show();                               \
                            printf("[\033[01m\033[91mPANIC\033[0m] "); \
                            printf (fmt, ##__VA_ARGS__);               \
                            printf("\n");                              \
                            fflush(stdout);                            \
                            destroy_cpu();                             \
                            destroy_ram();                             \
                            exit(-1);                                  \
                        } while (0);


/*
 * MACRO emit WARNING message like an operation that may present bugs or unmenaged operation.
 *
 */
#define WARNING(fmt, ...) do {                                        \
                            printf("[\033[01m\033[93mWARN\033[0m] "); \
                            printf (fmt, ##__VA_ARGS__);              \
                            printf("\n");                             \
                            fflush(stdout);                           \
                        } while (0);


/*
 * MACRO used to raise a condition that blocks normal emulation flow,
 * like a ByteCode mistake loading.
 *
 * This will call exit()
 *
 */
#define EMULATOR_ERROR(fmt, ...) do {                                      \
                            printf("[\033[01m\033[91mEMULATOR ERROR\033[0m] "); \
                            printf (fmt, ##__VA_ARGS__);               \
                            printf("\n");                              \
                            fflush(stdout);                            \
                            destroy_cpu();                             \
                            destroy_ram();                             \
                            exit(-1);                                  \
                        } while (0);


/*
 * MACRO used to prepend a tag to IO emulator.
 *
 */
#define IO_TASK(descr, fmt, ...) do {                                 \
                        IO_TASK_TAG(descr)                            \
                        printf (fmt, ##__VA_ARGS__);                  \
                        fflush(stdout);                               \
                    } while (0);

/*
 * MACRO used to prepend a tag to IO emulator loop.
 * It's different from the previous macro because this one allows to print sequences of chars (strings).
 *
 */
#define IO_TASK_TAG(descr) do {                                       \
                        if (descr)                                    \
                            printf("\n[\033[01m\033[95mIO\033[0m] "); \
                        fflush(stdout);                               \
                    } while (0);


/*
 * MACRO used to prepend a tag to step-by-step mode.
 *
 */
#define SBS_DEBUGGER(fmt, ...)do {                                \
                        printf("\n[\033[01m\033[94mDEBUGGER\033[0m] "); \
                        printf (fmt, ##__VA_ARGS__);              \
                        fflush(stdout);                           \
                    } while (0);


/*
 * MACRO used to print bits of number.
 *
 */
#define bprintf(x)                                               \
  do {                                                           \
    unsigned long long a__ = (x);                                \
    size_t bits__ = sizeof(x) * 8;                               \
    printf(#x ": ");                                             \
    while (bits__--) putchar(a__ &(1ULL << bits__) ? '1' : '0'); \
    putchar('\n');                                               \
  } while (0);


/*
 * MACRO used to print bits of number with bit's highlight.
 *
 */
#define bprintf_ht(x)                                            \
  do {                                                           \
    unsigned long long a__ = (x);                                \
    size_t bits__ = sizeof(x) * 8;                               \
    printf("\033[01m\033[37m");                                  \
    printf(#x);                                                  \
    printf("\033[0m: ");                                         \
    while (bits__--) putchar(a__ &(1ULL << bits__) ? '1' : '0'); \
    putchar('\n');                                               \
  } while (0);


/*
 * MACRO used to print bits of number with bit's highlight and 4 space tab.
 *
 */
#define bprintf_ht_4s(x)                                         \
  do {                                                           \
    unsigned long long a__ = (x);                                \
    size_t bits__ = sizeof(x) * 8;                               \
    printf("\033[01m\033[37m");                                  \
    printf(#x);                                                  \
    printf("\033[0m:     ");                                     \
    while (bits__--) putchar(a__ &(1ULL << bits__) ? '1' : '0'); \
  } while (0);



/*
 * DEFINING MNEMONIC HASHING VALUES, COMPUTED WITH 'generic_u32_t hash (const char* word)' func
 *
 */
#define ori   78534
#define andi  2013554
#define eori  2134113
#define move  2372561
#define moveq 73549472
#define divu  2098692
#define divs  2098690
#define or    2531
#define eor   68840
#define mulu  2378033
#define muls  2378031
#define and   64951
#define subi  2556457
#define subq  2556465
#define sub   82464
#define subx  2556472
#define addi  2003944
#define addq  2003952
#define add   64641
#define addx  2003959
#define cmpi  2072547
#define cmpm  2072551
#define cmp   66854
#define clr   66825
#define cmpa  2072539
#define negx  2392296
#define neg   77168
#define not   77491
#define ext   69121
#define swap  2558355
#define tst   83381
#define asl   65114
#define asr   65120
#define lsl   75685
#define lsr   75691
#define rol   81327
#define ror   81333
#define roxl  2521585
#define roxr  2521591




// -------------------- BEGIN PROTS ------------------------ //



generic_u32_t most_significant_byte(opsize size);
generic_u32_t mask_by_opsize(opsize size);
generic_u32_t hash (const char* word);
generic_32_t  sign_extended(generic_u32_t val, opsize size);


/* OPCODE DECODER */
void** eval_OP_EA(opcode code, bit ignore_direction);
void   free_eval_OP_EA_array(void** array);


/* IO EA */
generic_u32_t read_ram(generic_u32_t *addr, opsize *size);
generic_u32_t read_EA (generic_u32_t *addr, opsize *size, ADDRMode *mode, ea_direction *dir);
void          write_EA(generic_u32_t *addr, generic_u32_t val, opsize *size, ADDRMode *mode);
void          should_incr_pc(opsize *size, ADDRMode *mode);


/* MISC */
opsize_span size_to_span(opsize size);
bit is_ram_op(ADDRMode *mode);
bit is_addr_to_data_op(ADDRMode *mode);


/* TRAP */
char* trap_code_toString(generic_u32_t trapcode);
void  iotask(bit descr);



#endif // __UTILS_H__68000
