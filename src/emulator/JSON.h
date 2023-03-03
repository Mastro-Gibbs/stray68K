#ifndef __JSON_H__68000
#define __JSON_H__68000

#include "motorolatypes.h"


char* Jcpu(struct EmulationMachine* restrict emulator);

char* Jram(u32 from, u32 to, u32 sh);

char* Jchrono(u64 usec);

char* Jop(char *mnem, u32 code_promoted);

char* Jexception(char* cause, u32 type);

char* Jwarning(char* cause, char* mnem, u32 code_promoted);

char* Jio(char* io);

char* Jconcat2(struct EmulationMachine* restrict emulator, char *dst, char* (*Jsrc)(), ...);



#endif // __JSON_H__68000
