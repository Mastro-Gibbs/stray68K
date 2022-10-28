#include "utils.h"

u32 most_significant_byte(opsize size)
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


u32 mask_by_opsize(opsize size)
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
sspan size_to_span(opsize size)
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

bit is_ram_op(ADDRMode *mode)
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


bit is_addr_to_data_op(ADDRMode *mode)
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
char* trap_code_toString(u32 trapcode)
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

    emit_sys_status(em);

    em->Machine.IO.buffer  = NULL;
    em->Machine.IO.Type    = IO_UNDEF;
    em->Machine.IO.NewLine = NL_UNDEF;
}

void iotask(struct EmulationMachine *em)
{
    em->Machine.State = IO_STATE;

    u32 d0_val = read_datareg(0) & 0x000000FF;
    u32 d1_val = read_datareg(1);
    u32 d2_val = read_datareg(2) & 0x000000FF;

    s32    value;
    opsize size;

    switch (d2_val) {
        case 0x01:
            size = BYTE;
            break;
        case 0x02:
            size = WORD;
            break;
        default:
            size = LONG;
    }

    switch (d0_val)
    {
        case PRINTINT:
        {
            SIGN_EXTENDED(value, d1_val, size);

            u32 length = snprintf(NULL, 0, "%d", value);

            char* str = malloc(length + 1);
            snprintf(str, length + 1, "%d", value);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = OUTPUT;
            em->Machine.IO.NewLine = NL_FALSE;

            _io_dumps(em);

            IO_TASK(em->ExecArgs.descriptive_mode, "%d", value);

            free(str);
            break;
        }

        case PRINTINTLN:
        {
            SIGN_EXTENDED(value, d1_val, size);

            u32 length = snprintf(NULL, 0, "%d", value);

            char* str = malloc(length + 1);
            snprintf(str, length + 1, "%d", value);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = OUTPUT;
            em->Machine.IO.NewLine = NL_TRUE;

            _io_dumps(em);

            IO_TASK(em->ExecArgs.descriptive_mode, "%d\n", value);
            free(str);
            break;
        }

        case UPRINTINT:
        {
            u32 length = snprintf(NULL, 0, "%d", d1_val);

            char* str = malloc(length + 1);
            snprintf(str, length + 1, "%d", d1_val);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = OUTPUT;
            em->Machine.IO.NewLine = NL_FALSE;

            _io_dumps(em);

            IO_TASK(em->ExecArgs.descriptive_mode, "%d", d1_val);
            free(str);
            break;
        }

        case UPRINTINTLN:
        {
            u32 length = snprintf(NULL, 0, "%d", d1_val);

            char* str = malloc(length + 1);
            snprintf(str, length + 1, "%d", d1_val);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = OUTPUT;
            em->Machine.IO.NewLine = NL_TRUE;

            _io_dumps(em);

            IO_TASK(em->ExecArgs.descriptive_mode, "%d\n", d1_val);
            free(str);
            break;
        }

        case SCANINT:
        {
            u32 ip;
            scanf(" %u", &ip);
            write_datareg(1, ip, NULL);

            u32 length = snprintf(NULL, 0, "%d", ip);

            char* str = malloc(length + 1);
            snprintf(str, length + 1, "%d", ip);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = INPUT;
            em->Machine.IO.NewLine = NL_FALSE;

            _io_dumps(em);
            free(str);
            break;
        }

#include <string.h>
        case PRINTSTR:
        {
            u32 ramptr = read_addrreg(0);
            u32 pos = 0;

            char c;
            char *str;

            str = calloc(1, sizeof (s8));
            str[pos] = '\0';

            do
            {
                c = read_byte(ramptr++);

                str = realloc(str, pos+2);

                str[pos++] = c;
                str[pos]   = '\0';

            } while ((c & 0xFF) != 0b00000000);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = OUTPUT;
            em->Machine.IO.NewLine = NL_FALSE;

            _io_dumps(em);

            IO_TASK_TAG(em->ExecArgs.descriptive_mode)
            printf("%s", str);
            free(str);
            break;
        }

        case PRINTSTRLN:
        {
            em->Machine.IO.NewLine = NL_TRUE;

            u32 ramptr = read_addrreg(0);
            u32 pos = 0;

            char c;
            char *str;

            str = calloc(1, sizeof (s8));
            str[pos] = '\0';

            do
            {
                c = read_byte(ramptr++);

                str = realloc(str, pos+2);
                str[pos++] = c;
                str[pos]   = '\0';

            } while ((c & 0xFF) != 0b00000000);

            em->Machine.IO.buffer  = str;
            em->Machine.IO.Type    = OUTPUT;
            em->Machine.IO.NewLine = NL_TRUE;

            _io_dumps(em);

            IO_TASK_TAG(em->ExecArgs.descriptive_mode)
            printf("%s\n", str);
            free(str);
            break;
        }

        default:
            break;
    }

    em->Machine.State = EXECUTION_STATE;
}


