#include "utils.h"

generic_u32_t most_significant_byte(opsize size)
{
    switch (size)
    {
        case BYTE:
            return 0x00000080;

        case WORD:
            return 0x00008000;

        case LONG:
            return 0x80000000;

        default:
            return 0x00000000;
    }
}


generic_u32_t mask_by_opsize(opsize size)
{
    switch (size)
    {
        case BYTE:
            return 0x000000FF;

        case WORD:
            return 0x0000FFFF;

        case LONG:
            return 0xFFFFFFFF;

        default:
            return 0x00000000;
    }
}


generic_u32_t hash (const char* word)
{
    generic_u32_t hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
        hash = (31 * hash) + word[i];

    return hash;
}


generic_32_t sign_extended(generic_u32_t val, opsize size)
{
    int newValue = (int) val;
    switch (size)
    {
        case BYTE:
            if ((val & 0x80) == 0x80)
                newValue = (int)(newValue | 0xFFFFFF00);
            else
                newValue &= 0x000000ff;
            break;
        case WORD:
            if ((val & 0x8000) == 0x8000)
                newValue = (int)(newValue | 0xFFFF0000);
            else
                newValue &= 0x0000ffff;
            break;
        case LONG:
            break;
        default:
            break;

    }

    return newValue;
}



/**
 * @brief eval_OP_EA
 * @param code -> opcode
 * @return void ** array containing pointers to extracted parameters, if they exist, otherwise NULL
 */
void** eval_OP_EA(opcode code, bit ignore_direction)
{
#ifndef RESULT_ARRAY
#define RESULT_ARRAY 6
#else
#undef  RESULT_ARRAY
#define RESULT_ARRAY 6
#endif
    generic_u32_t __dst__, __src__;

    void **result_array = malloc(sizeof (void *) * RESULT_ARRAY);

    generic_u32_t *dst_reg   = malloc(sizeof (generic_u32_t));
    generic_u32_t *src_reg   = NULL;
    generic_u32_t *dVal      = malloc(sizeof (generic_u32_t));
    generic_u32_t *sVal      = malloc(sizeof (generic_u32_t));
    ea_direction  *direction = malloc(sizeof (ea_direction));
    opsize        *size      = malloc(sizeof (opsize));
    ADDRMode      *addr_mode = malloc(sizeof (ADDRMode));


    bitmask dest_reg_mask  = 0b0000111000000000,
            direction_mask = 0b0000000100000000,
            size_mask      = 0b0000000011000000,
            addr_mask      = 0b0000000000111000,
            immediate      = 0b0000000000111100,
            src_reg_mask   = 0b0000000000000111;


    *dst_reg   = (code & dest_reg_mask)  >> 9;
    *direction = (code & direction_mask) >> 8;
    *size      = (code & size_mask)      >> 6;


    if ( (code & immediate) == IMMEDIATE )
        *addr_mode = IMMEDIATE;
    else
    {
        *addr_mode = (code & addr_mask) >> 3;
         src_reg = malloc(sizeof (generic_u32_t));
        *src_reg = (generic_u32_t) (code & src_reg_mask);
    }

    if (ignore_direction == USE_DIRECTION)
    {
        if (*direction == INVERTED)
        {
            // SWAPPING dst-src
            bit tmp;
            switch (*addr_mode) {
                case ADDRESS:
                case ADDRESSPostIncr:
                case ADDRESSPreDecr:
                    tmp = *dst_reg;
                    *dst_reg = *src_reg;
                    *src_reg = tmp;
                    break;
                default:
                    break;
            }
        }
    }
    else  // invoke muls-mulu-divs-divu, size must be WORD, direction must be NORMAL
    {
        *size      = WORD;
        *direction = NORMAL;
    }

    __src__ = (src_reg) ? *src_reg : (generic_u32_t) (get_pc() + WORD_SPAN);
    __dst__ = ((generic_u32_t) *dst_reg);

    *sVal = read_EA(&__src__, size, addr_mode, direction);

    ea_direction tmp_dir = NORMAL;

    if (is_ram_op(addr_mode) || is_addr_to_data_op(addr_mode))
    {
        tmp_dir = INVERTED;
        ADDRMode tmp_mode = DATAReg;
        *dVal = read_EA(&__dst__, size, &tmp_mode, &tmp_dir);
    }
    else if (*direction == INVERTED)
    {
        *dVal = read_EA(&__dst__, size, addr_mode, &tmp_dir);
    }
    else
    {
        *dVal = read_EA(&__dst__, size, addr_mode, direction);
    }

    result_array[0] = dst_reg;
    result_array[1] = sVal;
    result_array[2] = dVal;
    result_array[3] = addr_mode;
    result_array[4] = size;
    result_array[5] = direction;

    if (src_reg) free(src_reg);

    return result_array;
}


