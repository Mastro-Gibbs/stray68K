#include "memory.h"


void __show_ram__ (generic_u32_t _start, generic_u32_t _end, generic_u32_t _ptr, char *pcptr_color);
void __show_ram_stack__ (generic_u32_t _top, generic_u32_t _bottom);


ram_t *ram = NULL;


ram_t* init_ram(generic_u32_t size)
{
    if (!ram)
    {
        ram = malloc(sizeof (*ram));
        ram->ram = calloc(size, sizeof (generic_u8_t));

        ram->size = size;

        ram->show  = __show_ram__;
        ram->stack = __show_ram_stack__;
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
    if (ptr > ram->size)
        PANIC("Segmentation fault: reading illegal memory address\naddress: 0x%X\nlimit: 0x%X\nfinal address: 0x%X",
              ptr, ram->size, ptr + limit)
}

void check_inst()
{
    if (!ram)
        PANIC("Segmentation fault: memory not initialized")
}


/* MEMORY READ */
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




void __show_ram__ (generic_u32_t _start, generic_u32_t _end, generic_u32_t _ptr, char *pcptr_color)
{
    if (_start < 0x00FFFF00)
        printf("\n                        [\033[01m\033[37mRAM STATUS\033[0m]\n\n");

    printf(" \033[01m\033[37mAddresses\033[0m | ");

    switch (_ptr & 0x0000000F) {
        case 0x00:
            printf("%s00\033[0m 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x01:
            printf("00 %s01\033[0m 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x02:
            printf("00 01 %s02\033[0m 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x03:
            printf("00 01 02 %s03\033[0m 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x04:
            printf("00 01 02 03 %s04\033[0m 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x05:
            printf("00 01 02 03 04 %s05\033[0m 06 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x06:
            printf("00 01 02 03 04 05 %s06\033[0m 07 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x07:
            printf("00 01 02 03 04 05 06 %s07\033[0m 08 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x08:
            printf("00 01 02 03 04 05 06 07 %s08\033[0m 09 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x09:
            printf("00 01 02 03 04 05 06 07 08 %s09\033[0m 0A 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x0A:
            printf("00 01 02 03 04 05 06 07 08 09 %s0A\033[0m 0B 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x0B:
            printf("00 01 02 03 04 05 06 07 08 09 0A %s0B\033[0m 0C 0D 0E 0F\n", pcptr_color);
            break;

        case 0x0C:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B %s0C\033[0m 0D 0E 0F\n", pcptr_color);
            break;

        case 0x0D:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C %s0D\033[0m 0E 0F\n", pcptr_color);
            break;

        case 0x0E:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D %s0E\033[0m 0F\n", pcptr_color);
            break;

        case 0x0F:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E %s0F\033[0m\n", pcptr_color);
            break;
    }

    printf("-----------|------------------------------------------------\n");

    if (_ptr == _start || (_ptr > _start && _ptr < (_start + 0x10))) printf("%s", pcptr_color);

    printf("0x");
    short int i = 4;
    do {
        generic_u8_t inner = _start >> (8 * (i - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        i--;
    } while (i);

    if (_ptr == _start || (_ptr > _start && _ptr < (_start + 0x10))) printf("\033[0m");

    printf(" | ");

    for (generic_u32_t i = _start, j = 1; i < _end; i++, j++)
    {
        if (i == ram->size) return;

        generic_u8_t b = ram->ram[i];

        if (i == _ptr || i == (_ptr + 1))
        {
            if (!b || b <= 0xF) printf("\033[01m%s0\033[0m", pcptr_color);

            printf("\033[01m%s%X\033[0m", pcptr_color, b);
            printf(" ");
        }
        else
        {
            if (!b || b <= 0xF) printf("0");

            printf("%X", b);
            printf(" ");
        }

        if (j % 16 == 0 && (i+1) < _end) {
            if (_ptr == i || (_ptr > i && _ptr < (i + 0x10))) printf("%s", pcptr_color);

            printf("\n0x");

            short int k = 4;
            do {
                generic_u8_t inner = (i+1) >> (8 * (k - 1));

                if (!inner || inner <= 0xF) printf("0");

                printf("%X", inner);

                k--;
            } while (k);

            if (_ptr == i || (_ptr > i && _ptr < (i + 0x10))) printf("\033[0m");

            printf(" | ");
        }
    }

    printf("\n\n");
}


void __show_ram_stack__ (generic_u32_t _top, generic_u32_t _bottom)
{
    printf("\n     [\033[01m\033[37mSTACK STATUS\033[0m]\n");

    printf(" \033[01m\033[37mAddresses\033[0m | 01 02 03 04\n");
    printf("-----------|------------\n");

    printf("0x");
    short int i = 4;
    do {
        generic_u8_t inner = _top >> (8 * (i - 1));

        if (!inner || inner <= 0xF) printf("0");

        printf("%X", inner);

        i--;
    } while (i);

    printf(" | ");

    for (generic_u32_t i = _top, j = 1; i <= _bottom; i++, j++)
    {
        if (i > ram->size || i > _bottom) return;

        generic_u8_t b = ram->ram[i];

        if (!b || b <= 0xF) printf("0");

        printf("%X", b);
        printf(" ");


        if (j % 4 == 0 && (i+1) < _bottom) {

            printf("\n0x");

            short int k = 4;
            do {
                generic_u8_t inner = (i+1) >> (8 * (k - 1));

                if (!inner || inner <= 0xF) printf("0");

                printf("%X", inner);

                k--;
            } while (k);

            printf(" | ");
        }
    }

    printf("\n\n");
}





