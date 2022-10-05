#ifndef __MOTOROLATYPES_H__68000
#define __MOTOROLATYPES_H__68000


#define LOAD_ERROR 0xFFFFFFFF


typedef unsigned short int opcode;
typedef unsigned char      opgroup;


/* CPU */
typedef unsigned short int srflags;
typedef unsigned char      bit;


/* UTILS */
typedef unsigned int       generic_u32_t;
typedef unsigned short int generic_u16_t;
typedef unsigned char      generic_u8_t;

typedef int       generic_32_t;
typedef short int generic_16_t;
typedef char      generic_8_t;


/* HANDLERS */
typedef unsigned short int bitmask;



#endif // __MOTOROLATYPES_H__68000
