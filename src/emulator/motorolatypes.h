#ifndef __MOTOROLATYPES_H__68000
#define __MOTOROLATYPES_H__68000

#include <regex.h>
#include <termios.h>

#define RAM_MAX_SIZE 0x00FFFFFF

// handler return types
#define RETURN_OK_PC_NO_INCR 2
#define RETURN_OK 1
#define RETURN_ERR 0
#define RETURN_FINISH 0

typedef unsigned short int opcode;

/* CPU */
typedef unsigned short int srflags;
typedef unsigned char bit;

/* UTILS */
typedef double f64;
typedef float f32;

typedef unsigned long u64;
typedef unsigned int u32;
typedef unsigned short int u16;
typedef unsigned char u8;

typedef long s64;
typedef int s32;
typedef short int s16;
typedef char s8;

/* HANDLERS */
typedef unsigned short int bitmask;

typedef unsigned char c_bool;

enum
{
    c_false = 0,
    c_true = 1
};

// FORWARDING EMULATOR MACHINE COMPLEX STRUCT
struct EmulationMachine;

// CPU STRUCT
typedef struct __m68k__cpu__
{
    u32 data_r[8]; // D0..D7 -> data registers

    u32 addr_r[7]; // A0..A6 -> address registers

    u32 usp; // aka A7 -> user stack pointer

    u32 ssp; // system stack pointer

    u32 pc; // program counter

    srflags sr; // status register flags

} m68k_cpu;

// RAM STRUCT
typedef struct __m68k__ram__
{
    u8 self[0x01000000];
    u32 size;

} m68k_ram;

// OPCODE STRUCT
typedef struct __m68k__opcode__
{
    opcode code;
    opcode mask;
    char *mnemonic;

    u32 (*handler)(struct EmulationMachine *emulator);

} m68k_opcode;

// OPCODE WEREHOUSE DS
typedef struct __m68k__codemap__
{
    u8 key;
    u8 size;
    m68k_opcode **instances;

} m68k_codemap;

// EMULATOR MACHINE COMPLEX STRUCT
struct EmulationMachine
{
    char* binary_path;

    struct
    {
        char *dump;

        m68k_cpu cpu;
        m68k_ram ram;
        struct __m68k__codemap__ *codemap;

        enum
        {
            BEGIN_STATE = 0,
            EXECUTION_STATE = 1,
            FINAL_STATE = 2,
            PANIC_STATE = 3,
            WARNING_STATE = 4,
            TRAP_STATE = 5,
            MERR_STATE = 6,
            IO_STATE = 7,
            SLEEP_STATE = 8
        } State;

        struct
        {
            u16 operation_code;
            char *mnemonic;

            u32 simhalt;
            u32 org_pointer;
            u32 last_loaded_byte_index;

            u32 JSR_CALL_COUNTER;
            u32 STACK_BOTTOM_INDEX;

            struct termios oldt;
            struct termios newt;

            struct
            {
                struct timespec t_begin;
                struct timespec t_end;
                u64 dt;
            } Chrono;

            struct
            {
                char panic_cause[200];
                char trap_cause[250];
                char merr_cause[250];

                enum
                {
                    PANIC_EXC_TYPE = 0,
                    TRAP_EXC_TYPE = 1,
                    MERR_EXC_TYPE = 2
                } Type;
            } Exception;

            struct
            {
                char mnem[10];
                u32 code;
                char cause[250];
            } Warning;

        } RunTime;

        struct
        {
            char *buffer;
            enum
            {
                INPUT = 0,
                OUTPUT = 1,
                IO_UNDEF = 2
            } Type;

            struct
            {
                s8 self[4096];
                u32 _pos;
                c_bool _valid;
                c_bool _able;

            } InputBuffer;
        } IO;

    } Machine;
};

#endif // __MOTOROLATYPES_H__68000
