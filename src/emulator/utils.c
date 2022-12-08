#include "utils.h"

#include <sys/time.h>

u32 most_significant_byte(const opsize size)
{
    switch (size)
    {
        case BYTE:
            return 0x00000080;

        case WORD:
            return 0x00008000;

        case LONG:
            return 0x80000000;

        default:
            return 0x00000000;
    }
}


u32 mask_by_opsize(const opsize size)
{
    switch (size)
    {
        case BYTE:
            return 0x000000FF;

        case WORD:
            return 0x0000FFFF;

        case LONG:
            return 0xFFFFFFFF;

        default:
            return 0x00000000;
    }
}


u32 hash (const char* word)
{
    u32 hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
        hash = (31 * hash) + word[i];

    return hash;
}


/* IO EA */
u32 read_ram(u32 *addr, opsize *size)
{
    switch (*size) {
        case BYTE:
            return (u32) read_byte(*addr);
        case WORD:
            return (u32) read_word(*addr);
        default: //LONG
            return read_long(*addr);
    }
}


/* MISC */
sspan size_to_span(const opsize size)
{
    switch (size) {
        case BYTE:
            return BYTE_SPAN;
        case WORD:
            return WORD_SPAN;
        default:
            return LONG_SPAN;
    }
}

bit is_ram_op(ADDRMode* const mode)
{
    switch (*mode)
    {
        case ADDRESS:
        case ADDRESSPostIncr:
        case ADDRESSPreDecr:
        case IMMEDIATE:
            return 1;
        default:
            return 0;
    }
}


bit is_addr_to_data_op(ADDRMode* const mode)
{
    switch (*mode)
    {
        case ADDRReg:
            return 1;
        default:
            return 0;
    }
}



/* TRAP */
char* trap_code_toString(const u32 trapcode)
{
    switch (trapcode) {
        case BusError:
            return "BusError";
        case AddressError:
            return "AddressError";
        case IllegalInstruction:
            return "IllegalInstruction";
        case DivideByZero:
            return "DivideByZero";
        case CHKInstruction:
            return "CHKInstruction";
        case TRAPVInstruction:
            return "TRAPVInstruction";
        case PrivilegeViolation:
            return "PrivilegeViolation";
        default:
            return "CustomException";
    }
}


void _io_dumps(struct EmulationMachine *em)
{
    emit_jio(em);

    em->Machine.IO.buffer  = NULL;
    em->Machine.IO.Type    = IO_UNDEF;
}


#include <string.h>
#define EVAL_ESCAPE_SEQUENCE(iostr, cchar, rptr)    do{ \
                                                        cchar = read_byte(rptr++); \
                                                        if (  /* ANSI ESCAPE SEQUENCE '\033'*/ \
                                                            cchar == '0' && \
                                                            read_byte(rptr) == '3' && \
                                                            read_byte(rptr + 1) == '3' \
                                                        ) { \
                                                            sprintf(iostr+strlen(iostr), "%c", '\033'); \
                                                            rptr += 2; \
                                                        } \
                                                        else  /* CLASSIC ESCAPE SEQUENCE */ \
                                                        { \
                                                            switch (cchar) { \
                                                                case '\\': \
                                                                    sprintf(iostr+strlen(iostr), "%c", '\\'); \
                                                                    if (read_byte(rptr) == '%') /*Escape for placeholder*/\
                                                                    { \
                                                                        iostr = realloc(iostr, strlen(iostr)+2); \
                                                                        sprintf(iostr+strlen(iostr), "%c", '%'); \
                                                                        rptr++; \
                                                                    }\
                                                                    break; \
                                                                case 'n':  \
                                                                    sprintf(iostr+strlen(iostr), "%c", '\n'); \
                                                                    break; \
                                                                case 't': \
                                                                    sprintf(iostr+strlen(iostr), "%c", '\t'); \
                                                                    break; \
                                                                case 'r': \
                                                                    sprintf(iostr+strlen(iostr), "%c", '\r'); \
                                                                    break; \
                                                                default: \
                                                                    sprintf(iostr+strlen(iostr), "%c", cchar); \
                                                                    break; \
                                                            } \
                                                        } \
                                                    } while(0);

