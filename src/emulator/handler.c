#include "handler.h"

#include <stdlib.h>
#include <unistd.h>


// custom traps
#define TRAP_PRINT 0xF
#define TRAP_SCAN  0xE
#define TRAP_SLEEP 0xD


//handler return types
#define RETURN_OK_PC_NO_INCR 2
#define RETURN_OK            1
#define RETURN_ERR           0


//dumbest way to unmark func param as unused
#define UNUSED(x) (void)(x);


//opcode werehouse utils
#define INSTRUCTION_SET_GROUPS_COUNT 14
#define GROUP_0x00_LEN  21
#define GROUP_0x01_LEN  1
#define GROUP_0x02_LEN  2
#define GROUP_0x03_LEN  2
#define GROUP_0x04_LEN  30
#define GROUP_0x05_LEN  4
#define GROUP_0x06_LEN  3
#define GROUP_0x07_LEN  1
#define GROUP_0x08_LEN  4
#define GROUP_0x09_LEN  3
#define GROUP_0x0B_LEN 4
#define GROUP_0x0C_LEN 5
#define GROUP_0x0D_LEN 3
#define GROUP_0x0E_LEN 16


#define SET_NEGATIVE(bit) do { \
                            if (bit) \
                                emulator->Machine.cpu.sr |= NEGATIVE; \
                            else \
                                emulator->Machine.cpu.sr &= ~NEGATIVE; \
                          } while(0);

#define SET_ZERO(bit) do { \
                        if (bit) \
                            emulator->Machine.cpu.sr |= ZERO; \
                        else \
                            emulator->Machine.cpu.sr &= ~ZERO; \
                      } while(0);

#define SET_OVERFLOW(bit) do { \
                            if (bit) \
                                emulator->Machine.cpu.sr |= OVERFLOW; \
                            else \
                                emulator->Machine.cpu.sr &= ~OVERFLOW; \
                          } while(0);


#define SET_CARRY(bit) do { \
                          if (bit) \
                              emulator->Machine.cpu.sr |= CARRY; \
                          else \
                              emulator->Machine.cpu.sr &= ~CARRY; \
                       } while(0);

#define SET_EXTENDED(bit) do{ \
                              if (bit) \
                                  emulator->Machine.cpu.sr |= EXTEND; \
                              else \
                                  emulator->Machine.cpu.sr &= ~EXTEND; \
                          } while(0);



#define INCR_PC(bits) emulator->Machine.cpu.pc += bits



/*
 * DYNAMIC SETTER FOR SR
 *
 */
#define SET_SRFLAGS(mnemonic, size, src, dst, res) do { \
                                                        const u32 msb  = most_significant_byte(size);  \
                                                        const u32 mask = mask_by_opsize(size);  \
                                                        const bit srcMSB = (src & msb) != 0;  \
                                                        const bit dstMSB = (dst & msb) != 0;  \
                                                        const bit resMSB = (res & msb) != 0;  \
                                                        \
                                                        switch (mnemonic)  \
                                                        {  \
                                                            case ori:  \
                                                            case andi:  \
                                                            case eori:  \
                                                            case move_op:  \
                                                            case moveq:  \
                                                            case divu:  \
                                                            case divs:  \
                                                            case _or:  \
                                                            case eor:  \
                                                            case mulu:  \
                                                            case muls:  \
                                                            case _and:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_OVERFLOW(0);  \
                                                                SET_CARRY(0);  \
                                                                break;  \
                                                            case subi:  \
                                                            case subq:  \
                                                            case sub:  \
                                                            case subx:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_OVERFLOW((srcMSB == resMSB) && (dstMSB != resMSB));  \
                                                                SET_CARRY((srcMSB && resMSB) || (srcMSB && !dstMSB) || (!dstMSB && resMSB));  \
                                                                SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                break;  \
                                                            case addi:  \
                                                            case addq:  \
                                                            case add:  \
                                                            case addx:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_OVERFLOW((srcMSB == dstMSB) && (srcMSB != resMSB));  \
                                                                SET_CARRY((srcMSB && !resMSB) || (srcMSB && dstMSB) || (dstMSB && !resMSB));  \
                                                                SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                break;  \
                                                            case cmpi:  \
                                                            case cmpm:  \
                                                            case _cmp:  \
                                                            case cmpa:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_OVERFLOW((srcMSB == resMSB) && (dstMSB != resMSB));  \
                                                                SET_CARRY((srcMSB && resMSB) || (srcMSB && !dstMSB) || (!dstMSB && resMSB));  \
                                                                break;  \
                                                            case negx:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_OVERFLOW(srcMSB && resMSB);  \
                                                                SET_CARRY(srcMSB || resMSB);  \
                                                                SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                break;  \
                                                            case neg:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_OVERFLOW(srcMSB && resMSB);  \
                                                                SET_CARRY((res & mask) != 0);  \
                                                                SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                break;  \
                                                            case _not:  \
                                                            case ext:  \
                                                            case _swap:  \
                                                            case tst:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_CARRY(0);  \
                                                                SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                break;  \
                                                            case asl:  \
                                                            case asr:  \
                                                            case lsl:  \
                                                            case lsr:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                if (src != 0)  \
                                                                {  \
                                                                    SET_CARRY(dst != 0);  \
                                                                    SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                }  \
                                                                else SET_CARRY(0);  \
                                                                break;  \
                                                            case rol:  \
                                                            case ror:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                SET_CARRY(src != 0 && dst != 0);  \
                                                                SET_OVERFLOW(0);  \
                                                                break;  \
                                                            case roxl:  \
                                                            case roxr:  \
                                                                SET_NEGATIVE(resMSB);  \
                                                                SET_ZERO((res & mask) == 0);  \
                                                                if (src != 0)  \
                                                                {  \
                                                                    SET_CARRY(dst != 0);  \
                                                                    SET_EXTENDED(emulator->Machine.cpu.sr & CARRY);  \
                                                                }  \
                                                                else SET_CARRY(0);  \
                                                                \
                                                                SET_OVERFLOW(0);  \
                                                                break;  \
                                                            case clr:  \
                                                                SET_NEGATIVE(0);  \
                                                                SET_OVERFLOW(0);  \
                                                                SET_CARRY(0);  \
                                                                SET_ZERO(1);  \
                                                            default:  \
                                                                break;  \
                                                            \
                                                        }\
                                                    } while(0);

/*
 *
 * OPS IMPL
 *
 */

// GROUP 0x00
u32 ORItoCCR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    u32 addr = (u32) (emulator->Machine.cpu.pc + WORD_SPAN);
    u8 bits  = read_byte(emulator, addr);
    srflags flags = emulator->Machine.cpu.sr;

    emulator->Machine.cpu.sr = (flags | bits);

    INCR_PC(BYTE_SPAN);

    return (RETURN_OK);
}


u32 ORItoSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    u32 addr = (u32) (emulator->Machine.cpu.pc + WORD_SPAN);
    u16 bits = read_word(emulator, addr);
    srflags flags = emulator->Machine.cpu.sr;

    emulator->Machine.cpu.sr = (flags | bits);

    INCR_PC(BYTE_SPAN);

    return (RETURN_OK);
}


u32 ORI(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 value;
    READ_EFFECTIVE_ADDRESS(value, dst, size, mode, NORMAL);
    u32 addr     = emulator->Machine.cpu.pc + WORD_SPAN;
    u32 ori_mask = read_ram(emulator, &addr, &size);

    value |= ori_mask;

    WRITE_EFFECTIVE_ADDRESS(dst, value, size, mode);

    SET_SRFLAGS(ori, size, 0, 0, value);

    INCR_PC(size_to_span(size));

    return (RETURN_OK);
}


u32 ANDItoCCR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    u32 addr = (u32) (emulator->Machine.cpu.pc + WORD_SPAN);
    u16 bits = (u16) (read_byte(emulator, addr) & 0x001F) | 0xFFE0;
    srflags flags = emulator->Machine.cpu.sr;

    emulator->Machine.cpu.sr = (flags & bits);

    INCR_PC(BYTE_SPAN);

    return (RETURN_OK);
}


u32 ANDItoSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    u32 addr = (u32) (emulator->Machine.cpu.pc + WORD_SPAN);
    u16 bits = read_word(emulator, addr);
    srflags flags = emulator->Machine.cpu.sr;

    emulator->Machine.cpu.sr = (flags | bits);

    INCR_PC(BYTE_SPAN);

    return (RETURN_OK);
}


u32 ANDI(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 value;
    READ_EFFECTIVE_ADDRESS(value, dst, size, mode, NORMAL);
    u32 addr      = emulator->Machine.cpu.pc + WORD_SPAN;
    u32 andi_mask = read_ram(emulator, &addr, &size);

    switch (size) {
        case BYTE:
            andi_mask |= 0xFFFFFF00;
            break;
        case WORD:
            andi_mask |= 0xFFFF0000;
            break;
        default:
            break;
    }

    value |= andi_mask;

    WRITE_EFFECTIVE_ADDRESS(dst, value, size, mode);
    SET_SRFLAGS(andi, size, 0, 0, value);

    INCR_PC(size_to_span(size));

    return (RETURN_OK);
}


u32 SUBI(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    opsize size = (code & SIZE_MASK) >> 6;
    opsize tmps = size;

    if (size == BYTE)
        tmps = WORD;

    u32 ramptr = emulator->Machine.cpu.pc + WORD_SPAN;
    u32 sVal   = read_ram(emulator, &ramptr, &tmps);
    u32 dVal;

    u32 dReg = (code & 0x0007);
    ADDRMode      mode = (code & 0x0038) >> 3;

    READ_EFFECTIVE_ADDRESS(dVal, dReg, size, mode, NORMAL);

    s32 res, ssVal, sdVal;

    SIGN_EXTENDED(ssVal, sVal, size);
    SIGN_EXTENDED(sdVal, dVal, size);

    res = sdVal - ssVal;

    WRITE_EFFECTIVE_ADDRESS(dReg, (u32) res, size, mode);

    SET_SRFLAGS(subi, size, sVal, dVal, (u32) res);

    INCR_PC(size_to_span(tmps));

    return (RETURN_OK);
}


u32 ADDI(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    opsize size = (code & SIZE_MASK) >> 6;
    opsize tmps = size;

    if (size == BYTE)
        tmps = WORD;

    u32 ramptr = emulator->Machine.cpu.pc + WORD_SPAN;
    u32 sVal   = read_ram(emulator, &ramptr, &tmps);
    u32 dVal;

    u32 dReg = (code & 0x0007);
    ADDRMode mode = (code & 0x0038) >> 3;

    READ_EFFECTIVE_ADDRESS(dVal, dReg, size, mode, NORMAL);

    s32 res, ssVal, sdVal;

    SIGN_EXTENDED(ssVal, sVal, size);
    SIGN_EXTENDED(sdVal, dVal, size);

    res = sdVal + ssVal;

    WRITE_EFFECTIVE_ADDRESS(dReg, (u32) res, size, mode);

    SET_SRFLAGS(addi, size, sVal, dVal, (u32) res);

    INCR_PC(size_to_span(tmps));

    return (RETURN_OK);
}


