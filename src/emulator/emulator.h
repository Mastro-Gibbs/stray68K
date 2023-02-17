#ifndef __EMULATOR_H__68000
#define __EMULATOR_H__68000

#include "motorolatypes.h"

int 
is_last_istr(struct EmulationMachine* emulator);

void 
begin_emulator(struct EmulationMachine* emulator);

void 
end_emulator(struct EmulationMachine* emulator);

int emulate
(struct EmulationMachine* emulator);

struct EmulationMachine*
obtain_emulation_machine(const char *path);


#endif // __EMULATOR_H__68000
