#include "JSON.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "cpu.h"
#include "ram.h"


char* Jcpu(struct EmulationMachine* emulator)
{
    char *res = NULL;
    char buf[410];

    sprintf(buf, "%s", "{\"CPU\":{");

    for (u16 i = 0; i < 8; i++)
    {
        sprintf(buf+strlen(buf), "\"D%d\":\"%X\",", i, emulator->Machine.cpu.data_r[i]);
    }

    for (u16 i = 0; i < 7; i++)
    {
        sprintf(buf+strlen(buf), "\"A%d\":\"%X\",", i, emulator->Machine.cpu.addr_r[i]);
    }

    sprintf(buf+strlen(buf), "\"A7\":\"%X\",", read_addrreg(emulator, 7));
    sprintf(buf+strlen(buf), "\"US\":\"%X\",", emulator->Machine.cpu.usp);
    sprintf(buf+strlen(buf), "\"SS\":\"%X\",", emulator->Machine.cpu.ssp);
    sprintf(buf+strlen(buf), "\"PC\":\"%X\",", emulator->Machine.cpu.pc);
    sprintf(buf+strlen(buf), "\"SR\":\"%X\"", emulator->Machine.cpu.sr);
    strncat(buf+strlen(buf), "}}\0", 3);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;
}


char* Jram(struct EmulationMachine* emulator, u32 from, u32 to, u32 sh)
{
    char *res = NULL;

    const char *base = "{\"RAM\":{\"BEGIN\":\"%X\",\"END\":\"%X\",\"HALT\":\"%X\",\"DUMP\":\"";
    const ssize_t base_size = strlen(base);

    char buf[((to - from) + base_size + 10) * 2];

    sprintf(buf, base, from, to, sh);

    for (u32 curr = from; curr <= to; curr++)
    {
        u8 byte = emulator->Machine.ram.self[curr];

        (byte <= 0xF) ? sprintf(buf+strlen(buf), "0%X", byte) : sprintf(buf+strlen(buf), "%X", byte);
    }

    strncat(buf+strlen(buf), "\"}}\0", 4);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;
}


char* Jstack(struct EmulationMachine* emulator, u32 bottom, u32 top)
{
    char *res = NULL;

    const char *base = "{\"STACK\":{\"BOTTOM\":\"%X\",\"TOP\":\"%X\",\"DUMP\":\"";
    const ssize_t base_size = strlen(base);

    char buf[((bottom - top) + base_size + 10) * 2];

    sprintf(buf, base, bottom, top);

    for (u32 curr = top; curr < bottom; curr++)
    {
        u8 byte = emulator->Machine.ram.self[curr];

        (byte <= 0xF) ? sprintf(buf+strlen(buf), "0%X", byte) : sprintf(buf+strlen(buf), "%X", byte);
    }

    strncat(buf+strlen(buf), "\"}}\0", 4);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;
}


char* Jchrono(u64 usec)
{
    char *res;
    char buf[100];

    sprintf(buf, "{\"TIME\":%lu}", usec);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size);

    res[size-1] = '\0';

    return res;

}

char* Jop(char *mnem, u32 code_promoted)
{
    char *res;
    char buf[100];
    u16 code = (u16) code_promoted;

    sprintf(buf, "{\"OP\":{\"MNEMONIC\":\"%s\",\"CODE\":\"%X\"}}", mnem, code);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size);

    res[size-1] = '\0';

    return res;
}


char* Jexception(char* cause, u32 type)
{
    char *res;
    char buf[300];

    if (type == TRAP_EXC_TYPE)
    {
        cause = strstr(cause, "Code: ");
        cause = strstr(cause, ": ") + 2;

        const char* colon = strstr(cause, ",");
        size_t size = (size_t) (colon - cause);

        char code[size + 1];
        snprintf(code, size+1, "%s", cause);

        cause = strstr(cause, ": ") + 2;

        sprintf(buf, "{\"EXCEPTION\":{\"%s\":\"%s\",\"CODE\":\"%s\",\"MNEM\":\"%s\"}}", "TYPE", "TRAP", code, cause);
    }
    else if (type == PANIC_EXC_TYPE)
    {
        sprintf(buf, "{\"EXCEPTION\":{\"%s\":\"%s\",\"CAUSE\":\"%s\"}}", "TYPE", "PANIC", cause);
    }
    else if (type == MERR_EXC_TYPE)
    {
        sprintf(buf, "{\"EXCEPTION\":{\"%s\":\"%s\",\"CAUSE\":\"%s\"}}", "TYPE", "EMULATOR-ERROR", cause);
    }
    else if (type == 3)
    {
        sprintf(buf, "{\"EXCEPTION\":{\"%s\":\"%s\",\"CAUSE\":\"%s\"}}", "TYPE", "ASSEMBLER ERROR", cause);
    }

    size_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size);

    res[size-1] = '\0';

    return res;
}


