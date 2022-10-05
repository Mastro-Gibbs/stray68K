#include "opcode_handlers.h"

#include <stdlib.h>

#define INSTRUCTION_SET_GROUPS_COUNT 14

#define GROUP_0x00_LEN  21
#define GROUP_0x01_LEN  1
#define GROUP_0x02_LEN  2
#define GROUP_0x03_LEN  2
#define GROUP_0x04_LEN  30
#define GROUP_0x05_LEN  4
#define GROUP_0x06_LEN  3
#define GROUP_0x07_LEN  1
#define GROUP_0x08_LEN  4
#define GROUP_0x09_LEN  3
#define GROUP_0x0B_LEN 4
#define GROUP_0x0C_LEN 5
#define GROUP_0x0D_LEN 3
#define GROUP_0x0E_LEN 16


opcodes_ds *codemap = NULL;


void init_codes()
{
    if (!codemap)
    {
        codemap = malloc(sizeof (*codemap) * INSTRUCTION_SET_GROUPS_COUNT);


        // GROUP 0x00
        codemap[0].key  = 0x00;
        codemap[0].size = GROUP_0x00_LEN;
        codemap[0].instances     = malloc(sizeof (*codemap[0].instances)  * GROUP_0x00_LEN);
        codemap[0].instances[0]  = new_opcode_t(0b0000000000111100, 0b1111111111111111, "ORItoCCR",  ORItoCCR);
        codemap[0].instances[1]  = new_opcode_t(0b0000000001111100, 0b1111111111111111, "ORItoSR",   ORItoSR);
        codemap[0].instances[2]  = new_opcode_t(0b0000000000000000, 0b1111111100000000, "ORI",       ORI);
        codemap[0].instances[3]  = new_opcode_t(0b0000001000111100, 0b1111111111111111, "ANDItoCCR", ANDItoCCR);
        codemap[0].instances[4]  = new_opcode_t(0b0000001001111100, 0b1111111111111111, "ANDItoSR",  ANDItoSR);
        codemap[0].instances[5]  = new_opcode_t(0b0000001000000000, 0b1111111100000000, "ANDI",      ANDI);
        codemap[0].instances[6]  = new_opcode_t(0b0000010000000000, 0b1111111100000000, "SUBI",      SUBI);
        codemap[0].instances[7]  = new_opcode_t(0b0000011000000000, 0b1111111100000000, "ADDI",      ADDI);
        codemap[0].instances[8]  = new_opcode_t(0b0000101000111100, 0b1111111111111111, "EORItoCCR", EORItoCCR);
        codemap[0].instances[9]  = new_opcode_t(0b0000101001111100, 0b1111111111111111, "EORItoSR",  EORItoSR);
        codemap[0].instances[10] = new_opcode_t(0b0000101000000000, 0b1111111100000000, "EORI",      EORI);
        codemap[0].instances[11] = new_opcode_t(0b0000110000000000, 0b1111111100000000, "CMPI",      CMPI);
        codemap[0].instances[12] = new_opcode_t(0b0000000100001000, 0b1111000100111000, "MOVEP",     MOVEP);
        codemap[0].instances[13] = new_opcode_t(0b0000100000000000, 0b1111111111000000, "BTST",      BTST);
        codemap[0].instances[14] = new_opcode_t(0b0000100001000000, 0b1111111111000000, "BCHG",      BCHG);
        codemap[0].instances[15] = new_opcode_t(0b0000100010000000, 0b1111111111000000, "BCLR",      BCLR);
        codemap[0].instances[16] = new_opcode_t(0b0000100011000000, 0b1111111111000000, "BSET",      BSET);
        codemap[0].instances[17] = new_opcode_t(0b0000000100000000, 0b1111000111000000, "BTST",      BTST);
        codemap[0].instances[18] = new_opcode_t(0b0000000101000000, 0b1111000111000000, "BCHG",      BCHG);
        codemap[0].instances[19] = new_opcode_t(0b0000000110000000, 0b1111000111000000, "BCLR",      BCLR);
        codemap[0].instances[20] = new_opcode_t(0b0000000111000000, 0b1111000111000000, "BSET",      BSET);


        // GROUP 0x01
        codemap[1].key  = 0x01;
        codemap[1].size = GROUP_0x01_LEN;
        codemap[1].instances    = malloc(sizeof (*codemap[1].instances)  * GROUP_0x01_LEN);
        codemap[1].instances[0] = new_opcode_t(0b0001000000000000, 0b1111000000000000, "MOVE", MOVE);


        // GROUP 0x02
        codemap[2].key  = 0x02;
        codemap[2].size = GROUP_0x02_LEN;
        codemap[2].instances    = malloc(sizeof (*codemap[2].instances)  * GROUP_0x02_LEN);
        codemap[2].instances[0] = new_opcode_t(0b0010000001000000, 0b1111000111000000, "MOVEA", MOVEA);
        codemap[2].instances[1] = new_opcode_t(0b0010000000000000, 0b1111000000000000, "MOVE",  MOVE);


        // GROUP 0x03
        codemap[3].key  = 0x03;
        codemap[3].size = GROUP_0x03_LEN;
        codemap[3].instances    = malloc(sizeof (*codemap[3].instances)  * GROUP_0x03_LEN);
        codemap[3].instances[0] = new_opcode_t(0b0011000001000000, 0b1111000111000000, "MOVEA", MOVEA);
        codemap[3].instances[1] = new_opcode_t(0b0011000000000000, 0b1111000000000000, "MOVE",  MOVE);


        // GROUP 0x04
        codemap[4].key  = 0x04;
        codemap[4].size = GROUP_0x04_LEN;
        codemap[4].instances     = malloc(sizeof (*codemap[4].instances)  * GROUP_0x04_LEN);
        codemap[4].instances[0]  = new_opcode_t(0b0100000011000000, 0b1111111111000000, "MOVEfromSR", MOVEfromSR);
        codemap[4].instances[1]  = new_opcode_t(0b0100010011000000, 0b1111111111000000, "MOVEtoCCR",  MOVEtoCCR);
        codemap[4].instances[2]  = new_opcode_t(0b0100011011000000, 0b1111111111000000, "MOVEtoSR",   MOVEtoSR);
        codemap[4].instances[3]  = new_opcode_t(0b0100000000000000, 0b1111111100000000, "NEGX",       NEGX);
        codemap[4].instances[4]  = new_opcode_t(0b0100001000000000, 0b1111111100000000, "CLR",        CLR);
        codemap[4].instances[5]  = new_opcode_t(0b0100010000000000, 0b1111111100000000, "NEG",        NEG);
        codemap[4].instances[6]  = new_opcode_t(0b0100011000000000, 0b1111111100000000, "NOT",        NOT);
        codemap[4].instances[7]  = new_opcode_t(0b0100100010000000, 0b1111111110111000, "EXT",        EXT);
        codemap[4].instances[8]  = new_opcode_t(0b0100100000000000, 0b1111111111000000, "NBCD",       NBCD);
        codemap[4].instances[9]  = new_opcode_t(0b0100100001000000, 0b1111111111111000, "SWAP",       SWAP);
        codemap[4].instances[10] = new_opcode_t(0b0100100001000000, 0b1111111111000000, "PEA",        PEA);
        codemap[4].instances[11] = new_opcode_t(0b0100101011111100, 0b1111111111111111, "ILLEGAL",    ILLEGAL);
        codemap[4].instances[12] = new_opcode_t(0b0100101011000000, 0b1111111111000000, "TAS",        TAS);
        codemap[4].instances[13] = new_opcode_t(0b0100101000000000, 0b1111111100000000, "TST",        TST);
        codemap[4].instances[14] = new_opcode_t(0b0100111001000000, 0b1111111111110000, "TRAP",       TRAP);
        codemap[4].instances[15] = new_opcode_t(0b0100111001010000, 0b1111111111111000, "LINK",       LINK);
        codemap[4].instances[16] = new_opcode_t(0b0100111001011000, 0b1111111111111000, "UNLK",       UNLK);
        codemap[4].instances[17] = new_opcode_t(0b0100111001100000, 0b1111111111110000, "MOVEUSP",    MOVEUSP);
        codemap[4].instances[18] = new_opcode_t(0b0100111001110000, 0b1111111111111111, "RESET",      RESET);
        codemap[4].instances[19] = new_opcode_t(0b0100111001110001, 0b1111111111111111, "NOP",        NOP);
        codemap[4].instances[20] = new_opcode_t(0b0100111001110010, 0b1111111111111111, "STOP",       STOP);
        codemap[4].instances[21] = new_opcode_t(0b0100111001110011, 0b1111111111111111, "RTE",        RTE);
        codemap[4].instances[22] = new_opcode_t(0b0100111001110101, 0b1111111111111111, "RTS",        RTS);
        codemap[4].instances[23] = new_opcode_t(0b0100111001110110, 0b1111111111111111, "TRAPV",      TRAPV);
        codemap[4].instances[24] = new_opcode_t(0b0100111001110111, 0b1111111111111111, "RTR",        RTR);
        codemap[4].instances[25] = new_opcode_t(0b0100111010000000, 0b1111111111000000, "JSR",        JSR);
        codemap[4].instances[26] = new_opcode_t(0b0100111011000000, 0b1111111111000000, "JMP",        JMP);
        codemap[4].instances[27] = new_opcode_t(0b0100100010000000, 0b1111101110000000, "MOVEM",      MOVEM);
        codemap[4].instances[28] = new_opcode_t(0b0100000110000000, 0b1111000111000000, "CHK",        CHK);
        codemap[4].instances[29] = new_opcode_t(0b0100000111000000, 0b1111000111000000, "LEA",        LEA);


        // GROUP 0x05
        codemap[5].key  = 0x05;
        codemap[5].size = GROUP_0x05_LEN;
        codemap[5].instances    = malloc(sizeof (*codemap[5].instances)  * GROUP_0x05_LEN);
        codemap[5].instances[0] = new_opcode_t(0b0101000011001000, 0b1111000011111000, "DBcc", DBcc);
        codemap[5].instances[1] = new_opcode_t(0b0101000011000000, 0b1111000011000000, "Scc",  Scc);
        codemap[5].instances[2] = new_opcode_t(0b0101000000000000, 0b1111000100000000, "ADDQ", ADDQ);
        codemap[5].instances[3] = new_opcode_t(0b0101000100000000, 0b1111000100000000, "SUBQ", SUBQ);


        // GROUP 0x06
        codemap[6].key = 0x06;
        codemap[6].size = GROUP_0x06_LEN;
        codemap[6].instances    = malloc(sizeof (*codemap[6].instances)  * GROUP_0x06_LEN);
        codemap[6].instances[0] = new_opcode_t(0b0110000000000000, 0b1111111100000000, "BRA", BRA);
        codemap[6].instances[1] = new_opcode_t(0b0110000100000000, 0b1111111100000000, "BSR", BSR);
        codemap[6].instances[2] = new_opcode_t(0b0110000000000000, 0b1111000000000000, "Bcc", Bcc);


        // GROUP 0x07
        codemap[7].key  = 0x07;
        codemap[7].size = GROUP_0x07_LEN;
        codemap[7].instances    = malloc(sizeof (*codemap[7].instances)  * GROUP_0x07_LEN);
        codemap[7].instances[0] = new_opcode_t(0b0111000000000000, 0b1111000100000000, "MOVEQ", MOVEQ);


        // GROUP 0x08
        codemap[8].key  = 0x08;
        codemap[8].size = GROUP_0x08_LEN;
        codemap[8].instances    = malloc(sizeof (*codemap[8].instances)  * GROUP_0x08_LEN);
        codemap[8].instances[0] = new_opcode_t(0b1000000011000000, 0b1111000111000000, "DIVU", DIVU);
        codemap[8].instances[1] = new_opcode_t(0b1000000111000000, 0b1111000111000000, "DIVS", DIVS);
        codemap[8].instances[2] = new_opcode_t(0b1000000100000000, 0b1111000111110000, "SBCD", SBCD);
        codemap[8].instances[3] = new_opcode_t(0b1000000000000000, 0b1111000000000000, "OR",   OR);


        // GROUP 0x09
        codemap[9].key  = 0x09;
        codemap[9].size = GROUP_0x09_LEN;
        codemap[9].instances    = malloc(sizeof (*codemap[9].instances)  * GROUP_0x09_LEN);
        codemap[9].instances[0] = new_opcode_t(0b1001000011000000, 0b1111000011000000, "SUBA", SUBA);
        codemap[9].instances[1] = new_opcode_t(0b1001000100000000, 0b1111000100110000, "SUBX", SUBX);
        codemap[9].instances[2] = new_opcode_t(0b1001000000000000, 0b1111000000000000, "SUB",  SUB);


        // GROUP 0x0B
        codemap[10].key  = 0x0B;
        codemap[10].size = GROUP_0x0B_LEN;
        codemap[10].instances    = malloc(sizeof (*codemap[10].instances) * GROUP_0x0B_LEN);
        codemap[10].instances[0] = new_opcode_t(0b1011000011000000, 0b1111000011000000, "CMPA", CMPA);
        codemap[10].instances[1] = new_opcode_t(0b1011000100001000, 0b1111000100111000, "CMPM", CMPM);
        codemap[10].instances[2] = new_opcode_t(0b1011000100000000, 0b1111000100000000, "EOR",  EOR);
        codemap[10].instances[3] = new_opcode_t(0b1011000000000000, 0b1111000100000000, "CMP",  CMP);


        // GROUP 0x0C
        codemap[11].key  = 0x0C;
        codemap[11].size = GROUP_0x0C_LEN;
        codemap[11].instances    = malloc(sizeof (*codemap[11].instances) * GROUP_0x0C_LEN);
        codemap[11].instances[0] = new_opcode_t(0b1100000011000000, 0b1111000111000000, "MULU", MULU);
        codemap[11].instances[1] = new_opcode_t(0b1100000111000000, 0b1111000111000000, "MULS", MULS);
        codemap[11].instances[2] = new_opcode_t(0b1100000100000000, 0b1111000111110000, "ABCD", ABCD);
        codemap[11].instances[3] = new_opcode_t(0b1100000100000000, 0b1111000100110000, "EXG",  EXG);
        codemap[11].instances[4] = new_opcode_t(0b1100000000000000, 0b1111000000000000, "AND",  AND);


        // GROUP 0x0D
        codemap[12].key  = 0x0D;
        codemap[12].size = GROUP_0x0D_LEN;
        codemap[12].instances    = malloc(sizeof (*codemap[12].instances) * GROUP_0x0D_LEN);
        codemap[12].instances[0] = new_opcode_t(0b1101000011000000, 0b1111000011000000, "ADDA", ADDA);
        codemap[12].instances[1] = new_opcode_t(0b1101000100000000, 0b1111000100110000, "ADDX", ADDX);
        codemap[12].instances[2] = new_opcode_t(0b1101000000000000, 0b1111000000000000, "ADD",  ADD);


        // GROUP 0x0E
        codemap[13].key  = 0x0E;
        codemap[13].size = GROUP_0x0E_LEN;
        codemap[13].instances     = malloc(sizeof (*codemap[13].instances) * GROUP_0x0E_LEN);
        codemap[13].instances[0]  = new_opcode_t(0b1110000011000000, 0b1111111111000000, "ASR",  ASR);
        codemap[13].instances[1]  = new_opcode_t(0b1110000111000000, 0b1111111111000000, "ASL",  ASL);
        codemap[13].instances[2]  = new_opcode_t(0b1110001011000000, 0b1111111111000000, "LSR",  LSR);
        codemap[13].instances[3]  = new_opcode_t(0b1110001111000000, 0b1111111111000000, "LSL",  LSL);
        codemap[13].instances[4]  = new_opcode_t(0b1110010011000000, 0b1111111111000000, "ROXR", ROXR);
        codemap[13].instances[5]  = new_opcode_t(0b1110010111000000, 0b1111111111000000, "ROXL", ROXL);
        codemap[13].instances[6]  = new_opcode_t(0b1110011011000000, 0b1111111111000000, "ROR",  ROR);
        codemap[13].instances[7]  = new_opcode_t(0b1110011111000000, 0b1111111111000000, "ROL",  ROL);
        codemap[13].instances[8]  = new_opcode_t(0b1110000000000000, 0b1111000100011000, "ASR",  ASR);
        codemap[13].instances[9]  = new_opcode_t(0b1110000100000000, 0b1111000100011000, "ASL",  ASL);
        codemap[13].instances[10] = new_opcode_t(0b1110000000001000, 0b1111000100011000, "LSR",  LSR);
        codemap[13].instances[11] = new_opcode_t(0b1110000100001000, 0b1111000100011000, "LSL",  LSL);
        codemap[13].instances[12] = new_opcode_t(0b1110000000010000, 0b1111000100011000, "ROXR", ROXR);
        codemap[13].instances[13] = new_opcode_t(0b1110000100010000, 0b1111000100011000, "ROXL", ROXL);
        codemap[13].instances[14] = new_opcode_t(0b1110000000011000, 0b1111000100011000, "ROR",  ROR);
        codemap[13].instances[15] = new_opcode_t(0b1110000100011000, 0b1111000100011000, "ROL",  ROL);

    }
}


