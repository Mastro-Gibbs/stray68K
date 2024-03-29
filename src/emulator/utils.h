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
#define TRAPEXC(cause)  do {                                         \
                            printf("[\033[01m\033[35mTRAP\033[0m] ");\
                            printf("%s\n", cause);                   \
                            fflush(stdout);                          \
                        } while (0);


/*
 * MACRO used to turn system into PANIC mode aka something that the sys don't know how to handle it.
 *
 */
#define PANIC(cause) do {                                          \
                        printf("[\033[01m\033[91mPANIC\033[0m] "); \
                        printf("%s\n", cause);                     \
                        fflush(stdout);                            \
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
#define EMULATOR_ERROR(fmt, ...) do {                                    \
                            em->Machine.State = MERR_STATE;                      \
                            printf("[\033[01m\033[91mEMULATOR ERROR\033[0m] ");            \
                            sprintf(em->Machine.Exception.merr_cause, fmt, ##__VA_ARGS__); \
                            printf ("%s\n", em->Machine.Exception.merr_cause);             \
                            fflush(stdout);                              \
                            if (em->ExecArgs.JSON.is_activated) emit_dump(em); \
                            destroy_cpu();                               \
                            destroy_ram();                               \
                            exit(-1);                                    \
                        } while (0);


#define EMULATOR_OUT(fmt, ...) do {                                   \
                            printf("[\033[01m\033[93mINFO\033[0m] "); \
                            printf (fmt, ##__VA_ARGS__);              \
                            fflush(stdout);                              \
                            if (em->ExecArgs.JSON.is_activated) emit_dump(em); \
                            destroy_cpu();                               \
                            destroy_ram();                               \
                            exit(-1);                                    \
                        } while (0);


/*
 * MACRO used to prepend a tag to IO emulator.
 *
 */
#define IO_TASK(descr, fmt, ...) do {                            \
                                    IO_TASK_TAG(descr)           \
                                    printf (fmt, ##__VA_ARGS__); \
                                    fflush(stdout);              \
                                } while (0);



/*
 * MACRO used to prepend a tag to IO emulator loop.
 * It's different from the previous macro because this one allows to print sequences of chars (strings).
 *
 */
#define IO_TASK_TAG(descr)  do {                                            \
                                if (descr)                                  \
                                    printf("[\033[01m\033[95mIO\033[0m] "); \
                                fflush(stdout);                             \
                            } while (0);


/*
 * MACRO used to prepend a tag to step-by-step mode.
 *
 */
#define SBS_DEBUGGER(fmt, ...)do {                                \
                        printf("[\033[01m\033[94mDEBUGGER\033[0m] "); \
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



#define SIGN_EXTENDED(dst, val, size) do{ \
                                    dst = (int) val; \
                                    switch (size) \
                                    { \
                                        case BYTE: \
                                            if ((val & 0x80) == 0x80) \
                                                dst = (int)(dst | 0xFFFFFF00); \
                                            else \
                                                dst &= 0x000000ff; \
                                            break; \
                                        case WORD: \
                                            if ((val & 0x8000) == 0x8000) \
                                                dst = (int)(dst | 0xFFFF0000); \
                                            else \
                                                dst &= 0x0000ffff; \
                                            break; \
                                        case LONG: \
                                            break; \
                                        default: \
                                            break; \
                                    } \
                                 } while(0);

