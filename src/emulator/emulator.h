#ifndef __EMULATOR_H__68000
#define __EMULATOR_H__68000

#include "motorolatypes.h"

void 
begin_emulator(struct EmulationMachine* restrict emulator, const char *path);

void 
end_emulator(struct EmulationMachine* restrict emulator);

int emulate
(struct EmulationMachine* restrict emulator);

struct EmulationMachine
obtain_emulation_machine();


#endif // __EMULATOR_H__68000