#define EVAL_PLACE_OLDER(iostr, cchar, rptr)    do { \
                                                    opsize size; \
                                                    cchar = read_byte(rptr++); \
                                                    \
                                                    switch (cchar) { /*if it's a signed integer print, dectect it's size*/\
                                                        case 'b':    \
                                                        case 'B':    \
                                                            size = BYTE; \
                                                            break;   \
                                                        case 'w':    \
                                                        case 'W':    \
                                                            size = WORD; \
                                                            break;   \
                                                        case 'l':    \
                                                        case 'L':    \
                                                            size = LONG; \
                                                            break;   \
                                                        default:     \
                                                        { /*Needs a forward reading to clear placeholder escape chars*/ \
                                                            char fw = read_byte(rptr); \
                                                            if (fw != 'x' && fw != 'X' && \
                                                                fw != 'a' && fw != 'A' && \
                                                                fw != 'd' && fw != 'D') \
                                                            { \
                                                                rptr++; \
                                                                fw = read_byte(rptr); \
                                                                if ((fw - 0x30) < 10) rptr++; \
                                                            } else if ((fw - 0x30) < 10) rptr++; \
                                                            \
                                                            continue;   \
                                                        } \
                                                    }                \
                                                    \
                                                    char ccchar = read_byte(rptr); \
                                                    if (ccchar == 'x' || ccchar == 'X' || \
                                                        ccchar == 'a' || ccchar == 'A' || \
                                                        ccchar == 'd' || ccchar == 'D') \
                                                    { \
                                                        cchar = ccchar; \
                                                        rptr++; \
                                                    } \
                                                    \
                                                    switch (cchar) \
                                                    { \
                                                        case 'x': \
                                                        { \
                                                            cchar = read_byte(rptr++);          \
                                                            const u32 index  = cchar - 0x30;          \
                                                            if (index > 7) break; \
                                                            const u32 value  = read_datareg(index) & mask_by_opsize(size);   \
                                                            const u32 length = snprintf(NULL, 0, "%x", value); \
                                                            iostr = realloc(iostr, strlen(iostr) + length + 1); \
                                                            snprintf(iostr+strlen(iostr), length + 1, "%x", value); \
                                                            break; \
                                                        } \
                                                        case 'X': \
                                                        { \
                                                            cchar = read_byte(rptr++);          \
                                                            const u32 index  = cchar - 0x30;          \
                                                            if (index > 7) break; \
                                                            const u32 value  = read_datareg(index) & mask_by_opsize(size);   \
                                                            const u32 length = snprintf(NULL, 0, "%X", value); \
                                                            iostr = realloc(iostr, strlen(iostr) + length + 1); \
                                                            snprintf(iostr+strlen(iostr), length + 1, "%X", value); \
                                                            break; \
                                                        } \
                                                        case 'b':  /*aka BYTE sign extend*/ \
                                                        case 'B':  \
                                                        case 'w':  /*aka WORD sign extend*/ \
                                                        case 'W':  \
                                                        case 'l':  /*aka LONG sign extend*/ \
                                                        case 'L':  \
                                                        { \
                                                            cchar = read_byte(rptr++);          \
                                                            const u32 index  = cchar - 0x30;          \
                                                            if (index > 7) break; \
                                                            const u32 value  = read_datareg(index);   \
                                                            s32 sval;                           \
                                                            SIGN_EXTENDED(sval, value, size);   \
                                                            const u32 length = snprintf(NULL, 0, "%d", sval); \
                                                            iostr = realloc(iostr, strlen(iostr) + length + 1); \
                                                            snprintf(iostr+strlen(iostr), length + 1, "%d", sval); \
                                                            break; \
                                                        } \
                                                        case 'a':  \
                                                        case 'A':  \
                                                        { \
                                                            cchar = read_byte(rptr++);        \
                                                            const u32 index  = cchar - 0x30;        \
                                                            if (index > 7) break; \
                                                            const u32 value  = read_addrreg(index) & mask_by_opsize(size);   \
                                                            const u32 length = snprintf(NULL, 0, "%X", value); \
                                                            iostr = realloc(iostr, strlen(iostr) + length + 1); \
                                                            snprintf(iostr+strlen(iostr), length + 1, "%X", value); \
                                                            break; \
                                                        } \
                                                        case 'd':  \
                                                        case 'D':  \
                                                        { \
                                                            cchar = read_byte(rptr++);        \
                                                            const u32 index  = cchar - 0x30;        \
                                                            if (index > 7) break; \
                                                            const u32 value  = read_datareg(index) & mask_by_opsize(size);   \
                                                            const u32 length = snprintf(NULL, 0, "%u", value); \
                                                            iostr = realloc(iostr, strlen(iostr) + length + 1); \
                                                            snprintf(iostr+strlen(iostr), length + 1, "%u", value); \
                                                            break; \
                                                        } \
                                                        default:   \
                                                            break; \
                                                    } \
                                                } while(0);

