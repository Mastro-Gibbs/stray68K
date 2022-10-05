#include "memory.h"


void __show_ram__ (generic_u32_t _start, generic_u32_t _end);


ram_t *ram = NULL;


ram_t* init_ram(generic_u32_t size)
{
    if (!ram)
    {
        ram = malloc(sizeof (*ram));
        ram->ram = calloc(size, sizeof (generic_u8_t));

        ram->size = size;

        ram->show = __show_ram__;
    }

    return ram;
}

void erase()
{
    if (ram)
    {
        for (generic_u32_t iter = 0; iter < ram->size; iter++)
            ram->ram[iter] = 0x00;
    }
}

void destroy_ram()
{
    if (ram)
    {
        free(ram->ram);
        free(ram);
    }
}


void check_addr(generic_u32_t ptr, generic_u8_t limit)
{
    if (ptr > ram->size - limit)
        { PANIC("PANIC! %s\naddress: 0x%X\nlimit: 0x%X\nfinal address: 0x%X\n",
                "Segmentation fault: reading illegal memory address", ptr, ram->size, ptr + limit) }
}

void check_inst()
{
    if (!ram)
        { PANIC("PANIC! %s\n", "Segmentation fault: memory not initialized") }
}


/* MEMORY READ */
generic_u8_t* read_chunk(generic_u32_t pointer, generic_u32_t length)
{
    check_inst();
    check_addr(pointer, length);

    generic_u8_t *read = malloc(sizeof (generic_u8_t) * length);

    for (generic_u32_t iter = 0; iter < length; iter++)
        read[iter] = ram->ram[pointer + iter];

    return read;
}

generic_u8_t read_byte(generic_u32_t pointer)
{
    check_inst();
    check_addr(pointer, BYTE_SPAN);

    return ram->ram[pointer];
}

generic_u16_t read_word(generic_u32_t pointer)
{
    check_inst();
    check_addr(pointer, WORD_SPAN);

    return (generic_u16_t)((ram->ram[pointer] << 8) + ram->ram[pointer + 1]);
}

generic_u32_t read_long(generic_u32_t pointer)
{
    check_inst();
    check_addr(pointer, LONG_SPAN);

    return (generic_u32_t)((ram->ram[pointer] << 24) + (ram->ram[pointer + 1] << 16) + (ram->ram[pointer + 2] << 8) + ram->ram[pointer + 3]);
}



/* MEMORY WRITE */
void write_chunk(generic_u32_t pointer, generic_u8_t *value, generic_u32_t size)
{
    check_inst();
    check_addr(pointer, size);

    for (generic_u32_t iter = 0; iter < size; iter++)
        ram->ram[pointer + iter] = value[iter];
}

void write_byte(generic_u32_t pointer, generic_u8_t value)
{
    check_inst();
    check_addr(pointer, BYTE_SPAN);

    ram->ram[pointer] = value;
}

void write_word(generic_u32_t pointer, generic_u16_t value)
{
    check_inst();
    check_addr(pointer, WORD_SPAN);

    ram->ram[pointer]     = (generic_u8_t)((value >> 8) & 0xFF);
    ram->ram[pointer + 1] = (generic_u8_t)(value & 0xFF);
}

void write_long(generic_u32_t pointer, generic_u32_t value)
{
    check_inst();
    check_addr(pointer, LONG_SPAN);

    ram->ram[pointer]     = (generic_u8_t)((value >> 24) & 0xFF);
    ram->ram[pointer + 1] = (generic_u8_t)((value >> 16) & 0xFF);
    ram->ram[pointer + 2] = (generic_u8_t)((value >> 8)  & 0xFF);
    ram->ram[pointer + 3] = (generic_u8_t)(value & 0xFF);
}




void __show_ram__ (generic_u32_t _start, generic_u32_t _end)
{
    if ((_end * 128) > (ram->size - 1)) return;

    printf(" \033[01m\033[37mAddresses\033[0m | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
    printf("-----------|------------------------------------------------\n");

    printf("0x");
    short int i = 4;
    do {
        generic_u8_t inner = _start >> (8 * (i - 1));

        if (!inner || inner < 0xF) printf("0");

        printf("%X", inner);

        i--;
    } while (i);


    printf(" | ");

    for (generic_u32_t i = _start, j = 1; i < _end; i++, j++)
    {
        if (i == ram->size) return;

        generic_u8_t b = ram->ram[i];

        if (!b || b <= 0xF) printf("0");

        printf("%X", ram->ram[i]);
        printf(" ");

        if (j % 16 == 0 && (i+1) < _end) {
            printf("\n0x");

            short int k = 4;
            do {
                generic_u8_t inner = (i+1) >> (8 * (k - 1));

                if (!inner || inner < 0xF) printf("0");

                printf("%X", inner);

                k--;
            } while (k);

            printf(" | ");
        }
    }

    printf("\n\n");
}





