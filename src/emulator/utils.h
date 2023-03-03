#ifndef __UTILS_H__68000
#define __UTILS_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "ram.h"
#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>


void flush_InputBuffer(struct EmulationMachine* restrict emulator);
void init_InputBuffer(struct EmulationMachine* restrict emulator);

void InputBuffer_cwrite(struct EmulationMachine* restrict emulator, char _c);
void set_InputBuffer_enabled(struct EmulationMachine* restrict emulator, c_bool _bool);

u32   read_int_InputBuffer(struct EmulationMachine* restrict emulator);
char* read_str_InputBuffer(struct EmulationMachine* restrict emulator);


/*
 * MACRO used to raise a condition that blocks normal emulator flow,
 * like a ByteCode mistake loading.
 *
 * This will call exit()
 *
 */
#define EMULATOR_ERROR(fmt, ...) do {                                    \
                            emulator->Machine.State = MERR_STATE;                      \
                            printf("[\033[01m\033[91mEMULATOR ERROR\033[0m] ");            \
                            sprintf(emulator->Machine.RunTime.Exception.merr_cause, fmt, ##__VA_ARGS__); \
                            printf ("%s\n", emulator->Machine.RunTime.Exception.merr_cause);             \
                            fflush(stdout);                              \
                            emit_dump(emulator); \
                            destroy_codes(emulator);                             \
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
                                                                            dst = read_datareg(emulator, addr); \
                                                                            break; \
                                                                        \
                                                                        default: \
                                                                        {\
                                                                            emulator->Machine.State = PANIC_STATE; \
                                                                            sprintf(emulator->Machine.RunTime.Exception.panic_cause, "Addressing mode not handled! (read_EA)"); \
                                                                            return (RETURN_ERR); \
                                                                        }\
                                                                    } \
                                                                else switch (mode) { \
                                                                    case IMMEDIATE: \
                                                                        if (tmpsize == BYTE) tmpsize = WORD; /*byte can't read byte in ram*/ \
                                                                        dst = read_ram(emulator, &addr, &tmpsize); \
                                                                        break; \
                                                                    \
                                                                    case DATAReg: \
                                                                        dst = read_datareg(emulator, addr); \
                                                                        break; \
                                                                    \
                                                                    case ADDRReg: \
                                                                        dst = read_addrreg(emulator, addr); \
                                                                        break; \
                                                                    \
                                                                    case ADDRESS: \
                                                                        if (addr == 7) { \
                                                                            switch (size) { \
                                                                                case BYTE: \
                                                                                case WORD: \
                                                                                    dst = pop_word(emulator); \
                                                                                    break; \
                                                                                case LONG: \
                                                                                    dst = pop_long(emulator); \
                                                                                    break; \
                                                                                default: \
                                                                                    return (RETURN_ERR); \
                                                                            } \
                                                                        } \
                                                                        else { \
                                                                            ptr = read_addrreg(emulator, addr); \
                                                                            dst = read_ram(emulator, &ptr, &size); \
                                                                        } \
                                                                        break; \
                                                                    \
                                                                    case ADDRESSPostIncr: \
                                                                        if (addr == 7) { \
                                                                            switch (size) { \
                                                                                case BYTE: \
                                                                                case WORD: \
                                                                                    dst = pop_word(emulator); \
                                                                                    break; \
                                                                                case LONG: \
                                                                                    dst = pop_long(emulator); \
                                                                                    break; \
                                                                                default: \
                                                                                    return (RETURN_ERR); \
                                                                            } \
                                                                        } \
                                                                        else { \
                                                                            ptr = read_addrreg(emulator, addr); \
                                                                            dst = read_ram(emulator, &ptr, &size); \
                                                                        } \
                                                                        break; \
                                                                        /* incr_addr_reg(emulator, *addr, *size); */ \
                                                                        /*/ incr must be done after memory read! */ \
                                                                    \
                                                                    case ADDRESSPreDecr: \
                                                                        decr_addr_reg(emulator, addr, size); \
                                                                        if (addr == 7) { \
                                                                            switch (size) { \
                                                                                case BYTE: \
                                                                                case WORD: \
                                                                                    dst = pop_word(emulator); \
                                                                                    break; \
                                                                                case LONG: \
                                                                                    dst = pop_long(emulator); \
                                                                                    break; \
                                                                                default: \
                                                                                    return (RETURN_ERR); \
                                                                            } \
                                                                        } \
                                                                        else { \
                                                                            ptr = read_addrreg(emulator, addr); \
                                                                            dst = read_ram(emulator, &ptr, &size); \
                                                                        } \
                                                                        break; \
                                                                    \
                                                                    case ADDRESSDisp: \
                                                                    { \
                                                                        u32 ramptr  = get_pc(emulator) + WORD_SPAN; \
                                                                        opsize tmpsize = WORD; \
                                                                        \
                                                                        u32 disp = read_ram(emulator, &ramptr, &tmpsize); \
                                                                        \
                                                                        ptr = read_addrreg(emulator, addr) + disp; \
                                                                        dst = read_ram(emulator, &ptr, &size); \
                                                                        \
                                                                        set_pc(emulator, get_pc(emulator) + size_to_span(tmpsize)); \
                                                                        \
                                                                        break; \
                                                                    } \
                                                                    \
                                                                    default: \
                                                                    { \
                                                                        emulator->Machine.State = PANIC_STATE; \
                                                                        sprintf(emulator->Machine.RunTime.Exception.panic_cause, "Addressing mode not handled! (read_EA)"); \
                                                                        return (RETURN_ERR); \
                                                                    } \
                                                                } \
                                                            }while (0);


