#ifndef __HANDLER_H__68000
#define __HANDLER_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "utils.h"
#include "cpu.h"
#include "ram.h"


void init_codes();
void destroy_codes();

generic_u32_t run_opcode(opcode code, bit describe_code);


#endif // __HANDLER_H__68000
