#include "JSON.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "cpu.h"
#include "ram.h"


char* Jcpu(struct EmulationMachine* restrict emulator)
{
    char *res = NULL;

    const char* base = "{\"CPU\":{\"D0\":\"%X\",\"D1\":\"%X\",\"D2\":\"%X\",\"D3\":\"%X\",\"D4\":\"%X\",\"D5\":\"%X\",\"D6\":\"%X\",\"D7\":\"%X\",\"A0\":\"%X\",\"A1\":\"%X\",\"A2\":\"%X\",\"A3\":\"%X\",\"A4\":\"%X\",\"A5\":\"%X\",\"A6\":\"%X\",\"A7\":\"%X\",\"US\":\"%X\",\"SS\":\"%X\",\"PC\":\"%X\",\"SR\":\"%X\"}}";

    s32 size = snprintf(NULL, 0, base,  emulator->Machine.cpu.data_r[0],
                                        emulator->Machine.cpu.data_r[1],
                                        emulator->Machine.cpu.data_r[2],
                                        emulator->Machine.cpu.data_r[3],
                                        emulator->Machine.cpu.data_r[4],
                                        emulator->Machine.cpu.data_r[5],
                                        emulator->Machine.cpu.data_r[6],
                                        emulator->Machine.cpu.data_r[7],
                                        emulator->Machine.cpu.addr_r[0],
                                        emulator->Machine.cpu.addr_r[1],
                                        emulator->Machine.cpu.addr_r[2],
                                        emulator->Machine.cpu.addr_r[3],
                                        emulator->Machine.cpu.addr_r[4],
                                        emulator->Machine.cpu.addr_r[5],
                                        emulator->Machine.cpu.addr_r[6],
                                        read_addrreg(emulator, 7),
                                        emulator->Machine.cpu.usp,
                                        emulator->Machine.cpu.ssp,
                                        emulator->Machine.cpu.pc,
                                        emulator->Machine.cpu.sr);

    res = malloc(sizeof(char) * (size+3));
    snprintf(res, size+2, base, emulator->Machine.cpu.data_r[0],
                                emulator->Machine.cpu.data_r[1],
                                emulator->Machine.cpu.data_r[2],
                                emulator->Machine.cpu.data_r[3],
                                emulator->Machine.cpu.data_r[4],
                                emulator->Machine.cpu.data_r[5],
                                emulator->Machine.cpu.data_r[6],
                                emulator->Machine.cpu.data_r[7],
                                emulator->Machine.cpu.addr_r[0],
                                emulator->Machine.cpu.addr_r[1],
                                emulator->Machine.cpu.addr_r[2],
                                emulator->Machine.cpu.addr_r[3],
                                emulator->Machine.cpu.addr_r[4],
                                emulator->Machine.cpu.addr_r[5],
                                emulator->Machine.cpu.addr_r[6],
                                read_addrreg(emulator, 7),
                                emulator->Machine.cpu.usp,
                                emulator->Machine.cpu.ssp,
                                emulator->Machine.cpu.pc,
                                emulator->Machine.cpu.sr);

    return res;
}


char* Jram(u32 from, u32 to, u32 sh)
{
    char *res = NULL;

    const char *base = "{\"RAM\":{\"BEGIN\":\"%X\",\"END\":\"%X\",\"HALT\":\"%X\"}}";
    
    s32 size = snprintf(NULL, 0, base, from, to, sh);

    res = (char *) malloc(sizeof(char) * (size+3));
    snprintf(res, size+2, base, from, to, sh);

    return res;
}


char* Jchrono(u64 usec)
{
    char *res = NULL;

    s32 size = snprintf(NULL, 0, "{\"TIME\":%lu}", usec);

    res = (char *) malloc(sizeof(char) * (size+3));
    snprintf(res, size+2, "{\"TIME\":%lu}", usec);

    return res;

}

char* Jop(char *mnem, u32 code_promoted)
{
    char *res = NULL;
    u16 code = (u16) code_promoted;

    if (!mnem)
        mnem = "none";

    s32 size = snprintf(NULL, 0, "{\"OP\":{\"MNEMONIC\":\"%s\",\"CODE\":\"%X\"}}", mnem, code);

    res = (char*) malloc(sizeof(char) * (size+3));
    snprintf(res, size+2, "{\"OP\":{\"MNEMONIC\":\"%s\",\"CODE\":\"%X\"}}", mnem, code);

    return res;
}


char* Jexception(char* cause, u32 type)
{
    char *res  = NULL;
    char* base = NULL;
    s32   size = 0;

    if (type == TRAP_EXC_TYPE)
    {
        cause = strstr(cause, "Code: ");
        cause = strstr(cause, ": ") + 2;

        const char* colon = strstr(cause, ",");
        size_t _size = (size_t) (colon - cause);

        char code[_size + 1];
        snprintf(code, _size+1, "%s", cause);

        cause = strstr(cause, ": ") + 2;

        base = "{\"EXCEPTION\":{\"TYPE\":\"TRAP\",\"CODE\":\"%s\",\"MNEM\":\"%s\"}}";
        size = snprintf(NULL, 0, base, code, cause);
        res = malloc(sizeof(char) * (size+3));
        snprintf(res, size+2, base, code, cause);
    }
    else if (type == PANIC_EXC_TYPE)
    {
        base = "{\"EXCEPTION\":{\"TYPE\":\"PANIC\",\"CAUSE\":\"%s\"}}";
        size = snprintf(NULL, 0, base, cause);
    }
    else if (type == MERR_EXC_TYPE)
    {
        base = "{\"EXCEPTION\":{\"TYPE\":\"EMULATOR-ERROR\",\"CAUSE\":\"%s\"}}";
        size = snprintf(NULL, 0, base, cause);
    }
    else if (type == 3)
    {
        base = "{\"EXCEPTION\":{\"TYPE\":\"ASSEMBLER ERROR\",\"CAUSE\":\"%s\"}}";
        size = snprintf(NULL, 0, base, cause);
    }
    
    if (type != TRAP_EXC_TYPE)
    {
        res = malloc(sizeof(char) * (size+3));
        snprintf(res, size+2, base, cause);
    }

    return res;
}


char* Jwarning(char *cause, char* mnem, u32 code_promoted)
{
    char *res = NULL;
    u16 code = (u16) code_promoted;

    const char* base = "{\"WARNING\":{\"CAUSE\":\"%s\",\"MNEMONIC\":\"%s\",\"CODE\":\"%X\"}}";

    s32 size = snprintf(NULL, 0, base, cause, mnem, code);

    res = (char*) malloc(sizeof(char) * (size+3));
    snprintf(res, size+2, base, cause, mnem, code);

    return res;
}


char* Jio(char* io)
{
    if (io)
    {   
        char* res  = NULL;
        char* base = NULL;
        s32   size = 0;

        base = "{\"IO\":{\"TYPE\":\"O\",\"VAL\":\"%s\"}}";
        size = snprintf(NULL, 0, base, io);

        res = malloc(sizeof(char) * (size+3));
        snprintf(res, size+2, base, io);

        return res;
    }
    
    return NULL;
}


char* Jconcat2(struct EmulationMachine* restrict emulator, char *dst, char* (*Jsrc)(), ...)
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

        src = Jram(_start, _end, _sh);
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

        src = Jio(buff);
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
        return dst;
    }

    const size_t dsts = strlen(dst);
    const size_t srcs = strlen(src);

    dst = realloc(dst, dsts + srcs);

    dst[dsts - 1] = ',';
    memcpy(dst + dsts, src + 1, srcs);

    free(src);

    return dst;
}