#define WRITE_EFFECTIVE_ADDRESS(addr, val, size, mode)  do { \
                                                            u32 ptr; \
                                                            \
                                                            switch (mode) { \
                                                                case DATAReg: \
                                                                    write_datareg(emulator, addr, val, &size); \
                                                                    break; \
                                                                case ADDRReg: \
                                                                case IMMEDIATE: \
                                                                    write_addrreg(emulator, addr, val, &size); \
                                                                    break; \
                                                                case ADDRESS: \
                                                                case ADDRESSPostIncr: \
                                                                case ADDRESSPreDecr: \
                                                                    ptr = read_addrreg(emulator, addr); \
                                                                    if (addr == 7) {\
                                                                        switch (size) { \
                                                                            case BYTE: \
                                                                            case WORD: \
                                                                                push_word(emulator, val); \
                                                                                break; \
                                                                            case LONG: \
                                                                                push_long(emulator, val); \
                                                                                break; \
                                                                            default: \
                                                                                return (RETURN_ERR); \
                                                                        } \
                                                                    } \
                                                                    else { \
                                                                        switch (size) { \
                                                                            case BYTE: \
                                                                                write_byte(emulator, ptr, val); \
                                                                                break; \
                                                                            case WORD: \
                                                                                write_word(emulator, ptr, val); \
                                                                                break; \
                                                                            case LONG: \
                                                                                write_long(emulator, ptr, val); \
                                                                                break; \
                                                                            default: \
                                                                                return (RETURN_ERR); \
                                                                        } \
                                                                    } \
                                                                    break; \
                                                                    \
                                                                case ADDRESSDisp: \
                                                                { \
                                                                    u32 ramptr  = get_pc(emulator) + WORD_SPAN; \
                                                                    opsize tmpsize = WORD; \
                                                                    \
                                                                    u32 disp = read_ram(emulator, &ramptr, &tmpsize); \
                                                                    \
                                                                    ptr = read_addrreg(emulator, addr) + disp; \
                                                                    \
                                                                    switch (size) { \
                                                                        case BYTE: \
                                                                            write_byte(emulator, ptr, val); \
                                                                            break; \
                                                                        case WORD: \
                                                                            write_word(emulator, ptr, val); \
                                                                            break; \
                                                                        case LONG: \
                                                                            write_long(emulator, ptr, val); \
                                                                            break; \
                                                                        default: \
                                                                            return (RETURN_ERR); \
                                                                    } \
                                                                    set_pc(emulator, get_pc(emulator) + size_to_span(tmpsize)); \
                                                                    \
                                                                    break; \
                                                                } \
                                                                \
                                                                default: \
                                                                { \
                                                                    emulator->Machine.State = PANIC_STATE; \
                                                                    sprintf(emulator->Machine.RunTime.Exception.panic_cause, "Writing an invalid Effective Address, %d!", mode); \
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
                                                                            __src__ = (src_reg) ? *src_reg : (u32) (get_pc(emulator) + WORD_SPAN); \
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
                                                set_pc(emulator, get_pc(emulator) + size_to_span(tmpsize)); \
                                                break; \
                                            } \
                                            case ADDRESSPostIncr: \
                                            case ADDRESSPreDecr: \
                                            {\
                                                set_pc(emulator, get_pc(emulator) + size_to_span(size)); \
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
u32 read_ram(struct EmulationMachine* restrict emulator, u32 *addr, opsize *size);

/* MISC */
sspan size_to_span(opsize size);
c_bool is_ram_op(ADDRMode *mode);
c_bool is_addr_to_data_op(ADDRMode *mode);


/* TRAP */
char* trap_code_toString(u32 trapcode);
c_bool iotask(struct EmulationMachine *emulator);


/* EMULATION MACHINE */
void emit_dump      (struct EmulationMachine *emulator);

#endif // __UTILS_H__68000
