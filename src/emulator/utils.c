#include "utils.h"

#include <sys/time.h>

#include <unistd.h>


void flush_InputBuffer(struct EmulationMachine* emulator) 
{ 
    emulator->Machine.IO.InputBuffer._valid = 1; 
}

void init_InputBuffer(struct EmulationMachine* emulator) 
{ 
    for(size_t i = 0; i < 4096; ++i) 
        emulator->Machine.IO.InputBuffer.self[i] = 0;  
    
    emulator->Machine.IO.InputBuffer._pos = 0; 
    emulator->Machine.IO.InputBuffer._valid = c_false; 
    emulator->Machine.IO.InputBuffer._able  = c_true; 
}

void InputBuffer_cwrite(struct EmulationMachine* emulator, char _c) 
{ 
    if (emulator->Machine.IO.InputBuffer._pos == 4095)
        return;
        
    emulator->Machine.IO.InputBuffer.self[emulator->Machine.IO.InputBuffer._pos] = _c;
    emulator->Machine.IO.InputBuffer._pos += 1; 
}

void set_InputBuffer_enabled(struct EmulationMachine* emulator, c_bool _bool)
{
    emulator->Machine.IO.InputBuffer._able  = _bool; 
}

c_bool is_buffer_valid(struct EmulationMachine* emulator)
{
    return emulator->Machine.IO.InputBuffer._valid;
}

c_bool is_buffering_enabled(struct EmulationMachine* emulator)
{
    return emulator->Machine.IO.InputBuffer._able;
}

u32 buffer_len(struct EmulationMachine* emulator)
{
    return emulator->Machine.IO.InputBuffer._pos;
}

u32 read_int_InputBuffer(struct EmulationMachine* emulator) 
{
    u32 res = 0;

    sscanf(emulator->Machine.IO.InputBuffer.self, "%u", &res);

    return res;
}

char* read_str_InputBuffer(struct EmulationMachine* emulator)
{
    char* str = malloc(4096);

    if (str) 
    {
        sscanf(emulator->Machine.IO.InputBuffer.self, "%[^\n]", str);
        str[emulator->Machine.IO.InputBuffer._pos] = '\0';
    }

    return str;
}


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
u32 read_ram(struct EmulationMachine* emulator, u32 *addr, opsize *size)
{
    switch (*size) {
        case BYTE:
            return (u32) read_byte(emulator, *addr);
        case WORD:
            return (u32) read_word(emulator, *addr);
        default: //LONG
            return read_long(emulator, *addr);
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
            return c_true;
        default:
            return c_false;
    }
}