void destroy_codes()
{
    if (codemap)
    {
        unsigned char outer = 0, inner = 0;

        for (outer = 0; outer < INSTRUCTION_SET_GROUPS_COUNT; outer++)
        {
            opcodes_ds *reference = &codemap[outer];

            if (reference)
            {
                if (reference->instances)
                {
                    for (inner = 0; inner < reference->size; inner++)
                    {
                        if (reference->instances[inner]) free(reference->instances[inner]);
                    }

                    free(reference->instances);
                }

            }

        }

        free(codemap);
    }

}


/*
 * FINDER
 *
 */
opcode_t* get_opcode_t(opcode code)
{
    opgroup code_group_id = (opgroup)((code & 0xF000) >> 12);

    if (code_group_id < 0x0F && code_group_id != 0x0A)
    {
        opcodes_ds *tmp = NULL;

        if (code_group_id > 0x09)
            tmp = &codemap[code_group_id - 0x01];
        else
            tmp = &codemap[code_group_id];

        if (tmp->key == code_group_id) // redundant
            for (unsigned char iter = 0; iter < tmp->size; iter++)
                if ((code & tmp->instances[iter]->mask) == tmp->instances[iter]->code)
                    return tmp->instances[iter];

    }

    return NULL;
}


/*
 * RUNNER
 *
 */

