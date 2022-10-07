#ifndef __UTILS_H__68000
#define __UTILS_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "memory.h"
#include "cpu.h"

#include <stdlib.h>


#include <stdio.h>
#define TRAPEXC(...) do {                                                   \
                            system("clear");                                \
                            cpu_t *cpu = init_cpu();                        \
                            cpu->show();                                    \
                            printf("\n[\033[01m\033[35mTRAP\033[0m] ");     \
                            printf("Raised trap exception: \n       \033[01m\033[37mcode\033[0m:     %d\n       \033[01m\033[37mmnemonic\033[0m: %s\n", ##__VA_ARGS__);\
                            fflush(stdout);                                 \
                        } while (0);                                        \
                        destroy_cpu();                                      \
                        destroy_ram();                                      \
                        exit(-1);

#define PANIC(fmt, ...) do {                                           \
                            system("clear");                           \
                            cpu_t *cpu = init_cpu();                   \
                            cpu->show();                               \
                            printf("[\033[01m\033[91mPANIC\033[0m] "); \
                            printf (fmt, ##__VA_ARGS__);               \
                            fflush(stdout);                            \
                        } while (0);                                   \
                        destroy_cpu();                                 \
                        destroy_ram();                                 \
                        exit(-1);

#define WARNING(fmt, ...) do {                                        \
                            printf("[\033[01m\033[93mWARN\033[0m] "); \
                            printf (fmt, ##__VA_ARGS__);              \
                            fflush(stdout);                           \
                        } while (0);


#define bprintf(x)                                               \
  do {                                                           \
    unsigned long long a__ = (x);                                \
    size_t bits__ = sizeof(x) * 8;                               \
    printf(#x ": ");                                             \
    while (bits__--) putchar(a__ &(1ULL << bits__) ? '1' : '0'); \
    putchar('\n');                                               \
  } while (0)


#define bprintf_ht(x)                                            \
  do {                                                           \
    unsigned long long a__ = (x);                                \
    size_t bits__ = sizeof(x) * 8;                               \
    printf("\033[01m\033[37m");                                  \
    printf(#x);                                                  \
    printf("\033[0m: ");                                         \
    while (bits__--) putchar(a__ &(1ULL << bits__) ? '1' : '0'); \
    putchar('\n');                                               \
  } while (0)


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

// DEFINE MNEMONIC HASHING VALUES, COMPUTED WITH 'generic_u32_t hash (const char* word)' func

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



typedef enum __known_masks__
{
    DST_MASK      = 0b0000111000000000,
    SRC_MASK      = 0b0000000000000111,
    SIZE_MASK     = 0b0000000011000000,
    ADDRMODE_MASK = 0b0000000000111111

} KnownMasks;


#endif // __UTILS_H__68000
