#include "ram.h"


void __show_ram__ (u32 _start, u32 _end, u32 _ptr, char *pcptr_color);
void __show_ram_stack__ (u32 _top, u32 _bottom);


struct EmulationMachine *emulator;
m68k_ram *ram = NULL;



m68k_ram* init_ram(struct EmulationMachine *em)
{
    if (!ram)
    {
        emulator = em;

        ram = malloc(sizeof (*ram));

        if (!ram)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Cannot init ram, aborting.");
            return (NULL);
        }

        ram->ram = calloc(em->Machine.RuntimeData.RAM_SIZE, sizeof (u8));

        if (!ram->ram)
        {
            em->Machine.State = PANIC_STATE;
            sprintf(em->Machine.Exception.panic_cause, "Cannot init ram, aborting.");
            return (NULL);
        }

        ram->size = em->Machine.RuntimeData.RAM_SIZE;
    }

    return (ram);
}

m68k_ram* get_ram(void)
{
    return (ram);
}

void erase_ram(void)
{
    if (ram)
    {
        for (u32 iter = 0; iter < ram->size; iter++)
            ram->ram[iter] = 0x00;

        ram->ram = NULL;
    }

    ram = NULL;
}

void destroy_ram(void)
{
    if (ram)
    {
        if (ram->ram)
            free(ram->ram);

        free(ram);
    }
}


void check_addr(u32 pointer, u32 iospan)
{
    if ((pointer + iospan) > (ram->size + 1))
    {
        char panic_str[200];
        sprintf(panic_str, "Seg-fault: illegal memory address, address: 0x%X, limit: 0x%X",
                 pointer + iospan, ram->size);

        emulator->Machine.State = PANIC_STATE;

        PANIC(panic_str);

        exit(EXIT_FAILURE);
    }
}


/* MEMORY READ */
u8 read_byte(const u32 pointer)
{
    check_addr(pointer, BYTE_SPAN);

    return ram->ram[pointer];
}

u16 read_word(const u32 pointer)
{
    check_addr(pointer, WORD_SPAN);

    return (u16)((ram->ram[pointer] << 8) + ram->ram[pointer + 1]);
}

u32 read_long(const u32 pointer)
{
    check_addr(pointer, LONG_SPAN);

    return (u32)((ram->ram[pointer] << 24) + (ram->ram[pointer + 1] << 16) + (ram->ram[pointer + 2] << 8) + ram->ram[pointer + 3]);
}



/* MEMORY WRITE */
void write_byte(const u32 pointer, const u8 value)
{
    check_addr(pointer, BYTE_SPAN);

    ram->ram[pointer] = value;
}

void write_word(const u32 pointer, const u16 value)
{
    check_addr(pointer, WORD_SPAN);

    ram->ram[pointer]     = (u8)((value >> 8) & 0xFF);
    ram->ram[pointer + 1] = (u8)(value & 0xFF);
}

void write_long(const u32 pointer, const u32 value)
{
    check_addr(pointer, LONG_SPAN);

    ram->ram[pointer]     = (u8)((value >> 24) & 0xFF);
    ram->ram[pointer + 1] = (u8)((value >> 16) & 0xFF);
    ram->ram[pointer + 2] = (u8)((value >> 8)  & 0xFF);
    ram->ram[pointer + 3] = (u8)(value & 0xFF);
}