generic_u32_t run_opcode(opcode code, bit describe_code)
{
    opcode_t *tmp = get_opcode_t(code);

    if (tmp == NULL) { PANIC("[PANIC] Instruction code 0x%X not reconized\n", code); }

    if (describe_code)
    {
        printf("\033[01m\033[37mCode\033[0m: 0x%X, \033[01m\033[37mmnemonic\033[0m: %s\n", code, tmp->mnemonic);
        fflush(stdout);
    }

    generic_u32_t res = tmp->handler(code);

    incr_pc(WORD_SPAN);

    return res;
}



void set_srflags(const generic_u32_t mnemonic, opsize size, generic_u32_t src, generic_u32_t dst, generic_u32_t res)
{
    generic_u32_t msb  = most_significant_byte(size);
    generic_u32_t mask = mask_by_opsize(size);
    bit srcMSB = (src & msb) != 0;
    bit dstMSB = (dst & msb) != 0;
    bit resMSB = (res & msb) != 0;

    switch (mnemonic)
    {
        case ori:
        case andi:
        case eori:
        case move:
        case moveq:
        case divu:
        case divs:
        case or:
        case eor:
        case mulu:
        case muls:
        case and:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_overflow(0);
            set_carry(0);
            break;
        case subi:
        case subq:
        case sub:
        case subx:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_overflow((srcMSB == resMSB) && (dstMSB != resMSB));
            set_carry((srcMSB && resMSB) || (srcMSB && !dstMSB) || (!dstMSB && resMSB));
            set_extended(get_carry());
            break;
        case addi:
        case addq:
        case add:
        case addx:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_overflow((srcMSB == dstMSB) && (srcMSB != resMSB));
            set_carry((srcMSB && !resMSB) || (srcMSB && dstMSB) || (dstMSB && !resMSB));
            set_extended(get_carry());
            break;
        case cmpi:
        case cmpm:
        case cmp:
        case cmpa:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_overflow((srcMSB == resMSB) && (dstMSB != resMSB));
            set_carry((srcMSB && resMSB) || (srcMSB && !dstMSB) || (!dstMSB && resMSB));
            break;
        case negx:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_overflow(srcMSB && resMSB);
            set_carry(srcMSB || resMSB);
            set_extended(get_carry());
            break;
        case neg:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_overflow(srcMSB && resMSB);
            set_carry((res & mask) != 0);
            set_extended(get_carry());
            break;
        case not:
        case ext:
        case swap:
        case tst:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_carry(0);
            set_extended(get_carry());
            break;
        case asl:
        case asr:
        case lsl:
        case lsr:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            if (src != 0)
            {
                set_carry(dst != 0);
                set_extended(get_carry());
            }
            else set_carry(0);
            break;
        case rol:
        case ror:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            set_carry(src != 0 && dst != 0);
            set_overflow(0);
            break;
        case roxl:
        case roxr:
            set_negative(resMSB);
            set_zero((res & mask) == 0);
            if (src != 0)
            {
                set_carry(dst != 0);
                set_extended(get_carry());
            }
            else set_carry(0);

            set_overflow(0);
            break;
        case clr:
            set_negative(0);
            set_overflow(0);
            set_carry(0);
            set_zero(1);
        default:
            break;

    }

}



/*
 *
 * OPS IMPL
 *
 */

// GROUP 0x00
generic_u32_t ORItoCCR(opcode code)
{
    generic_u32_t addr = (generic_u32_t) (get_pc() + WORD_SPAN);
    generic_u8_t bits  = read_byte(addr);
    srflags flags      = get_sr();

    set_sr(flags | bits);

    incr_pc(BYTE_SPAN);

    return (RETURN_OK);
}


generic_u32_t ORItoSR(opcode code)
{
    generic_u32_t addr = (generic_u32_t) (get_pc() + WORD_SPAN);
    generic_u16_t bits = read_word(addr);
    srflags flags      = get_sr();

    set_sr(flags | bits);

    incr_pc(BYTE_SPAN);

    return (RETURN_OK);
}


