#ifndef __ENUMS_H__68000
#define __ENUMS_H__68000

#include "motorolatypes.h"


typedef enum __operation_size_span__
{
    BYTE_SPAN = 0x01,
    WORD_SPAN = 0x02,
    LONG_SPAN = 0x04

} opsize_span;



typedef enum __operation_size__
{
    BYTE  = 0b00000000, // 00
    WORD  = 0b00000001, // 01
    LONG  = 0b00000010, // 10
    BYTE2 = 0b00000001, // 01
    WORD2 = 0b00000011  // 11


} opsize;


typedef enum __status_register_flags__
{
    CARRY    = 0x01,
    OVERFLOW = 0x02,
    ZERO     = 0x04,
    NEGATIVE = 0x08,
    EXTEND   = 0x10,
    SUPERVISOR = 0x2000,
    TRACE      = 0x8000

} srflag_bits;


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


typedef enum __effective_address_type__
{
    NORMAL   = 0x00,
    INVERTED = 0x01
} ea_direction;


typedef enum __direction__mode__
{
    DATAREG   = 0x00,
    MEMORYPD  = 0x01
} direction_mode;


typedef enum __rotation_direction__
{
    LEFT  = 1,
    RIGHT = 0
} Rot;


typedef enum __storing__direction__
{
    MEMORY_REGISTER = 0x00,
    REGISTER_MEMORY = 0x01,
    INVERTED_MEMORY_REGISTER = 0x01,
    INVERTED_REGISTER_MEMORY = 0x00

} Sdirection;


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

enum __ignore_direction__
{
    IGNORE_DIRECTION = 0,
    USE_DIRECTION    = 1
};


typedef enum __bcd_type__
{
    ADDICTION   = 0,
    SUBTRACTION = 1
} BCD_type;

#endif // __ENUMS_H__68000
