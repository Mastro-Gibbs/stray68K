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

    char *res = NULL;
    char tmp[16];
    char buf[410];

    tmp[15] = '\0';

    sprintf(buf, "%s", "{\"CPU\": {");

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


char* Jram(u32 from, u32 to)
{
    m68k_ram *ram = get_ram();

    char *res = NULL;
    char tmp[2];
    char buf[(to - from) + 50];

    tmp[1] = '\0';

    sprintf(buf, "{\"%s\":\"", "RAM");

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

    strncat(buf, "\"}\0", 3);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;
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

    sprintf(buf, "{\"%s\":%lu}", "TIME", usec);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;

}


char* Jmnemonic(char *mnem)
{
    char *res;
    char buf[60];

    sprintf(buf, "{\"%s\":\"%s\"}", "MENMONIC", mnem);

    ssize_t size = strlen(buf) + 1;
    res = malloc(sizeof (* res) * size);

    strncpy(res, buf, size-1);

    res[size-1] = '\0';

    return res;
}


char* Jcode(u32 code_promoted)
{
    u16 code = (u16) code_promoted;

    const int usec_size = snprintf(NULL, 0, "%d", code);

    char *res;
    char buf[(usec_size) + 50];

    sprintf(buf, "{\"%s\":%d}", "CODE", code);

    ssize_t size = strlen(buf) + 1;
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
        u32 _start, _end;
        _start = va_arg(va_ptr, u32);
        _end   = va_arg(va_ptr, u32);

        src = Jram(_start, _end);
    }
    else if (Jsrc == Jchrono)
        src = Jchrono(va_arg(va_ptr, u64));
    else if (Jsrc == Jmnemonic)
        src = Jmnemonic(va_arg(va_ptr, char *));
    else if (Jsrc == Jcode)
        src = Jcode(va_arg(va_ptr, u32));

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