generic_u32_t ORI(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    ea_direction dummy_dir = NORMAL;

    generic_u32_t value    = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_u32_t addr     = get_pc() + WORD_SPAN;
    generic_u32_t ori_mask = read_ram(&addr, &size);

    value |= ori_mask;

    write_EA(&dst, value, &size, &mode);
    set_srflags(ori, size, 0, 0, value);

    incr_pc(size_to_span(size));

    return (RETURN_OK);
}


generic_u32_t ANDItoCCR(opcode code)
{
    generic_u32_t addr = (generic_u32_t) (get_pc() + WORD_SPAN);
    generic_u16_t bits = (generic_u16_t) (read_byte(addr) & 0x001F) | 0xFFE0;
    srflags flags      = get_sr();

    set_sr(flags & bits);

    incr_pc(BYTE_SPAN);

    return (RETURN_OK);
}


generic_u32_t ANDItoSR(opcode code)
{
    generic_u32_t addr = (generic_u32_t) (get_pc() + WORD_SPAN);
    generic_u16_t bits = read_word(addr);
    srflags flags      = get_sr();

    set_sr(flags | bits);

    incr_pc(BYTE_SPAN);

    return (RETURN_OK);
}


generic_u32_t ANDI(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    ea_direction dummy_dir = NORMAL;

    generic_u32_t value     = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_u32_t addr      = get_pc() + WORD_SPAN;
    generic_u32_t andi_mask = read_ram(&addr, &size);


    switch (size) {
        case BYTE:
            andi_mask |= 0xFFFFFF00;
            break;
        case WORD:
            andi_mask |= 0xFFFF0000;
            break;
        default:
            break;
    }

    value |= andi_mask;

    write_EA(&dst, value, &size, &mode);
    set_srflags(andi, size, 0, 0, value);

    incr_pc(size_to_span(size));

    return (RETURN_OK);
}


generic_u32_t SUBI(opcode code)
{
    bitmask op   = 0b1001000000111100,
           dst  = 0b0000000000000111,
           size = 0b0000000011000000,
           cdir = 0b0000000000111000,
           dir;

    bitmask set_dst  = (code & dst) << 9,
           set_size = code & size;

    if (((code & cdir) >> 3) == 0)
        dir = 0b0000000000000000;
    else
        dir = 0b0000000100000000;

    code = 0b0000000000000000;
    code |= op;
    code |= set_dst;
    code |= dir;
    code |= set_size;

    return SUB(code);
}


generic_u32_t ADDI(opcode code)
{
    bitmask op   = 0b1101000000000000,
           dst  = 0b0000000000000111,
           size = 0b0000000011000000,
           cdir = 0b0000000000111000,
           dir;

    bitmask set_dst  = (code & dst) << 9,
           set_size = code & size;

    if (((code & cdir) >> 3) == 0)
        dir = 0b0000000000000000;
    else
        dir = 0b0000000100000000;

    code = 0b0000000000111100;
    code |= op;
    code |= set_dst;
    code |= dir;
    code |= set_size;

    return ADD(code);
}


generic_u32_t EORItoCCR(opcode code)
{
    generic_u32_t addr = (generic_u32_t) (get_pc() + WORD_SPAN);
    generic_u16_t bits = (generic_u16_t) (read_byte(addr) & 0x001F) | 0xFFE0;
    srflags flags      = get_sr();

    set_sr(flags ^ bits);

    incr_pc(BYTE_SPAN);

    return (RETURN_OK);
}


generic_u32_t EORItoSR(opcode code)
{
    generic_u32_t addr = (generic_u32_t) (get_pc() + WORD_SPAN);
    generic_u16_t bits = read_word(addr);
    srflags flags      = get_sr();

    set_sr(flags ^ bits);

    incr_pc(BYTE_SPAN);

    return (RETURN_OK);
}


generic_u32_t EORI(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    ea_direction dummy_dir = NORMAL;

    generic_u32_t value     = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_u32_t addr      = get_pc() + WORD_SPAN;
    generic_u32_t eori_mask = read_ram(&addr, &size);

    value ^= eori_mask;

    write_EA(&dst, value, &size, &mode);
    set_srflags(eori, size, 0, 0, value);

    incr_pc(size_to_span(size));

    return (RETURN_OK);
}


generic_u32_t CMPI(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    printf("size: %d\n", size);

    ea_direction dummy_dir = NORMAL;

    generic_u32_t dst_val = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_u32_t addr    = get_pc() + WORD_SPAN;
    generic_u32_t ram_val = read_ram(&addr, &size);

    generic_u32_t value = dst_val - ram_val;

    write_EA(&dst, value, &size, &mode);
    set_srflags(cmpi, size, ram_val, dst_val, value);

    incr_pc(size_to_span(size));

    return (RETURN_OK);
}


generic_u32_t MOVEP(opcode code)
{
    return 0;
}


generic_u32_t BTST(opcode code)
{
    return 0;
}


generic_u32_t BCHG(opcode code)
{
    return 0;
}


generic_u32_t BCLR(opcode code)
{
    return 0;
}


generic_u32_t BSET(opcode code)
{
    return 0;
}




// GROUP 0x01
generic_u32_t MOVE(opcode code)
{
    generic_u32_t dst_reg,  src_reg;
    generic_u32_t dst_mode, src_mode;
    generic_u32_t rVal;
    opsize size;

    dst_reg  = (code & DST_MASK) >> 9;
    dst_mode = (code & 0b0000000111000000) >> 6;
    size     = (code & 0b0011000000000000) >> 12;

    if (size == WORD2)      size = WORD;
    else if (size == BYTE2) size = BYTE;

    if ((code & ADDRMODE_MASK) == IMMEDIATE) // move.l #<val>,Rd
    {
        opsize tmpsize = size;
        if (tmpsize == BYTE) tmpsize = WORD; //byte can't be wrote in ram

        generic_u32_t ram_ptr = get_pc() + WORD_SPAN;
        rVal = read_ram(&ram_ptr, &tmpsize);

        write_EA(&dst_reg, rVal, &tmpsize, &dst_mode);

        set_srflags(move, size, 0, 0, rVal);

        incr_pc(size_to_span(tmpsize));
    }
    else                                    // everything else
    {
        src_reg  = (code & SRC_MASK);
        src_mode = (code & 0b0000000000111000) >> 3; //src_mode

        ea_direction direction = NORMAL;    // forced to use it

        rVal = read_EA(&src_reg, &size, &src_mode, &direction);

        if (src_mode == ADDRESSPostIncr) incr_addr_reg(src_reg, size);
        if (dst_mode == ADDRESSPreDecr)  decr_addr_reg(dst_reg, size);

        write_EA(&dst_reg, rVal, &size, &dst_mode);

        if (dst_mode == ADDRESSPostIncr) incr_addr_reg(dst_reg, size);

        set_srflags(move, size, 0, 0, rVal);
    }

    return (RETURN_OK);
}




// GROUP 0x02-0x03
generic_u32_t MOVEA(opcode code)
{
    /* hack:
         call 'move' with dst_mode as 001 aka ADDRReg.
         for sure this code will go into the 'move' proc's else branch
    */

    return MOVE(code);
}




// group 0X04
generic_u32_t MOVEfromSR(opcode code)
{
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;

    generic_u32_t dst  = (generic_u32_t) (code & dst_mask);
    ADDRMode      mode = (code & mode_mask) >> 3;

    srflags flags = get_sr();
    opsize  size  = WORD;

    write_EA(&dst, flags, &size, &mode);

    return (RETURN_OK);
}


