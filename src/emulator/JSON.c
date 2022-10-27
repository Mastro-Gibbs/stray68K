#include "JSON.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "cpu.h"
#include "ram.h"


char* Jcpu()
{
    m68k_cpu *cpu = get_cpu();

    if (cpu != NULL)
    {
        char *res = NULL;
        char tmp[16];
        char buf[410];

        tmp[15] = '\0';

        sprintf(buf, "%s", "{\"CPU\":{");

        for (u16 i = 0; i < 8; i++)
        {
            sprintf(tmp, "\"D%d\":\"%X\",", i, cpu->data_r[i]);
            strncat(buf, tmp, 17);
        }

        for (u16 i = 0; i < 7; i++)
        {
            sprintf(tmp, "\"A%d\":\"%X\",", i, cpu->addr_r[i]);
            strncat(buf, tmp, 17);
        }

        sprintf(tmp, "\"A7\":\"%X\",", read_addrreg(7));
        strncat(buf, tmp, 17);

        sprintf(tmp, "\"US\":\"%X\",", cpu->usp);
        strncat(buf, tmp, 17);

        sprintf(tmp, "\"SS\":\"%X\",", cpu->ssp);
        strncat(buf, tmp, 17);

        sprintf(tmp, "\"PC\":\"%X\",", cpu->pc);
        strncat(buf, tmp, 17);

        sprintf(tmp, "\"SR\":\"%X\"", cpu->sr);
        strncat(buf, tmp, 17);

        strncat(buf, "}}\0", 3);

        ssize_t size = strlen(buf) + 1;
        res = malloc(sizeof (* res) * size);

        strncpy(res, buf, size-1);

        res[size-1] = '\0';

        return res;
    }

    return (NULL);
}


char* Jram(u32 from, u32 to, u32 sh)
{
    m68k_ram *ram = get_ram();

    if (ram != NULL)
    {
        char *res = NULL;
        char tmp[2];
        char buf[(to - from) + 100];

        tmp[1] = '\0';

        sprintf(buf, "{\"RAM\":{\"BEGIN\":\"%X\",\"END\":\"%X\",\"HALT\":\"%X\",\"DUMP\":\"", from, to, sh);

        for (u32 curr = from; curr <= to; curr++)
        {
            u8 byte = ram->ram[curr];

            if (!byte || byte <= 0xF)
            {
                strncat(buf, "0\0", 2);
                sprintf(tmp, "%X", byte);
                strncat(buf, tmp, 2);
            }
            else
            {
                char tmp2[3];
                tmp2[2] = '\0';
                sprintf(tmp2, "%X", byte);
                strncat(buf, tmp2, 3);
            }
        }

        strncat(buf, "\"}}\0", 4);

        ssize_t size = strlen(buf) + 1;
        res = malloc(sizeof (* res) * size);

        strncpy(res, buf, size-1);

        res[size-1] = '\0';

        return res;
    }

    return (NULL);
}


char* Jstack(u32 from, u32 to)
{
    m68k_ram *stack = get_ram();

    char *res = NULL;
    char tmp[2];
    char buf[(to - from) + 50];

    tmp[1] = '\0';

    sprintf(buf, "{\"%s\":\"", "STACK");

    for (u32 curr = from; curr <= to; curr++)
    {
        u8 byte = stack->ram[curr];

        if (!byte || byte <= 0xF)
        {
            strncat(buf, "0\0", 2);
            sprintf(tmp, "%X", byte);
            strncat(buf, tmp, 2);
        }
        else
        {
            char tmp2[3];
            tmp2[2] = '\0';
            sprintf(tmp2, "%X", byte);
            strncat(buf, tmp2, 3);
        }
    }

    strncat(buf, "\"}\0", 3);

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

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;

}

char* Jop(char *mnem, u32 code_promoted)
{
    char *res;
    char buf[100];
    u16 code = (u16) code_promoted;

    sprintf(buf, "{\"OP\":{\"MENMONIC\":\"%s\",\"CODE\":\"%X\"}}", mnem, code);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

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

    size_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;
}

char* Jio(char* io, u32 type, u32 nl)
{
    char *res;
    ssize_t size = strlen(io) + 1;
    char buf[size + 60];

    if (type == INPUT)
        sprintf(buf, "{\"IO\":{\"TYPE\":\"I\",\"VAL\":\"%s\",\"NL\":%s}}", io, "null");
    else
        sprintf(buf, "{\"IO\":{\"TYPE\":\"O\",\"VAL\":\"%s\",\"NL\":%s}}", io, nl ? "true" : "false");

    res = malloc(sizeof (* res) * size);

    res[size-1] = '\0';

    size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

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


char* Jconcat2(char *dst, char* (*Jsrc)(), ...)
{
    va_list va_ptr;

    va_start(va_ptr, Jsrc);

    char *src = NULL;

    if (Jsrc == Jcpu)
        src = Jcpu();
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
        u32   type = va_arg(va_ptr, u32);
        u32   nl   = va_arg(va_ptr, u32);

        src = Jio(buff, type, nl);
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