#define EVAL_PRINT_SEQUENCE(iostr)  do { \
                                        u32 rptr; \
                                        s8  cchar; \
                                        \
                                        rptr = read_addrreg(0);\
                                        \
                                        iostr = malloc(2 * sizeof (s8)); \
                                        iostr[0] = '\0'; \
                                        \
                                        do { \
                                            cchar = read_byte(rptr++); \
                                            \
                                            if (cchar == '\\') \
                                                EVAL_ESCAPE_SEQUENCE(iostr, cchar, rptr) \
                                            else if (cchar == '%') \
                                                EVAL_PLACE_OLDER(iostr, cchar, rptr) \
                                            else \
                                                sprintf(iostr+strlen(iostr), "%c", cchar); \
                                            \
                                            str = realloc(str, strlen(str)+2); \
                                            \
                                        } while ((cchar & 0xFF) != 0b00000000); \
                                    } while(0);

#define EVAL_SCAN_SEQUENCE(iostr)   do { \
                                        u32 rptr, index, value, length; \
                                        char c; \
                                        \
                                        rptr = read_addrreg(0); \
                                        \
                                        while ((c = read_byte(rptr++)) == '%' || (c & 0xFF) != 0x00) \
                                        { \
                                            if (read_byte(rptr) == 't' || read_byte(rptr) == 'T') {  \
                                                index = read_byte(rptr+1); \
                                                if (index == 0x00) return; \
                                                index = index - 0x30;      \
                                                if (index > 7) continue;   \
                                                struct timeval tv;         \
                                                gettimeofday(&tv,NULL);    \
                                                u32 time = (u32) ((tv.tv_sec * (unsigned long)1000000 + tv.tv_usec) & 0x00000000FFFFFFFF); \
                                                write_datareg(index, time, NULL); \
                                                rptr += 2; \
                                            }\
                                            else { \
                                                if (iostr == NULL) {\
                                                    iostr = malloc(2 * sizeof (s8)); \
                                                    iostr[0] = '{'; iostr[1] = '\0'; \
                                                } \
                                                \
                                                if (c != '%') continue; \
                                                \
                                                opsize size; \
                                                char cchar = read_byte(rptr++); \
                                                if (cchar == 0x00) { free(iostr); iostr = NULL; break; }  \
                                                \
                                                switch (cchar) { /*if it's a signed integer print, dectect it's size*/\
                                                    case 'b':    \
                                                    case 'B':    \
                                                        size = BYTE; \
                                                        break;   \
                                                    case 'w':    \
                                                    case 'W':    \
                                                        size = WORD; \
                                                        break;   \
                                                    case 'l':    \
                                                    case 'L':    \
                                                        size = LONG; \
                                                        break;   \
                                                    default:     \
                                                        continue;   \
                                                } \
                                                char ccchar = read_byte(rptr); \
                                                if (cchar == 0x00) { free(iostr); iostr = NULL; break; }  \
                                                if (ccchar == 'a' || ccchar == 'A' || \
                                                    ccchar == 'd' || ccchar == 'D') \
                                                { \
                                                    cchar = ccchar; \
                                                    rptr++; \
                                                } \
                                                else continue; \
                                                \
                                                char rtype = cchar; \
                                                \
                                                cchar = read_byte(rptr++);     \
                                                if (cchar == 0x00) { free(iostr); iostr = NULL; break; }  \
                                                index = cchar - 0x30;          \
                                                if (index > 7) continue;       \
                                                \
                                                s32 sf_r;                      \
                                                sf_r = scanf(" %u", &value);   \
                                                if (sf_r == 0 || sf_r == EOF)  continue; \
                                                \
                                                value &= mask_by_opsize(size); \
                                                \
                                                switch (rtype) \
                                                { \
                                                    case 'a':  \
                                                    case 'A':  \
                                                    { \
                                                        write_addrreg(index, value, &size);   \
                                                        break; \
                                                    } \
                                                    case 'd':  \
                                                    case 'D':  \
                                                    { \
                                                        write_datareg(index, value, &size);   \
                                                        break; \
                                                    } \
                                                    default:   \
                                                        break; \
                                                } \
                                                length = snprintf(NULL, 0, "%d", value); \
                                                if (strlen(iostr) == 1) { \
                                                    iostr  = realloc(iostr, strlen(iostr) + length + 8); \
                                                    sprintf(iostr+strlen(iostr), "\"%c%d\":\"%d\"", rtype, index, value); \
                                                } else { \
                                                    iostr  = realloc(iostr, strlen(iostr) + length + 9); \
                                                    sprintf(iostr+strlen(iostr), ",\"%c%d\":\"%d\"", rtype, index, value); \
                                                } \
                                            } \
                                        } \
                                        if (iostr != NULL) { \
                                            u32 pos = strlen(iostr);       \
                                            iostr = realloc(str, pos + 2); \
                                            iostr[pos] = '}'; iostr[pos+1] = '\0'; \
                                        } \
                                    } while(0);

