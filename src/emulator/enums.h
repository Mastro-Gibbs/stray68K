/**
 * Author: Stefano Fattore
 *
 * This header contains some enums mainly used in 'handler.c' functions
 *
 *
 *
 */

#ifndef __ENUMS_H__68000
#define __ENUMS_H__68000

#include "motorolatypes.h"


/*
 * OPERATION SIZE AS PROGRAM COUNTER SPAN
 *
 * Simply, op bytes count
 *
 */
typedef enum __operation_size_span__
{
    BYTE_SPAN = 0x01,
    WORD_SPAN = 0x02,
    LONG_SPAN = 0x04

} sspan;



/*
 * Known mask for op sizes.
 *
 * BYTE2 and WORD2 are special case!
 *
 */

typedef enum __operation_size__
{
    BYTE  = 0b00000000, // 00
    WORD  = 0b00000001, // 01
    LONG  = 0b00000010, // 10
    BYTE2 = 0b00000001, // 01
    WORD2 = 0b00000011  // 11
} opsize;



/*
 * Enum for ccr bits position
 *
 */
typedef enum __status_register_flags__
{
    CARRY      = 0x01,
    OVERFLOW   = 0x02,
    ZERO       = 0x04,
    NEGATIVE   = 0x08,
    EXTEND     = 0x10,
    SUPERVISOR = 0x2000,
    TRACE      = 0x8000

} srflag_bits;




/*
 * Condition codes
 *
 */
typedef enum __condition_mnemonics__
{
    T = 0x00,		// True
    F = 0x01,		// False
    HI = 0x02,		// Higher
    LS = 0x03,		// Lower or Same
    CC = 0x04,		// Carry Clear
    CS = 0x05,		// Carry Set
    NE = 0x06,		// Not Equal
    EQ = 0x07,		// Equal
    VC = 0x08,		// Overflow Clear
    VS = 0x09,		// Overflow Set
    PL = 0x0A,		// Plus
    MI = 0x0B,		// Minus
    GE = 0x0C,		// Greater or Equal
    LT = 0x0D,		// Less Than
    GT = 0x0E,		// Greater Than
    LE = 0x0F		// Less or Equal

} CCm;



/*
 * Addressing mode enum
 *
 */
typedef enum __addressing_mode__
{
    DATAReg         = 0b00000000,   // Dn
    ADDRReg         = 0b00000001,	// An
    ADDRESS         = 0b00000010,   // (An)
    ADDRESSPostIncr = 0b00000011,   // (An)+
    ADDRESSPreDecr  = 0b00000100,	// -(An)
    ADDRESSDisp     = 0b00000101, 	// (d,An)
    ADDRESSIndex    = 0b00000110,	// (d,An,Xn)
    PCDisp          = 0b00111010, 	// (d,PC)
    PCIndex         = 0b00111011, 	// (d,PC,Xn)
    ABSShort        = 0b00111000,	// (xxx).W
    ABSLong         = 0b00111001, 	// (xxx).L
    IMMEDIATE       = 0b00111100    // #<data>

} ADDRMode;




/*
 * Enum that rapresents a particular bit in some ops
 *
 * Es. ADD op
 *
 * If it's set, source and destination bits are swapped
 *
 */
typedef enum __effective_address_type__
{
    NORMAL   = 0x00,
    INVERTED = 0x01
} ea_direction;



/*
 * Enum that rapresents data direction:
 *
 * 1) to datareg
 * 2) to memory with pre decrement
 *
 */
typedef enum __direction__mode__
{
    DATAREG   = 0x00,
    MEMORYPD  = 0x01
} direction_mode;



/*
 * Enum used for bit rol, shift and etc..
 *
 */
typedef enum __rotation_direction__
{
    LEFT  = 1,
    RIGHT = 0
} Rot;



/*
 *
 *
 *
 */
typedef enum __storing__direction__
{
    MEMORY_REGISTER = 0x00,
    REGISTER_MEMORY = 0x01,
    INVERTED_MEMORY_REGISTER = 0x01,
    INVERTED_REGISTER_MEMORY = 0x00

} Sdirection;



/*
 * Trap vector
 *
 */
typedef enum __trap__vector__
{
    BusError           = 2,
    AddressError       = 3,
    IllegalInstruction = 4,
    DivideByZero       = 5,
    CHKInstruction     = 6,
    TRAPVInstruction   = 7,
    PrivilegeViolation = 8
} TrapVec;



/*
 * Stupid enum to ignore a block of code in 'void **eval_OP_EA(opcode code)'
 *
 *
 */
enum __ignore_direction__
{
    IGNORE_DIRECTION = 0,
    USE_DIRECTION    = 1
};



/*
 * type of xBCD operation:
 *
 * 1) ABCD
 * 2) SBCD
 *
 */
typedef enum __bcd_type__
{
    ADDICTION   = 0,
    SUBTRACTION = 1
} BCD_type;



/*
 * Codes used to invoke sys primitives through TRAP #15
 *
 *
 */
typedef enum __custom_trap_behavior__
{
    PRINTINT     = 0,
    PRINTINTLN   = 1,
    UPRINTINT    = 2,
    UPRINTINTLN  = 3,
    SCANINT      = 4,
    PRINTSTR     = 5,
    PRINTSTRLN   = 6

} CustomTrap;


/*
 * Some frequently used masks
 *
 */
typedef enum __known_masks__
{
    DST_MASK      = 0b0000111000000000,
    SRC_MASK      = 0b0000000000000111,
    SIZE_MASK     = 0b0000000011000000,
    ADDRMODE_MASK = 0b0000000000111111

} KnownMasks;


#endif // __ENUMS_H__68000
