#include "cpu.h"

#include <stdlib.h>
#include <string.h>


generic_u32_t __exec__(bit describe_code);
void     __show__();


cpu_t *cpu = NULL;

cpu_t* init_cpu()
{
    if (!cpu)
    {
        cpu = malloc(sizeof (*cpu));

        reset_cpu();

        init_codes();
    }
    return cpu;
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


generic_u32_t __exec__(bit describe_code)
{
    return run_opcode(read_word(get_pc()), describe_code);
}


void __show__()
{
    char d = 0x30, a = 0x30;
    char id[3];
    id[2] = '\0';

    id[0] = 'D';
    for (generic_u8_t i = 1; i <= 4; i++) // data regs
    {
        id[1] = d++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        generic_u8_t iter = 4;
        do
        {
            generic_u8_t inner = cpu->data_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    printf("| ");

    id[0] = 'A';
    for (generic_u8_t i = 1; i <= 4; i++) // addr regs
    {
        id[1] = a++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        generic_u8_t iter = 4;
        do
        {
            generic_u8_t inner = cpu->addr_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    printf("\n");
    id[0] = 'D';
    for (generic_u8_t i = 5; i <= 8; i++) // data regs
    {
        id[1] = d++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        generic_u8_t iter = 4;
        do
        {
            generic_u8_t inner = cpu->data_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    printf("| ");

    id[0] = 'A';
    for (generic_u8_t i = 4; i <= 6; i++) // addr regs
    {
        id[1] = a++;
        printf("\033[01m\033[37m%s\033[0m: 0x", id);

        generic_u8_t iter = 4;
        do
        {
            generic_u8_t inner = cpu->addr_r[i-1] >> (8 * (iter - 1));

            if (!inner || inner <= 0xF) printf("0");

            printf("%X", inner);

            iter -= 1;
        } while (iter);

        printf(" ");
    }

    generic_u8_t iter = 4;
    printf("\033[01m\033[37mA7\033[0m: 0x");

    generic_u32_t *curr = get_supervisor() ? &cpu->ssp : &cpu->usp;

    do
    {
        generic_u8_t inner = *curr >> (8 * (iter - 1));

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
        generic_u8_t inner = cpu->usp >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    printf("\n");

    iter = 4;
    printf("\033[01m\033[37mSS\033[0m: 0x");
    do
    {
        generic_u8_t inner = cpu->ssp >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    iter = 4;
    printf("\n\033[01m\033[37mPC\033[0m: 0x");
    do
    {
        generic_u8_t inner = cpu->pc >> (8 * (iter - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        iter -= 1;
    } while (iter);

    srflags SR = cpu->sr;

    printf("\n");

    bprintf_ht(SR);

    printf("\033[01m\033[37m    t s        xnzvc\033[0m\n");

}



// FLAGS GETTER & SETTER

bit get_carry()
{
    return cpu->sr & CARRY;
}

void  set_carry(bit bit)
{
    if (bit)
        cpu->sr |= CARRY;
    else
        cpu->sr &= ~CARRY;
}


bit get_overflow()
{
    return cpu->sr & OVERFLOW;
}

void  set_overflow(bit bit)
{
    if (bit)
        cpu->sr |= OVERFLOW;
    else
        cpu->sr &= ~OVERFLOW;
}

bit get_zero()
{
    return cpu->sr & ZERO;
}

void  set_zero(bit bit)

{
    if (bit)
        cpu->sr |= ZERO;
    else
        cpu->sr &= ~ZERO;
}

bit get_negative()
{
    return cpu->sr & NEGATIVE;
}

void  set_negative(bit bit)
{
    if (bit)
        cpu->sr |= NEGATIVE;
    else
        cpu->sr &= ~NEGATIVE;
}

bit get_extended()
{
    return cpu->sr & EXTEND;
}

void  set_extended(bit bit)
{
    if (bit)
        cpu->sr |= EXTEND;
    else
        cpu->sr &= ~EXTEND;
}


bit get_supervisor()
{
    unsigned int tmp = cpu->sr & SUPERVISOR;

    return (tmp ? 1 : 0);
}

void  set_supervisor(bit bit)
{
    if (bit)
        cpu->sr |= SUPERVISOR;
    else
        cpu->sr &= ~SUPERVISOR;
}

bit get_trace()
{
    unsigned int tmp = cpu->sr & TRACE;

    return (tmp ? 1 : 0);
}

void  set_trace(bit bit)
{
    if (bit)
        cpu->sr |= TRACE;
    else
        cpu->sr &= ~TRACE;
}



// DATA REGS GETTER & SETTER
generic_u32_t read_datareg(generic_u32_t reg)
{
    if (reg < 8)
        return cpu->data_r[reg];

    return 0;
}

/*
 * @param size is ptr, we can pass NULL value to get the default (LONG)
 */
void  write_datareg(generic_u32_t reg, generic_u32_t val, opsize *size)
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

generic_u32_t read_addrreg(generic_u32_t reg)
{
    if (reg < 8)
    {
        if (reg < 7)
            return cpu->addr_r[reg];

        else if (reg == 7)

            return get_supervisor() ? cpu->ssp : cpu->usp;
    }

    return 0;
}

/*
 * @param size is ptr, we can pass NULL value to get the default (LONG)
 */
void  write_addrreg(generic_u32_t reg, generic_u32_t val, opsize *size)
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
        if (get_supervisor())
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

void incr_addr_reg(generic_u32_t reg, opsize size)
{
    generic_u32_t tmp = read_addrreg(reg);

    if (size == LONG)
        tmp += 4; //LONG
    else if (size == WORD)
        tmp += 2; //WORD
    else
        tmp += 1; //BYTE

    write_addrreg(reg, tmp, NULL);
}

void decr_addr_reg(generic_u32_t reg, opsize size)
{
    generic_u32_t tmp = read_addrreg(reg);

    if (size == LONG)
        tmp -= 4; //LONG
    else if (size == WORD)
        tmp -= 2; //WORD
    else
        tmp -= 1; //BYTE

    write_addrreg(reg, tmp, NULL);
}


srflags get_sr() { return cpu->sr; }

void set_sr(srflags bits) { cpu->sr = bits; }






/* STACKS */
generic_u16_t pop_word()
{
    generic_u32_t stack = read_addrreg(7);
    generic_u16_t value = read_word(stack);
    stack += WORD_SPAN;
    write_addrreg(7, stack, NULL);

    return value;
}

generic_u32_t pop_long()
{
    generic_u32_t stack = read_addrreg(7);
    generic_u32_t value = read_long(stack);
    stack += LONG_SPAN;
    write_addrreg(7, stack, NULL);

    return value;
}

void push_word(generic_u16_t word)
{
    generic_u32_t stack = read_addrreg(7);
    stack -= WORD_SPAN;
    write_addrreg(7, stack, NULL);
    write_word(stack, word);
}

void push_long(generic_u32_t longword)
{
    generic_u32_t stack = read_addrreg(7);
    stack -= LONG_SPAN;
    write_addrreg(7, stack, NULL);
    write_long(stack, longword);
}


generic_u32_t get_stack_ptr()
{
    return get_supervisor() ? cpu->ssp : cpu->usp;
}


void set_usp(generic_u32_t ptr)
{
    cpu->usp = ptr;
}

generic_u32_t get_usp()
{
    return cpu->usp;
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
            return !get_zero() && !get_carry();
        case LS:
            return get_zero() || get_carry();
        case CC:
            return !get_carry();
        case CS:
            return get_carry();
        case NE:
            return !get_zero();
        case EQ:
            return get_zero();
        case VC:
            return !get_overflow();
        case VS:
            return get_overflow();
        case PL:
            return !get_negative();
        case MI:
            return get_negative();
        case GE:
            return get_negative() == get_overflow();
        case LT:
            return get_negative() != get_overflow();
        case GT:
            return !get_zero() && (get_negative() == get_overflow());
        case LE:
            return get_zero() || (get_negative() != get_overflow());
        default:
            return 0;
    }
}



/* PROGRAM COUNTER */
void set_pc(generic_u32_t pc) { cpu->pc = pc; }

void incr_pc(bit bits) { cpu->pc += bits; }

generic_u32_t get_pc() { return cpu->pc; }


