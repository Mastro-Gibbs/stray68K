#ifndef __MOTOROLATYPES_H__68000
#define __MOTOROLATYPES_H__68000


typedef unsigned short int opcode;


/* CPU */
typedef unsigned short int srflags;
typedef unsigned char      bit;


/* UTILS */
typedef unsigned int       generic_u32_t;
typedef unsigned short int generic_u16_t;
typedef unsigned char      generic_u8_t;

typedef int       generic_32_t;
typedef short int generic_16_t;
typedef char      generic_8_t;


/* HANDLERS */
typedef unsigned short int bitmask;


//CPU STRUCT
typedef struct __m68k__cpu__
{
    generic_u32_t data_r[8];  // D0..D7 -> data registers

    generic_u32_t addr_r[7];  // A0..A6 -> address registers

    generic_u32_t  usp;        // aka A7 -> user stack pointer

    generic_u32_t  ssp;        // system stack pointer

    generic_u32_t  pc;         // program counter

    srflags sr;        // status register flags


    generic_u32_t (*exec) (bit describe_code); // runner

    void (*show)();

} m68k_cpu;


//RAM STRUCT
typedef struct __m68k__ram__
{
    generic_u8_t *ram;
    generic_u32_t size;

    void (*show)  (generic_u32_t _start, generic_u32_t _end, generic_u32_t _ptr, char *pcptr_color);
    void (*stack) (generic_u32_t _top, generic_u32_t _bottom);

} m68k_ram;


//OPCODE STRUCT
typedef struct __m68k__opcode__
{
    opcode code;
    opcode mask;
    char*  mnemonic;

    generic_u32_t (*handler) (const opcode code);

} m68k_opcode;


//OPCODE WEREHOUSE DS
typedef struct __m68k__codemap__
{
    generic_u8_t key;
    generic_u8_t size;
    m68k_opcode  **instances;

} m68k_codemap;

#endif // __MOTOROLATYPES_H__68000