#include <unistd.h>
void machine_waiter(struct EmulationMachine *em)
{
    if (em->Machine.RuntimeData.sbs_printer_enabler)
    {
        fputs(
            "\n---------------- Execution Options ----------------\n"
            "[\033[01m\033[37ms\033[0m] \033[01m\033[37mstack\033[0m | "
            "[\033[01m\033[37mn\033[0m] \033[01m\033[37mnext\033[0m | "
            "[\033[01m\033[37mk\033[0m] \033[01m\033[37mskip\033[0m | "
            "[\033[01m\033[37mt\033[0m] \033[01m\033[37mfull skip\033[0m\n",
        stdout);

        fflush(stdout);
        fflush(stdin);

        char opt;
        bit loop = TRUE;

        while (loop)
        {
            tcgetattr(STDIN_FILENO, &em->Machine.RuntimeData.oldt);
            em->Machine.RuntimeData.newt = em->Machine.RuntimeData.oldt;
            em->Machine.RuntimeData.newt.c_lflag &= ~(ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &em->Machine.RuntimeData.newt);

            opt = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &em->Machine.RuntimeData.oldt);

            switch (opt) {
                case 's': //stack;
                {
                    u32 _top = 0, _bottom = em->Machine.RuntimeData.STACK_BOTTOM_INDEX - 1;

                    SBS_DEBUGGER("Insert stack top address: ");
                    scanf("%X", &_top);
                    SBS_DEBUGGER("Insert stack bottom address: ");
                    scanf("%X", &_bottom);

                    if (_bottom >= em->Machine.RuntimeData.STACK_BOTTOM_INDEX || (((_bottom & 0x0000000F) + 1) % 4) != 0)
                    {
                        SBS_DEBUGGER("Invalid bottom index");
                    }
                    else
                    {
                        em->Machine.ram->stack(_top, _bottom);
                    }

                    break;
                }

                case 'n': //goto next istr, print cpu & ram
                {
                    emit_sys_status(em);

                    loop = FALSE;
                    break;
                }

                case 'k': //skip
                {
                    system("clear");
                    SBS_DEBUGGER("Skip selected, the execution proceeds.\n");

                    loop = FALSE;
                    break;
                }

                case 't': //terminate
                {
                    system("clear");
                    SBS_DEBUGGER("Full skip selected, the execution proceeds to the end.\n");

                    loop = FALSE;

                    em->Machine.RuntimeData.sbs_printer_enabler = FALSE;
                    em->ExecArgs.descriptive_mode = FALSE;
                    break;
                }

                default: //catch \n and do nothing here
                { break; }
            }
        }
    }
}

