#include "memory.h"


void __show_ram__ (generic_u32_t _start, generic_u32_t _end, generic_u32_t _ptr);


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




void __show_ram__ (generic_u32_t _start, generic_u32_t _end, generic_u32_t _ptr)
{
    if ((_end * 128) > (ram->size - 1)) return;

    printf("\n                        [\033[01m\033[37mRAM STATUS\033[0m]\n\n");

    printf(" \033[01m\033[37mAddresses\033[0m | ");

    switch (_ptr & 0x0000000F) {
        case 0x00:
            printf("\033[93m00\033[0m 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x01:
            printf("00 \033[93m01\033[0m 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x02:
            printf("00 01 \033[93m02\033[0m 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x03:
            printf("00 01 02 \033[93m03\033[0m 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x04:
            printf("00 01 02 03 \033[93m04\033[0m 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x05:
            printf("00 01 02 03 04 \033[93m05\033[0m 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x06:
            printf("00 01 02 03 04 05 \033[93m06\033[0m 07 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x07:
            printf("00 01 02 03 04 05 06 \033[93m07\033[0m 08 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x08:
            printf("00 01 02 03 04 05 06 07 \033[93m08\033[0m 09 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x09:
            printf("00 01 02 03 04 05 06 07 08 \033[93m09\033[0m 0A 0B 0C 0D 0E 0F\n");
            break;

        case 0x0A:
            printf("00 01 02 03 04 05 06 07 08 09 \033[93m0A\033[0m 0B 0C 0D 0E 0F\n");
            break;

        case 0x0B:
            printf("00 01 02 03 04 05 06 07 08 09 0A \033[93m0B\033[0m 0C 0D 0E 0F\n");
            break;

        case 0x0C:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B \033[93m0C\033[0m 0D 0E 0F\n");
            break;

        case 0x0D:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C \033[93m0D\033[0m 0E 0F\n");
            break;

        case 0x0E:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D \033[93m0E\033[0m 0F\n");
            break;

        case 0x0F:
            printf("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E \033[93m0F\033[0m\n");
            break;
    }

    printf("-----------|------------------------------------------------\n");

    if (_ptr == _start || (_ptr > _start && _ptr < (_start + 0x10))) printf("\033[93m");

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
            if (!b || b <= 0xF) printf("\033[01m\033[93m0\033[0m");

            printf("\033[01m\033[93m%X\033[0m", b);
            printf(" ");
        }
        else
        {
            if (!b || b <= 0xF) printf("0");

            printf("%X", b);
            printf(" ");
        }

        if (j % 16 == 0 && (i+1) < _end) {
            if (_ptr == i || (_ptr > i && _ptr < (i + 0x10))) printf("\033[93m");

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





