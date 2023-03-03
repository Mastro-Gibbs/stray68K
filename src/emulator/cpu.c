#include "cpu.h"

#include <stdlib.h>
#include <string.h>


void init_cpu(struct EmulationMachine *emulator)
{
    reset_cpu(emulator);
}


void reset_cpu(struct EmulationMachine* restrict emulator)
{
    unsigned char iter;
    for(iter = 0; iter < 8; iter++)
        emulator->Machine.cpu.data_r[iter] = 0x00000000;

    for(iter = 0; iter < 7; iter++)
        emulator->Machine.cpu.addr_r[iter] = 0x00000000;

    emulator->Machine.cpu.pc  = 0x00000000;
    emulator->Machine.cpu.usp = 0x00FF0000;
    emulator->Machine.cpu.ssp = 0x01000000;
    emulator->Machine.cpu.sr  = 0x2000;
    
}


// DATA REGS GETTER & SETTER
u32 read_datareg(struct EmulationMachine* restrict emulator, const u32 reg)
{
    if (reg < 8)
        return emulator->Machine.cpu.data_r[reg];

    return (0);
}

/*
 * @param size is ptr, we can pass NULL value to get the default (LONG)
 */
void  write_datareg(struct EmulationMachine* restrict emulator, const u32 reg, const u32 val, opsize* const size)
{
    opsize static_size;

    if (size)
        static_size = *size;
    else
        static_size = LONG;

    if (reg < 8)
    {
        switch (static_size)
        {
            case BYTE:
                emulator->Machine.cpu.data_r[reg] = (emulator->Machine.cpu.data_r[reg] & 0xFFFFFF00) | (val & 0x000000FF);
            break;

            case WORD:
                emulator->Machine.cpu.data_r[reg] = (emulator->Machine.cpu.data_r[reg] & 0xFFFF0000) | (val & 0x0000FFFF);
            break;

            case LONG:
                emulator->Machine.cpu.data_r[reg] = val;
            break;
            default: //dummy, cant flow here
            break;

        }
    }
}

u32 read_addrreg(struct EmulationMachine* restrict emulator, const u32 reg)
{
    if (reg < 8)
    {
        if (reg < 7)
            return emulator->Machine.cpu.addr_r[reg];

        else if (reg == 7)

            return ((emulator->Machine.cpu.sr & SUPERVISOR) ? 1 : 0) ? emulator->Machine.cpu.ssp : emulator->Machine.cpu.usp;
    }

    return (0);
}

/*
 * @param size is ptr, we can pass NULL value to get the default (LONG)
 */
void  write_addrreg(struct EmulationMachine* restrict emulator, const u32 reg, const u32 val, opsize* const size)
{
    if (reg > 7) return;

    opsize static_size;

    if (size)
        static_size = *size;
    else
        static_size = LONG;

    if (reg < 7)
    {
        switch (static_size)
        {
            case BYTE:
                emulator->Machine.cpu.addr_r[reg] = (emulator->Machine.cpu.addr_r[reg] & 0xFFFFFF00) | (val & 0x000000FF);
            break;

            case WORD:
                emulator->Machine.cpu.addr_r[reg] = (emulator->Machine.cpu.addr_r[reg] & 0xFFFF0000) | (val & 0x0000FFFF);
            break;

            case LONG:
                emulator->Machine.cpu.addr_r[reg] = val;
            break;
            default:
            break;

        }
    }
    else if (reg == 7)
    {
        if ((emulator->Machine.cpu.sr & SUPERVISOR) ? 1 : 0)
        {
            switch (static_size)
            {
                case BYTE:
                    emulator->Machine.cpu.ssp = (emulator->Machine.cpu.ssp & 0xFFFFFF00) | (val & 0x000000FF);
                break;

                case WORD:
                    emulator->Machine.cpu.ssp = (emulator->Machine.cpu.ssp & 0xFFFF0000) | (val & 0x0000FFFF);
                break;

                case LONG:
                    emulator->Machine.cpu.ssp = val;
                break;
                default: //dummy, cant flow here
                break;

            }
        }
        else
        {
            switch (static_size)
            {
                case BYTE:
                    emulator->Machine.cpu.usp = (emulator->Machine.cpu.usp & 0xFFFFFF00) | (val & 0x000000FF);
                break;

                case WORD:
                    emulator->Machine.cpu.usp = (emulator->Machine.cpu.usp & 0xFFFF0000) | (val & 0x0000FFFF);
                break;

                case LONG:
                    emulator->Machine.cpu.usp = val;
                break;
                default: //dummy, cant flow here
                break;

            }
        }
    }
}

