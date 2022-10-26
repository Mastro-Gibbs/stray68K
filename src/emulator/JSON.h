#ifndef __JSON_H__68000
#define __JSON_H__68000

#include "motorolatypes.h"


char* Jcpu();

char* Jram(u32 from, u32 to);

char* Jstack(u32 from, u32 to);

char* Jchrono(u64 usec);

char* Jmnemonic(char *mnem);

char* Jcode(u16 code);



#endif // __JSON_H__68000