#define READ_EFFECTIVE_ADDRESS(dst, addr, size, mode, dir)  do { \
                                                                u32 ptr; \
                                                                opsize tmpsize = size; \
                                                                \
                                                                if (dir == INVERTED) \
                                                                    switch (mode) { \
                                                                        case DATAReg: \
                                                                        case ADDRReg: \
                                                                        case ADDRESS: \
                                                                        case ADDRESSPostIncr: \
                                                                        case ADDRESSPreDecr: \
                                                                            dst = read_datareg(addr); \
                                                                            break; \
                                                                        \
                                                                        default: \
                                                                        {\
                                                                            emulation->Machine.State = PANIC_STATE; \
                                                                            sprintf(emulation->Machine.Exception.panic_cause, "Addressing mode not handled! (read_EA)"); \
                                                                            return (RETURN_ERR); \
                                                                        }\
                                                                    } \
                                                                else switch (mode) { \
                                                                    case IMMEDIATE: \
                                                                        if (tmpsize == BYTE) tmpsize = WORD; /*byte can't read byte in ram*/ \
                                                                        dst = read_ram(&addr, &tmpsize); \
                                                                        break; \
                                                                    \
                                                                    case DATAReg: \
                                                                        dst = read_datareg(addr); \
                                                                        break; \
                                                                    \
                                                                    case ADDRReg: \
                                                                        dst = read_addrreg(addr); \
                                                                        break; \
                                                                    \
                                                                    case ADDRESS: \
                                                                        if (addr == 7) { \
                                                                            switch (size) { \
                                                                                case BYTE: \
                                                                                case WORD: \
                                                                                    dst = pop_word(); \
                                                                                    break; \
                                                                                case LONG: \
                                                                                    dst = pop_long(); \
                                                                                    break; \
                                                                                default: \
                                                                                    return (RETURN_ERR); \
                                                                            } \
                                                                        } \
                                                                        else { \
                                                                            ptr = read_addrreg(addr); \
                                                                            dst = read_ram(&ptr, &size); \
                                                                        } \
                                                                        break; \
                                                                    \
                                                                    case ADDRESSPostIncr: \
                                                                        if (addr == 7) { \
                                                                            switch (size) { \
                                                                                case BYTE: \
                                                                                case WORD: \
                                                                                    dst = pop_word(); \
                                                                                    break; \
                                                                                case LONG: \
                                                                                    dst = pop_long(); \
                                                                                    break; \
                                                                                default: \
                                                                                    return (RETURN_ERR); \
                                                                            } \
                                                                        } \
                                                                        else { \
                                                                            ptr = read_addrreg(addr); \
                                                                            dst = read_ram(&ptr, &size); \
                                                                        } \
                                                                        break; \
                                                                        /* incr_addr_reg(*addr, *size); */ \
                                                                        /*/ incr must be done after memory read! */ \
                                                                    \
                                                                    case ADDRESSPreDecr: \
                                                                        decr_addr_reg(addr, size); \
                                                                        if (addr == 7) { \
                                                                            switch (size) { \
                                                                                case BYTE: \
                                                                                case WORD: \
                                                                                    dst = pop_word(); \
                                                                                    break; \
                                                                                case LONG: \
                                                                                    dst = pop_long(); \
                                                                                    break; \
                                                                                default: \
                                                                                    return (RETURN_ERR); \
                                                                            } \
                                                                        } \
                                                                        else { \
                                                                            ptr = read_addrreg(addr); \
                                                                            dst = read_ram(&ptr, &size); \
                                                                        } \
                                                                        break; \
                                                                    \
                                                                    case ADDRESSDisp: \
                                                                    { \
                                                                        u32 ramptr  = get_pc() + WORD_SPAN; \
                                                                        opsize tmpsize = WORD; \
                                                                        \
                                                                        u32 disp = read_ram(&ramptr, &tmpsize); \
                                                                        \
                                                                        ptr = read_addrreg(addr) + disp; \
                                                                        dst = read_ram(&ptr, &size); \
                                                                        \
                                                                        set_pc(get_pc() + size_to_span(tmpsize)); \
                                                                        \
                                                                        break; \
                                                                    } \
                                                                    \
                                                                    default: \
                                                                    { \
                                                                        emulation->Machine.State = PANIC_STATE; \
                                                                        sprintf(emulation->Machine.Exception.panic_cause, "Addressing mode not handled! (read_EA)"); \
                                                                        return (RETURN_ERR); \
                                                                    } \
                                                                } \
                                                            }while (0);


