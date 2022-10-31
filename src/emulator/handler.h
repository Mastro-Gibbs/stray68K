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
u32  run_opcode();





/*
 * BEGIN DUMBS PROTOS
 *
 */
// GROUP 0x00
u32 ORItoCCR();  //ok
u32 ORItoSR();   //ok
u32 ORI();       //ok
u32 ANDItoCCR(); //ok
u32 ANDItoSR();  //ok
u32 ANDI();      //ok
u32 SUBI();      //ok
u32 ADDI();      //ok
u32 EORItoCCR(); //ok
u32 EORItoSR();  //ok
u32 EORI();      //ok
u32 CMPI();      //ok
u32 MOVEP();     // maybe next -warn
u32 BTST();      //ok
u32 BCHG();      //ok
u32 BCLR();      //ok
u32 BSET();      //ok


// GROUP 0x01
u32 MOVE();   //ok


// GROUP 0x02-0x03
u32 MOVEA();  //ok


// group 0X04
u32 MOVEfromSR(); //ok
u32 MOVEtoCCR();  //ok
u32 MOVEtoSR();   //ok
u32 NEGX();       //ok
u32 CLR();        //ok
u32 NEG();        //ok
u32 NOT();        //ok
u32 EXT();        //ok
u32 NBCD();       //ok
u32 SWAP();       //ok
u32 PEA();        //ok
u32 ILLEGAL();    //ok
u32 TAS();        // ?? -warn
u32 TST();        //ok
u32 TRAP();       //ok
u32 LINK();       //ok
u32 UNLK();       //ok
u32 MOVEUSP();    //ok
u32 RESET();      // ?? -warn
u32 NOP();        //ok
u32 STOP();       // ?? -warn
u32 RTE();        //ok
u32 RTS();        //ok
u32 TRAPV();      //ok
u32 RTR();        //ok
u32 JSR();        //ok
u32 JMP();        //ok
u32 MOVEM();      // wtf -warn
u32 CHK();        // ok -warn
u32 LEA();        //ok


// GROUP 0x05
u32 DBcc();      //ok
u32 Scc();       //ok
u32 ADDQ();      //ok
u32 SUBQ();      //ok


// GROUP 0x06
u32 BRA();      //ok
u32 BSR();      //ok
u32 Bcc();      //ok


// GROUP 0x07
u32 MOVEQ();     //ok


// GROUP 0x08
u32 DIVU();   //ok
u32 DIVS();   //ok
u32 SBCD();   //ok
u32 OR();     //ok


// GROUP 0x09
u32 SUBA();  //ok
u32 SUBX();  //ok
u32 SUB();   //ok


// GROUP 0x0B
u32 CMPA();  //ok
u32 CMPM();  //ok
u32 EOR();   //ok
u32 CMP();   //ok


// GROUP 0x0C
u32 MULU();  //ok
u32 MULS();  //ok
u32 ABCD();  //ok
u32 EXG();   //ok
u32 AND();   //ok


// GROUP 0x0D
u32 ADDA();  //ok
u32 ADDX();  //ok
u32 ADD();   //ok


// GROUP 0x0E
u32 ASR();   //ok
u32 ASL();   //ok
u32 LSR();   //ok
u32 LSL();   //ok
u32 ROXR();  //ok
u32 ROXL();  //ok
u32 ROR();   //ok
u32 ROL();   //ok


//Bxxx
u32 Bxxx();


//abcd-sbcd
u32 xBCD(BCD_type type);
u32 perform_BCD(BCD_type type, u32 src, u32 dest);


//A-Lxx
u32 ALxx();

//Roxx
u32 ROxx();

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