u32 EORItoCCR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    u32 addr = (u32) (emulator->Machine.cpu.pc + WORD_SPAN);
    u16 bits = (u16) (read_byte(emulator, addr) & 0x001F) | 0xFFE0;
    srflags flags = emulator->Machine.cpu.sr;

    emulator->Machine.cpu.sr = (flags ^ bits);

    INCR_PC(BYTE_SPAN);

    return (RETURN_OK);
}


u32 EORItoSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    u32 addr = (u32) (emulator->Machine.cpu.pc + WORD_SPAN);
    u16 bits = read_word(emulator, addr);
    srflags flags = emulator->Machine.cpu.sr;

    emulator->Machine.cpu.sr = (flags ^ bits);

    INCR_PC(BYTE_SPAN);

    return (RETURN_OK);
}


u32 EORI(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 value;
    READ_EFFECTIVE_ADDRESS(value, dst, size, mode, NORMAL);

    u32 addr      = emulator->Machine.cpu.pc + WORD_SPAN;
    u32 eori_mask = read_ram(emulator, &addr, &size);

    value ^= eori_mask;

    WRITE_EFFECTIVE_ADDRESS(dst, value, size, mode);
    SET_SRFLAGS(eori, size, 0, 0, value);

    INCR_PC(size_to_span(size));

    return (RETURN_OK);
}


u32 CMPI(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    opsize tmpsize = size;

    if (tmpsize == BYTE) tmpsize = WORD;

    s32 dst_val, ram_val;
    u32 val;
    READ_EFFECTIVE_ADDRESS(val, dst, size, mode, NORMAL);

    SIGN_EXTENDED(dst_val, val, size);
    u32 addr    = emulator->Machine.cpu.pc + WORD_SPAN;
    SIGN_EXTENDED(ram_val, read_ram(emulator, &addr, &tmpsize), size);

    s32 value = dst_val - ram_val;

    SET_SRFLAGS(cmpi, size, (u32) ram_val, (u32) dst_val, (u32) value);

    INCR_PC(size_to_span(tmpsize));

    return (RETURN_OK);
}


u32 MOVEP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 

    emulator->Machine.State = WARNING_STATE;
    
    sprintf(emulator->Machine.Warning.cause, "%s", "Unmenaged operation");
    emulator->Machine.Warning.code = code;
    sprintf(emulator->Machine.Warning.mnem, "%s", "MOVEP");

    return (RETURN_OK);
}


u32 BTST(struct EmulationMachine* emulator)
{
    return Bxxx(emulator);
}


u32 BCHG(struct EmulationMachine* emulator)
{
    return Bxxx(emulator);
}


u32 BCLR(struct EmulationMachine* emulator)
{
    return Bxxx(emulator);
}


u32 BSET(struct EmulationMachine* emulator)
{
    return Bxxx(emulator);
}




// GROUP 0x01
u32 MOVE(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst_reg,  src_reg;
    u32 dst_mode, src_mode;
    u32 rVal;
    opsize size;

    dst_reg  = (code & DST_MASK) >> 9;
    dst_mode = (code & 0b0000000111000000) >> 6;
    size     = (code & 0b0011000000000000) >> 12;

    if (size == WORD2)      size = WORD;
    else if (size == BYTE2) size = BYTE;

    if ((code & ADDRMODE_MASK) == IMMEDIATE) // move.s #<val>,Rd
    {
        opsize tmpsize = size;
        opsize ramrsize = tmpsize == BYTE ? WORD : tmpsize;    

        u32 ram_ptr = emulator->Machine.cpu.pc + WORD_SPAN;
        rVal = read_ram(emulator, &ram_ptr, &ramrsize);

        if (dst_mode == ADDRESSPreDecr)  decr_addr_reg(emulator, dst_reg, size);

        WRITE_EFFECTIVE_ADDRESS(dst_reg, rVal, tmpsize, dst_mode);

        if (dst_mode == ADDRESSPostIncr) incr_addr_reg(emulator, dst_reg, size);

        SET_SRFLAGS(move_op, size, 0, 0, rVal);

        INCR_PC(size_to_span(tmpsize == BYTE ? WORD : tmpsize));
    }
    else                                    // everything else
    {
        src_reg  = (code & SRC_MASK);
        src_mode = (code & 0b0000000000111000) >> 3; //src_mode

        READ_EFFECTIVE_ADDRESS(rVal, src_reg, size, src_mode, NORMAL);

        if (src_mode == ADDRESSPostIncr) incr_addr_reg(emulator, src_reg, size);
        if (dst_mode == ADDRESSPreDecr)  decr_addr_reg(emulator, dst_reg, size);

        WRITE_EFFECTIVE_ADDRESS(dst_reg, rVal, size, dst_mode);

        if (dst_mode == ADDRESSPostIncr) incr_addr_reg(emulator, dst_reg, size);

        SET_SRFLAGS(move_op, size, 0, 0, rVal);
    }

    return (RETURN_OK);
}




// GROUP 0x02-0x03
u32 MOVEA(struct EmulationMachine* emulator)
{
    /* hack:
         call 'move' with dst_mode as 001 aka ADDRReg.
         for sure this code will go into the 'move' proc's if-true-branch
    */

    return MOVE(emulator);
}




// group 0X04
u32 MOVEfromSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;

    u32 dst  = (u32) (code & dst_mask);
    ADDRMode mode = (code & mode_mask) >> 3;

    srflags flags = emulator->Machine.cpu.sr;
    opsize  size  = WORD;

    WRITE_EFFECTIVE_ADDRESS(dst, flags, size, mode);

    return (RETURN_OK);
}


u32 MOVEtoCCR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;

    u32 src  = (u32) (code & dst_mask);
    ADDRMode mode = (code & mode_mask) >> 3;

    srflags flags = emulator->Machine.cpu.sr;

    switch (mode) {
        case DATAReg:
            flags = (srflags) (read_addrreg(emulator, src) | 0xFFE0);
            break;
        default:
            break;
    }

    emulator->Machine.cpu.sr = (flags);

    return (RETURN_OK);
}


u32 MOVEtoSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;

    u32 src  = (u32) (code & dst_mask);
    ADDRMode mode = (code & mode_mask) >> 3;

    srflags flags = emulator->Machine.cpu.sr;

    switch (mode) {
        case DATAReg:
            flags = read_addrreg(emulator, src);
            break;
        default:
            break;
    }

    emulator->Machine.cpu.sr = (flags);

    return (RETURN_OK);
}


u32 NEGX(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 src_value;
    READ_EFFECTIVE_ADDRESS(src_value, dst, size, mode, NORMAL);

    s32  signValue;
    SIGN_EXTENDED(signValue, src_value, size);

    s32 result = 0 - (signValue + ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0));

    WRITE_EFFECTIVE_ADDRESS(dst, (u32) result, size, mode);

    SET_SRFLAGS(negx, size, src_value, 0, (u32) result);

    return (RETURN_OK);
}


u32 CLR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 reg  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 value;
    READ_EFFECTIVE_ADDRESS(value, reg, size, mode, NORMAL);

    switch (size) {
        case BYTE:
            value = value & 0xFFFFFF00;
            break;
        case WORD:
            value = value & 0xFFFF0000;
            break;
        case LONG:
            value = 0x00000000;
            break;
        default:
            break;
    }

    WRITE_EFFECTIVE_ADDRESS(reg, value, size, mode);

    SET_SRFLAGS(clr, size, 0, 0, 0);

    return (RETURN_OK);
}


u32 NEG(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 src_value;
    READ_EFFECTIVE_ADDRESS(src_value, dst, size, mode, NORMAL);

    s32  signValue;
    SIGN_EXTENDED(signValue, src_value, size);

    s32 result = 0 - signValue;

    WRITE_EFFECTIVE_ADDRESS(dst, (u32) result, size, mode);

    SET_SRFLAGS(neg, size, src_value, 0, (u32) result);

    return (RETURN_OK);
}


u32 NOT(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    u32 src_value;
    READ_EFFECTIVE_ADDRESS(src_value, dst, size, mode, NORMAL);

    s32  signValue;
    SIGN_EXTENDED(signValue, src_value, size);

    s32 result = ~signValue;

    WRITE_EFFECTIVE_ADDRESS(dst, (u32) result, size, mode);

    SET_SRFLAGS(_not, size, src_value, 0, (u32) result);

    return (RETURN_OK);
}


u32 EXT(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32  regptr = (code & 0x0007);
    opsize size = (code & 0x0040) == 0 ? WORD : LONG;

    u32 value = read_addrreg(emulator, regptr);

    s32 extval;
    SIGN_EXTENDED(extval, value, size == WORD ? BYTE : WORD);

    write_datareg(emulator, regptr, (u32) extval, &size);

    SET_SRFLAGS(ext, size, 0, 0, (u32) extval);

    return (RETURN_OK);
}


u32 NBCD(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    s32 lo_val, hi_val;
    bit carry;

    u32 dst = (code & SRC_MASK);
    opsize   size = BYTE;
    ADDRMode mode = (code & 0b0000000000111000) >> 3;

    u32 val;
    READ_EFFECTIVE_ADDRESS(val, dst, size, mode, NORMAL);

    lo_val = 10 - (val & 0x0000000F) - ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0);
    carry = lo_val < 10;

    if (lo_val >= 10)
        lo_val = 0;

    hi_val = 10 - ((val >> 4) & 0x0000000F) - (carry ? 1 : 0);
    carry = hi_val < 10;

    if (hi_val >= 10)
        hi_val = 0;

    s32 result = (hi_val << 4) + lo_val;

    WRITE_EFFECTIVE_ADDRESS(dst, (u32)(val & 0x000000FF), size, mode);

    SET_CARRY(carry);
    SET_EXTENDED(carry);

    if (result != 0)
        SET_ZERO(0);

    return (RETURN_OK);
}


u32 SWAP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask reg_mask = 0b0000000000000111;

    u32 val = read_addrreg(emulator, code & reg_mask);
    val = (val >> 16) | ((val & 0x0000FFFF) << 16);

    write_datareg(emulator, code & reg_mask, val, NULL);
    SET_SRFLAGS(_swap, LONG, 0, 0, val);

    return (RETURN_OK);
}


u32 PEA(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    ADDRMode mode = (code & 0b0000000000111000) >> 3;

    if (mode == ADDRESS || mode == ADDRESSDisp)
    {
        u32 addr_reg = (code & SRC_MASK);
        opsize size = LONG;

        u32 value;
        READ_EFFECTIVE_ADDRESS(value, addr_reg, size, mode, NORMAL);

        push_long(emulator, value);
    }

    return 0;
}


u32 ILLEGAL(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    emulator->Machine.State = TRAP_STATE;
    sprintf(emulator->Machine.Exception.trap_cause,
            "Raised trap exception: Code: %d, Mnemonic: %s",
            IllegalInstruction, trap_code_toString(IllegalInstruction));

    return (RETURN_ERR);
}


u32 TAS(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 

    emulator->Machine.State = WARNING_STATE;
    
    sprintf(emulator->Machine.Warning.cause, "%s", "Unmenaged operation");
    emulator->Machine.Warning.code = code;
    sprintf(emulator->Machine.Warning.mnem, "%s", "TAS");

    return (RETURN_OK);
}