#include "JSON.h"
void emit_sys_status(struct EmulationMachine *em)
{
    if (em->EmuType == EMULATE_SBS && em->Machine.RuntimeData.sbs_printer_enabler) system("clear");

    if (em->ExecArgs.JSON.is_activated)
    {
        if (em->EmuType == EMULATE_STD && em->ExecArgs.quiet_mode && em->Machine.State != FINAL_STATE) goto maybe_sbs_print;

        char *buf = NULL;

        if (em->ExecArgs.JSON.dump)
        {
            emit_dump(em);
        }
        else if (em->ExecArgs.JSON.concat)
        {
            emit_jconcat(em);
        }
        else
        {
            if (em->ExecArgs.JSON.cpu)
            {
                buf = Jcpu();
                printf("%s\n", buf);
                free(buf);
            }

            if (em->ExecArgs.JSON.ram)
            {
                buf = Jram(em->Machine.RuntimeData.org_pointer, em->Machine.RuntimeData.last_loaded_byte_index, em->Machine.RuntimeData.simhalt);
                printf("%s\n", buf);
                free(buf);
            }

            if (em->ExecArgs.JSON.op)
            {
                buf = Jop(em->Machine.RuntimeData.mnemonic, em->Machine.RuntimeData.operation_code);
                printf("%s\n", buf);
                free(buf);
            }

            if (em->Machine.State == FINAL_STATE && em->ExecArgs.JSON.chrono)
            {
                buf = Jchrono(em->Machine.Chrono.dt);
                printf("%s\n", buf);
                free(buf);
            }
        }
    }

maybe_sbs_print:
    if (!em->ExecArgs.quiet_mode)
    {
        u32 _start = em->Machine.RuntimeData.org_pointer;
        u32 _end   = (em->Machine.RuntimeData.last_loaded_byte_index | 0x0000000F) + 0x11;
        u32 _ptr   = em->Machine.cpu->pc;
        char *pcptr_color    = "";
        char *halt_color     = "\033[37m";

        if (em->Machine.State == BEGIN_STATE)
        {
            printf("\033[01m\033[37mInitial State:\033[0m");
            pcptr_color = "\033[92m";
        }
        else if (em->Machine.State == EXECUTION_STATE)
        {
            printf("\033[01m\033[37mExecution State:\033[0m");
            _start = (_ptr & 0xFFFFFFF0) - 0x20;
            _end   = (_ptr | 0x0000000F) + 0x31;
            pcptr_color    = "\033[93m";

        }
        else if (em->Machine.State == FINAL_STATE)
        {
            if (em->EmuType == EMULATE_STD)
                printf("-------------------------------------------------------------------------------------------------------------------------\n");

            printf("\033[01m\033[37mFinal State:\033[0m");
            pcptr_color    = "\033[91m";
            halt_color     = "\033[91m";
        }

        em->Machine.cpu->show();
        printf("\n");

        em->Machine.ram->show(_start, _end, _ptr, pcptr_color);
        printf("\n");

        if (em->EmuType == EMULATE_STD && em->Machine.State == FINAL_STATE)
            printf("\033[01m\033[37mHalt\033[0m:     %s0x%X\033[0m\n", halt_color, em->Machine.RuntimeData.simhalt);
        else if (em->EmuType == EMULATE_SBS)
            printf("\033[01m\033[37mHalt\033[0m:     %s0x%X\033[0m\n", halt_color, em->Machine.RuntimeData.simhalt);

        if (em->ExecArgs.descriptive_mode)
        {
            opcode Code = em->Machine.RuntimeData.operation_code;

            bprintf_ht_4s(Code)
            printf(" -> 0x%.4X (hex)\n", Code);
            printf("\033[01m\033[37mMnemonic\033[0m: %s\n", em->Machine.RuntimeData.mnemonic);
        }

        fflush(stdout);
    }

    if (em->Machine.State == FINAL_STATE && em->ExecArgs.chrono_mode)
    {
        if (!em->ExecArgs.quiet_mode)
            printf("-------------------------------------------------------------------------------------------------------------------------\n");
        printf("\033[01m\033[37mTimer\033[0m: %.3fms -> %.3fs\n",
               (f64) em->Machine.Chrono.dt / (f64) 1000,
               (f64) em->Machine.Chrono.dt / (f64) 1000000);
    }
}

void emit_dump(struct EmulationMachine *em)
{
    char *buf = NULL;

    if (get_cpu() == NULL || get_ram() == NULL)
    {
        if (em->Machine.State == PANIC_STATE)
            buf = Jexception(em->Machine.Exception.panic_cause, PANIC_EXC_TYPE);
        else if (em->Machine.State == MERR_STATE)
            buf = Jexception(em->Machine.Exception.merr_cause, MERR_EXC_TYPE);
    }
    else
    {
        buf = Jcpu();
        buf = Jconcat2(buf, Jram,    em->Machine.RuntimeData.org_pointer, em->Machine.RuntimeData.last_loaded_byte_index, em->Machine.RuntimeData.simhalt);
        buf = Jconcat2(buf, Jop,     em->Machine.RuntimeData.mnemonic, em->Machine.RuntimeData.operation_code);
        buf = Jconcat2(buf, Jchrono, em->Machine.Chrono.dt);

        if (em->Machine.IO.buffer != NULL && em->Machine.IO.Type != IO_UNDEF && em->Machine.IO.NewLine != NL_UNDEF)
            buf = Jconcat2(buf, Jio, em->Machine.IO.buffer, em->Machine.IO.Type, em->Machine.IO.NewLine);

        if (em->Machine.State == TRAP_STATE)
            buf = Jconcat2(buf, Jexception, em->Machine.Exception.trap_cause, TRAP_EXC_TYPE);
        else if (em->Machine.State == PANIC_STATE)
            buf = Jconcat2(buf, Jexception, em->Machine.Exception.panic_cause, PANIC_EXC_TYPE);
        else if (em->Machine.State == MERR_STATE)
            buf = Jconcat2(buf, Jexception, em->Machine.Exception.merr_cause, MERR_EXC_TYPE);
    }

    printf("%s\n", buf);
    free(buf);
}

void emit_jio(struct EmulationMachine *em)
{
    if (em->ExecArgs.JSON.is_activated && em->ExecArgs.JSON.io)
    {
        char *buf = NULL;

        buf = Jio(em->Machine.IO.buffer, em->Machine.IO.Type, em->Machine.IO.NewLine);

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