#define WRITE_EFFECTIVE_ADDRESS(addr, val, size, mode)  do { \
                                                            u32 ptr; \
                                                            \
                                                            switch (mode) { \
                                                                case DATAReg: \
                                                                    write_datareg(addr, val, &size); \
                                                                    break; \
                                                                case ADDRReg: \
                                                                case IMMEDIATE: \
                                                                    write_addrreg(addr, val, &size); \
                                                                    break; \
                                                                case ADDRESS: \
                                                                case ADDRESSPostIncr: \
                                                                case ADDRESSPreDecr: \
                                                                    ptr = read_addrreg(addr); \
                                                                    if (addr == 7) {\
                                                                        switch (size) { \
                                                                            case BYTE: \
                                                                            case WORD: \
                                                                                push_word(val); \
                                                                                break; \
                                                                            case LONG: \
                                                                                push_long(val); \
                                                                                break; \
                                                                            default: \
                                                                                return (RETURN_ERR); \
                                                                        } \
                                                                    } \
                                                                    else { \
                                                                        switch (size) { \
                                                                            case BYTE: \
                                                                                write_byte(ptr, val); \
                                                                                break; \
                                                                            case WORD: \
                                                                                write_word(ptr, val); \
                                                                                break; \
                                                                            case LONG: \
                                                                                write_long(ptr, val); \
                                                                                break; \
                                                                            default: \
                                                                                return (RETURN_ERR); \
                                                                        } \
                                                                    } \
                                                                    break; \
                                                                    \
                                                                case ADDRESSDisp: \
                                                                { \
                                                                    u32 ramptr  = get_pc() + WORD_SPAN; \
                                                                    opsize tmpsize = WORD; \
                                                                    \
                                                                    u32 disp = read_ram(&ramptr, &tmpsize); \
                                                                    \
                                                                    ptr = read_addrreg(addr) + disp; \
                                                                    \
                                                                    switch (size) { \
                                                                        case BYTE: \
                                                                            write_byte(ptr, val); \
                                                                            break; \
                                                                        case WORD: \
                                                                            write_word(ptr, val); \
                                                                            break; \
                                                                        case LONG: \
                                                                            write_long(ptr, val); \
                                                                            break; \
                                                                        default: \
                                                                            return (RETURN_ERR); \
                                                                    } \
                                                                    set_pc(get_pc() + size_to_span(tmpsize)); \
                                                                    \
                                                                    break; \
                                                                } \
                                                                \
                                                                default: \
                                                                { \
                                                                    emulation->Machine.State = PANIC_STATE; \
                                                                    sprintf(emulation->Machine.Exception.panic_cause, "Writing an invalid Effective Address, %d!", mode); \
                                                                    return (RETURN_ERR); \
                                                                } \
                                                            } \
                                                        } while(0);


/**
 * @brief eval_OP_EA
 * @param code -> opcode
 * @return void ** array containing pointers to extracted parameters, if they exist, otherwise NULL
 */
#ifndef RESULT_ARRAY
#define RESULT_ARRAY 6
#endif

#define EVAL_OP_EFFECTIVE_ADDRESS(result_array, code, ignore_direction) do { \
                                                                            u32 __dst__, __src__; \
                                                                            \
                                                                            result_array = malloc(sizeof (void *) * RESULT_ARRAY); \
                                                                            \
                                                                            u32 *dst_reg   = malloc(sizeof (u32)); \
                                                                            u32 *src_reg   = NULL; \
                                                                            u32 *dVal      = malloc(sizeof (u32)); \
                                                                            u32 *sVal      = malloc(sizeof (u32)); \
                                                                            ea_direction  *direction = malloc(sizeof (ea_direction)); \
                                                                            opsize        *size      = malloc(sizeof (opsize)); \
                                                                            ADDRMode      *addr_mode = malloc(sizeof (ADDRMode)); \
                                                                            \
                                                                            bitmask dest_reg_mask  = 0b0000111000000000, \
                                                                                    direction_mask = 0b0000000100000000, \
                                                                                    size_mask      = 0b0000000011000000, \
                                                                                    addr_mask      = 0b0000000000111000, \
                                                                                    immediate      = 0b0000000000111100, \
                                                                                    src_reg_mask   = 0b0000000000000111; \
                                                                            \
                                                                            *dst_reg   = (code & dest_reg_mask)  >> 9; \
                                                                            *direction = (code & direction_mask) >> 8; \
                                                                            *size      = (code & size_mask)      >> 6; \
                                                                            \
                                                                            if ( (code & immediate) == IMMEDIATE ) \
                                                                                *addr_mode = IMMEDIATE; \
                                                                            else \
                                                                            { \
                                                                                *addr_mode = (code & addr_mask) >> 3; \
                                                                                src_reg = malloc(sizeof (u32)); \
                                                                                *src_reg = (u32) (code & src_reg_mask); \
                                                                            } \
                                                                            \
                                                                            if (ignore_direction == USE_DIRECTION) \
                                                                            { \
                                                                                if (*direction == INVERTED) \
                                                                                { \
                                                                                    /* SWAPPING dst-src*/ \
                                                                                    bit tmp; \
                                                                                    switch (*addr_mode) { \
                                                                                        case ADDRESS: \
                                                                                        case ADDRESSPostIncr: \
                                                                                        case ADDRESSPreDecr: \
                                                                                            tmp = *dst_reg; \
                                                                                            *dst_reg = *src_reg; \
                                                                                            *src_reg = tmp; \
                                                                                            break; \
                                                                                        default: \
                                                                                            break; \
                                                                                    } \
                                                                                } \
                                                                            } \
                                                                            else  /* invoke muls-mulu-divs-divu, size must be WORD, direction must be NORMAL*/ \
                                                                            { \
                                                                                *size      = WORD; \
                                                                                *direction = NORMAL; \
                                                                            } \
                                                                            \
                                                                            __src__ = (src_reg) ? *src_reg : (u32) (get_pc() + WORD_SPAN); \
                                                                            __dst__ = ((u32) *dst_reg); \
                                                                            \
                                                                            READ_EFFECTIVE_ADDRESS(*sVal, __src__, *size, *addr_mode, *direction); \
                                                                            \
                                                                            ea_direction tmp_dir = NORMAL; \
                                                                            \
                                                                            if (is_ram_op(addr_mode) || is_addr_to_data_op(addr_mode)) \
                                                                            { \
                                                                                tmp_dir = INVERTED; \
                                                                                READ_EFFECTIVE_ADDRESS(*dVal, __dst__, *size, DATAReg, tmp_dir); \
                                                                            } \
                                                                            else if (*direction == INVERTED) \
                                                                            { \
                                                                                READ_EFFECTIVE_ADDRESS(*dVal, __dst__, *size, *addr_mode, tmp_dir); \
                                                                            } \
                                                                            else \
                                                                            { \
                                                                                READ_EFFECTIVE_ADDRESS(*dVal, __dst__, *size, *addr_mode, *direction); \
                                                                            } \
                                                                            \
                                                                            result_array[0] = dst_reg; \
                                                                            result_array[1] = sVal; \
                                                                            result_array[2] = dVal; \
                                                                            result_array[3] = addr_mode; \
                                                                            result_array[4] = size; \
                                                                            result_array[5] = direction; \
                                                                            \
                                                                            if (src_reg) free(src_reg); \
                                                                            \
                                                                        } while (0);