void iotask(struct EmulationMachine *em)
{
    char *str = NULL;

    if (em->Machine.IO.Type == OUTPUT)
    {
        EVAL_PRINT_SEQUENCE(str)

        if (str != NULL)
        {
            em->Machine.IO.buffer  = str;

            emit_dump(em);

            IO_TASK(em->ExecArgs.descriptive_mode, "%s", str)
            free(str);
        }
    }
    else if (em->Machine.IO.Type == INPUT)
    {
        EVAL_SCAN_SEQUENCE(str)

        if (str != NULL)
        {
            em->Machine.IO.buffer  = str;

            emit_dump(em);
            free(str);
        }
    }


}


#include <unistd.h>
void machine_waiter(struct EmulationMachine *em)
{
}

#include "JSON.h"

char* _dump = NULL;

void emit_dump(struct EmulationMachine *em)
{
    if (_dump != NULL) free(_dump);
    _dump = NULL;

    if (get_cpu() == NULL || get_ram() == NULL)
    {
        if (em->Machine.State == PANIC_STATE)
            _dump = Jexception(em->Machine.Exception.panic_cause, PANIC_EXC_TYPE);
        else if (em->Machine.State == MERR_STATE)
            _dump = Jexception(em->Machine.Exception.merr_cause, MERR_EXC_TYPE);
    }
    else
    {
        _dump = Jcpu();
        _dump = Jconcat2(_dump, Jram,    em->Machine.RuntimeData.org_pointer, em->Machine.RuntimeData.last_loaded_byte_index, em->Machine.RuntimeData.simhalt);

        if (em->Machine.cpu->ssp != em->Machine.RuntimeData.STACK_BOTTOM_INDEX)
            _dump = Jconcat2(_dump, Jstack, em->Machine.RuntimeData.STACK_BOTTOM_INDEX, em->Machine.cpu->ssp);

        _dump = Jconcat2(_dump, Jop,     em->Machine.RuntimeData.mnemonic, em->Machine.RuntimeData.operation_code);
        _dump = Jconcat2(_dump, Jchrono, em->Machine.Chrono.dt);

        if (em->Machine.IO.buffer != NULL && em->Machine.IO.Type != IO_UNDEF)
            _dump = Jconcat2(_dump, Jio, em->Machine.IO.buffer, em->Machine.IO.Type);

        if (em->Machine.State == TRAP_STATE)
            _dump = Jconcat2(_dump, Jexception, em->Machine.Exception.trap_cause, TRAP_EXC_TYPE);
        else if (em->Machine.State == PANIC_STATE)
            _dump = Jconcat2(_dump, Jexception, em->Machine.Exception.panic_cause, PANIC_EXC_TYPE);
        else if (em->Machine.State == MERR_STATE)
            _dump = Jconcat2(_dump, Jexception, em->Machine.Exception.merr_cause, MERR_EXC_TYPE);
    }
}

const char* machine_status ()
{
    return _dump;
}

void emit_jio(struct EmulationMachine *em)
{
    if (em->ExecArgs.JSON.is_activated && em->ExecArgs.JSON.io)
    {
        char *buf = NULL;

        buf = Jio(em->Machine.IO.buffer, em->Machine.IO.Type);

        printf("%s\n", buf);
        free(buf);
    }
}

void emit_jconcat(struct EmulationMachine *em)
{
    char *buf = NULL;

    if (em->ExecArgs.JSON.concat)
    {
        if (em->ExecArgs.JSON.cpu)
            buf = Jcpu();

        if (em->ExecArgs.JSON.ram)
        {
            u32 _start, _end, _ptr = em->Machine.cpu->pc;
            _start = (_ptr & 0xFFFFFFF0) - 0x20;
            _end   = (_ptr | 0x0000000F) + 0x31;

            buf = Jconcat2(buf, Jram, _start, _end);
        }

        if (em->ExecArgs.JSON.op)
            buf = Jconcat2(buf, Jop, em->Machine.RuntimeData.mnemonic, em->Machine.RuntimeData.operation_code);

        if (em->Machine.State == FINAL_STATE && em->ExecArgs.JSON.chrono)
            buf = Jconcat2(buf, Jchrono, em->Machine.Chrono.dt);

        if (buf)
        {
            printf("%s\n", buf);
            free(buf);
        }
    }
}
