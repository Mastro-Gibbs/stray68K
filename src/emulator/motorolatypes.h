#ifndef __MOTOROLATYPES_H__68000
#define __MOTOROLATYPES_H__68000

#include <regex.h>
#include <termios.h>

//handler return types
#define RETURN_OK_PC_NO_INCR 2
#define RETURN_OK            1
#define RETURN_ERR           0

#define TRUE        1
#define FALSE       0

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

    u32 (*handler) ();

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
    enum { EMULATE_STD = 0, EMULATE_SBS = 1 } EmuType;

    struct
    {
        struct
        {
            bit is_activated;

            bit cpu;
            bit ram;
            bit chrono;
            bit op;
            bit io;

            bit concat;
            bit dump;
        } JSON;

        bit  descriptive_mode;
        bit  quiet_mode;
        bit  chrono_mode;
        char *executable_path;
    } ExecArgs;

    struct
    {
        m68k_cpu *cpu;
        m68k_ram *ram;

        enum
        {
            BEGIN_STATE     = 0,
            EXECUTION_STATE = 1,
            FINAL_STATE     = 2,
            PANIC_STATE     = 3,
            WARNING_STATE   = 4,
            TRAP_STATE      = 5,
            MERR_STATE      = 6,
            IO_STATE        = 7
        } State;

        struct
        {
            u16  operation_code;
            char *mnemonic;

            bit sbs_printer_enabler;
            u32 simhalt;
            u32 org_pointer;
            u32 last_loaded_byte_index;

            u32 JSR_CALL_COUNTER;
            u32 RAM_SIZE;
            u32 STACK_BOTTOM_INDEX;

            struct termios oldt;
            struct termios newt;
        } RuntimeData;

        struct
        {
            struct timespec t_begin;
            struct timespec t_end;
            u64 dt;
        } Chrono;

        struct
        {
            char panic_cause[200];
            char trap_cause [250];
            char merr_cause [250];

            enum { PANIC_EXC_TYPE = 0, TRAP_EXC_TYPE  = 1, MERR_EXC_TYPE  = 2 } Type;
        } Exception;

        struct
        {
            char *buffer;
            enum { INPUT = 0,    OUTPUT = 1,  IO_UNDEF = 2 } Type;
        } IO;

    } Machine;

};

#endif // __MOTOROLATYPES_H__68000
