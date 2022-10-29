#ifndef __HANDLER_H__68000
#define __HANDLER_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "utils.h"
#include "cpu.h"
#include "ram.h"


void init_codes(struct EmulationMachine *em);
void destroy_codes();

void preset_hander(struct EmulationMachine *em);
u32 run_opcode(struct EmulationMachine *em);





/*
 * BEGIN DUMBS PROTOS
 *
 */
// GROUP 0x00
u32 ORItoCCR(opcode code);  //ok
u32 ORItoSR(opcode code);   //ok
u32 ORI(opcode code);       //ok
u32 ANDItoCCR(opcode code); //ok
u32 ANDItoSR(opcode code);  //ok
u32 ANDI(opcode code);      //ok
u32 SUBI(opcode code);      //ok
u32 ADDI(opcode code);      //ok
u32 EORItoCCR(opcode code); //ok
u32 EORItoSR(opcode code);  //ok
u32 EORI(opcode code);      //ok
u32 CMPI(opcode code);      //ok
u32 MOVEP(opcode code);     // maybe next -warn
u32 BTST(opcode code);      //ok
u32 BCHG(opcode code);      //ok
u32 BCLR(opcode code);      //ok
u32 BSET(opcode code);      //ok


// GROUP 0x01
u32 MOVE(opcode code);   //ok


// GROUP 0x02-0x03
u32 MOVEA(opcode code);  //ok


// group 0X04
u32 MOVEfromSR(opcode code); //ok
u32 MOVEtoCCR(opcode code);  //ok
u32 MOVEtoSR(opcode code);   //ok
u32 NEGX(opcode code);       //ok
u32 CLR(opcode code);        //ok
u32 NEG(opcode code);        //ok
u32 NOT(opcode code);        //ok
u32 EXT(opcode code);        //ok
u32 NBCD(opcode code);       //ok
u32 SWAP(opcode code);       //ok
u32 PEA(opcode code);        //ok
u32 ILLEGAL(opcode code);    //ok
u32 TAS(opcode code);        // ?? -warn
u32 TST(opcode code);        //ok
u32 TRAP(opcode code);       //ok
u32 LINK(opcode code);       //ok
u32 UNLK(opcode code);       //ok
u32 MOVEUSP(opcode code);    //ok
u32 RESET(opcode code);      // ?? -warn
u32 NOP(opcode code);        //ok
u32 STOP(opcode code);       // ?? -warn
u32 RTE(opcode code);        //ok
u32 RTS(opcode code);        //ok
u32 TRAPV(opcode code);      //ok
u32 RTR(opcode code);        //ok
u32 JSR(opcode code);        //ok
u32 JMP(opcode code);        //ok
u32 MOVEM(opcode code);      // wtf -warn
u32 CHK(opcode code);        // ok -warn
u32 LEA(opcode code);        //ok


// GROUP 0x05
u32 DBcc(opcode code);      //ok
u32 Scc(opcode code);       //ok
u32 ADDQ(opcode code);      //ok
u32 SUBQ(opcode code);      //ok


// GROUP 0x06
u32 BRA(opcode code);      //ok
u32 BSR(opcode code);      //ok
u32 Bcc(opcode code);      //ok


// GROUP 0x07
u32 MOVEQ(opcode code);     //ok


// GROUP 0x08
u32 DIVU(opcode code);   //ok
u32 DIVS(opcode code);   //ok
u32 SBCD(opcode code);   //ok
u32 OR(opcode code);     //ok


// GROUP 0x09
u32 SUBA(opcode code);  //ok
u32 SUBX(opcode code);  //ok
u32 SUB(opcode code);   //ok


// GROUP 0x0B
u32 CMPA(opcode code);  //ok
u32 CMPM(opcode code);  //ok
u32 EOR(opcode code);   //ok
u32 CMP(opcode code);   //ok


// GROUP 0x0C
u32 MULU(opcode code);  //ok
u32 MULS(opcode code);  //ok
u32 ABCD(opcode code);  //ok
u32 EXG(opcode code);   //ok
u32 AND(opcode code);   //ok


// GROUP 0x0D
u32 ADDA(opcode code);  //ok
u32 ADDX(opcode code);  //ok
u32 ADD(opcode code);   //ok


// GROUP 0x0E
u32 ASR(opcode code);   //ok
u32 ASL(opcode code);   //ok
u32 LSR(opcode code);   //ok
u32 LSL(opcode code);   //ok
u32 ROXR(opcode code);  //ok
u32 ROXL(opcode code);  //ok
u32 ROR(opcode code);   //ok
u32 ROL(opcode code);   //ok


//Bxxx
u32 Bxxx(opcode code);


//abcd-sbcd
u32 xBCD(opcode code, BCD_type type);
u32 perform_BCD(BCD_type type, u32 src, u32 dest);


//A-Lxx
u32 ALxx(u32 code);

//Roxx
u32 ROxx(u32 code);

/*
 * END DUMBS PROTOS
 *
 */




/*
 * DEFINING MNEMONIC HASHING VALUES, COMPUTED WITH 'generic_u32_t hash (const char* word)' func
 *
 */
#define ori   78534
#define andi  2013554
#define eori  2134113
#define move_op 2372561
#define moveq 73549472
#define divu  2098692
#define divs  2098690
#define or    2531
#define eor   68840
#define mulu  2378033
#define muls  2378031
#define and   64951
#define subi  2556457
#define subq  2556465
#define sub   82464
#define subx  2556472
#define addi  2003944
#define addq  2003952
#define add   64641
#define addx  2003959
#define cmpi  2072547
#define cmpm  2072551
#define cmp   66854
#define clr   66825
#define cmpa  2072539
#define negx  2392296
#define neg   77168
#define not   77491
#define ext   69121
#define swap  2558355
#define tst   83381
#define asl   65114
#define asr   65120
#define lsl   75685
#define lsr   75691
#define rol   81327
#define ror   81333
#define roxl  2521585
#define roxr  2521591





#endif // __HANDLER_H__68000