void free_eval_OP_EA_array(void** array)
{
    if (array)
    {
        if (array[0]) { free(array[0]); array[0] = NULL; }
        if (array[1]) { free(array[1]); array[1] = NULL; }
        if (array[2]) { free(array[2]); array[2] = NULL; }
        if (array[3]) { free(array[3]); array[3] = NULL; }
        if (array[4]) { free(array[4]); array[4] = NULL; }
        if (array[5]) { free(array[5]); array[5] = NULL; }

        free(array);

        array = NULL;
    }
}





/* IO EA */
generic_u32_t read_ram(generic_u32_t *addr, opsize *size)
{
    switch (*size) {
        case BYTE:
            return (generic_u32_t) read_byte(*addr);
        case WORD:
            return (generic_u32_t) read_word(*addr);
        default: //LONG
            return read_long(*addr);
    }
}



generic_u32_t read_EA(generic_u32_t *addr, opsize *size, ADDRMode *mode, ea_direction *dir)
{
    generic_u32_t val;
    generic_u32_t ptr;
    opsize        tmpsize = *size;

    if (*dir == INVERTED)
        switch (*mode) {
            case DATAReg:
            case ADDRReg:
            case ADDRESS:
            case ADDRESSPostIncr:
            case ADDRESSPreDecr:
                val = read_datareg(*addr);
                break;

            default:
                { PANIC("PANIC!, addressing mode not handled bla bla!\n") }
                break;
        }
    else switch (*mode) {
        case IMMEDIATE:
            if (tmpsize == BYTE) tmpsize = WORD; //byte can't read byte in ram
            val = read_ram(addr, &tmpsize);
            break;

        case DATAReg:
            val = read_datareg(*addr);
            break;

        case ADDRReg:
            val = read_addrreg(*addr);
            break;

        case ADDRESS:
            ptr = read_addrreg(*addr);
            val = read_ram(&ptr, size);
            break;

        case ADDRESSPostIncr:
            ptr = read_addrreg(*addr);
            val = read_ram(&ptr, size);
            // incr_addr_reg(*addr, *size);
            // incr must be done after memory read!
            break;

        case ADDRESSPreDecr:
            decr_addr_reg(*addr, *size);
            ptr = read_addrreg(*addr);
            val = read_ram(&ptr, size);
            break;

        default:
            { PANIC("PANIC!, addressing mode not handled!\n") }
            break;
    }

    return val;
}


void write_EA(generic_u32_t *addr, generic_u32_t val, opsize *size, ADDRMode *mode)
{
    generic_u32_t ptr;

    switch (*mode) {
        case DATAReg:
            write_datareg(*addr, val, size);
            break;
        case ADDRReg:
        case IMMEDIATE:
            write_addrreg(*addr, val, size);
            break;
        case ADDRESS:
        case ADDRESSPostIncr:
        case ADDRESSPreDecr:
            ptr = read_addrreg(*addr);

            switch (*size) {
                case BYTE:
                    write_byte(ptr, val);
                    break;
                case WORD:
                    write_word(ptr, val);
                    break;
                case LONG:
                    write_long(ptr, val);
                    break;
                default:
                    break;
            }

            break;

        default:
            { PANIC("PANIC!, writing an invalid Effective Address!\n") }
            break;
    }
}


void should_incr_pc(opsize *size, ADDRMode *mode)
{
    opsize tmpsize = *size;

    switch (*mode) {
        case IMMEDIATE:
            if (tmpsize == BYTE) tmpsize = WORD;
            incr_pc(size_to_span(tmpsize));
            break;
        case ADDRESSPostIncr:
        case ADDRESSPreDecr:
            incr_pc(size_to_span(*size));
            break;

        default:
            break;
    }
}




/* MISC */
opsize_span size_to_span(opsize size)
{
    switch (size) {
        case BYTE:
            return BYTE_SPAN;
        case WORD:
            return WORD_SPAN;
        default:
            return LONG_SPAN;
    }
}

bit is_ram_op(ADDRMode *mode)
{
    switch (*mode)
    {
        case ADDRESS:
        case ADDRESSPostIncr:
        case ADDRESSPreDecr:
        case IMMEDIATE:
            return 1;
        default:
            return 0;
    }
}


bit is_addr_to_data_op(ADDRMode *mode)
{
    switch (*mode)
    {
        case ADDRReg:
            return 1;
        default:
            return 0;
    }
}



/* TRAP */
char* trap_code_toString(generic_u32_t trapcode)
{
    switch (trapcode) {
        case BusError:
            return "BusError";
        case AddressError:
            return "AddressError";
        case IllegalInstruction:
            return "IllegalInstruction";
        case DivideByZero:
            return "DivideByZero";
        case CHKInstruction:
            return "CHKInstruction";
        case TRAPVInstruction:
            return "TRAPVInstruction";
        case PrivilegeViolation:
            return "PrivilegeViolation";
        default:
            return "CustomException";
    }
}