#define FREE_EVLUATED_OP_ARRAY(array) do { \
                                        if (array) \
                                        { \
                                            if (array[0]) { free(array[0]); array[0] = NULL; } \
                                            if (array[1]) { free(array[1]); array[1] = NULL; } \
                                            if (array[2]) { free(array[2]); array[2] = NULL; } \
                                            if (array[3]) { free(array[3]); array[3] = NULL; } \
                                            if (array[4]) { free(array[4]); array[4] = NULL; } \
                                            if (array[5]) { free(array[5]); array[5] = NULL; } \
                                            \
                                            free(array); \
                                            \
                                            array = NULL; \
                                        } \
                                    } while(0);


#define SHOULD_INCR_PC(size, mode)  do{ \
                                        opsize tmpsize = size; \
                                        switch (mode) { \
                                            case IMMEDIATE: \
                                            { \
                                                if (tmpsize == BYTE) tmpsize = WORD; \
                                                set_pc(get_pc() + size_to_span(tmpsize)); \
                                                break; \
                                            } \
                                            case ADDRESSPostIncr: \
                                            case ADDRESSPreDecr: \
                                            {\
                                                set_pc(get_pc() + size_to_span(size)); \
                                                break; \
                                            } \
                                            default: \
                                                break; \
                                        } \
                                    } while(0);



// -------------------- BEGIN PROTS ------------------------ //

u32 most_significant_byte(opsize size);
u32 mask_by_opsize(opsize size);
u32 hash (const char* word);


/* IO EA */
u32 read_ram(u32* const restrict addr, opsize* const restrict size);

/* MISC */
sspan size_to_span(opsize size);
bit   is_ram_op(ADDRMode* const restrict mode);
bit   is_addr_to_data_op(ADDRMode* const restrict mode);


/* TRAP */
char* trap_code_toString(u32 trapcode);
void  iotask(struct EmulationMachine* restrict em);


/* EMULATION MACHINE */
void machine_waiter (struct EmulationMachine* restrict em);
void emit_sys_status(struct EmulationMachine* restrict em);
void emit_dump      (struct EmulationMachine* restrict em);
void emit_jio       (struct EmulationMachine* restrict em);
void emit_jconcat   (struct EmulationMachine* restrict em);

#endif // __UTILS_H__68000
