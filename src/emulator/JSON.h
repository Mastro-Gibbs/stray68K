#ifndef __JSON_H__68000
#define __JSON_H__68000

#include "motorolatypes.h"


char* Jcpu();

char* Jram(u32 from, u32 to, u32 sh);

char* Jstack(u32 from, u32 to);

char* Jchrono(u64 usec);

char* Jop(char *mnem, u32 code_promoted);

char* Jexception(char* cause, u32 type);

char* Jio(char* io, u32 type, u32 nl);

char* Jconcat(char *dst, char *src);

char* Jconcat2(char *dst, char* (*Jsrc)(), ...);



#endif // __JSON_H__68000
