#ifndef __HANDLER_H__68000
#define __HANDLER_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "utils.h"
#include "cpu.h"
#include "ram.h"


void init_opcodes(struct EmulationMachine* restrict em);
void destroy_codes(void);

void preset_hander(struct EmulationMachine* restrict em);
u32  run_opcode(void);





/*
 * BEGIN DUMBS PROTOS
 *
 */
// GROUP 0x00
u32 ORItoCCR(void);  //ok
u32 ORItoSR(void);   //ok
u32 ORI(void);       //ok
u32 ANDItoCCR(void); //ok
u32 ANDItoSR(void);  //ok
u32 ANDI(void);      //ok
u32 SUBI(void);      //ok
u32 ADDI(void);      //ok
u32 EORItoCCR(void); //ok
u32 EORItoSR(void);  //ok
u32 EORI(void);      //ok
u32 CMPI(void);      //ok
u32 MOVEP(void);     // maybe next -warn
u32 BTST(void);      //ok
u32 BCHG(void);      //ok
u32 BCLR(void);      //ok
u32 BSET(void);      //ok


// GROUP 0x01
u32 MOVE(void);   //ok


// GROUP 0x02-0x03
u32 MOVEA(void);  //ok


// group 0X04
u32 MOVEfromSR(void); //ok
u32 MOVEtoCCR(void);  //ok
u32 MOVEtoSR(void);   //ok
u32 NEGX(void);       //ok
u32 CLR(void);        //ok
u32 NEG(void);        //ok
u32 NOT(void);        //ok
u32 EXT(void);        //ok
u32 NBCD(void);       //ok
u32 SWAP(void);       //ok
u32 PEA(void);        //ok
u32 ILLEGAL(void);    //ok
u32 TAS(void);        // ?? -warn
u32 TST(void);        //ok
u32 TRAP(void);       //ok
u32 LINK(void);       //ok
u32 UNLK(void);       //ok
u32 MOVEUSP(void);    //ok
u32 RESET(void);      // ?? -warn
u32 NOP(void);        //ok
u32 STOP(void);       // ?? -warn
u32 RTE(void);        //ok
u32 RTS(void);        //ok
u32 TRAPV(void);      //ok
u32 RTR(void);        //ok
u32 JSR(void);        //ok
u32 JMP(void);        //ok
u32 MOVEM(void);      // wtf -warn
u32 CHK(void);        // ok -warn
u32 LEA(void);        //ok


// GROUP 0x05
u32 DBcc(void);      //ok
u32 Scc(void);       //ok
u32 ADDQ(void);      //ok
u32 SUBQ(void);      //ok


// GROUP 0x06
u32 BRA(void);      //ok
u32 BSR(void);      //ok
u32 Bcc(void);      //ok


// GROUP 0x07
u32 MOVEQ(void);     //ok


// GROUP 0x08
u32 DIVU(void);   //ok
u32 DIVS(void);   //ok
u32 SBCD(void);   //ok
u32 OR(void);     //ok


// GROUP 0x09
u32 SUBA(void);  //ok
u32 SUBX(void);  //ok
u32 SUB(void);   //ok


// GROUP 0x0B
u32 CMPA(void);  //ok
u32 CMPM(void);  //ok
u32 EOR(void);   //ok
u32 CMP(void);   //ok


// GROUP 0x0C
u32 MULU(void);  //ok
u32 MULS(void);  //ok
u32 ABCD(void);  //ok
u32 EXG(void);   //ok
u32 AND(void);   //ok


// GROUP 0x0D
u32 ADDA(void);  //ok
u32 ADDX(void);  //ok
u32 ADD(void);   //ok


// GROUP 0x0E
u32 ASR(void);   //ok
u32 ASL(void);   //ok
u32 LSR(void);   //ok
u32 LSL(void);   //ok
u32 ROXR(void);  //ok
u32 ROXL(void);  //ok
u32 ROR(void);   //ok
u32 ROL(void);   //ok


//Bxxx
u32 Bxxx(void);


//abcd-sbcd
u32 xBCD(BCD_type type);
u32 perform_BCD(BCD_type type, u32 src, u32 dest);


//A-Lxx
u32 ALxx(void);

//Roxx
u32 ROxx(void);

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
