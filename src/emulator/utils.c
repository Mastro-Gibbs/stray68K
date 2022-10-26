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







void iotask(bit descr)
{
    u32 d0_val = read_datareg(0) & 0x000000FF;
    u32 d1_val = read_datareg(1);
    u32 d2_val = read_datareg(2) & 0x000000FF;

    s32  value;
    opsize        size;

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
            SING_EXTENDED(value, d1_val, size);
            IO_TASK(descr, "%d", value);
            break;
        }

        case PRINTINTLN:
        {
            SING_EXTENDED(value, d1_val, size);
            IO_TASK(descr, "%d\n", value);
            break;
        }

        case UPRINTINT:
        {
            IO_TASK(descr, "%d", d1_val);
            break;
        }

        case UPRINTINTLN:
        {
            IO_TASK(descr, "%d\n", d1_val);
            break;
        }

        case SCANINT:
        {
            u32 ip;
            scanf(" %u", &ip);
            write_datareg(1, ip, NULL);
            break;
        }

        case PRINTSTR:
        {
            u32 ramptr = read_addrreg(0);
            char c;

            IO_TASK_TAG(descr)
            do
            {
                c = read_byte(ramptr++);
                printf("%c", c);

            } while ((c & 0xFF) != 0b00000000);

            break;
        }

        case PRINTSTRLN:
        {
            u32 ramptr = read_addrreg(0);
            char c;

            IO_TASK_TAG(descr)
            do
            {
                c = read_byte(ramptr++);
                printf("%c", c);

            } while ((c & 0xFF) != 0b00000000);
            printf("\n");

            break;
        }

        default:
            break;
    }
}


#include <unistd.h>
void machine_waiter(struct EmulationMachine *em)
{
    if (em->Machine.Data.sbs_debugger)
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
            tcgetattr(STDIN_FILENO, &em->Machine.Waiting.oldt);
            em->Machine.Waiting.newt = em->Machine.Waiting.oldt;
            em->Machine.Waiting.newt.c_lflag &= ~(ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &em->Machine.Waiting.newt);

            opt = getchar();

            tcsetattr(STDIN_FILENO, TCSANOW, &em->Machine.Waiting.oldt);

            switch (opt) {
                case 's': //stack;
                {
                    u32 _top = 0, _bottom = 0x00FFFFFF;

                    SBS_DEBUGGER("Insert stack top address: ");
                    scanf("%X", &_top);
                    SBS_DEBUGGER("Insert stack bottom address: ");
                    scanf("%X", &_bottom);

                    if (_bottom > RAM_SIZE || (((_bottom & 0x0000000F) + 1) % 4) != 0)
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
                    printf_sstatus(em);

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

                    em->Machine.Data.sbs_debugger = FALSE;
                    em->ExecArgs.descr = FALSE;
                    break;
                }

                default: //catch \n and do nothing here
                { break; }
            }
        }
    }
}

#include "JSON.h"
void printf_sstatus(struct EmulationMachine *em)
{
    if (em->ExecArgs.JSON.enable)
    {
        if (em->ExecArgs.quiet && em->State != FINAL_STATE) return;

        if (em->Machine.Data.sbs_debugger) system("clear");

        char *buf = NULL;

        if (em->ExecArgs.JSON.cpu)
        {
            buf = Jcpu();
            printf("%s\n", buf);
            free(buf);
        }

        if (em->ExecArgs.JSON.ram)
        {
            u32 _start, _end, _ptr = em->Machine.cpu->pc;
            _start = (_ptr & 0xFFFFFFF0) - 0x20;
            _end   = (_ptr | 0x0000000F) + 0x31;
            buf = Jram(_start, _end);
            printf("%s\n", buf);
            free(buf);
        }

        if (em->ExecArgs.JSON.ocode)
        {
            buf = Jcode(em->Machine.OpCode.code);
            printf("%s\n", buf);
            free(buf);
        }

        if (em->ExecArgs.JSON.menm)
        {
            buf = Jmnemonic(em->Machine.OpCode.mnemonic);
            printf("%s\n", buf);
            free(buf);
        }

        if (em->State == FINAL_STATE && em->ExecArgs.JSON.timer)
        {
            buf = Jchrono(em->Machine.Timer.dt);
            printf("%s\n", buf);
            free(buf);
        }

    }
    else if (!em->ExecArgs.quiet)
    {
        if (em->EmuType == EMULATE_SBS && em->Machine.Data.sbs_debugger) system("clear");

        u32 _start = em->Machine.Data.orgptr;
        u32 _end   = (em->Machine.Data.lwb | 0x0000000F) + 0x11;
        u32 _ptr   = em->Machine.cpu->pc;
        char *pcptr_color    = "";
        char *halt_color     = "\033[37m";

        if (em->State == BEGIN_STATE)
        {
            printf("\033[01m\033[37mInitial State:\033[0m");
            pcptr_color = "\033[92m";
        }
        else if (em->State == EXECUTION_STATE)
        {
            printf("\033[01m\033[37mExecution State:\033[0m");
            _start = (_ptr & 0xFFFFFFF0) - 0x20;
            _end   = (_ptr | 0x0000000F) + 0x31;
            pcptr_color    = "\033[93m";

        }
        else if (em->State == FINAL_STATE)
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

        if (em->EmuType == EMULATE_STD && em->State == FINAL_STATE)
            printf("\033[01m\033[37mHalt\033[0m:     %s0x%X\033[0m\n", halt_color, em->Machine.Data.simhalt);
        else if (em->EmuType == EMULATE_SBS)
            printf("\033[01m\033[37mHalt\033[0m:     %s0x%X\033[0m\n", halt_color, em->Machine.Data.simhalt);

        if (em->ExecArgs.descr)
        {
            opcode Code = em->Machine.OpCode.code;

            bprintf_ht_4s(Code)
            printf(" -> 0x%.4X (hex)\n", Code);
            printf("\033[01m\033[37mMnemonic\033[0m: %s\n", em->Machine.OpCode.mnemonic);
        }

        fflush(stdout);
    }

    if (em->State == FINAL_STATE && em->ExecArgs.timer)
    {
        if (!em->ExecArgs.quiet)
            printf("-------------------------------------------------------------------------------------------------------------------------\n");
        printf("\033[01m\033[37mTimer\033[0m: %.3fms -> %.3fs\n",
               (f64) em->Machine.Timer.dt / (f64) 1000,
               (f64) em->Machine.Timer.dt / (f64) 1000000);
    }
}
