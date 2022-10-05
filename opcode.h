#ifndef __OPCODE_H__68000
#define __OPCODE_H__68000

#include "motorolatypes.h"

typedef struct __opcode__
{
    opcode code;
    opcode mask;
    char*  mnemonic;

    generic_u32_t (*handler) (const opcode code);

} opcode_t;


opcode_t* new_opcode_t(const opcode bitcode, const bitmask mask, char *mnemonic, generic_u32_t (*handler)(const opcode code));


#endif // __OPCODE_H__68000

