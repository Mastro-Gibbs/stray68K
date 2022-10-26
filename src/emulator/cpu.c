#include "cpu.h"

#include <stdlib.h>
#include <string.h>


u32 __exec__(struct EmulationMachine *em);
void __show__();


m68k_cpu *cpu = NULL;

m68k_cpu* init_cpu()
{
    if (!cpu)
    {
        cpu = malloc(sizeof (*cpu));

        if (!cpu)
            PANIC("Cannot init cpu, aborting.")

        reset_cpu();

        init_codes();
    }

    return (cpu);
}


void reset_cpu()
{
    if (cpu)
    {
        unsigned char iter;
        for(iter = 0; iter < 8; iter++)
            cpu->data_r[iter] = 0x00000000;

        for(iter = 0; iter < 7; iter++)
            cpu->addr_r[iter] = 0x00000000;

        cpu->pc  = 0x00000000;
        cpu->usp = 0x00FF0000;
        cpu->ssp = 0x01000000;
        cpu->sr  = 0x2000;

        cpu->exec = __exec__;
        cpu->show = __show__;
    }
}


void destroy_cpu()
{
    if (cpu)
        free(cpu);

    destroy_codes();
}


u32 __exec__(struct EmulationMachine *em)
{
    u32 istruction_ptr = em->Machine.cpu->pc;

    if ((istruction_ptr % 2) != 0)
        PANIC("Segmentation fault while reading next istruction on odd address");

    em->Machine.OpCode.code = read_word(istruction_ptr);;

    return run_opcode(em);
}


