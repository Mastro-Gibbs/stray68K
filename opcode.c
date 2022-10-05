#include "opcode.h"

#include <stdlib.h>


opcode_t* new_opcode_t(const opcode bitcode, const bitmask mask, char *mnemonic, generic_u32_t (*handler)(const opcode))
{
    struct __opcode__ *newopcode = malloc(sizeof (*newopcode));

    if (newopcode)
    {
        newopcode->code     = bitcode;
        newopcode->mask     = mask;
        newopcode->mnemonic = mnemonic;
        newopcode->handler  = handler;

        return newopcode;
    }

    return NULL;
}