u32 TST(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;
    bitmask size_mask = 0b0000000011000000;

    opsize   size = (opsize) (code & size_mask);
    ADDRMode mode = (code & mode_mask) >> 3;
    u32 src  = (u32) (code & dst_mask);

    u32 val;

    switch (mode) {
        case DATAReg:
            val = read_addrreg(emulator, src);
            break;
        case ADDRESSPostIncr:
            val = read_addrreg(emulator, src);
            incr_addr_reg(emulator, src, size);
            break;
        case ADDRESSPreDecr:
            decr_addr_reg(emulator, src, size);
            val = read_addrreg(emulator, src);
            break;
        default:
            return (RETURN_ERR);
    }

    SET_SRFLAGS(tst, size, 0, 0, val);

    return (RETURN_OK);
}


u32 TRAP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u16 vector = (u16)(code & 0x0000000F);

    emulator->Machine.IO.Type = IO_UNDEF;

    switch (vector)
    {
        case TRAP_PRINT:
        {
            emulator->Machine.IO.Type = OUTPUT;
            emulator->Machine.State   = IO_STATE;

            return iotask(emulator);
        }

        case TRAP_SCAN:
        {
            emulator->Machine.IO.Type = INPUT;
            emulator->Machine.State   = IO_STATE;

            return iotask(emulator);
        }

        case TRAP_SLEEP:
        {
            u32 time, mult;

            emulator->Machine.State = SLEEP_STATE;

            time = read_datareg(emulator, 0);
            mult = read_datareg(emulator, 1);

            if (mult == 0) mult = 1;

            if (time != 0)
                while (mult--)
                    usleep(time);

            return (RETURN_OK);
        }

        default:
        {
            emulator->Machine.State   = TRAP_STATE;

            sprintf(emulator->Machine.Exception.trap_cause,
                    "Raised trap exception: Code: %d, Mnemonic: %s",
                    0x20 + vector, trap_code_toString(0x20 + vector));
        }
    }

    return (RETURN_ERR);
}


u32 LINK(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask reg_mask = 0b0000000000000111;

    u32 reg = code & reg_mask;
    s16 val;

    SIGN_EXTENDED(val, read_word(emulator, emulator->Machine.cpu.pc + WORD_SPAN), WORD);
    u32 rVal = read_addrreg(emulator, reg);

    push_long(emulator, rVal);

    u32 sp = ((emulator->Machine.cpu.sr & SUPERVISOR) ? 1 : 0) ? emulator->Machine.cpu.ssp : emulator->Machine.cpu.usp;

    write_addrreg(emulator, reg, sp, NULL);

    write_addrreg(emulator, 7, (u32)((s32) sp + val), NULL);

    INCR_PC(WORD_SPAN); // 2B for word read

    return (RETURN_OK);
}


u32 UNLK(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bitmask reg_mask = 0b0000000000000111;
    u32 reg = code & reg_mask;

    write_addrreg(emulator, 7,   read_addrreg(emulator, reg), NULL);
    write_addrreg(emulator, reg, pop_long(emulator), NULL);

    return (RETURN_OK);
}


u32 MOVEUSP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    if (!((emulator->Machine.cpu.sr & SUPERVISOR) ? 1 : 0))
    {
        emulator->Machine.State = TRAP_STATE;
        sprintf(emulator->Machine.Exception.trap_cause,
                "Raised trap exception: Code: %d, Mnemonic: %s",
                PrivilegeViolation, trap_code_toString(PrivilegeViolation));

        return (RETURN_ERR);
    }

    u32 addr_reg  = (code & SRC_MASK);
    u32 direction = (code & 0b00000000000001000) >> 3;


    if (direction == MEMORY_REGISTER)
    {
        emulator->Machine.cpu.usp = (read_addrreg(emulator, addr_reg));
    }
    else
    {
        write_addrreg(emulator, addr_reg, emulator->Machine.cpu.usp, NULL);
    }


    return (RETURN_OK);
}


u32 RESET(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    
    emulator->Machine.State = WARNING_STATE;

    sprintf(emulator->Machine.Warning.cause, "%s", "Unmenaged operation");
    emulator->Machine.Warning.code = code;
    sprintf(emulator->Machine.Warning.mnem, "%s", "RESET");

    return (RETURN_OK);
}


u32 NOP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    return (RETURN_OK);
}


u32 STOP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
   
    emulator->Machine.State = WARNING_STATE;

    sprintf(emulator->Machine.Warning.cause, "%s", "Unmenaged operation");
    emulator->Machine.Warning.code = code;
    sprintf(emulator->Machine.Warning.mnem, "%s", "STOP");

    return (RETURN_OK);
}


u32 RTE(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    if ((emulator->Machine.cpu.sr & SUPERVISOR) ? 1 : 0)
    {
        srflags sr = pop_word(emulator);

        emulator->Machine.cpu.pc = (pop_long(emulator));

        emulator->Machine.cpu.sr = (sr);
    }
    else
    {
        emulator->Machine.State = TRAP_STATE;
        sprintf(emulator->Machine.Exception.trap_cause,
                "Raised trap exception: Code: %d, Mnemonic: %s",
                PrivilegeViolation, trap_code_toString(PrivilegeViolation));

        return (RETURN_ERR);
    }

    return (RETURN_OK_PC_NO_INCR);
}


u32 RTS(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    if (emulator->Machine.RuntimeData.JSR_CALL_COUNTER == 0)
    {
        emulator->Machine.State = PANIC_STATE;
        sprintf(emulator->Machine.Exception.panic_cause, "RTS instruction invoked in main label, code: 0x%X", code);

        return (RETURN_ERR);
    }

    emulator->Machine.cpu.pc = (pop_long(emulator));

    emulator->Machine.RuntimeData.JSR_CALL_COUNTER--;

    return (RETURN_OK_PC_NO_INCR);
}


u32 TRAPV(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    if ((emulator->Machine.cpu.sr & OVERFLOW))
    {
        emulator->Machine.State = TRAP_STATE;
        sprintf(emulator->Machine.Exception.trap_cause,
                "Raised trap exception: Code: %d, Mnemonic: %s",
                TRAPVInstruction, trap_code_toString(TRAPVInstruction));

        return (RETURN_ERR);
    }

    return (RETURN_OK);
}


u32 RTR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    UNUSED(code)

    srflags ccr   = pop_word(emulator);
    srflags srval = emulator->Machine.cpu.sr;

    srval = (srval & 0xFFE0) | (ccr & 0x001F);

    emulator->Machine.cpu.sr = (srval);
    emulator->Machine.cpu.pc = (pop_long(emulator));

    return (RETURN_OK_PC_NO_INCR);
}


u32 JSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    ADDRMode mode = (code & ADDRMODE_MASK);
    u32  addr_reg = (code & SRC_MASK);

    u32 jmp_addr;

    if (mode == ABSLong || mode == ADDRESS)
    {
        u32 ram_ptr = read_addrreg(emulator, addr_reg);
        opsize size = LONG;
        jmp_addr = read_ram(emulator, &ram_ptr, &size);
        INCR_PC(LONG_SPAN);
    }
    else
    {
        emulator->Machine.State = PANIC_STATE;
        sprintf(emulator->Machine.Exception.panic_cause, "Unmenaged mode 0x%X", mode);

        return (RETURN_ERR);
    }


    push_long(emulator, emulator->Machine.cpu.pc);

    emulator->Machine.cpu.pc = (jmp_addr);

    emulator->Machine.RuntimeData.JSR_CALL_COUNTER++;

    return (RETURN_OK_PC_NO_INCR);
}


u32 JMP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    ADDRMode mode = (code & ADDRMODE_MASK);
    u32  addr_reg = (code & SRC_MASK);

    u32 jmp_addr;

    if (mode == ABSLong)
    {
        u32 ram_ptr = emulator->Machine.cpu.pc + WORD_SPAN;
        opsize size = LONG;
        jmp_addr = read_ram(emulator, &ram_ptr, &size);
    }
    else if (mode == ADDRESS)
    {
        u32 ram_ptr = read_addrreg(emulator, addr_reg);
        opsize size = LONG;
        jmp_addr = read_ram(emulator, &ram_ptr, &size);
    }
    else
    {
        emulator->Machine.State = PANIC_STATE;
        sprintf(emulator->Machine.Exception.panic_cause, "Unmenaged mode 0x%X", mode);

        return (RETURN_ERR);
    }

    emulator->Machine.cpu.pc = (jmp_addr);

    return (RETURN_OK_PC_NO_INCR);
}


u32 MOVEM(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 

    emulator->Machine.State = WARNING_STATE;
    
    sprintf(emulator->Machine.Warning.cause, "%s", "Unmenaged operation");
    emulator->Machine.Warning.code = code;
    sprintf(emulator->Machine.Warning.mnem, "%s", "MOVEM");

    return (RETURN_OK);
}


u32 CHK(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 

    u32 addr_reg = (code & SRC_MASK);
    u32 data_reg = (code & DST_MASK) >> 9;
    opsize            size = WORD;
    ADDRMode      mode = (code & 0b0000000000111000) >> 3;

    u32 value;
    READ_EFFECTIVE_ADDRESS(value, addr_reg, size, mode, NORMAL);
    u32 dVal  = read_addrreg(emulator, data_reg);

    s32 signVALUE, signDVAL;
    SIGN_EXTENDED(signVALUE, value, size);
    SIGN_EXTENDED(signDVAL, dVal, size);

    if (signDVAL < 0 || signDVAL > signVALUE)
    {
        if (signDVAL < 0) SET_NEGATIVE(1)

        if (signDVAL > signVALUE) SET_NEGATIVE(0)

        {
            emulator->Machine.State = TRAP_STATE;
            sprintf(emulator->Machine.Exception.trap_cause,
                    "Raised trap exception: Code: %d, Mnemonic: %s",
                    CHKInstruction, trap_code_toString(CHKInstruction));

            return (RETURN_ERR);
        }
    }

    return (RETURN_OK);
}


u32 LEA(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u8 mode     = (code & ADDRMODE_MASK);
    u8 addr_reg = (code & DST_MASK) >> 9;

    if (mode == ABSLong)
    {
        u32 label = read_long(emulator, emulator->Machine.cpu.pc + WORD_SPAN);

        write_addrreg(emulator, addr_reg, label, NULL);
    }
    else
    {
        emulator->Machine.State = PANIC_STATE;
        sprintf(emulator->Machine.Exception.panic_cause, "Unmenaged mode 0x%X", mode);

        return (RETURN_ERR);
    }

    INCR_PC(LONG_SPAN); // memory readF

    return (RETURN_OK);
}




// GROUP 0x05
u32 DBcc(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    opsize size = WORD;
    CCm condition = (code & 0x0F00) >> 8;

    if (!eval_cc(emulator, condition))
    {
        u32 dst  = code & 0x0007;
        u32 dval = read_addrreg(emulator, dst);

        s32 new_dval;
        SIGN_EXTENDED(new_dval, dval, size);
        new_dval -= 1;

        write_datareg(emulator, dst, (u32) new_dval, &size);

        if (new_dval != -1)
        {
            s32  disp;
            u32 ramptr = emulator->Machine.cpu.pc + WORD_SPAN;
            opsize        size   = WORD;
            SIGN_EXTENDED(disp, read_ram(emulator, &ramptr, &size), WORD);

            u32 pc = emulator->Machine.cpu.pc;
            pc += WORD_SPAN;

            emulator->Machine.cpu.pc = (pc + disp);
        }
        else INCR_PC(WORD_SPAN);
    }

    return (RETURN_OK_PC_NO_INCR);
}