generic_u32_t MOVEtoCCR(opcode code)
{
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;

    generic_u32_t src  = (generic_u32_t) (code & dst_mask);
    ADDRMode      mode = (code & mode_mask) >> 3;

    srflags flags = get_sr();

    switch (mode) {
        case DATAReg:
            flags = (srflags) (read_datareg(src) | 0xFFE0);
            break;
        default:
            break;
    }

    set_sr(flags);

    return (RETURN_OK);
}


generic_u32_t MOVEtoSR(opcode code)
{
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;

    generic_u32_t src  = (generic_u32_t) (code & dst_mask);
    ADDRMode      mode = (code & mode_mask) >> 3;

    srflags flags = get_sr();

    switch (mode) {
        case DATAReg:
            flags = read_datareg(src);
            break;
        default:
            break;
    }

    set_sr(flags);

    return (RETURN_OK);
}


generic_u32_t NEGX(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    ea_direction dummy_dir = NORMAL;

    generic_u32_t src_value = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_32_t  signValue = sign_extended(src_value, size);
    generic_32_t     result = 0 - (signValue + (get_extended() ? 1 : 0));

    write_EA(&dst, (generic_u32_t) result, &size, &mode);

    set_srflags(negx, size, src_value, 0, (generic_u32_t) result);

    return (RETURN_OK);
}


generic_u32_t CLR(opcode code)
{
    generic_u32_t reg  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;
    ea_direction direc = NORMAL;

    generic_u32_t value = read_EA(&reg, &size, &mode, &direc);

    switch (size) {
        case BYTE:
            value = value & 0xFFFFFF00;
            break;
        case WORD:
            value = value & 0xFFFF0000;
            break;
        case LONG:
            value = 0x00000000;
            break;
        default:
            break;
    }

    write_EA(&reg, value, &size, &mode);

    set_srflags(clr, size, 0, 0, 0);

    return (RETURN_OK);
}


generic_u32_t NEG(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    ea_direction dummy_dir = NORMAL;

    generic_u32_t src_value = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_32_t  signValue = sign_extended(src_value, size);
    generic_32_t     result = 0 - signValue;

    write_EA(&dst, (generic_u32_t) result, &size, &mode);

    set_srflags(neg, size, src_value, 0, (generic_u32_t) result);

    return (RETURN_OK);
}


generic_u32_t NOT(opcode code)
{
    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    ea_direction dummy_dir = NORMAL;

    generic_u32_t src_value = read_EA(&dst, &size, &mode, &dummy_dir);
    generic_32_t  signValue = sign_extended(src_value, size);
    generic_32_t     result = ~signValue;

    write_EA(&dst, (generic_u32_t) result, &size, &mode);

    set_srflags(not, size, src_value, 0, (generic_u32_t) result);

    return (RETURN_OK);
}


generic_u32_t EXT(opcode code)
{
    return 0;
}


generic_u32_t NBCD(opcode code)
{
    return 0;
}


generic_u32_t SWAP(opcode code)
{
    bitmask reg_mask = 0b0000000000000111;

    generic_u32_t val = read_datareg(code & reg_mask);
    val = (val >> 16) | ((val & 0x0000FFFF) << 16);

    write_datareg(code & reg_mask, val, NULL);
    set_srflags(swap, LONG, 0, 0, val);

    return (RETURN_OK);
}


generic_u32_t PEA(opcode code)
{
    ADDRMode mode = (code & 0b0000000000111000) >> 3;

    if (mode == ADDRESS || mode == ADDRESSDisp)
    {
        generic_u32_t addr_reg = (code & SRC_MASK);
        opsize            size = LONG;
        ea_direction direction = NORMAL;

        generic_u32_t value = read_EA(&addr_reg, &size, &mode, &direction);

        push_long(value);
    }

    return 0;
}


generic_u32_t ILLEGAL(opcode code)
{
    PANIC("[TRAP] Executed trap exception, code: %d, mnemonic: %s\n", IllegalInstruction, trap_code_toString(IllegalInstruction));
    return 0;
}


generic_u32_t TAS(opcode code)
{
    return 0;
}


generic_u32_t TST(opcode code)
{
    bitmask dst_mask  = 0b0000000000000111;
    bitmask mode_mask = 0b0000000000111000;
    bitmask size_mask = 0b0000000011000000;

    opsize        size = (opsize) (code & size_mask);
    ADDRMode      mode = (code & mode_mask) >> 3;
    generic_u32_t src  = (generic_u32_t) (code & dst_mask);

    generic_u32_t val;

    switch (mode) {
        case DATAReg:
            val = read_datareg(src);
            break;
        case ADDRESSPostIncr:
            val = read_datareg(src);
            incr_addr_reg(src, size);
            break;
        case ADDRESSPreDecr:
            decr_addr_reg(src, size);
            val = read_datareg(src);
            break;
        default:
            return (RETURN_ERR);
    }

    set_srflags(tst, size, 0, 0, val);

    return (RETURN_OK);
}


generic_u32_t TRAP(opcode code)
{
    generic_u16_t vector = code & 0x000F;

    PANIC("[TRAP] Raised trap exception: code %d, mnemonic: %s\n", 0x20 + vector, trap_code_toString(0x20 + vector));

    return (RETURN_ERR);
}


generic_u32_t LINK(opcode code)
{
    bitmask reg_mask   = 0b0000000000000111;

    generic_u32_t reg = code & reg_mask;
    generic_16_t  val  = sign_extended(read_word(get_pc() + WORD_SPAN), WORD);
    generic_u32_t rVal = read_addrreg(reg);

    push_long(rVal);

    generic_u32_t sp = get_stack_ptr();

    write_addrreg(reg, sp, NULL);

    write_addrreg(7, (generic_u32_t)((generic_32_t) sp + val), NULL);

    incr_pc(WORD_SPAN); // 2B for word read

    return (RETURN_OK);
}


generic_u32_t UNLK(opcode code)
{
    bitmask reg_mask   = 0b0000000000000111;
    generic_u32_t reg = code & reg_mask;

    write_addrreg(7,   read_addrreg(reg), NULL);
    write_addrreg(reg, pop_long(), NULL);

    return (RETURN_OK);
}


generic_u32_t MOVEUSP(opcode code)
{
    if (!get_supervisor())
    {
        PANIC("[TRAP] Executed trap exception, code: %d, mnemonic: %s\n", PrivilegeViolation, trap_code_toString(PrivilegeViolation));
    }

    generic_u32_t addr_reg  = (code & SRC_MASK);
    generic_u32_t direction = (code & 0b00000000000001000) >> 3;


    if (direction == MEMORY_REGISTER)
    {
        set_usp(read_addrreg(addr_reg));
    }
    else
    {
        write_addrreg(addr_reg, get_usp(), NULL);
    }


    return (RETURN_OK);
}


generic_u32_t RESET(opcode code)
{
    // ??
    return (RETURN_OK);
}


generic_u32_t NOP(opcode code)
{
    return (RETURN_OK);
}


generic_u32_t STOP(opcode code)
{
    // ??
    return (RETURN_OK);
}


generic_u32_t RTE(opcode code)
{
    return 0;
}


generic_u32_t RTS(opcode code)
{
    return 0;
}


generic_u32_t TRAPV(opcode code)
{
    if (get_overflow())
    {
        PANIC("[TRAP] Executed trap exception, code: %d, mnemonic: %s\n", TRAPVInstruction, trap_code_toString(TRAPVInstruction));
    }

    return (RETURN_OK);
}


generic_u32_t RTR(opcode code)
{
    return 0;
}


generic_u32_t JSR(opcode code)
{
    return 0;
}