bit is_addr_to_data_op(ADDRMode* const mode)
{
    switch (*mode)
    {
        case ADDRReg:
            return c_true;
        default:
            return c_false;
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


#include <string.h>

char* eval_print_placeholder_seq(struct EmulationMachine *emulator, u32* restrict ram_ptr)
{
    char* result = NULL;

    opsize size;
    char cchar;

    cchar = read_byte(emulator, *ram_ptr);
    *ram_ptr = *ram_ptr+1;

    switch (cchar)
    {
        case 'b':
        case 'B':
            size = BYTE;
            break;

        case 'w':
        case 'W':
            size = WORD;
            break;

        case 'l':
        case 'L':
            size = LONG;
            break;
        
        default:
        { 
            /*Needs a forward reading to clear placeholder escape chars*/
            
            char fw = read_byte(emulator, *ram_ptr);
            if (fw != 'x' && fw != 'X' && fw != 'a' && fw != 'A' && fw != 'd' && fw != 'D')
            {
                *ram_ptr = *ram_ptr+1;
                fw = read_byte(emulator, *ram_ptr);

                if ((fw - 0x30) < 10)
                    *ram_ptr = *ram_ptr+1; 
            } 
            else if ((fw - 0x30) < 10) 
                *ram_ptr = *ram_ptr+1; 
            
            return NULL;   
        } 
    }

    char ccchar = read_byte(emulator, *ram_ptr);

    if (ccchar == 'x' || ccchar == 'X' || ccchar == 'a' || ccchar == 'A' || ccchar == 'd' || ccchar == 'D') 
    {
        *ram_ptr = *ram_ptr+1;
        cchar = ccchar;
    }

    switch (cchar)
    {
        case 'x':
        case 'X':
        {
            cchar = read_byte(emulator, *ram_ptr);
            *ram_ptr = *ram_ptr+1;
            const u32 index  = cchar - 0x30;

            if (index > 7) return NULL;

            const u32 value  = read_datareg(emulator, index) & mask_by_opsize(size);
            const u32 length = snprintf(NULL, 0, "%x", value);

            result = malloc(length+2);
            if (!result) return NULL;

            (cchar == 'x') ?
                snprintf(result, length+1, "%x", value) :
                snprintf(result, length+1, "%X", value);
            
            return result;
        }

        case 'b':  /*aka BYTE sign extend*/
        case 'B':
        case 'w':  /*aka WORD sign extend*/ 
        case 'W': 
        case 'l':  /*aka LONG sign extend*/
        case 'L': 
        { 
            cchar = read_byte(emulator, *ram_ptr);  
            *ram_ptr = *ram_ptr+1; 
            const u32 index  = cchar - 0x30;  

            if (index > 7) return NULL;

            const u32 value  = read_datareg(emulator, index);

            s32 signed_value;                           
            SIGN_EXTENDED(signed_value, value, size);

            const u32 length = snprintf(NULL, 0, "%d", signed_value); 

            result = malloc(length+2);
            if (!result) return NULL;

            snprintf(result, length+1, "%d", signed_value);
            
            return result;
        } 

        case 'a':
        case 'A':
        {
            cchar = read_byte(emulator, *ram_ptr);
            *ram_ptr = *ram_ptr+1;
            const u32 index  = cchar - 0x30;

            if (index > 7) return NULL;
            
            const u32 value  = read_addrreg(emulator, index) & mask_by_opsize(size);
            const u32 length = snprintf(NULL, 0, "%X", value);
            
            result = malloc(length+2);
            if (!result) return NULL;
            
            (cchar == 'a') ?
                snprintf(result, length+1, "%x", value) :
                snprintf(result, length+1, "%X", value);
            
            return result;
        } 

        case 'd':
        case 'D':
        {
            cchar = read_byte(emulator, *ram_ptr);
            *ram_ptr = *ram_ptr+1;
            const u32 index  = cchar - 0x30;

            if (index > 7) return NULL;
            
            const u32 value  = read_datareg(emulator, index) & mask_by_opsize(size);
            const u32 length = snprintf(NULL, 0, "%u", value);
            
            result = malloc(length+2);
            if (!result) return NULL;
            
            snprintf(result, length+1, "%u", value);
            
            return result;
        } 
        
        default:
            return NULL;
    }

    return NULL;
}

char* eval_print_seq(struct EmulationMachine *emulator)
{
    char* dst = NULL;
    char  cchar;
    u32   ram_ptr;
    u32   dst_size = 5000;

    dst = malloc(sizeof(char) * dst_size);
    if (!dst) return dst;

    dst[0] = '\0';

    ram_ptr = read_addrreg(emulator, 0);

    while (((cchar = read_byte(emulator, ram_ptr++)) & 0xFF) != 0x00)
    {
        switch (cchar)
        {
            case '%':
            {
                char* result = eval_print_placeholder_seq(emulator, &ram_ptr);

                if (result)
                {
                    const size_t length = strlen(result);

                    dst = realloc(dst, strlen(dst)+length+4);

                    if (!dst) 
                    {
                        free(result);
                        return NULL;
                    }

                    snprintf(dst+strlen(dst), length+1, "%s", result);

                    free(result);

                    break;
                }
                
                break;
            }

            default:
                snprintf(dst+strlen(dst), 2, "%c", cchar);
                
                dst = realloc(dst, strlen(dst)+3);
                
                if (!dst) return NULL;
                break;
        }
    }

    return dst;
}


c_bool eval_scan_placeholder_seq(struct EmulationMachine* emulator, u32* restrict ram_ptr)
{
    char cchar = 0x0, lookahead = 0x0; 
    s32  index = 0;

    cchar = read_byte(emulator, *ram_ptr);

    switch(cchar)
    {
        case 't':
        case 'T':
        {
            lookahead = read_byte(emulator, (*ram_ptr)+1);

            if (lookahead == 0x00 || (lookahead - 0x30) > 7)
                return c_false;

            index = lookahead - 0x30;  

            struct timeval tv;         
            gettimeofday(&tv,NULL);    
            u32 time = (u32) ((tv.tv_sec * (unsigned long)1000000 + tv.tv_usec) & 0x00000000FFFFFFFF); 
            write_datareg(emulator, index, time, NULL); 

            *ram_ptr += *ram_ptr + 2; 

            break;
        }

        case 's':
        case 'S':
        {
            u32 d0_reg = 0x0, stack_value = 0x0; 

            lookahead = read_byte(emulator, (*ram_ptr)+1); 

            if (lookahead == 0x00 || (lookahead - 0x30) > 6)
                index = -1;
            else
                index = lookahead - 0x30;
            
            d0_reg = read_datareg(emulator, 0);

            while (!is_buffer_valid(emulator) && is_buffering_enabled(emulator))
                usleep(25000);

            if (is_buffering_enabled(emulator)) 
            { 
                char* str = read_str_InputBuffer(emulator);

                if (str) 
                { 
                    if (index >= 0)
                    {
                        *ram_ptr = *ram_ptr + 1;

                        u32 rptr2 = read_addrreg(emulator, index); 
                        u32 i = 0;                 
                        while (i < d0_reg && i < buffer_len(emulator))
                        { 
                            write_byte(emulator, rptr2++, str[i]); 
                            i++; 
                        } 

                        write_byte(emulator, rptr2, 0x00); 
                    }
                    else
                    {
                        const u32 len = (u32) strlen(str);
                        u32 stack_ptr = read_addrreg(emulator, 7);

                        if (emulator->Machine.RunTime.STACK_BOTTOM_INDEX == stack_ptr)
                            stack_value = 0;
                        else
                            stack_value = pop_long(emulator);

                        stack_value += len;
                        push_long(emulator, stack_value);
                    }
                       
                    free(str); 
                } 
                init_InputBuffer(emulator); 
            } 
            else return c_false;

            *ram_ptr = *ram_ptr + 1;
            break; 
        }

        default:
        {
            opsize size;
            u32 value = 0;

            switch (cchar) 
            {
                case 'b':   
                case 'B':   
                    size = BYTE;
                    break;  
                case 'w':   
                case 'W':   
                    size = WORD;
                    break;  
                case 'l':   
                case 'L':   
                    size = LONG;
                    break;  
                default:    
                    return c_false;  
            }

            lookahead = read_byte(emulator, (*ram_ptr)+1);

            if (lookahead == 0x00)
                return c_false;

            if (lookahead == 'a' || lookahead == 'A' ||
                lookahead == 'd' || lookahead == 'D')
            {
                cchar = lookahead;
                *ram_ptr = *ram_ptr+1;
            }
            else return c_false;
            
            char rtype = cchar;
            
            lookahead = read_byte(emulator, (*ram_ptr)+1);  

            if (lookahead == 0x00 || (lookahead - 0x30) > 7)
                return c_false;

            index = lookahead - 0x30;

            *ram_ptr = *ram_ptr+1;  
     
            while (!is_buffer_valid(emulator) && is_buffering_enabled(emulator))
                usleep(25000);

            if (is_buffering_enabled(emulator)) 
            {
                value = read_int_InputBuffer(emulator) & mask_by_opsize(size);
                
                init_InputBuffer(emulator);
                
                switch (rtype)
                {
                    case 'a': 
                    case 'A': 
                        write_addrreg(emulator, index, value, &size);  
                        break;

                    case 'd': 
                    case 'D': 
                        write_datareg(emulator, index, value, &size);  
                        break;
                }
            }
            else return c_false;
        }
    
    }

    return c_true;
}

void eval_scan_seq(struct EmulationMachine* emulator)
{
    u32  ram_ptr = 0x0;
    char cchar   = 0x0;

    ram_ptr = read_addrreg(emulator, 0);
    
    while (((cchar = read_byte(emulator, ram_ptr++)) & 0xFF) != 0x00) 
    { 
        switch(cchar)
        {
            case '%':
                if (!eval_scan_placeholder_seq(emulator, &ram_ptr))
                    return; 

                break;

            default:
                break;
        }
    }
}


c_bool iotask(struct EmulationMachine *emulator)
{
    char *str = NULL;

    if (emulator->Machine.IO.buffer)
        free(emulator->Machine.IO.buffer);
    
    emulator->Machine.IO.buffer = NULL;

    if (emulator->Machine.IO.Type == OUTPUT)
    {
        str = eval_print_seq(emulator);

        if (str != NULL)
        {
            emulator->Machine.IO.buffer  = str;
        }
    }
    else if (emulator->Machine.IO.Type == INPUT)
    {
        eval_scan_seq(emulator);
    }
    
    return is_buffering_enabled(emulator);
}



#include "JSON.h"

void emit_dump(struct EmulationMachine *emulator)
{
    if (emulator->Machine.dump != NULL) 
        free(emulator->Machine.dump);
        
    emulator->Machine.dump = NULL;

    emulator->Machine.dump = Jcpu(emulator);
    emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jram,    emulator->Machine.RunTime.org_pointer, emulator->Machine.RunTime.last_loaded_byte_index, emulator->Machine.RunTime.simhalt);

    emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jop,     emulator->Machine.RunTime.mnemonic, emulator->Machine.RunTime.operation_code);
    emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jchrono, emulator->Machine.RunTime.Chrono.dt);

    if (emulator->Machine.State == IO_STATE && emulator->Machine.IO.Type == OUTPUT)
        emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jio, emulator->Machine.IO.buffer);

    if (emulator->Machine.State == TRAP_STATE)
        emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jexception, emulator->Machine.RunTime.Exception.trap_cause, TRAP_EXC_TYPE);
    else if (emulator->Machine.State == PANIC_STATE)
        emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jexception, emulator->Machine.RunTime.Exception.panic_cause, PANIC_EXC_TYPE);
    else if (emulator->Machine.State == MERR_STATE)
        emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jexception, emulator->Machine.RunTime.Exception.merr_cause, MERR_EXC_TYPE);
    else if (emulator->Machine.State == WARNING_STATE)
        emulator->Machine.dump = Jconcat2(emulator, emulator->Machine.dump, Jwarning, emulator->Machine.RunTime.Warning.cause, emulator->Machine.RunTime.Warning.mnem, emulator->Machine.RunTime.Warning.code);
}