u32 Scc(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst = (code & SRC_MASK);
    opsize   size = BYTE;
    ADDRMode mode = (code & 0b0000000000111000) >> 3;

    CCm condition = (code & 0x0F00) >> 8;

    if (eval_cc(emulator, condition))
    {
        WRITE_EFFECTIVE_ADDRESS(dst, 0x000000FF, size, mode);
    }
    else
    {
        WRITE_EFFECTIVE_ADDRESS(dst, 0x000000FF, size, mode);
    }

    return (RETURN_OK);
}


u32 ADDQ(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 value = (code & DST_MASK) >> 9;

    if (value == 0) value = 8;

    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    if (mode == ADDRReg) // no effect on flags
    {
        u32 reg_val     = read_addrreg(emulator, dst);
        u32 sign_regval;
        SIGN_EXTENDED(sign_regval, reg_val, LONG);
        u32 result      = (u32)(sign_regval + value);

        write_addrreg(emulator, dst, result, NULL);
        return (RETURN_OK);
    }

    u32 reg_content;
    READ_EFFECTIVE_ADDRESS(reg_content, dst, size, mode, NORMAL);

    u32 sign_regval;
    SIGN_EXTENDED(sign_regval, reg_content, LONG);

    u32 result = (u32)(sign_regval + value);

    WRITE_EFFECTIVE_ADDRESS(dst, result, size, mode);
    SET_SRFLAGS(addq, size, reg_content, 0, result);

    return (RETURN_OK);
}


u32 SUBQ(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 value = (code & DST_MASK) >> 9;

    if (value == 0) value = 8;

    u32 dst  = (code & SRC_MASK);
    u32 mode = (code & 0b0000000000111000) >> 3;
    opsize size = (code & SIZE_MASK) >> 6;

    if (mode == ADDRReg) // no effect on flags
    {
        u32 reg_val     = read_addrreg(emulator, dst);
        u32 sign_regval;
        SIGN_EXTENDED(sign_regval, reg_val, LONG);
        u32 result      = (u32)(sign_regval - value);

        write_addrreg(emulator, dst, result, NULL);
        return (RETURN_OK);
    }

    u32 reg_content;
    READ_EFFECTIVE_ADDRESS(reg_content, dst, size, mode, NORMAL);

    u32 sign_regval;
    SIGN_EXTENDED(sign_regval, reg_content, LONG);

    u32 result = (u32)(sign_regval - value);

    WRITE_EFFECTIVE_ADDRESS(dst, result, size, mode);
    SET_SRFLAGS(addq, size, reg_content, 0, result);

    return (RETURN_OK);
}




// GROUP 0x06
u32 BRA(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 pc   = emulator->Machine.cpu.pc;
    s32  disp = (code & 0x00FF);

    if (disp == 0)
    {
        u32 ram_ptr = pc + WORD_SPAN;
        opsize        dummy   = WORD;

        SIGN_EXTENDED(disp, read_ram(emulator, &ram_ptr, &dummy), WORD);
    }
    else
        SIGN_EXTENDED(disp, (u32) disp, WORD);

    emulator->Machine.cpu.pc = (pc + disp);

    return (RETURN_OK_PC_NO_INCR);
}


u32 BSR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 pc = emulator->Machine.cpu.pc;

    u32 disp = code & 0x00FF;

    if (disp == 0)
    {
        u32 ramptr = emulator->Machine.cpu.pc + WORD_SPAN;
        opsize        size   = WORD;
        SIGN_EXTENDED(disp, read_ram(emulator, &ramptr, &size), WORD);
        push_long(emulator, pc + LONG_SPAN);
    }
    else
    {
        SIGN_EXTENDED(disp, disp, WORD);
        push_long(emulator, pc + WORD_SPAN);
    }

    emulator->Machine.cpu.pc = (pc + disp);

    emulator->Machine.RuntimeData.JSR_CALL_COUNTER++;

    return (RETURN_OK);
}


u32 Bcc(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    CCm condition = (code & 0x0F00) >> 8;

    if (eval_cc(emulator, condition))
    {
        u32 pc   = emulator->Machine.cpu.pc;
        s32  disp = (code & 0x00FF);

        if (disp == 0)
        {
            u32 ramptr = pc + WORD_SPAN;
            opsize size = WORD;
            SIGN_EXTENDED(disp, read_ram(emulator, &ramptr, &size), WORD);
        }
        else
        {
            SIGN_EXTENDED(disp, disp, WORD);
        }

        emulator->Machine.cpu.pc = (pc + disp);
    }
    else
    {
        INCR_PC(WORD_SPAN);
    }

    return (RETURN_OK);
}




// GROUP 0x07
u32 MOVEQ(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst = (code & DST_MASK) >> 9;
    s32 val;
    SIGN_EXTENDED(val, (code & 0b0000000011111111), LONG);

    write_datareg(emulator, dst, val, NULL);

    SET_SRFLAGS(moveq, LONG, 0, 0, (u32) val);

    return 0;
}




// GROUP 0x08
u32 DIVU(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 _val;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, IGNORE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode = (ADDRMode *) a[3];

    if (*sVal == 0)
    {
        emulator->Machine.State = TRAP_STATE;
        sprintf(emulator->Machine.Exception.trap_cause,
                "Raised trap exception: Code: %d, Mnemonic: %s",
                DivideByZero, trap_code_toString(DivideByZero));

        return (RETURN_ERR);
    }

    opsize size = WORD;

    _val = (u32) *dVal / *sVal;

    SHOULD_INCR_PC(size, *mode);

    if (_val > 0xFFFF)
    {
        SET_OVERFLOW(1);

        FREE_EVLUATED_OP_ARRAY(a);

        return (RETURN_ERR);
    }

    int remainder = (int)(*dVal % *sVal) & 0xFFFF;

    write_datareg(emulator, *dst, remainder << 16, NULL);
    write_datareg(emulator, *dst, _val,      &size);

    SET_SRFLAGS(divu, LONG, 0, 0, _val);

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}


u32 DIVS(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    s32 _val, signed_sVal, signed_dVal;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, IGNORE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode = (ADDRMode *) a[3];

    opsize size = WORD;

    SIGN_EXTENDED(signed_dVal, *dVal, WORD);
    SIGN_EXTENDED(signed_sVal, *sVal, WORD);

    if (signed_sVal == 0)
    {
        emulator->Machine.State = TRAP_STATE;
        sprintf(emulator->Machine.Exception.trap_cause,
                "Raised trap exception: Code: %d, Mnemonic: %s",
                DivideByZero, trap_code_toString(DivideByZero));

        return (RETURN_ERR);
    }

    _val = (s32) signed_dVal / signed_sVal;

    SHOULD_INCR_PC(size, *mode);

    if (_val < -32768 || _val > 32767)
    {
        SET_OVERFLOW(1);

        FREE_EVLUATED_OP_ARRAY(a);

        return (RETURN_ERR);
    }
    int remainder = (int)(signed_dVal % signed_sVal) & 0xFFFF;

    write_datareg(emulator, *dst, remainder << 16, NULL);
    write_datareg(emulator, *dst, _val,      &size);

    SET_SRFLAGS(divs, LONG, 0, 0, _val);

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}


u32 SBCD(struct EmulationMachine* emulator)
{
    return xBCD(emulator, SUBTRACTION);
}


u32 OR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 _val;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, USE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode = (ADDRMode *) a[3];
    opsize   *size = (opsize *)   a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    _val = *dVal | *sVal;

    if (*direction == 0)
    {
        write_datareg(emulator, *dst, _val, size);
    }
    else
    {
        WRITE_EFFECTIVE_ADDRESS(*dst, _val, *size, *mode);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(emulator, *dst, *size);
    }

    SET_SRFLAGS(_or, *size, 0, 0, _val);

    SHOULD_INCR_PC(*size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}




// GROUP 0x09
u32 SUBA(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst_reg = (code & DST_MASK) >> 9;
    u32 src_reg = (code & SRC_MASK);
    ADDRMode mode = (code & 0b0000000000111000) >> 3;
    opsize   size;

    if (((code & 0b0000000100000000) >> 8) == 1)
        size = LONG;
    else
        size = WORD;

    u32 src_val;
    READ_EFFECTIVE_ADDRESS(src_val, src_reg, size, mode, NORMAL);

    u32 dst_val = read_addrreg(emulator, dst_reg);

    if (mode == ADDRESSPostIncr) incr_addr_reg(emulator, src_reg, size);

    s32 signSRC;
    SIGN_EXTENDED(signSRC, src_val, size);

    u32 result  = (u32)(dst_val - signSRC);
    write_addrreg(emulator, dst_reg, result, NULL);


    return (RETURN_OK);
}


u32 SUBX(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32  dst_reg = (code & DST_MASK) >> 9;
    u32  src_reg = (code & SRC_MASK);
    opsize         size   = (code & SIZE_MASK) >> 6;
    direction_mode drmode = (code & 0b0000000000001000) >> 3;

    s32 signSRC, signDST, result;
    switch (drmode) {
        case DATAREG:
            SIGN_EXTENDED(signDST, read_addrreg(emulator, dst_reg), size);
            SIGN_EXTENDED(signSRC, read_addrreg(emulator, src_reg), size);
            result  = signDST - signSRC - ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0);
            SET_SRFLAGS(addx, size, (u32) signSRC, (u32) signDST, (u32) result);
            break;

        case MEMORYPD:
            decr_addr_reg(emulator, dst_reg, size);
            decr_addr_reg(emulator, src_reg, size);

            SIGN_EXTENDED(signDST, read_ram(emulator, &dst_reg, &size), size);
            SIGN_EXTENDED(signSRC, read_ram(emulator, &src_reg, &size), size);
            result  = signDST - signSRC - ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0);

            WRITE_EFFECTIVE_ADDRESS(dst_reg, (u32) result, size, ADDRESSPreDecr);
            SET_SRFLAGS(addx, size, (u32) signSRC, (u32) signDST, (u32) result);
            break;
    }

    return (RETURN_OK);
}