generic_u32_t JMP(opcode code)
{
    ADDRMode      mode     = (code & ADDRMODE_MASK);
    generic_u32_t addr_reg = (code & SRC_MASK);

    generic_u32_t jmp_addr;

    if (mode == ABSLong)
    {
        generic_u32_t ram_ptr = get_pc() + WORD_SPAN;
        opsize size = LONG;
        jmp_addr = read_ram(&ram_ptr, &size);
        incr_pc(LONG_SPAN);
    }
    else if (mode == ADDRESS)
    {
        generic_u32_t ram_ptr = read_addrreg(addr_reg);
        opsize size = LONG;
        jmp_addr = read_ram(&ram_ptr, &size);
    }
    else
    {
        PANIC("[PANIC] Unmenaged mode\n");
    }

    set_pc(jmp_addr - WORD_SPAN); //prevent pc incr

    return (RETURN_OK);
}


generic_u32_t MOVEM(opcode code)
{
    // wtf is this?? maybe later

    return (RETURN_OK);
}


generic_u32_t CHK(opcode code)
{
    generic_u32_t addr_reg = (code & SRC_MASK);
    generic_u32_t data_reg = (code & DST_MASK) >> 9;
    opsize            size = WORD;
    ADDRMode          mode = (code & 0b0000000000111000) >> 3;

    ea_direction dummy = NORMAL;
    generic_u32_t value = read_EA(&addr_reg, &size, &mode, &dummy);
    generic_u32_t dVal  = read_datareg(data_reg);

    generic_32_t signVALUE, signDVAL;
    signVALUE = sign_extended(value, size);
    signDVAL = sign_extended(dVal, size);

    if (signDVAL < 0 || signDVAL > signVALUE)
    {
        (signDVAL < 0)         ? set_negative(1) : set_negative(get_negative());
        (signDVAL > signVALUE) ? set_negative(0) : set_negative(get_negative());

        PANIC("[TRAP] Executed trap exception, code: %d, mnemonic: %s\n", CHKInstruction, trap_code_toString(CHKInstruction));
    }


    return (RETURN_OK);
}


generic_u32_t LEA(opcode code)
{
    generic_u8_t mode     = (code & ADDRMODE_MASK) & 0xFF00;
    generic_u8_t addr_reg = (code & DST_MASK)      >> 9;

    if (mode == ABSLong)
    {
        generic_u32_t label = read_long(get_pc() + WORD_SPAN);

        write_addrreg(addr_reg, label, NULL);
    }
    else
    {
        PANIC("Unmenaged mode 0x%X\n", mode);
    }

    incr_pc(LONG_SPAN); // memory readF

    return (RETURN_OK);
}




// GROUP 0x05
generic_u32_t DBcc(opcode code)
{
    return 0;
}


generic_u32_t Scc(opcode code)
{
    return 0;
}


generic_u32_t ADDQ(opcode code)
{
    generic_u32_t value = (code & DST_MASK) >> 9;

    if (value == 0) value = 8;

    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    if (mode == ADDRReg) // no effect on flags
    {
        generic_u32_t reg_val     = read_addrreg(dst);
        generic_u32_t sign_regval = sign_extended(reg_val, LONG);
        generic_u32_t result      = (generic_u32_t)(sign_regval + value);

        write_addrreg(dst, result, NULL);
        return (RETURN_OK);
    }


    ea_direction dir = NORMAL;
    generic_u32_t reg_content = read_EA(&dst, &size, &mode, &dir);
    generic_u32_t sign_regval = sign_extended(reg_content, LONG);
    generic_u32_t result      = (generic_u32_t)(sign_regval + value);

    write_EA(&dst, result, &size, &mode);
    set_srflags(addq, size, reg_content, 0, result);

    return (RETURN_OK);
}


generic_u32_t SUBQ(opcode code)
{
    generic_u32_t value = (code & DST_MASK) >> 9;

    if (value == 0) value = 8;

    generic_u32_t dst  = (code & SRC_MASK);
    generic_u32_t mode = (code & 0b0000000000111000) >> 3;
    opsize        size = (code & SIZE_MASK) >> 6;

    if (mode == ADDRReg) // no effect on flags
    {
        generic_u32_t reg_val     = read_addrreg(dst);
        generic_u32_t sign_regval = sign_extended(reg_val, LONG);
        generic_u32_t result      = (generic_u32_t)(sign_regval - value);

        write_addrreg(dst, result, NULL);
        return (RETURN_OK);
    }


    ea_direction dir = NORMAL;
    generic_u32_t reg_content = read_EA(&dst, &size, &mode, &dir);
    generic_u32_t sign_regval = sign_extended(reg_content, LONG);
    generic_u32_t result      = (generic_u32_t)(sign_regval - value);

    write_EA(&dst, result, &size, &mode);
    set_srflags(addq, size, reg_content, 0, result);

    return (RETURN_OK);
}




// GROUP 0x06
generic_u32_t BRA(opcode code)
{
    generic_u32_t pc   = get_pc();
    generic_32_t  disp = (code & 0x00FF);

    if (disp == 0)
    {
        generic_u32_t ram_ptr = pc + WORD_SPAN;
        opsize        dummy   = WORD;

        disp = sign_extended(read_ram(&ram_ptr, &dummy), WORD);
        pc -= 2;
    }
    else
        disp = sign_extended((generic_u32_t) disp, WORD);

    set_pc((generic_u32_t)(pc + disp));

    return (RETURN_OK);
}


generic_u32_t BSR(opcode code)
{
    return 0;
}


generic_u32_t Bcc(opcode code)
{
    CCm condition = (code & 0x0F00) >> 8;

    if (eval_cc(condition))
    {
        generic_u32_t pc   = get_pc();
        generic_32_t  disp = (code & 0x00FF);

        if (disp == 0)
        {
            generic_u32_t ramptr = get_pc() + WORD_SPAN;
            opsize        size   = WORD;
            disp = sign_extended(read_ram(&ramptr, &size), WORD);
        }
        else
        {
            disp = sign_extended(disp, WORD);
        }

        set_pc(pc + disp);
    }
    else
    {
        incr_pc(WORD_SPAN);
    }

    return (RETURN_OK);
}




// GROUP 0x07
generic_u32_t MOVEQ(opcode code)
{
    generic_u32_t dst = (code & DST_MASK) >> 9;
    generic_32_t  val = sign_extended((code & 0b0000000011111111), LONG);

    write_datareg(dst, val, NULL);

    set_srflags(moveq, LONG, 0, 0, (generic_u32_t) val);

    return 0;
}