void __show__()
{
    char d = 0x30, a = 0x30;
    char id[3];

    printf("\n                                                      [\033[01m\033[37mCPU STATUS\033[0m]\n\n");

    id[2] = '\0';

    id[0] = 'D';
    for (u8 i = 1; i <= 4; i++) // data regs
    {
        id[1] = d++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        u8 iter = 4;
        do
        {
            u8 inner = cpu->data_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    printf("| ");

    id[0] = 'A';
    for (u8 i = 1; i <= 4; i++) // addr regs
    {
        id[1] = a++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        u8 iter = 4;
        do
        {
            u8 inner = cpu->addr_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    printf("\n");
    id[0] = 'D';
    for (u8 i = 5; i <= 8; i++) // data regs
    {
        id[1] = d++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        u8 iter = 4;
        do
        {
            u8 inner = cpu->data_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    printf("| ");

    id[0] = 'A';
    for (u8 i = 4; i <= 6; i++) // addr regs
    {
        id[1] = a++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        u8 iter = 4;
        do
        {
            u8 inner = cpu->addr_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    u8 iter = 4;
    printf("\033[01m\033[37mA7\033[0m: 0x");

    u32 *curr = ((cpu->sr & SUPERVISOR) ? 1 : 0) ? &cpu->ssp : &cpu->usp;

    do
    {
        u8 inner = *curr >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    printf("\n");

    printf("-------------------------------------------------------------------------------------------------------------------------\n");

    iter = 4;
    printf("\033[01m\033[37mUS\033[0m: 0x");
    do
    {
        u8 inner = cpu->usp >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    printf("\n");

    iter = 4;
    printf("\033[01m\033[37mSS\033[0m: 0x");
    do
    {
        u8 inner = cpu->ssp >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    iter = 4;
    printf("\n\033[01m\033[37mPC\033[0m: 0x");
    do
    {
        u8 inner = cpu->pc >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    srflags SR = cpu->sr;

    printf("\n");

    bprintf_ht(SR);

    printf("\033[01m\033[37m    t s        xnzvc\033[0m\n");

}




// DATA REGS GETTER & SETTER
u32 read_datareg(u32 reg)
{
    if (reg < 8)
        return cpu->data_r[reg];

    return (0);
}

/*
 * @param size is ptr, we can pass NULL value to get the default (LONG)
 */
void  write_datareg(u32 reg, u32 val, opsize *size)
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
                cpu->data_r[reg] = (cpu->data_r[reg] & 0xFFFFFF00) | (val & 0x000000FF);
            break;

            case WORD:
                cpu->data_r[reg] = (cpu->data_r[reg] & 0xFFFF0000) | (val & 0x0000FFFF);
            break;

            case LONG:
                cpu->data_r[reg] = val;
            break;
            default: //dummy, cant flow here
            break;

        }
    }
}

u32 read_addrreg(u32 reg)
{
    if (reg < 8)
    {
        if (reg < 7)
            return cpu->addr_r[reg];

        else if (reg == 7)

            return ((cpu->sr & SUPERVISOR) ? 1 : 0) ? cpu->ssp : cpu->usp;
    }

    return (0);
}

/*
 * @param size is ptr, we can pass NULL value to get the default (LONG)
 */
void  write_addrreg(u32 reg, u32 val, opsize *size)
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
                cpu->addr_r[reg] = (cpu->addr_r[reg] & 0xFFFFFF00) | (val & 0x000000FF);
            break;

            case WORD:
                cpu->addr_r[reg] = (cpu->addr_r[reg] & 0xFFFF0000) | (val & 0x0000FFFF);
            break;

            case LONG:
                cpu->addr_r[reg] = val;
            break;
            default:
            break;

        }
    }
    else if (reg == 7)
    {
        if ((cpu->sr & SUPERVISOR) ? 1 : 0)
        {
            switch (static_size)
            {
                case BYTE:
                    cpu->ssp = (cpu->ssp & 0xFFFFFF00) | (val & 0x000000FF);
                break;

                case WORD:
                    cpu->ssp = (cpu->ssp & 0xFFFF0000) | (val & 0x0000FFFF);
                break;

                case LONG:
                    cpu->ssp = val;
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
                    cpu->usp = (cpu->usp & 0xFFFFFF00) | (val & 0x000000FF);
                break;

                case WORD:
                    cpu->usp = (cpu->usp & 0xFFFF0000) | (val & 0x0000FFFF);
                break;

                case LONG:
                    cpu->usp = val;
                break;
                default: //dummy, cant flow here
                break;

            }
        }
    }
}

void incr_addr_reg(u32 reg, opsize size)
{
    u32 tmp = read_addrreg(reg);

    if (size == LONG)
        tmp += 4; //LONG
    else if (size == WORD)
        tmp += 2; //WORD
    else
        tmp += 1; //BYTE

    write_addrreg(reg, tmp, NULL);
}

void decr_addr_reg(u32 reg, opsize size)
{
    u32 tmp = read_addrreg(reg);

    if (size == LONG)
        tmp -= 4; //LONG
    else if (size == WORD)
        tmp -= 2; //WORD
    else
        tmp -= 1; //BYTE

    write_addrreg(reg, tmp, NULL);
}



/* STACKS */
u16 pop_word()
{
    u32 stack = read_addrreg(7);
    u16 value = read_word(stack);
    stack += WORD_SPAN;
    write_addrreg(7, stack, NULL);

    return (value);
}

u32 pop_long()
{
    u32 stack = read_addrreg(7);
    u32 value = read_long(stack);
    stack += LONG_SPAN;
    write_addrreg(7, stack, NULL);

    return (value);
}

void push_word(u16 word)
{
    u32 stack = read_addrreg(7);
    stack -= WORD_SPAN;
    write_addrreg(7, stack, NULL);
    write_word(stack, word);
}

void push_long(u32 longword)
{
    u32 stack = read_addrreg(7);
    stack -= LONG_SPAN;
    write_addrreg(7, stack, NULL);
    write_long(stack, longword);
}



/* CONDITION CODES */
bit eval_cc(CCm cc)
{
    switch (cc) {
        case T:
            return 1;
        case F:
            return 0;
        case HI:
            return !(cpu->sr & ZERO) && !(cpu->sr & CARRY);
        case LS:
            return (cpu->sr & ZERO) || (cpu->sr & CARRY);
        case CC:
            return !(cpu->sr & CARRY);
        case CS:
            return (cpu->sr & CARRY);
        case NE:
            return !(cpu->sr & ZERO);
        case EQ:
            return (cpu->sr & ZERO);
        case VC:
            return !(cpu->sr & OVERFLOW);
        case VS:
            return (cpu->sr & OVERFLOW);
        case PL:
            return !(cpu->sr & NEGATIVE);
        case MI:
            return (cpu->sr & NEGATIVE);
        case GE:
            return (cpu->sr & NEGATIVE) == (cpu->sr & OVERFLOW);
        case LT:
            return (cpu->sr & NEGATIVE) != (cpu->sr & OVERFLOW);
        case GT:
            return !(cpu->sr & ZERO) && ((cpu->sr & NEGATIVE) == (cpu->sr & OVERFLOW));
        case LE:
            return (cpu->sr & ZERO) || ((cpu->sr & NEGATIVE) != (cpu->sr & OVERFLOW));
        default:
            return 0;
    }
}



/* PROGRAM COUNTER */
void set_pc(u32 pc) { cpu->pc = pc; }

u32 get_pc() { return (cpu->pc); }