u32 SUB(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    s32 _val, signed_sVal, signed_dVal;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, USE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    opsize   *size      = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    SIGN_EXTENDED(signed_sVal, *sVal, *size);
    SIGN_EXTENDED(signed_dVal, *dVal, *size);

    _val  = (*direction) ? signed_sVal - signed_dVal : signed_dVal - signed_sVal;

    if (!(*direction))
    {
        write_datareg(emulator, *dst, (u32)_val, size);
        SET_SRFLAGS(sub, *size, *sVal, *dVal, (u32)_val);
    }
    else
    {
        WRITE_EFFECTIVE_ADDRESS(*dst, (u32)_val, *size, *mode);
        SET_SRFLAGS(sub, *size, *dVal, *sVal, (u32)_val);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(emulator, *dst, *size);
    }

    SHOULD_INCR_PC(*size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}




// GROUP 0x0B
u32 CMPA(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst_reg = (code & DST_MASK) >> 9;
    u32 src_reg = (code & SRC_MASK);

    ADDRMode mode = (code & ADDRMODE_MASK);
    opsize   size;

    if (((code & 0b0000000100000000) >> 8) == 1)
        size = LONG;
    else
        size = WORD;

    s32 signSRC;

    if (mode == IMMEDIATE)
    {
        u32 ram_ptr = emulator->Machine.cpu.pc + WORD_SPAN;
        u32 imm_val = read_ram(emulator, &ram_ptr, &size);
        SIGN_EXTENDED(signSRC, imm_val, size);

        INCR_PC(size_to_span(size));
    }
    else
    {
        mode = (code & 0b0000000000111000) >> 3;

        u32 src_val;
        READ_EFFECTIVE_ADDRESS(src_val, src_reg, size, mode, NORMAL);
        SIGN_EXTENDED(signSRC, src_val, size);

        if (mode == ADDRESSPostIncr) incr_addr_reg(emulator, src_reg, size);
    }

    u32 dst_val = read_addrreg(emulator, dst_reg);

    u32 result  = (u32)(dst_val - signSRC);

    SET_SRFLAGS(cmpa, size, (u32) signSRC, dst_val, result);

    return (RETURN_OK);
}


u32 CMPM(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 dst_addr_reg = (code & DST_MASK) >> 9;
    u32 src_addr_reg = (code & SRC_MASK);
    opsize      size = (code & SIZE_MASK) >> 6;

    u32 ram_ptr;

    ram_ptr = read_addrreg(emulator, dst_addr_reg);
    u32 DST = read_ram(emulator, &ram_ptr, &size);

    ram_ptr = read_addrreg(emulator, src_addr_reg);
    u32 SRC = read_ram(emulator, &ram_ptr, &size);

    s32 signDST, signSRC;

    SIGN_EXTENDED(signDST, DST, size);
    SIGN_EXTENDED(signSRC, SRC, size);

    incr_addr_reg(emulator, dst_addr_reg, size);
    incr_addr_reg(emulator, src_addr_reg, size);

    s32 result = signDST - signSRC;
    SET_SRFLAGS(cmpm, size, SRC, DST, (u32) result);

    return (RETURN_OK);
}


u32 EOR(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 _val;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, USE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode = (ADDRMode *) a[3];
    opsize   *size = (opsize *)   a[4];

    _val = *dVal ^ *sVal;

    WRITE_EFFECTIVE_ADDRESS(*dst, _val, *size, *mode);

    if (*mode == ADDRESSPostIncr) incr_addr_reg(emulator, *dst, *size);

    SET_SRFLAGS(_or, *size, 0, 0, _val);

    SHOULD_INCR_PC(*size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}


u32 CMP(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32  dst_reg = (code & DST_MASK) >> 9;
    u32  src_reg = (code & SRC_MASK);

    ADDRMode mode = (code & ADDRMODE_MASK);
    opsize   size = (code & SIZE_MASK) >> 6;

    s32 signSRC;

    if (mode == IMMEDIATE)
    {
        opsize tmpsize = size;
        if (tmpsize == BYTE) tmpsize = WORD; //byte can't be wrote in ram

        INCR_PC(size_to_span(size));

        u32 ram_ptr = emulator->Machine.cpu.pc + size_to_span(size);
        u32 imm_val = read_ram(emulator, &ram_ptr, &tmpsize);
        SIGN_EXTENDED(signSRC, imm_val, tmpsize);

        INCR_PC(size_to_span(size));
    }
    else
    {
        mode = (code & 0b0000000000111000) >> 3;
        u32 src_val;
        READ_EFFECTIVE_ADDRESS(src_val, src_reg, size, mode, NORMAL);
        SIGN_EXTENDED(signSRC, src_val, size);

        if (mode == ADDRESSPostIncr) incr_addr_reg(emulator, src_reg, size);
    }

    s32 signDST;
    SIGN_EXTENDED(signDST, read_addrreg(emulator, dst_reg), size);

    s32 result  = (signDST - signSRC);

    SET_SRFLAGS(_cmp, size, (u32) signSRC, (u32) signDST, (u32) result);

    return (RETURN_OK);
}




// GROUP 0x0C
u32 MULU(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 _val;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, IGNORE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode = (ADDRMode *) a[3];

    opsize size = WORD;

    _val = *dVal * *sVal;

    write_datareg(emulator, *dst, (u32)_val, &size);
    SET_SRFLAGS(mulu, LONG, 0, 0, (u32)_val);

    SHOULD_INCR_PC(size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}


u32 MULS(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    s32 _val, signed_sVal, signed_dVal;;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, IGNORE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode = (ADDRMode *) a[3];

    opsize size = WORD;

    SIGN_EXTENDED(signed_dVal, *dVal, WORD);
    SIGN_EXTENDED(signed_sVal, *sVal, WORD);

    _val = signed_dVal * signed_sVal;

    write_datareg(emulator, *dst, (u32)_val, NULL);
    SET_SRFLAGS(muls, LONG, 0, 0, (u32)_val);

    SHOULD_INCR_PC(size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}


u32 ABCD(struct EmulationMachine* emulator)
{
    return xBCD(emulator, ADDICTION);
}


u32 EXG(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 rX = (code & 0x0007);
    u32 rY = (code & 0x0E00) >> 9;
    bit mode         = (bit)((code & 0x00F8) >> 3);

    u32 x, y;
    switch (mode)
    {
        case 0x08:      // Data Register exg Data Register
            x = read_addrreg(emulator, rX);
            y = read_addrreg(emulator, rY);
            write_datareg(emulator, rX, y, NULL);
            write_datareg(emulator, rY, x, NULL);
            break;
        case 0x09:      // Address Register exg Address Register
            x = read_addrreg(emulator, rX);
            y = read_addrreg(emulator, rY);
            write_addrreg(emulator, rX, y, NULL);
            write_addrreg(emulator, rY, x, NULL);
            break;
        case 0x11:      // Data Register exg Address Register
            x = read_addrreg(emulator, rX);
            y = read_addrreg(emulator, rY);
            write_addrreg(emulator, rX, y, NULL);
            write_datareg(emulator, rY, x, NULL);
            break;
        default:
        {
            emulator->Machine.State = PANIC_STATE;
            sprintf(emulator->Machine.Exception.panic_cause, "Unmenaged mode 0x%X", mode);

            return (RETURN_ERR);
        }
    }

    return (RETURN_OK);
}


u32 AND(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32 _val;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, USE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode  *mode = (ADDRMode *)      a[3];
    opsize        *size = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    _val = *dVal & *sVal;

    if (*direction == 0)
    {
        write_datareg(emulator, *dst, _val, size);
    }
    else
    {
        WRITE_EFFECTIVE_ADDRESS(*dst, _val, *size, *mode);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(emulator, *dst, *size);
    }

    SET_SRFLAGS(_or, *size, 0, 0, _val);

    SHOULD_INCR_PC(*size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}




// GROUP 0x0D
u32 ADDA(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32  dst_reg = (code & DST_MASK) >> 9;
    u32  src_reg = (code & SRC_MASK);
    ADDRMode   mode    = (code & 0b0000000000111000) >> 3;
    opsize         size;

    if (((code & 0b0000000100000000) >> 8) == 1)
        size = LONG;
    else
        size = WORD;

    u32 src_val;
    READ_EFFECTIVE_ADDRESS(src_val, src_reg, size, mode, NORMAL);
    u32 dst_val = read_addrreg(emulator, dst_reg);

    if (mode == ADDRESSPostIncr) incr_addr_reg(emulator, src_reg, size);

    s32 signSRC;
    SIGN_EXTENDED(signSRC, src_val, size);

    u32 result  = (u32)(dst_val + signSRC);
    write_addrreg(emulator, dst_reg, result, NULL);


    return (RETURN_OK);
}


u32 ADDX(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    u32  dst_reg = (code & DST_MASK) >> 9;
    u32  src_reg = (code & SRC_MASK);
    opsize         size    = (code & SIZE_MASK) >> 6;
    direction_mode drmode  = (code & 0b0000000000001000) >> 3;

    s32 signSRC, signDST, result;
    switch (drmode) {
        case DATAREG:
            SIGN_EXTENDED(signDST, read_addrreg(emulator, dst_reg), size);
            SIGN_EXTENDED(signSRC, read_addrreg(emulator, src_reg), size);
            result  = signDST + signSRC + ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0);
            SET_SRFLAGS(addx, size, (u32) signSRC, (u32) signDST, (u32) result);
            break;

        case MEMORYPD:
            decr_addr_reg(emulator, dst_reg, size);
            decr_addr_reg(emulator, src_reg, size);

            SIGN_EXTENDED(signDST, read_ram(emulator, &dst_reg, &size), size);
            SIGN_EXTENDED(signSRC, read_ram(emulator, &src_reg, &size), size);
            result  = signDST + signSRC + ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0);

            WRITE_EFFECTIVE_ADDRESS(dst_reg, (u32) result, size, ADDRESSPreDecr);
            SET_SRFLAGS(addx, size, (u32) signSRC, (u32) signDST, (u32) result);
            break;
    }

    return (RETURN_OK);
}


u32 ADD(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    s32  _val, signed_sVal, signed_dVal;

    void **a;
    EVAL_OP_EFFECTIVE_ADDRESS(a, code, USE_DIRECTION);

    u32 *dst  = (u32 *) a[0];
    u32 *sVal = (u32 *) a[1];
    u32 *dVal = (u32 *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    opsize   *size      = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    SIGN_EXTENDED(signed_sVal, *sVal, *size);
    SIGN_EXTENDED(signed_dVal, *dVal, *size);

    _val  = signed_dVal + signed_sVal;

    if (*direction == NORMAL)
    {
        write_datareg(emulator, *dst, (u32)_val, size);
        SET_SRFLAGS(add, *size, *sVal, *dVal, (u32)_val);
    }
    else
    {
        WRITE_EFFECTIVE_ADDRESS(*dst, (u32)_val, *size, *mode);
        SET_SRFLAGS(add, *size, *dVal, *sVal, (u32)_val);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(emulator, *dst, *size);
    }

    SHOULD_INCR_PC(*size, *mode); // for IMMEDIATE mode

    FREE_EVLUATED_OP_ARRAY(a);

    return (RETURN_OK);
}




// GROUP 0x0E
u32 ASR(struct EmulationMachine* emulator)
{
    return ALxx(emulator);
}


u32 ASL(struct EmulationMachine* emulator)
{
    return ALxx(emulator);
}


u32 LSR(struct EmulationMachine* emulator)
{
    return ALxx(emulator);
}


u32 LSL(struct EmulationMachine* emulator)
{
    return ALxx(emulator);
}


u32 ROXR(struct EmulationMachine* emulator)
{
    return ROxx(emulator);
}


u32 ROXL(struct EmulationMachine* emulator)
{
    return ROxx(emulator);
}


u32 ROR(struct EmulationMachine* emulator)
{
    return ROxx(emulator);
}


u32 ROL(struct EmulationMachine* emulator)
{
    return ROxx(emulator);
}



//Bxxx
u32 Bxxx(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code; 
    bit mode = (code & 0x0100) == 0x0000; // if true mean IMMEDIATE, read extension word

    u32 dst = (code & 0x0007);
    ADDRMode addrmode = (code & 0x0038) >> 3;

    u32 src, sVal, dVal;

    opsize size = LONG;

    bit type = (code & 0x00C0) >> 6;

    if (mode)
    {
        u32 ramptr = emulator->Machine.cpu.pc + WORD_SPAN;
        opsize tmpsize = WORD;

        sVal = read_ram(emulator, &ramptr, &tmpsize) & 0x000000FF;

        INCR_PC(WORD_SPAN);
    }
    else
    {
        src  = (code & 0x0E00) >> 9;
        sVal = read_addrreg(emulator, src) & 0x000000FF;
    }

    if (addrmode != DATAReg)
    {
        size = BYTE;
        sVal &= 0x00000007;
    }
    else
    {
        size = LONG;
        sVal &= 0x0000001F;
    }

    READ_EFFECTIVE_ADDRESS(dVal, dst, size, addrmode, NORMAL);

    SET_ZERO(((dVal >> sVal) & 0x00000001) == 0);

    switch (type) {
        case 0x01: //BCHG
            dVal = dVal ^ (1 << sVal);
            break;
        case 0x02: //BCLR
            dVal = dVal & (~(1 << sVal));
            break;
        case 0x03: //BSET
            dVal = dVal | (1 << sVal);
            break;
        default:  //BTST
            break;
    }

    if (type != 0x00)
        WRITE_EFFECTIVE_ADDRESS(dst, dVal, size, addrmode);

    return (RETURN_OK);

}




//abcd-sbcd
u32 xBCD(struct EmulationMachine* emulator, BCD_type type)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code;

    u32 srcval, dstval, result;

    u32 srcptr = (code & 0x0007);
    u32 dstptr = (code & 0x0E00) >> 9;

    if ((code & 0x0008) == DATAREG)
    {
        srcval = read_addrreg(emulator, srcptr) & 0x000000FF;
        dstval = read_addrreg(emulator, dstptr) & 0x000000FF;
        result = perform_BCD(emulator, type, srcval, dstval);

        opsize size = BYTE;
        write_datareg(emulator, dstptr, result, &size);
    }
    else //MEMORYPD
    {
        u32 src_ram_ptr, dst_ram_ptr;

        decr_addr_reg(emulator, srcptr, BYTE);
        decr_addr_reg(emulator, dstptr, BYTE);

        src_ram_ptr = read_addrreg(emulator, srcptr);
        dst_ram_ptr = read_addrreg(emulator, dstptr);

        srcval = read_byte(emulator, src_ram_ptr);
        dstval = read_byte(emulator, dst_ram_ptr);

        result = perform_BCD(emulator, type, srcval, dstval);

        write_byte(emulator, dst_ram_ptr, (u8) (result & 0x000000FF));
    }

    return (RETURN_OK);
}

u32 perform_BCD(struct EmulationMachine* emulator, BCD_type type, u32 src, u32 dest)
{
    s32 lo_val, hi_val;
    bit carry;

    if (type == ADDICTION)
    {
        lo_val = (s32)((src & 0x000F) + (dest & 0x000F) + ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0));
        carry = lo_val > 9;

        if (lo_val > 9)
            lo_val -= 10;

        hi_val = (s32)(((src >> 4) & 0x000F) + ((dest >> 4) & 0x000F) + (carry ? 1 : 0));
        carry = hi_val > 9;

        if (hi_val > 9)
            hi_val -= 10;
    }
    else
    {
        lo_val = (s32)((dest & 0x000F) - (src & 0x000F) - ((emulator->Machine.cpu.sr & EXTEND) ? 1 : 0));
        carry = lo_val < 0;

        if (lo_val < 0)
            lo_val += 10;

        hi_val = (s32)(((dest >> 4) & 0x000F) - ((src >> 4) & 0x000F) - (carry ? 1 : 0));
        carry = hi_val < 0;

        if (hi_val < 0)
            hi_val += 10;
    }

    s32 result = (hi_val << 4) + lo_val;

    SET_CARRY(carry);
    SET_EXTENDED(carry);

    if (result != 0)
        SET_ZERO(0);

    return (u32)(result & 0x000000FF);
}



//A-Lxx
u32 ALxx(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code;

    Rot al_dir  = (code & 0x0100) >> 8;
    opsize size = (code & 0x00C0) >> 6;

    bit logical;
    u32 value;

    switch (size) {
        case BYTE2:
        /* cannot reach this case, i really hope :D */
        {
            emulator->Machine.State = PANIC_STATE;
            sprintf(emulator->Machine.Exception.panic_cause, "ALxx invalid size 0x%X", BYTE);

            return (RETURN_ERR);
        }

        case WORD2: //same as ROxx
        {
            u32 addr_reg;
            ADDRMode      addr_mode;

            logical   = (code & 0x0E00) != 0;
            addr_reg  = (code & SRC_MASK);
            addr_mode = (code & 0x0038) >> 3;

            size = WORD;

            READ_EFFECTIVE_ADDRESS(value, addr_reg, size, addr_mode, NORMAL);

            u32 result;
            if (al_dir == LEFT)
            {
                result = value << 1;
                WRITE_EFFECTIVE_ADDRESS(addr_reg, result, size, addr_mode);

                SET_SRFLAGS(asl, size, 1, value, result);
                SET_OVERFLOW(logical ? 0 : (result & 0x8000) != (value & 0x8000));
            }
            else
            {
                u32 msb = value & most_significant_byte(size);

                result = (value >> 1) | (logical ? 0 : msb);
                WRITE_EFFECTIVE_ADDRESS(addr_reg, result, size, addr_mode);

                SET_SRFLAGS(asl, size, 1, (value & 0x0001), result);
                SET_OVERFLOW(logical ? 0 : (result & 0x8000) != (value & 0x8000));
            }

            break;
        }

        default:
        {
            logical = (code & 0x0018) != 0;

            u32 data_reg = (code & 0x0007);
            u32 dVal     = read_addrreg(emulator, data_reg) & mask_by_opsize(size);

            bit two_reg_op = (code & 0x0020) != 0;
            u32 src = (code & 0x0E00) >> 9;
            u32 sVal;

            u32 shift = (code & 0x0E00) >> 9;
            u32 msb   = most_significant_byte(size);

            if (two_reg_op)
                sVal = read_addrreg(emulator, src) & 0x003F;
            else
                sVal = src != 0 ? shift : 8;

            bit bso = 0;
            bit msb_change = 0;

            if (al_dir == LEFT)
            {
                for (u32 s = 0; s < sVal; s++)
                {
                    bso = dVal & msb;

                    dVal <<= 1;

                    if ((dVal & msb) != bso)
                        msb_change = 1;
                }
            }
            else
            {
                u32 msb_inner = dVal & msb;
                for (u32 s = 0; s < sVal; s++)
                {
                    bso = dVal & 0x00000001;

                    dVal >>= 1;

                    if (!logical)
                        dVal |= msb_inner;
                }
            }

            dVal &= msb;
            write_datareg(emulator, data_reg, dVal, &size);

            SET_SRFLAGS(asl, size, sVal, bso, dVal);
            SET_OVERFLOW(logical ? 0 : msb_change);
            break;
        }
    }

    return (RETURN_OK);

}

//Roxx
u32 ROxx(struct EmulationMachine* emulator)
{
    const opcode code = emulator->Machine.RuntimeData.operation_code;

    Rot rot_dir = (code & 0x0100) >> 8;
    opsize size = (code & 0x00C0) >> 6;

    bit extend;
    u32 value;

    switch (size) {
        case BYTE2:
        /* cannot reach this case, i really hope :D */
        {
            emulator->Machine.State = PANIC_STATE;
            sprintf(emulator->Machine.Exception.panic_cause, "ROxx invalid size 0x%X", BYTE);

            return (RETURN_ERR);
        }

        case WORD2: //ROxx to memory
        {
            u32 addr_reg;
            ADDRMode      addr_mode;

            extend    = (code & 0x0E00) == 0x0400;
            addr_reg  = (code & SRC_MASK);
            addr_mode = (code & 0x0038) >> 3;
            size = WORD;

            READ_EFFECTIVE_ADDRESS(value, addr_reg, size, addr_mode, NORMAL);

            if (rot_dir == LEFT)
            {
                u32 bso    = value & 0x00008000;
                u32 result = value << 1;

                bit isext = extend ? (emulator->Machine.cpu.sr & EXTEND) : bso != 0;

                if (isext)
                    result |= 0x00000001;

                WRITE_EFFECTIVE_ADDRESS(addr_reg, result, size, addr_mode);

                SET_SRFLAGS(extend ? roxl : rol, size, 1, bso, result);
            }
            else
            {
                u32 bso    = value & 0x00000001;
                u32 result = value >> 1;

                bit isext = extend ? (emulator->Machine.cpu.sr & EXTEND) : bso != 0;

                if (isext)
                    result |= 0x00008000;

                WRITE_EFFECTIVE_ADDRESS(addr_reg, result, size, addr_mode);

                SET_SRFLAGS(extend ? roxr : ror, size, 1, bso, result);
            }

            break;
        }

        default:
        /* for everything else sizes */
        {
            extend = (code & 0x0018) == 0x0010;

            u32 data_reg = (code & 0x0007);
            u32 dVal     = read_addrreg(emulator, data_reg) & mask_by_opsize(size);

            bit two_reg_op = (code & 0x0020) != 0;
            u32 src = (code & 0x0E00) >> 9;
            u32 sVal;

            u32 bso = 0;
            u32 msb = most_significant_byte(size);

            if (two_reg_op)
                sVal = read_addrreg(emulator, src) & 0x003F; // max 63bits rotation
            else
                sVal = src != 0 ? src : 8;

            if (rot_dir == LEFT)
            {
                bit extendbit = (emulator->Machine.cpu.sr & EXTEND);

                for (u32 r = 0; r < sVal; r++)
                {
                    bso = dVal & msb;
                    dVal <<= 1;

                    bit iBit = extend ? extendbit : bso != 0;

                    if (iBit)
                        dVal |= 0x00000001;

                    extendbit = bso != 0;
                }

                dVal &= mask_by_opsize(size);
                write_datareg(emulator, data_reg, dVal, &size);

                SET_SRFLAGS(extend ? roxl : rol, size, (uint) sVal, bso, dVal);
            }
            else
            {
                bit extendbit = (emulator->Machine.cpu.sr & EXTEND);

                for (u32 r = 0; r < sVal; r++)
                {
                    bso = dVal & 0x00000001;

                    dVal >>= 1;

                    bit iBit = extend ? extendbit : bso != 0;

                    if (iBit)
                        dVal |= msb;

                    extendbit = bso != 0;
                }

                dVal &= mask_by_opsize(size);
                write_datareg(emulator, data_reg, dVal, &size);

                SET_SRFLAGS(extend ? roxr : ror, size, (uint) sVal, bso, dVal);
            }

            break;
        }
    }

    return (RETURN_OK);
}




m68k_opcode* new_opcode_t(const opcode bitcode, const bitmask mask, char *mnemonic, u32 (*handler)())
{
    m68k_opcode *newopcode = malloc(sizeof (*newopcode));

    newopcode->code     = bitcode;
    newopcode->mask     = mask;
    newopcode->mnemonic = mnemonic;
    newopcode->handler  = handler;

    return newopcode;

}

void init_opcodes(struct EmulationMachine *em)
{
    if (!em->Machine.codemap)
    {
        em->Machine.codemap = malloc(sizeof (*em->Machine.codemap) * INSTRUCTION_SET_GROUPS_COUNT);

        if (!em->Machine.codemap)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 0), aborting.");
            return;
        }


        // GROUP 0x00
        em->Machine.codemap[0].key  = 0x00;
        em->Machine.codemap[0].size = GROUP_0x00_LEN;
        em->Machine.codemap[0].instances     = malloc(sizeof (*em->Machine.codemap[0].instances)  * GROUP_0x00_LEN);
        if (!em->Machine.codemap[0].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 1), aborting.");
            return;
        }
        em->Machine.codemap[0].instances[0]  = new_opcode_t(0b0000000000111100, 0b1111111111111111, "ORItoCCR",  ORItoCCR);
        em->Machine.codemap[0].instances[1]  = new_opcode_t(0b0000000001111100, 0b1111111111111111, "ORItoSR",   ORItoSR);
        em->Machine.codemap[0].instances[2]  = new_opcode_t(0b0000000000000000, 0b1111111100000000, "ORI",       ORI);
        em->Machine.codemap[0].instances[3]  = new_opcode_t(0b0000001000111100, 0b1111111111111111, "ANDItoCCR", ANDItoCCR);
        em->Machine.codemap[0].instances[4]  = new_opcode_t(0b0000001001111100, 0b1111111111111111, "ANDItoSR",  ANDItoSR);
        em->Machine.codemap[0].instances[5]  = new_opcode_t(0b0000001000000000, 0b1111111100000000, "ANDI",      ANDI);
        em->Machine.codemap[0].instances[6]  = new_opcode_t(0b0000010000000000, 0b1111111100000000, "SUBI",      SUBI);
        em->Machine.codemap[0].instances[7]  = new_opcode_t(0b0000011000000000, 0b1111111100000000, "ADDI",      ADDI);
        em->Machine.codemap[0].instances[8]  = new_opcode_t(0b0000101000111100, 0b1111111111111111, "EORItoCCR", EORItoCCR);
        em->Machine.codemap[0].instances[9]  = new_opcode_t(0b0000101001111100, 0b1111111111111111, "EORItoSR",  EORItoSR);
        em->Machine.codemap[0].instances[10] = new_opcode_t(0b0000101000000000, 0b1111111100000000, "EORI",      EORI);
        em->Machine.codemap[0].instances[11] = new_opcode_t(0b0000110000000000, 0b1111111100000000, "CMPI",      CMPI);
        em->Machine.codemap[0].instances[12] = new_opcode_t(0b0000000100001000, 0b1111000100111000, "MOVEP",     MOVEP);
        em->Machine.codemap[0].instances[13] = new_opcode_t(0b0000100000000000, 0b1111111111000000, "BTST",      BTST);
        em->Machine.codemap[0].instances[14] = new_opcode_t(0b0000100001000000, 0b1111111111000000, "BCHG",      BCHG);
        em->Machine.codemap[0].instances[15] = new_opcode_t(0b0000100010000000, 0b1111111111000000, "BCLR",      BCLR);
        em->Machine.codemap[0].instances[16] = new_opcode_t(0b0000100011000000, 0b1111111111000000, "BSET",      BSET);
        em->Machine.codemap[0].instances[17] = new_opcode_t(0b0000000100000000, 0b1111000111000000, "BTST",      BTST);
        em->Machine.codemap[0].instances[18] = new_opcode_t(0b0000000101000000, 0b1111000111000000, "BCHG",      BCHG);
        em->Machine.codemap[0].instances[19] = new_opcode_t(0b0000000110000000, 0b1111000111000000, "BCLR",      BCLR);
        em->Machine.codemap[0].instances[20] = new_opcode_t(0b0000000111000000, 0b1111000111000000, "BSET",      BSET);


        // GROUP 0x01
        em->Machine.codemap[1].key  = 0x01;
        em->Machine.codemap[1].size = GROUP_0x01_LEN;
        em->Machine.codemap[1].instances    = malloc(sizeof (*em->Machine.codemap[1].instances)  * GROUP_0x01_LEN);
        if (!em->Machine.codemap[1].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 2), aborting.");
            return;
        }
        em->Machine.codemap[1].instances[0] = new_opcode_t(0b0001000000000000, 0b1111000000000000, "MOVE", MOVE);


        // GROUP 0x02
        em->Machine.codemap[2].key  = 0x02;
        em->Machine.codemap[2].size = GROUP_0x02_LEN;
        em->Machine.codemap[2].instances    = malloc(sizeof (*em->Machine.codemap[2].instances)  * GROUP_0x02_LEN);
        if (!em->Machine.codemap[2].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 3), aborting.");
            return;
        }
        em->Machine.codemap[2].instances[0] = new_opcode_t(0b0010000001000000, 0b1111000111000000, "MOVEA", MOVEA);
        em->Machine.codemap[2].instances[1] = new_opcode_t(0b0010000000000000, 0b1111000000000000, "MOVE",  MOVE);


        // GROUP 0x03
        em->Machine.codemap[3].key  = 0x03;
        em->Machine.codemap[3].size = GROUP_0x03_LEN;
        em->Machine.codemap[3].instances    = malloc(sizeof (*em->Machine.codemap[3].instances)  * GROUP_0x03_LEN);
        if (!em->Machine.codemap[3].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 4), aborting.");
            return;
        }
        em->Machine.codemap[3].instances[0] = new_opcode_t(0b0011000001000000, 0b1111000111000000, "MOVEA", MOVEA);
        em->Machine.codemap[3].instances[1] = new_opcode_t(0b0011000000000000, 0b1111000000000000, "MOVE",  MOVE);


        // GROUP 0x04
        em->Machine.codemap[4].key  = 0x04;
        em->Machine.codemap[4].size = GROUP_0x04_LEN;
        em->Machine.codemap[4].instances     = malloc(sizeof (*em->Machine.codemap[4].instances)  * GROUP_0x04_LEN);
        if (!em->Machine.codemap[4].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 5), aborting.");
            return;
        }
        em->Machine.codemap[4].instances[0]  = new_opcode_t(0b0100000011000000, 0b1111111111000000, "MOVEfromSR", MOVEfromSR);
        em->Machine.codemap[4].instances[1]  = new_opcode_t(0b0100010011000000, 0b1111111111000000, "MOVEtoCCR",  MOVEtoCCR);
        em->Machine.codemap[4].instances[2]  = new_opcode_t(0b0100011011000000, 0b1111111111000000, "MOVEtoSR",   MOVEtoSR);
        em->Machine.codemap[4].instances[3]  = new_opcode_t(0b0100000000000000, 0b1111111100000000, "NEGX",       NEGX);
        em->Machine.codemap[4].instances[4]  = new_opcode_t(0b0100001000000000, 0b1111111100000000, "CLR",        CLR);
        em->Machine.codemap[4].instances[5]  = new_opcode_t(0b0100010000000000, 0b1111111100000000, "NEG",        NEG);
        em->Machine.codemap[4].instances[6]  = new_opcode_t(0b0100011000000000, 0b1111111100000000, "NOT",        NOT);
        em->Machine.codemap[4].instances[7]  = new_opcode_t(0b0100100010000000, 0b1111111110111000, "EXT",        EXT);
        em->Machine.codemap[4].instances[8]  = new_opcode_t(0b0100100000000000, 0b1111111111000000, "NBCD",       NBCD);
        em->Machine.codemap[4].instances[9]  = new_opcode_t(0b0100100001000000, 0b1111111111111000, "SWAP",       SWAP);
        em->Machine.codemap[4].instances[10] = new_opcode_t(0b0100100001000000, 0b1111111111000000, "PEA",        PEA);
        em->Machine.codemap[4].instances[11] = new_opcode_t(0b0100101011111100, 0b1111111111111111, "ILLEGAL",    ILLEGAL);
        em->Machine.codemap[4].instances[12] = new_opcode_t(0b0100101011000000, 0b1111111111000000, "TAS",        TAS);
        em->Machine.codemap[4].instances[13] = new_opcode_t(0b0100101000000000, 0b1111111100000000, "TST",        TST);
        em->Machine.codemap[4].instances[14] = new_opcode_t(0b0100111001000000, 0b1111111111110000, "TRAP",       TRAP);
        em->Machine.codemap[4].instances[15] = new_opcode_t(0b0100111001010000, 0b1111111111111000, "LINK",       LINK);
        em->Machine.codemap[4].instances[16] = new_opcode_t(0b0100111001011000, 0b1111111111111000, "UNLK",       UNLK);
        em->Machine.codemap[4].instances[17] = new_opcode_t(0b0100111001100000, 0b1111111111110000, "MOVEUSP",    MOVEUSP);
        em->Machine.codemap[4].instances[18] = new_opcode_t(0b0100111001110000, 0b1111111111111111, "RESET",      RESET);
        em->Machine.codemap[4].instances[19] = new_opcode_t(0b0100111001110001, 0b1111111111111111, "NOP",        NOP);
        em->Machine.codemap[4].instances[20] = new_opcode_t(0b0100111001110010, 0b1111111111111111, "STOP",       STOP);
        em->Machine.codemap[4].instances[21] = new_opcode_t(0b0100111001110011, 0b1111111111111111, "RTE",        RTE);
        em->Machine.codemap[4].instances[22] = new_opcode_t(0b0100111001110101, 0b1111111111111111, "RTS",        RTS);
        em->Machine.codemap[4].instances[23] = new_opcode_t(0b0100111001110110, 0b1111111111111111, "TRAPV",      TRAPV);
        em->Machine.codemap[4].instances[24] = new_opcode_t(0b0100111001110111, 0b1111111111111111, "RTR",        RTR);
        em->Machine.codemap[4].instances[25] = new_opcode_t(0b0100111010000000, 0b1111111111000000, "JSR",        JSR);
        em->Machine.codemap[4].instances[26] = new_opcode_t(0b0100111011000000, 0b1111111111000000, "JMP",        JMP);
        em->Machine.codemap[4].instances[27] = new_opcode_t(0b0100100010000000, 0b1111101110000000, "MOVEM",      MOVEM);
        em->Machine.codemap[4].instances[28] = new_opcode_t(0b0100000110000000, 0b1111000111000000, "CHK",        CHK);
        em->Machine.codemap[4].instances[29] = new_opcode_t(0b0100000111000000, 0b1111000111000000, "LEA",        LEA);


        // GROUP 0x05
        em->Machine.codemap[5].key  = 0x05;
        em->Machine.codemap[5].size = GROUP_0x05_LEN;
        em->Machine.codemap[5].instances    = malloc(sizeof (*em->Machine.codemap[5].instances)  * GROUP_0x05_LEN);
        if (!em->Machine.codemap[5].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 6), aborting.");
            return;
        }
        em->Machine.codemap[5].instances[0] = new_opcode_t(0b0101000011001000, 0b1111000011111000, "DBcc", DBcc);
        em->Machine.codemap[5].instances[1] = new_opcode_t(0b0101000011000000, 0b1111000011000000, "Scc",  Scc);
        em->Machine.codemap[5].instances[2] = new_opcode_t(0b0101000000000000, 0b1111000100000000, "ADDQ", ADDQ);
        em->Machine.codemap[5].instances[3] = new_opcode_t(0b0101000100000000, 0b1111000100000000, "SUBQ", SUBQ);


        // GROUP 0x06
        em->Machine.codemap[6].key = 0x06;
        em->Machine.codemap[6].size = GROUP_0x06_LEN;
        em->Machine.codemap[6].instances    = malloc(sizeof (*em->Machine.codemap[6].instances)  * GROUP_0x06_LEN);
        if (!em->Machine.codemap[6].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 7), aborting.");
            return;
        }
        em->Machine.codemap[6].instances[0] = new_opcode_t(0b0110000000000000, 0b1111111100000000, "BRA", BRA);
        em->Machine.codemap[6].instances[1] = new_opcode_t(0b0110000100000000, 0b1111111100000000, "BSR", BSR);
        em->Machine.codemap[6].instances[2] = new_opcode_t(0b0110000000000000, 0b1111000000000000, "Bcc", Bcc);


        // GROUP 0x07
        em->Machine.codemap[7].key  = 0x07;
        em->Machine.codemap[7].size = GROUP_0x07_LEN;
        em->Machine.codemap[7].instances    = malloc(sizeof (*em->Machine.codemap[7].instances)  * GROUP_0x07_LEN);
        if (!em->Machine.codemap[7].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 8), aborting.");
            return;
        }
        em->Machine.codemap[7].instances[0] = new_opcode_t(0b0111000000000000, 0b1111000100000000, "MOVEQ", MOVEQ);


        // GROUP 0x08
        em->Machine.codemap[8].key  = 0x08;
        em->Machine.codemap[8].size = GROUP_0x08_LEN;
        em->Machine.codemap[8].instances    = malloc(sizeof (*em->Machine.codemap[8].instances)  * GROUP_0x08_LEN);
        if (!em->Machine.codemap[8].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 9), aborting.");
            return;
        }
        em->Machine.codemap[8].instances[0] = new_opcode_t(0b1000000011000000, 0b1111000111000000, "DIVU", DIVU);
        em->Machine.codemap[8].instances[1] = new_opcode_t(0b1000000111000000, 0b1111000111000000, "DIVS", DIVS);
        em->Machine.codemap[8].instances[2] = new_opcode_t(0b1000000100000000, 0b1111000111110000, "SBCD", SBCD);
        em->Machine.codemap[8].instances[3] = new_opcode_t(0b1000000000000000, 0b1111000000000000, "OR",   OR);


        // GROUP 0x09
        em->Machine.codemap[9].key  = 0x09;
        em->Machine.codemap[9].size = GROUP_0x09_LEN;
        em->Machine.codemap[9].instances    = malloc(sizeof (*em->Machine.codemap[9].instances)  * GROUP_0x09_LEN);
        if (!em->Machine.codemap[9].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 10), aborting.");
            return;
        }
        em->Machine.codemap[9].instances[0] = new_opcode_t(0b1001000011000000, 0b1111000011000000, "SUBA", SUBA);
        em->Machine.codemap[9].instances[1] = new_opcode_t(0b1001000100000000, 0b1111000100110000, "SUBX", SUBX);
        em->Machine.codemap[9].instances[2] = new_opcode_t(0b1001000000000000, 0b1111000000000000, "SUB",  SUB);


        // GROUP 0x0B
        em->Machine.codemap[10].key  = 0x0B;
        em->Machine.codemap[10].size = GROUP_0x0B_LEN;
        em->Machine.codemap[10].instances    = malloc(sizeof (*em->Machine.codemap[10].instances) * GROUP_0x0B_LEN);
        if (!em->Machine.codemap[10].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 11), aborting.");
            return;
        }
        em->Machine.codemap[10].instances[0] = new_opcode_t(0b1011000011000000, 0b1111000011000000, "CMPA", CMPA);
        em->Machine.codemap[10].instances[1] = new_opcode_t(0b1011000100001000, 0b1111000100111000, "CMPM", CMPM);
        em->Machine.codemap[10].instances[2] = new_opcode_t(0b1011000100000000, 0b1111000100000000, "EOR",  EOR);
        em->Machine.codemap[10].instances[3] = new_opcode_t(0b1011000000000000, 0b1111000100000000, "CMP",  CMP);


        // GROUP 0x0C
        em->Machine.codemap[11].key  = 0x0C;
        em->Machine.codemap[11].size = GROUP_0x0C_LEN;
        em->Machine.codemap[11].instances    = malloc(sizeof (*em->Machine.codemap[11].instances) * GROUP_0x0C_LEN);
        if (!em->Machine.codemap[11].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 12), aborting.");
            return;
        }
        em->Machine.codemap[11].instances[0] = new_opcode_t(0b1100000011000000, 0b1111000111000000, "MULU", MULU);
        em->Machine.codemap[11].instances[1] = new_opcode_t(0b1100000111000000, 0b1111000111000000, "MULS", MULS);
        em->Machine.codemap[11].instances[2] = new_opcode_t(0b1100000100000000, 0b1111000111110000, "ABCD", ABCD);
        em->Machine.codemap[11].instances[3] = new_opcode_t(0b1100000100000000, 0b1111000100110000, "EXG",  EXG);
        em->Machine.codemap[11].instances[4] = new_opcode_t(0b1100000000000000, 0b1111000000000000, "AND",  AND);


        // GROUP 0x0D
        em->Machine.codemap[12].key  = 0x0D;
        em->Machine.codemap[12].size = GROUP_0x0D_LEN;
        em->Machine.codemap[12].instances    = malloc(sizeof (*em->Machine.codemap[12].instances) * GROUP_0x0D_LEN);
        if (!em->Machine.codemap[12].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 13), aborting.");
            return;
        }
        em->Machine.codemap[12].instances[0] = new_opcode_t(0b1101000011000000, 0b1111000011000000, "ADDA", ADDA);
        em->Machine.codemap[12].instances[1] = new_opcode_t(0b1101000100000000, 0b1111000100110000, "ADDX", ADDX);
        em->Machine.codemap[12].instances[2] = new_opcode_t(0b1101000000000000, 0b1111000000000000, "ADD",  ADD);


        // GROUP 0x0E
        em->Machine.codemap[13].key  = 0x0E;
        em->Machine.codemap[13].size = GROUP_0x0E_LEN;
        em->Machine.codemap[13].instances     = malloc(sizeof (*em->Machine.codemap[13].instances) * GROUP_0x0E_LEN);
        if (!em->Machine.codemap[13].instances)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Internal error (em->Machine.codemap stage 14), aborting.");
            return;
        }
        em->Machine.codemap[13].instances[0]  = new_opcode_t(0b1110000011000000, 0b1111111111000000, "ASR",  ASR);
        em->Machine.codemap[13].instances[1]  = new_opcode_t(0b1110000111000000, 0b1111111111000000, "ASL",  ASL);
        em->Machine.codemap[13].instances[2]  = new_opcode_t(0b1110001011000000, 0b1111111111000000, "LSR",  LSR);
        em->Machine.codemap[13].instances[3]  = new_opcode_t(0b1110001111000000, 0b1111111111000000, "LSL",  LSL);
        em->Machine.codemap[13].instances[4]  = new_opcode_t(0b1110010011000000, 0b1111111111000000, "ROXR", ROXR);
        em->Machine.codemap[13].instances[5]  = new_opcode_t(0b1110010111000000, 0b1111111111000000, "ROXL", ROXL);
        em->Machine.codemap[13].instances[6]  = new_opcode_t(0b1110011011000000, 0b1111111111000000, "ROR",  ROR);
        em->Machine.codemap[13].instances[7]  = new_opcode_t(0b1110011111000000, 0b1111111111000000, "ROL",  ROL);
        em->Machine.codemap[13].instances[8]  = new_opcode_t(0b1110000000000000, 0b1111000100011000, "ASR",  ASR);
        em->Machine.codemap[13].instances[9]  = new_opcode_t(0b1110000100000000, 0b1111000100011000, "ASL",  ASL);
        em->Machine.codemap[13].instances[10] = new_opcode_t(0b1110000000001000, 0b1111000100011000, "LSR",  LSR);
        em->Machine.codemap[13].instances[11] = new_opcode_t(0b1110000100001000, 0b1111000100011000, "LSL",  LSL);
        em->Machine.codemap[13].instances[12] = new_opcode_t(0b1110000000010000, 0b1111000100011000, "ROXR", ROXR);
        em->Machine.codemap[13].instances[13] = new_opcode_t(0b1110000100010000, 0b1111000100011000, "ROXL", ROXL);
        em->Machine.codemap[13].instances[14] = new_opcode_t(0b1110000000011000, 0b1111000100011000, "ROR",  ROR);
        em->Machine.codemap[13].instances[15] = new_opcode_t(0b1110000100011000, 0b1111000100011000, "ROL",  ROL);

    }
}