// GROUP 0x08
generic_u32_t DIVU(opcode code)
{
    generic_u32_t _val;

    void **a = eval_OP_EA(code, IGNORE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    // opsize   *size      = (opsize *)        a[4];
    // ea_direction *direction = (ea_direction *)  a[5];

    if (*sVal == 0) { PANIC("[PANIC! (DIVU)], Division by zero\n") }

    opsize size = WORD;

    _val = (generic_u32_t) *dVal / *sVal;

    should_incr_pc(&size, mode);

    if (_val > 0xFFFF)
    {
        set_overflow(1);
        return (RETURN_ERR);
    }

    int remainder = (int)(*dVal % *sVal) & 0xFFFF;

    write_datareg(*dst, remainder, NULL);
    write_datareg(*dst, _val,      &size);

    set_srflags(divu, LONG, 0, 0, _val);

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}


generic_u32_t DIVS(opcode code)
{
    generic_32_t _val, signed_sVal, signed_dVal;

    void **a = eval_OP_EA(code, IGNORE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    // opsize   *size      = (opsize *)        a[4];
    // ea_direction *direction = (ea_direction *)  a[5];

    opsize size = WORD;

    signed_dVal = sign_extended(*dVal, WORD);
    signed_sVal = sign_extended(*sVal, WORD);

    if (signed_sVal == 0) { PANIC("[PANIC! (DIVS)], Division by zero\n") }


    _val = (generic_32_t) signed_dVal / signed_sVal;

    should_incr_pc(&size, mode);

    if (_val < -32768 || _val > 32767)
    {
        set_overflow(1);
        return (RETURN_ERR);
    }
    int remainder = (int)(signed_dVal % signed_sVal) & 0xFFFF;

    write_datareg(*dst, remainder, NULL);
    write_datareg(*dst, _val,      &size);

    set_srflags(divs, LONG, 0, 0, _val);

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}


generic_u32_t SBCD(opcode code)
{
    return 0;
}


generic_u32_t OR(opcode code)
{
    generic_u32_t _val;

    void **a = eval_OP_EA(code, USE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode      *mode = (ADDRMode *)      a[3];
    opsize        *size = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    _val = *dVal | *sVal;

    if (*direction == 0)
    {
        write_datareg(*dst, _val, size);
    }
    else
    {
        write_EA(dst, _val, size, mode);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(*dst, *size);
    }

    set_srflags(or, *size, 0, 0, _val);

    should_incr_pc(size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}




// GROUP 0x09
generic_u32_t SUBA(opcode code)
{
    generic_u32_t  dst_reg = (code & DST_MASK) >> 9;
    generic_u32_t  src_reg = (code & SRC_MASK);
    ADDRMode       mode    = (code & 0b0000000000111000) >> 3;
    opsize         size;

    if (((code & 0b0000000100000000) >> 8) == 1)
        size = LONG;
    else
        size = WORD;

    ea_direction dummy_dir = NORMAL;
    generic_u32_t src_val = read_EA(&src_reg, &size, &mode, &dummy_dir);
    generic_u32_t dst_val = read_addrreg(dst_reg);

    if (mode == ADDRESSPostIncr) incr_addr_reg(src_reg, size);

    generic_32_t signSRC = sign_extended(src_val, size);

    generic_u32_t result  = (generic_u32_t)(dst_val - signSRC);
    write_addrreg(dst_reg, result, NULL);


    return (RETURN_OK);
}


generic_u32_t SUBX(opcode code)
{
    generic_u32_t  dst_reg = (code & DST_MASK) >> 9;
    generic_u32_t  src_reg = (code & SRC_MASK);
    opsize         size    = (code & SIZE_MASK) >> 6;
    direction_mode drmode  = (code & 0b0000000000001000) >> 3;

    generic_32_t signSRC, signDST, result;
    switch (drmode) {
        case DATAREG:
            signDST = sign_extended(read_datareg(dst_reg), size);
            signSRC = sign_extended(read_datareg(src_reg), size);
            result  = signDST - signSRC - (get_extended() ? 1 : 0);
            set_srflags(addx, size, (generic_u32_t) signSRC, (generic_u32_t) signDST, (generic_u32_t) result);
            break;

        case MEMORYPD:
            decr_addr_reg(dst_reg, size);
            decr_addr_reg(src_reg, size);

            signDST = sign_extended(read_ram(&dst_reg, &size), size);
            signSRC = sign_extended(read_ram(&src_reg, &size), size);
            result  = signDST - signSRC - (get_extended() ? 1 : 0);

            ADDRMode local_mode = ADDRESSPreDecr;
            write_EA(&dst_reg, (generic_u32_t) result, &size, &local_mode);
            set_srflags(addx, size, (generic_u32_t) signSRC, (generic_u32_t) signDST, (generic_u32_t) result);
            break;
    }

    return (RETURN_OK);
}


generic_u32_t SUB(opcode code)
{
    generic_32_t _val, signed_sVal, signed_dVal;

    void **a = eval_OP_EA(code, USE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    opsize   *size      = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    signed_sVal = sign_extended(*sVal, *size);
    signed_dVal = sign_extended(*dVal, *size);

    _val  = (*direction) ? signed_sVal - signed_dVal : signed_dVal - signed_sVal;

    if (!(*direction))
    {
        write_datareg(*dst, (generic_u32_t)_val, size);
        set_srflags(sub, *size, *sVal, *dVal, (generic_u32_t)_val);
    }
    else
    {
        write_EA(dst, (generic_u32_t)_val, size, mode);
        set_srflags(sub, *size, *dVal, *sVal, (generic_u32_t)_val);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(*dst, *size);
    }

    should_incr_pc(size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}




// GROUP 0x0B
generic_u32_t CMPA(opcode code)
{
    generic_u32_t  dst_reg = (code & DST_MASK) >> 9;
    generic_u32_t  src_reg = (code & SRC_MASK);

    ADDRMode       mode    = (code & ADDRMODE_MASK);
    opsize         size;

    if (((code & 0b0000000100000000) >> 8) == 1)
        size = LONG;
    else
        size = WORD;

    generic_32_t signSRC;

    if (mode == IMMEDIATE)
    {
        generic_u32_t ram_ptr = get_pc() + WORD_SPAN;
        generic_u32_t imm_val = read_ram(&ram_ptr, &size);
        signSRC = sign_extended(imm_val, size);

        incr_pc(size_to_span(size));
    }
    else
    {
        mode = (code & 0b0000000000111000) >> 3;
        ea_direction dummy_dir = NORMAL;
        generic_u32_t src_val = read_EA(&src_reg, &size, &mode, &dummy_dir);
        signSRC = sign_extended(src_val, size);

        if (mode == ADDRESSPostIncr) incr_addr_reg(src_reg, size);
    }

    generic_u32_t dst_val = read_addrreg(dst_reg);

    generic_u32_t result  = (generic_u32_t)(dst_val - signSRC);

    set_srflags(cmpa, size, (generic_u32_t) signSRC, dst_val, result);

    return (RETURN_OK);
}


generic_u32_t CMPM(opcode code)
{
    generic_u32_t dst_addr_reg = (code & DST_MASK) >> 9;
    generic_u32_t src_addr_reg = (code & SRC_MASK);
    opsize                size = (code & SIZE_MASK) >> 6;

    generic_u32_t ram_ptr;

    ram_ptr = read_datareg(dst_addr_reg);
    generic_u32_t DST = read_ram(&ram_ptr, &size);

    ram_ptr = read_datareg(src_addr_reg);
    generic_u32_t SRC = read_ram(&ram_ptr, &size);

    generic_32_t signDST, signSRC;

    signDST = sign_extended(DST, size);
    signSRC = sign_extended(SRC, size);

    incr_addr_reg(dst_addr_reg, size);
    incr_addr_reg(src_addr_reg, size);

    generic_32_t result = signDST - signSRC;
    set_srflags(cmpm, size, SRC, DST, (generic_u32_t) result);

    return (RETURN_OK);
}


generic_u32_t EOR(opcode code)
{
    generic_u32_t _val;

    void **a = eval_OP_EA(code, USE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode      *mode = (ADDRMode *)      a[3];
    opsize        *size = (opsize *)        a[4];
    //ea_direction *direction = (ea_direction *)  a[5];

    _val = *dVal ^ *sVal;

    write_EA(dst, _val, size, mode);

    if (*mode == ADDRESSPostIncr) incr_addr_reg(*dst, *size);

    set_srflags(or, *size, 0, 0, _val);

    should_incr_pc(size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}


generic_u32_t CMP(opcode code)
{
    generic_u32_t  dst_reg = (code & DST_MASK) >> 9;
    generic_u32_t  src_reg = (code & SRC_MASK);

    ADDRMode       mode    = (code & ADDRMODE_MASK);
    opsize         size    = (code & SIZE_MASK) >> 6;

    generic_32_t signSRC;

    if (mode == IMMEDIATE)
    {
        opsize tmpsize = size;
        if (tmpsize == BYTE) tmpsize = WORD; //byte can't be wrote in ram
        generic_u32_t ram_ptr = get_pc() + WORD_SPAN;
        generic_u32_t imm_val = read_ram(&ram_ptr, &tmpsize);
        signSRC = sign_extended(imm_val, tmpsize);

        incr_pc(size_to_span(tmpsize));
    }
    else
    {
        mode = (code & 0b0000000000111000) >> 3;
        ea_direction dummy_dir = NORMAL;
        generic_u32_t src_val = read_EA(&src_reg, &size, &mode, &dummy_dir);
        signSRC = sign_extended(src_val, size);

        if (mode == ADDRESSPostIncr) incr_addr_reg(src_reg, size);
    }

    generic_32_t signDST = sign_extended(read_datareg(dst_reg), size);

    generic_32_t result  = (signDST - signSRC);

    set_srflags(cmp, size, (generic_u32_t) signSRC, (generic_u32_t) signDST, (generic_u32_t) result);

    return (RETURN_OK);
}




// GROUP 0x0C
generic_u32_t MULU(opcode code)
{
    generic_u32_t _val;

    void **a = eval_OP_EA(code, IGNORE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    // opsize   *size      = (opsize *)        a[4];
    // ea_direction *direction = (ea_direction *)  a[5];

    opsize size = WORD;

    _val = *dVal * *sVal;

    write_datareg(*dst, (generic_u32_t)_val, &size);
    set_srflags(mulu, LONG, 0, 0, (generic_u32_t)_val);

    should_incr_pc(&size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}


generic_u32_t MULS(opcode code)
{
    generic_32_t _val, signed_sVal, signed_dVal;;

    void **a = eval_OP_EA(code, IGNORE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    // opsize   *size      = (opsize *)        a[4];
    // ea_direction *direction = (ea_direction *)  a[5];

    opsize size = WORD;

    signed_dVal = sign_extended(*dVal, WORD);
    signed_sVal = sign_extended(*sVal, WORD);

    _val = signed_dVal * signed_sVal;

    write_datareg(*dst, (generic_u32_t)_val, NULL);
    set_srflags(muls, LONG, 0, 0, (generic_u32_t)_val);

    should_incr_pc(&size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}


generic_u32_t ABCD(opcode code)
{
    return 0;
}


generic_u32_t EXG(opcode code)
{
    return 0;
}


generic_u32_t AND(opcode code)
{
    generic_u32_t _val;

    void **a = eval_OP_EA(code, USE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode      *mode = (ADDRMode *)      a[3];
    opsize        *size = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    _val = *dVal & *sVal;

    if (*direction == 0)
    {
        write_datareg(*dst, _val, size);
    }
    else
    {
        write_EA(dst, _val, size, mode);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(*dst, *size);
    }

    set_srflags(or, *size, 0, 0, _val);

    should_incr_pc(size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}




// GROUP 0x0D
generic_u32_t ADDA(opcode code)
{
    generic_u32_t  dst_reg = (code & DST_MASK) >> 9;
    generic_u32_t  src_reg = (code & SRC_MASK);
    ADDRMode       mode    = (code & 0b0000000000111000) >> 3;
    opsize         size;

    if (((code & 0b0000000100000000) >> 8) == 1)
        size = LONG;
    else
        size = WORD;

    ea_direction dummy_dir = NORMAL;
    generic_u32_t src_val = read_EA(&src_reg, &size, &mode, &dummy_dir);
    generic_u32_t dst_val = read_addrreg(dst_reg);

    if (mode == ADDRESSPostIncr) incr_addr_reg(src_reg, size);

    generic_32_t signSRC = sign_extended(src_val, size);

    generic_u32_t result  = (generic_u32_t)(dst_val + signSRC);
    write_addrreg(dst_reg, result, NULL);


    return (RETURN_OK);
}


generic_u32_t ADDX(opcode code)
{
    generic_u32_t  dst_reg = (code & DST_MASK) >> 9;
    generic_u32_t  src_reg = (code & SRC_MASK);
    opsize         size    = (code & SIZE_MASK) >> 6;
    direction_mode drmode  = (code & 0b0000000000001000) >> 3;

    generic_32_t signSRC, signDST, result;
    switch (drmode) {
        case DATAREG:
            signDST = sign_extended(read_datareg(dst_reg), size);
            signSRC = sign_extended(read_datareg(src_reg), size);
            result  = signDST + signSRC + (get_extended() ? 1 : 0);
            set_srflags(addx, size, (generic_u32_t) signSRC, (generic_u32_t) signDST, (generic_u32_t) result);
            break;

        case MEMORYPD:
            decr_addr_reg(dst_reg, size);
            decr_addr_reg(src_reg, size);

            signDST = sign_extended(read_ram(&dst_reg, &size), size);
            signSRC = sign_extended(read_ram(&src_reg, &size), size);
            result  = signDST + signSRC + (get_extended() ? 1 : 0);

            ADDRMode local_mode = ADDRESSPreDecr;
            write_EA(&dst_reg, (generic_u32_t) result, &size, &local_mode);
            set_srflags(addx, size, (generic_u32_t) signSRC, (generic_u32_t) signDST, (generic_u32_t) result);
            break;
    }

    return (RETURN_OK);
}


generic_u32_t ADD(opcode code)
{
    generic_32_t  _val, signed_sVal, signed_dVal;

    void **a = eval_OP_EA(code, USE_DIRECTION);

    generic_u32_t *dst  = (generic_u32_t *) a[0];
    generic_u32_t *sVal = (generic_u32_t *) a[1];
    generic_u32_t *dVal = (generic_u32_t *) a[2];
    ADDRMode *mode      = (ADDRMode *)      a[3];
    opsize   *size      = (opsize *)        a[4];
    ea_direction *direction = (ea_direction *)  a[5];

    signed_sVal = sign_extended(*sVal, *size);
    signed_dVal = sign_extended(*dVal, *size);

    _val  = signed_dVal + signed_sVal;

    if (*direction == NORMAL)
    {
        write_datareg(*dst, (generic_u32_t)_val, size);
        set_srflags(add, *size, *sVal, *dVal, (generic_u32_t)_val);
    }
    else
    {
        write_EA(dst, (generic_u32_t)_val, size, mode);
        set_srflags(add, *size, *dVal, *sVal, (generic_u32_t)_val);

        if (*mode == ADDRESSPostIncr) incr_addr_reg(*dst, *size);
    }

    should_incr_pc(size, mode); // for IMMEDIATE mode

    free_eval_OP_EA_array(a);

    return (RETURN_OK);
}




// GROUP 0x0E
generic_u32_t ASR(opcode code)
{
    return 0;
}


generic_u32_t ASL(opcode code)
{
    return 0;
}


generic_u32_t LSR(opcode code)
{
    return 0;
}


generic_u32_t LSL(opcode code)
{
    return 0;
}


generic_u32_t ROXR(opcode code)
{
    return 0;
}


generic_u32_t ROXL(opcode code)
{
    return 0;
}


generic_u32_t ROR(opcode code)
{
    return 0;
}


generic_u32_t ROL(opcode code)
{
    return 0;
}