char* Jwarning(char *cause, char* mnem, u32 code_promoted)
{
    char *res;
    char buf[350];

    u16 code = (u16) code_promoted;

    sprintf(buf, "{\"WARNING\":{\"CAUSE\":\"%s\",\"MNEMONIC\":\"%s\",\"CODE\":\"%X\"}}", cause, mnem, code);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size);

    res[size-1] = '\0';

    return res;
}


#define SANIFICATE_ESCAPE_SEQUENCE(iostr, str)  do { \
                                                    u32 length, i, j; \
                                                    length = strlen(str); \
                                                    i = 0; \
                                                    j = 0; \
                                                    for (; i < length; i++, j++) { \
                                                        char c = str[i]; \
                                                        \
                                                        switch (c) { \
                                                            case '\033': \
                                                                iostr = realloc(iostr, strlen(iostr) + 5); \
                                                                iostr[j++] = '\\'; iostr[j++] = '0'; \
                                                                iostr[j++] = '3';  iostr[j]   = '3'; \
                                                                break; \
                                                            case '\n': \
                                                                iostr = realloc(iostr, strlen(iostr) + 3); \
                                                                iostr[j++] = '\\'; iostr[j] = 'n'; \
                                                                break; \
                                                            case '\t': \
                                                                iostr = realloc(iostr, strlen(iostr) + 3); \
                                                                iostr[j++] = '\\'; iostr[j] = 't'; \
                                                                break; \
                                                            case '\r': \
                                                                iostr = realloc(iostr, strlen(iostr) + 3); \
                                                                iostr[j++] = '\\'; iostr[j] = 'r'; \
                                                                break; \
                                                            default: \
                                                                iostr[j] = c; \
                                                                break; \
                                                        } \
                                                    } \
                                                    iostr[j] = '\0'; \
                                                } while(0);

char* Jio(char* io, u32 type)
{
    char *res;
    ssize_t size = strlen(io) + 1;
    char buf[(size + 30) * 2];

    if (type == INPUT)
        sprintf(buf, "{\"IO\":{\"TYPE\":\"I\",\"VAL\":%s}}", io);
    else
    {
        char *str = malloc(sizeof(s8) * strlen(io) + 1);
        SANIFICATE_ESCAPE_SEQUENCE(str, io);
        sprintf(buf, "{\"IO\":{\"TYPE\":\"O\",\"VAL\":\"%s\"}}", str);
        free(str);
    }

    res = malloc(sizeof (* res) * size);

    res[size-1] = '\0';

    size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size);

    res[size-1] = '\0';

    return res;
}

char* Jconcat(char *dst, char *src)
{
    const size_t dsts = strlen(dst);
    const size_t srcs = strlen(src);

    dst = realloc(dst, dsts + srcs);

    dst[dsts - 1] = ',';
    memcpy(dst + dsts, src + 1, srcs);

    return dst;
}


char* Jconcat2(struct EmulationMachine* emulator, char *dst, char* (*Jsrc)(), ...)
{
    va_list va_ptr;

    va_start(va_ptr, Jsrc);

    char *src = NULL;

    if (Jsrc == Jcpu)
        src = Jcpu(emulator);
    else if (Jsrc == Jram)
    {
        u32 _start, _end, _sh;
        _start = va_arg(va_ptr, u32);
        _end   = va_arg(va_ptr, u32);
        _sh   = va_arg(va_ptr, u32);

        src = Jram(emulator, _start, _end, _sh);
    }
    else if (Jsrc == Jstack)
    {
        u32 _bottom, _top;
        _bottom = va_arg(va_ptr, u32);
        _top    = va_arg(va_ptr, u32);

        src = Jstack(emulator, _bottom, _top);
    }
    else if (Jsrc == Jchrono)
        src = Jchrono(va_arg(va_ptr, u64));
    else if (Jsrc == Jop)
    {
        char *mnem = va_arg(va_ptr, char *);
        u32   code = va_arg(va_ptr, u32);

        src = Jop(mnem, code);
    }
    else if (Jsrc == Jexception)
    {
        char *cause = va_arg(va_ptr, char *);
        u32   type  = va_arg(va_ptr, u32);

        src = Jexception(cause, type);
    }
    else if (Jsrc == Jio)
    {
        char *buff = va_arg(va_ptr, char *);
        u32   type = va_arg(va_ptr, u32);

        src = Jio(buff, type);
    }
    else if (Jsrc == Jwarning)
    {
        char* cause = va_arg(va_ptr, char *);
        char* mnem  = va_arg(va_ptr, char *);
        u32   code  = va_arg(va_ptr, u32);

        src = Jwarning(cause, mnem, code);
    }

    va_end(va_ptr);

    if (src == NULL)
    {
        free(dst);
        return NULL;
    }

    const size_t dsts = strlen(dst);
    const size_t srcs = strlen(src);

    dst = realloc(dst, dsts + srcs);

    dst[dsts - 1] = ',';
    memcpy(dst + dsts, src + 1, srcs);

    free(src);

    return dst;
}


