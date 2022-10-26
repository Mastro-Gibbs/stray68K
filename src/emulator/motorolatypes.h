#ifndef __MOTOROLATYPES_H__68000
#define __MOTOROLATYPES_H__68000

#include <regex.h>
#include <termios.h>

#define TRUE        1
#define FALSE       0

#define RAM_SIZE 0x00FFFFFF

typedef unsigned short int opcode;


/* CPU */
typedef unsigned short int srflags;
typedef unsigned char      bit;


/* UTILS */
typedef double             f64;
typedef float              f32;

typedef unsigned long      u64;
typedef unsigned int       u32;
typedef unsigned short int u16;
typedef unsigned char      u8;

typedef long               s64;
typedef int                s32;
typedef short int          s16;
typedef char               s8;


/* HANDLERS */
typedef unsigned short int bitmask;


//FORWARDING EMULATOR MACHINE COMPLEX STRUCT
struct EmulationMachine;

//CPU STRUCT
typedef struct __m68k__cpu__
{
    u32 data_r[8];  // D0..D7 -> data registers

    u32 addr_r[7];  // A0..A6 -> address registers

    u32 usp;        // aka A7 -> user stack pointer

    u32 ssp;        // system stack pointer

    u32 pc;         // program counter

    srflags sr;        // status register flags

    u32 (*exec) (struct EmulationMachine *em); // runner

    void (*show)();

} m68k_cpu;


//RAM STRUCT
typedef struct __m68k__ram__
{
    u8 *ram;
    u32 size;

    void (*show)  (u32 _start, u32 _end, u32 _ptr, char *pcptr_color);
    void (*stack) (u32 _top, u32 _bottom);

} m68k_ram;


//OPCODE STRUCT
typedef struct __m68k__opcode__
{
    opcode code;
    opcode mask;
    char*  mnemonic;

    u32 (*handler) (const opcode code);

} m68k_opcode;


//OPCODE WEREHOUSE DS
typedef struct __m68k__codemap__
{
    u8 key;
    u8 size;
    m68k_opcode  **instances;

} m68k_codemap;


//EMULATOR MACHINE COMPLEX STRUCT
struct EmulationMachine
{
    enum
    {
        EMULATE_STD = 0,
        EMULATE_SBS = 1
    } EmuType;

    enum
    {
        BEGIN_STATE     = 0,
        EXECUTION_STATE = 1,
        FINAL_STATE     = 2
    } State;

    struct
    {
        struct
        {
            bit enable;
            bit cpu;
            bit ram;
            bit timer;
            bit menm;
            bit ocode;
        } JSON;

        bit  descr;
        bit  quiet;
        bit  timer;
        char *path;
    } ExecArgs;

    struct
    {
        u32        size;
        regex_t    hex_rx;
        const char *hex_regex;
    } Loader;

    struct
    {
        m68k_cpu *cpu;
        m68k_ram *ram;

        struct
        {
            bit sbs_debugger;
            u32 simhalt;
            u32 orgptr;
            u32 lwb;
            u32 JSR_CALL_COUNTER;
        } Data;

        struct
        {
            struct termios oldt;
            struct termios newt;
        } Waiting;

        struct
        {
            struct timespec t_begin;
            struct timespec t_end;
            u64 dt;
        } Timer;

        struct
        {
            u16  code;
            char *mnemonic;
        } OpCode;

    } Machine;

};

#endif // __MOTOROLATYPES_H__68000
