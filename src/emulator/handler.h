#ifndef __HANDLER_H__68000
#define __HANDLER_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "utils.h"
#include "cpu.h"
#include "ram.h"


void init_opcodes(struct EmulationMachine *em);
void destroy_codes(struct EmulationMachine *em);

u32 execute_istr(struct EmulationMachine *emulator);





/*
 * BEGIN DUMBS PROTOS
 *
 */
// GROUP 0x00
u32 ORItoCCR(struct EmulationMachine* emulator);  //ok
u32 ORItoSR(struct EmulationMachine* emulator);   //ok
u32 ORI(struct EmulationMachine* emulator);       //ok
u32 ANDItoCCR(struct EmulationMachine* emulator); //ok
u32 ANDItoSR(struct EmulationMachine* emulator);  //ok
u32 ANDI(struct EmulationMachine* emulator);      //ok
u32 SUBI(struct EmulationMachine* emulator);      //ok
u32 ADDI(struct EmulationMachine* emulator);      //ok
u32 EORItoCCR(struct EmulationMachine* emulator); //ok
u32 EORItoSR(struct EmulationMachine* emulator);  //ok
u32 EORI(struct EmulationMachine* emulator);      //ok
u32 CMPI(struct EmulationMachine* emulator);      //ok
u32 MOVEP(struct EmulationMachine* emulator);     // maybe next -warn
u32 BTST(struct EmulationMachine* emulator);      //ok
u32 BCHG(struct EmulationMachine* emulator);      //ok
u32 BCLR(struct EmulationMachine* emulator);      //ok
u32 BSET(struct EmulationMachine* emulator);      //ok


// GROUP 0x01
u32 MOVE(struct EmulationMachine* emulator);   //ok


// GROUP 0x02-0x03
u32 MOVEA(struct EmulationMachine* emulator);  //ok


// group 0X04
u32 MOVEfromSR(struct EmulationMachine* emulator); //ok
u32 MOVEtoCCR(struct EmulationMachine* emulator);  //ok
u32 MOVEtoSR(struct EmulationMachine* emulator);   //ok
u32 NEGX(struct EmulationMachine* emulator);       //ok
u32 CLR(struct EmulationMachine* emulator);        //ok
u32 NEG(struct EmulationMachine* emulator);        //ok
u32 NOT(struct EmulationMachine* emulator);        //ok
u32 EXT(struct EmulationMachine* emulator);        //ok
u32 NBCD(struct EmulationMachine* emulator);       //ok
u32 SWAP(struct EmulationMachine* emulator);       //ok
u32 PEA(struct EmulationMachine* emulator);        //ok
u32 ILLEGAL(struct EmulationMachine* emulator);    //ok
u32 TAS(struct EmulationMachine* emulator);        // ?? -warn
u32 TST(struct EmulationMachine* emulator);        //ok
u32 TRAP(struct EmulationMachine* emulator);       //ok
u32 LINK(struct EmulationMachine* emulator);       //ok
u32 UNLK(struct EmulationMachine* emulator);       //ok
u32 MOVEUSP(struct EmulationMachine* emulator);    //ok
u32 RESET(struct EmulationMachine* emulator);      // ?? -warn
u32 NOP(struct EmulationMachine* emulator);        //ok
u32 STOP(struct EmulationMachine* emulator);       // ?? -warn
u32 RTE(struct EmulationMachine* emulator);        //ok
u32 RTS(struct EmulationMachine* emulator);        //ok
u32 TRAPV(struct EmulationMachine* emulator);      //ok
u32 RTR(struct EmulationMachine* emulator);        //ok
u32 JSR(struct EmulationMachine* emulator);        //ok
u32 JMP(struct EmulationMachine* emulator);        //ok
u32 MOVEM(struct EmulationMachine* emulator);      // wtf -warn
u32 CHK(struct EmulationMachine* emulator);        // ok -warn
u32 LEA(struct EmulationMachine* emulator);        //ok


// GROUP 0x05
u32 DBcc(struct EmulationMachine* emulator);      //ok
u32 Scc(struct EmulationMachine* emulator);       //ok
u32 ADDQ(struct EmulationMachine* emulator);      //ok
u32 SUBQ(struct EmulationMachine* emulator);      //ok


// GROUP 0x06
u32 BRA(struct EmulationMachine* emulator);      //ok
u32 BSR(struct EmulationMachine* emulator);      //ok
u32 Bcc(struct EmulationMachine* emulator);      //ok


// GROUP 0x07
u32 MOVEQ(struct EmulationMachine* emulator);     //ok


// GROUP 0x08
u32 DIVU(struct EmulationMachine* emulator);   //ok
u32 DIVS(struct EmulationMachine* emulator);   //ok
u32 SBCD(struct EmulationMachine* emulator);   //ok
u32 OR(struct EmulationMachine* emulator);     //ok


// GROUP 0x09
u32 SUBA(struct EmulationMachine* emulator);  //ok
u32 SUBX(struct EmulationMachine* emulator);  //ok
u32 SUB(struct EmulationMachine* emulator);   //ok


// GROUP 0x0B
u32 CMPA(struct EmulationMachine* emulator);  //ok
u32 CMPM(struct EmulationMachine* emulator);  //ok
u32 EOR(struct EmulationMachine* emulator);   //ok
u32 CMP(struct EmulationMachine* emulator);   //ok


// GROUP 0x0C
u32 MULU(struct EmulationMachine* emulator);  //ok
u32 MULS(struct EmulationMachine* emulator);  //ok
u32 ABCD(struct EmulationMachine* emulator);  //ok
u32 EXG(struct EmulationMachine* emulator);   //ok
u32 AND(struct EmulationMachine* emulator);   //ok


// GROUP 0x0D
u32 ADDA(struct EmulationMachine* emulator);  //ok
u32 ADDX(struct EmulationMachine* emulator);  //ok
u32 ADD(struct EmulationMachine* emulator);   //ok


// GROUP 0x0E
u32 ASR(struct EmulationMachine* emulator);   //ok
u32 ASL(struct EmulationMachine* emulator);   //ok
u32 LSR(struct EmulationMachine* emulator);   //ok
u32 LSL(struct EmulationMachine* emulator);   //ok
u32 ROXR(struct EmulationMachine* emulator);  //ok
u32 ROXL(struct EmulationMachine* emulator);  //ok
u32 ROR(struct EmulationMachine* emulator);   //ok
u32 ROL(struct EmulationMachine* emulator);   //ok


//Bxxx
u32 Bxxx(struct EmulationMachine* emulator);


//abcd-sbcd
u32 xBCD(struct EmulationMachine* emulator, BCD_type type);
u32 perform_BCD(struct EmulationMachine* emulator, BCD_type type, u32 src, u32 dest);


//A-Lxx
u32 ALxx(struct EmulationMachine* emulator);

//Roxx
u32 ROxx(struct EmulationMachine* emulator);

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
#define _or   2531
#define eor   68840
#define mulu  2378033
#define muls  2378031
#define _and  64951
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
#define _cmp   66854
#define clr   66825
#define cmpa  2072539
#define negx  2392296
#define neg   77168
#define _not  77491
#define ext   69121
#define _swap  2558355
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