void incr_addr_reg(struct EmulationMachine* restrict emulator, const u32 reg, const opsize size)
{
    u32 tmp = read_addrreg(emulator, reg);

    if (size == LONG)
        tmp += 4; //LONG
    else if (size == WORD)
        tmp += 2; //WORD
    else
        tmp += 1; //BYTE

    write_addrreg(emulator, reg, tmp, NULL);
}

void decr_addr_reg(struct EmulationMachine* restrict emulator, const u32 reg, const opsize size)
{
    u32 tmp = read_addrreg(emulator, reg);

    if (size == LONG)
        tmp -= 4; //LONG
    else if (size == WORD)
        tmp -= 2; //WORD
    else
        tmp -= 1; //BYTE

    write_addrreg(emulator, reg, tmp, NULL);
}



/* STACKS */
u16 pop_word(struct EmulationMachine* restrict emulator)
{
    u32 stack = read_addrreg(emulator, 7);
    u16 value = read_word(emulator, stack);
    stack += WORD_SPAN;
    write_addrreg(emulator, 7, stack, NULL);

    return (value);
}

u32 pop_long(struct EmulationMachine* restrict emulator)
{
    u32 stack = read_addrreg(emulator, 7);
    u32 value = read_long(emulator, stack);
    stack += LONG_SPAN;
    write_addrreg(emulator, 7, stack, NULL);

    return (value);
}

void push_word(struct EmulationMachine* restrict emulator, const u16 word)
{
    u32 stack = read_addrreg(emulator, 7);
    stack -= WORD_SPAN;
    write_addrreg(emulator, 7, stack, NULL);
    write_word(emulator, stack, word);
}

void push_long(struct EmulationMachine* restrict emulator, const u32 longword)
{
    u32 stack = read_addrreg(emulator, 7);
    stack -= LONG_SPAN;
    write_addrreg(emulator, 7, stack, NULL);
    write_long(emulator, stack, longword);
}



/* CONDITION CODES */
bit eval_cc(struct EmulationMachine* restrict emulator, const CCm cc)
{
    switch (cc) {
        case T:
            return 1;
        case F:
            return 0;
        case HI:
            return !(emulator->Machine.cpu.sr & ZERO) && !(emulator->Machine.cpu.sr & CARRY);
        case LS:
            return (emulator->Machine.cpu.sr & ZERO) || (emulator->Machine.cpu.sr & CARRY);
        case CC:
            return !(emulator->Machine.cpu.sr & CARRY);
        case CS:
            return (emulator->Machine.cpu.sr & CARRY);
        case NE:
            return !(emulator->Machine.cpu.sr & ZERO);
        case EQ:
            return (emulator->Machine.cpu.sr & ZERO);
        case VC:
            return !(emulator->Machine.cpu.sr & OVERFLOW);
        case VS:
            return (emulator->Machine.cpu.sr & OVERFLOW);
        case PL:
            return !(emulator->Machine.cpu.sr & NEGATIVE);
        case MI:
            return (emulator->Machine.cpu.sr & NEGATIVE);
        case GE:
            return (emulator->Machine.cpu.sr & NEGATIVE) == (emulator->Machine.cpu.sr & OVERFLOW);
        case LT:
            return (emulator->Machine.cpu.sr & NEGATIVE) != (emulator->Machine.cpu.sr & OVERFLOW);
        case GT:
            return !(emulator->Machine.cpu.sr & ZERO) && ((emulator->Machine.cpu.sr & NEGATIVE) == (emulator->Machine.cpu.sr & OVERFLOW));
        case LE:
            return (emulator->Machine.cpu.sr & ZERO) || ((emulator->Machine.cpu.sr & NEGATIVE) != (emulator->Machine.cpu.sr & OVERFLOW));
        default:
            return 0;
    }
}



/* PROGRAM COUNTER */
void set_pc(struct EmulationMachine* restrict emulator, const u32 pc) { emulator->Machine.cpu.pc = pc; }

u32 get_pc(struct EmulationMachine* restrict emulator) { return (emulator->Machine.cpu.pc); }


