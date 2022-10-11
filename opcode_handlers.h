#ifndef __OPCODE_HANDLERS_H__68000
#define __OPCODE_HANDLERS_H__68000

#include "motorolatypes.h"
#include "opcode.h"
#include "enums.h"
#include "utils.h"
#include "cpu.h"
#include "memory.h"


#define RETURN_OK_PC_NO_INCR 2
#define RETURN_OK            1
#define RETURN_ERR           0


typedef struct __opcodes__datastructure__
{
    opgroup  key;
    opcode_t **instances;
    generic_u8_t size;

} opcodes_ds;



void init_codes();

void destroy_codes();

opcode_t* get_opcode_t(opcode code);

generic_u32_t  run_opcode(opcode code, bit describe_code);

void set_srflags(const generic_u32_t mnemonic, opsize size, generic_u32_t src, generic_u32_t dst, generic_u32_t res);



// GROUP 0x00
generic_u32_t ORItoCCR(opcode code);  //ok
generic_u32_t ORItoSR(opcode code);   //ok
generic_u32_t ORI(opcode code);       //ok
generic_u32_t ANDItoCCR(opcode code); //ok
generic_u32_t ANDItoSR(opcode code);  //ok
generic_u32_t ANDI(opcode code);      //ok
generic_u32_t SUBI(opcode code);      //ok
generic_u32_t ADDI(opcode code);      //ok
generic_u32_t EORItoCCR(opcode code); //ok
generic_u32_t EORItoSR(opcode code);  //ok
generic_u32_t EORI(opcode code);      //ok
generic_u32_t CMPI(opcode code);      //ok
generic_u32_t MOVEP(opcode code);     // maybe next -warn
generic_u32_t BTST(opcode code);      //ok
generic_u32_t BCHG(opcode code);      //ok
generic_u32_t BCLR(opcode code);      //ok
generic_u32_t BSET(opcode code);      //ok


// GROUP 0x01
generic_u32_t MOVE(opcode code);   //ok


// GROUP 0x02-0x03
generic_u32_t MOVEA(opcode code);  //ok


// group 0X04
generic_u32_t MOVEfromSR(opcode code); //ok
generic_u32_t MOVEtoCCR(opcode code);  //ok
generic_u32_t MOVEtoSR(opcode code);   //ok
generic_u32_t NEGX(opcode code);       //ok
generic_u32_t CLR(opcode code);        //ok
generic_u32_t NEG(opcode code);        //ok
generic_u32_t NOT(opcode code);        //ok
generic_u32_t EXT(opcode code);        //ok
generic_u32_t NBCD(opcode code);       //ok
generic_u32_t SWAP(opcode code);       //ok
generic_u32_t PEA(opcode code);        //ok
generic_u32_t ILLEGAL(opcode code);    //ok
generic_u32_t TAS(opcode code);        // ?? -warn
generic_u32_t TST(opcode code);        //ok
generic_u32_t TRAP(opcode code);       //ok
generic_u32_t LINK(opcode code);       //ok
generic_u32_t UNLK(opcode code);       //ok
generic_u32_t MOVEUSP(opcode code);    //ok
generic_u32_t RESET(opcode code);      // ?? -warn
generic_u32_t NOP(opcode code);        //ok
generic_u32_t STOP(opcode code);       // ?? -warn
generic_u32_t RTE(opcode code);        //ok
generic_u32_t RTS(opcode code);        //ok
generic_u32_t TRAPV(opcode code);      //ok
generic_u32_t RTR(opcode code);        //ok
generic_u32_t JSR(opcode code);        //ok
generic_u32_t JMP(opcode code);        //ok
generic_u32_t MOVEM(opcode code);      // wtf -warn
generic_u32_t CHK(opcode code);        // ok -warn
generic_u32_t LEA(opcode code);        //ok


// GROUP 0x05
generic_u32_t DBcc(opcode code);      //ok
generic_u32_t Scc(opcode code);       //ok
generic_u32_t ADDQ(opcode code);      //ok
generic_u32_t SUBQ(opcode code);      //ok


// GROUP 0x06
generic_u32_t BRA(opcode code);      //ok
generic_u32_t BSR(opcode code);      //ok
generic_u32_t Bcc(opcode code);      //ok


// GROUP 0x07
generic_u32_t MOVEQ(opcode code);     //ok


// GROUP 0x08
generic_u32_t DIVU(opcode code);   //ok
generic_u32_t DIVS(opcode code);   //ok
generic_u32_t SBCD(opcode code);   //ok
generic_u32_t OR(opcode code);     //ok


// GROUP 0x09
generic_u32_t SUBA(opcode code);  //ok
generic_u32_t SUBX(opcode code);  //ok
generic_u32_t SUB(opcode code);   //ok


// GROUP 0x0B
generic_u32_t CMPA(opcode code);  //ok
generic_u32_t CMPM(opcode code);  //ok
generic_u32_t EOR(opcode code);   //ok
generic_u32_t CMP(opcode code);   //ok


// GROUP 0x0C
generic_u32_t MULU(opcode code);  //ok
generic_u32_t MULS(opcode code);  //ok
generic_u32_t ABCD(opcode code);  //ok
generic_u32_t EXG(opcode code);   //ok
generic_u32_t AND(opcode code);   //ok


// GROUP 0x0D
generic_u32_t ADDA(opcode code);  //ok
generic_u32_t ADDX(opcode code);  //ok
generic_u32_t ADD(opcode code);   //ok


// GROUP 0x0E
generic_u32_t ASR(opcode code);   //ok
generic_u32_t ASL(opcode code);   //ok
generic_u32_t LSR(opcode code);   //ok
generic_u32_t LSL(opcode code);   //ok
generic_u32_t ROXR(opcode code);  //ok
generic_u32_t ROXL(opcode code);  //ok
generic_u32_t ROR(opcode code);   //ok
generic_u32_t ROL(opcode code);   //ok


//Bxxx
generic_u32_t Bxxx(opcode code);


//abcd-sbcd
generic_u32_t xBCD(opcode code, BCD_type type);
generic_u32_t perform_BCD(BCD_type type, generic_u32_t src, generic_u32_t dest);


//A-Lxx
generic_u32_t ALxx(generic_u32_t code);

//Roxx
generic_u32_t ROxx(generic_u32_t code);



//dumbest way to ignore param 'code' :D
generic_u32_t UNUSED(generic_u32_t code);

#endif // __OPCODE_HANDLERS_H__68000
