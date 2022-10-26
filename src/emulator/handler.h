#ifndef __HANDLER_H__68000
#define __HANDLER_H__68000

#include "motorolatypes.h"
#include "enums.h"
#include "utils.h"
#include "cpu.h"
#include "ram.h"


void init_codes();
void destroy_codes();

void preset_handler(struct EmulationMachine *em);
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






#endif // __HANDLER_H__68000