void destroy_codes(struct EmulationMachine *em)
{
    if (em->Machine.codemap)
    {
        unsigned char outer = 0, inner = 0;

        int x = 0;

        for (outer = 0; outer < INSTRUCTION_SET_GROUPS_COUNT; outer++)
        {
            m68k_codemap *reference = &em->Machine.codemap[outer];

            if (reference)
            {
                if (reference->instances)
                {
                    x += reference->size;
                    for (inner = 0; inner < reference->size; inner++)
                    {
                        if (reference->instances[inner]) free(reference->instances[inner]);
                    }

                    free(reference->instances);

                    reference->instances = NULL;
                }

            }

        }

        free(em->Machine.codemap);

    }

    em->Machine.codemap = NULL;
}


/*
 * FINDER
 *
 */
m68k_opcode* get_opcode_t(struct EmulationMachine* emulator)
{
    const u8 code_group_id = (u8)((emulator->Machine.RuntimeData.operation_code & 0xF000) >> 12);

    if (code_group_id < 0x0F && code_group_id != 0x0A)
    {
        m68k_codemap* const tmp = (code_group_id > 0x09) ? 
            &emulator->Machine.codemap[code_group_id - 0x01] : 
            &emulator->Machine.codemap[code_group_id];

        for (unsigned char iter = 0; iter < tmp->size; iter++)
            if ((emulator->Machine.RuntimeData.operation_code & tmp->instances[iter]->mask) == tmp->instances[iter]->code)
            {
                emulator->Machine.RuntimeData.mnemonic = tmp->instances[iter]->mnemonic;
                return tmp->instances[iter];
            }
    }

    return NULL;
}


u32 run_opcode(struct EmulationMachine* emulator)
{
    emulator->Machine.State = EXECUTION_STATE;

    m68k_opcode* const tmp = get_opcode_t(emulator);

    if (tmp == NULL)
    {
        emulator->Machine.State = PANIC_STATE;
        sprintf(emulator->Machine.Exception.panic_cause, "Instruction code 0x%X not reconized", emulator->Machine.RuntimeData.operation_code);
        return (RETURN_ERR);
    }

    const u32 res = tmp->handler(emulator);

    if (res != RETURN_OK_PC_NO_INCR)
        INCR_PC(WORD_SPAN);

    emit_dump(emulator);

    return res;
}


u32 execute_istr(struct EmulationMachine *emulator)
{
    u32 istruction_ptr = emulator->Machine.cpu.pc;

    if ((istruction_ptr % 2) != 0)
    {
        emulator->Machine.State = PANIC_STATE;
        sprintf(emulator->Machine.Exception.panic_cause, "Segmentation fault while reading next istruction on odd address");
        return (RETURN_ERR);
    }

    emulator->Machine.RuntimeData.operation_code = read_word(emulator, istruction_ptr);;

    return run_opcode(emulator);
}