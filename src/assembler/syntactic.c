/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         M68KASM_STYPE
/* Substitute the variable and function names.  */
#define yyparse         m68kasm_parse
#define yylex           m68kasm_lex
#define yyerror         m68kasm_error
#define yydebug         m68kasm_debug
#define yynerrs         m68kasm_nerrs


# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "syntactic.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_DIRECTIVE_ORI = 3,        /* TOKEN_DIRECTIVE_ORI  */
  YYSYMBOL_TOKEN_DIRECTIVE_ANDI = 4,       /* TOKEN_DIRECTIVE_ANDI  */
  YYSYMBOL_TOKEN_DIRECTIVE_SUBI = 5,       /* TOKEN_DIRECTIVE_SUBI  */
  YYSYMBOL_TOKEN_DIRECTIVE_ADDI = 6,       /* TOKEN_DIRECTIVE_ADDI  */
  YYSYMBOL_TOKEN_DIRECTIVE_EORI = 7,       /* TOKEN_DIRECTIVE_EORI  */
  YYSYMBOL_TOKEN_DIRECTIVE_CMPI = 8,       /* TOKEN_DIRECTIVE_CMPI  */
  YYSYMBOL_TOKEN_DIRECTIVE_BTST = 9,       /* TOKEN_DIRECTIVE_BTST  */
  YYSYMBOL_TOKEN_DIRECTIVE_BCHG = 10,      /* TOKEN_DIRECTIVE_BCHG  */
  YYSYMBOL_TOKEN_DIRECTIVE_BCLR = 11,      /* TOKEN_DIRECTIVE_BCLR  */
  YYSYMBOL_TOKEN_DIRECTIVE_BSET = 12,      /* TOKEN_DIRECTIVE_BSET  */
  YYSYMBOL_TOKEN_DIRECTIVE_MOVEP = 13,     /* TOKEN_DIRECTIVE_MOVEP  */
  YYSYMBOL_TOKEN_DIRECTIVE_MOVEA = 14,     /* TOKEN_DIRECTIVE_MOVEA  */
  YYSYMBOL_TOKEN_DIRECTIVE_MOVE = 15,      /* TOKEN_DIRECTIVE_MOVE  */
  YYSYMBOL_TOKEN_DIRECTIVE_NEGX = 16,      /* TOKEN_DIRECTIVE_NEGX  */
  YYSYMBOL_TOKEN_DIRECTIVE_CLR = 17,       /* TOKEN_DIRECTIVE_CLR  */
  YYSYMBOL_TOKEN_DIRECTIVE_NEG = 18,       /* TOKEN_DIRECTIVE_NEG  */
  YYSYMBOL_TOKEN_DIRECTIVE_NOT = 19,       /* TOKEN_DIRECTIVE_NOT  */
  YYSYMBOL_TOKEN_DIRECTIVE_EXT = 20,       /* TOKEN_DIRECTIVE_EXT  */
  YYSYMBOL_TOKEN_DIRECTIVE_NBCD = 21,      /* TOKEN_DIRECTIVE_NBCD  */
  YYSYMBOL_TOKEN_DIRECTIVE_SWAP = 22,      /* TOKEN_DIRECTIVE_SWAP  */
  YYSYMBOL_TOKEN_DIRECTIVE_PEA = 23,       /* TOKEN_DIRECTIVE_PEA  */
  YYSYMBOL_TOKEN_DIRECTIVE_ILLEGAL = 24,   /* TOKEN_DIRECTIVE_ILLEGAL  */
  YYSYMBOL_TOKEN_DIRECTIVE_TAS = 25,       /* TOKEN_DIRECTIVE_TAS  */
  YYSYMBOL_TOKEN_DIRECTIVE_TST = 26,       /* TOKEN_DIRECTIVE_TST  */
  YYSYMBOL_TOKEN_DIRECTIVE_TRAP = 27,      /* TOKEN_DIRECTIVE_TRAP  */
  YYSYMBOL_TOKEN_DIRECTIVE_LINK = 28,      /* TOKEN_DIRECTIVE_LINK  */
  YYSYMBOL_TOKEN_DIRECTIVE_UNLK = 29,      /* TOKEN_DIRECTIVE_UNLK  */
  YYSYMBOL_TOKEN_DIRECTIVE_RESET = 30,     /* TOKEN_DIRECTIVE_RESET  */
  YYSYMBOL_TOKEN_DIRECTIVE_NOP = 31,       /* TOKEN_DIRECTIVE_NOP  */
  YYSYMBOL_TOKEN_DIRECTIVE_STOP = 32,      /* TOKEN_DIRECTIVE_STOP  */
  YYSYMBOL_TOKEN_DIRECTIVE_RTE = 33,       /* TOKEN_DIRECTIVE_RTE  */
  YYSYMBOL_TOKEN_DIRECTIVE_RTS = 34,       /* TOKEN_DIRECTIVE_RTS  */
  YYSYMBOL_TOKEN_DIRECTIVE_TRAPV = 35,     /* TOKEN_DIRECTIVE_TRAPV  */
  YYSYMBOL_TOKEN_DIRECTIVE_RTR = 36,       /* TOKEN_DIRECTIVE_RTR  */
  YYSYMBOL_TOKEN_DIRECTIVE_JSR = 37,       /* TOKEN_DIRECTIVE_JSR  */
  YYSYMBOL_TOKEN_DIRECTIVE_JMP = 38,       /* TOKEN_DIRECTIVE_JMP  */
  YYSYMBOL_TOKEN_DIRECTIVE_MOVEM = 39,     /* TOKEN_DIRECTIVE_MOVEM  */
  YYSYMBOL_TOKEN_DIRECTIVE_LEA = 40,       /* TOKEN_DIRECTIVE_LEA  */
  YYSYMBOL_TOKEN_DIRECTIVE_CHK = 41,       /* TOKEN_DIRECTIVE_CHK  */
  YYSYMBOL_TOKEN_DIRECTIVE_ADDQ = 42,      /* TOKEN_DIRECTIVE_ADDQ  */
  YYSYMBOL_TOKEN_DIRECTIVE_SUBQ = 43,      /* TOKEN_DIRECTIVE_SUBQ  */
  YYSYMBOL_TOKEN_DIRECTIVE_ST = 44,        /* TOKEN_DIRECTIVE_ST  */
  YYSYMBOL_TOKEN_DIRECTIVE_SF = 45,        /* TOKEN_DIRECTIVE_SF  */
  YYSYMBOL_TOKEN_DIRECTIVE_SHI = 46,       /* TOKEN_DIRECTIVE_SHI  */
  YYSYMBOL_TOKEN_DIRECTIVE_SLS = 47,       /* TOKEN_DIRECTIVE_SLS  */
  YYSYMBOL_TOKEN_DIRECTIVE_SCC = 48,       /* TOKEN_DIRECTIVE_SCC  */
  YYSYMBOL_TOKEN_DIRECTIVE_SCS = 49,       /* TOKEN_DIRECTIVE_SCS  */
  YYSYMBOL_TOKEN_DIRECTIVE_SNE = 50,       /* TOKEN_DIRECTIVE_SNE  */
  YYSYMBOL_TOKEN_DIRECTIVE_SEQ = 51,       /* TOKEN_DIRECTIVE_SEQ  */
  YYSYMBOL_TOKEN_DIRECTIVE_SVC = 52,       /* TOKEN_DIRECTIVE_SVC  */
  YYSYMBOL_TOKEN_DIRECTIVE_SVS = 53,       /* TOKEN_DIRECTIVE_SVS  */
  YYSYMBOL_TOKEN_DIRECTIVE_SPL = 54,       /* TOKEN_DIRECTIVE_SPL  */
  YYSYMBOL_TOKEN_DIRECTIVE_SMI = 55,       /* TOKEN_DIRECTIVE_SMI  */
  YYSYMBOL_TOKEN_DIRECTIVE_SGE = 56,       /* TOKEN_DIRECTIVE_SGE  */
  YYSYMBOL_TOKEN_DIRECTIVE_SLT = 57,       /* TOKEN_DIRECTIVE_SLT  */
  YYSYMBOL_TOKEN_DIRECTIVE_SGT = 58,       /* TOKEN_DIRECTIVE_SGT  */
  YYSYMBOL_TOKEN_DIRECTIVE_SLE = 59,       /* TOKEN_DIRECTIVE_SLE  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBT = 60,       /* TOKEN_DIRECTIVE_DBT  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBF = 61,       /* TOKEN_DIRECTIVE_DBF  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBHI = 62,      /* TOKEN_DIRECTIVE_DBHI  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBLS = 63,      /* TOKEN_DIRECTIVE_DBLS  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBCC = 64,      /* TOKEN_DIRECTIVE_DBCC  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBCS = 65,      /* TOKEN_DIRECTIVE_DBCS  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBNE = 66,      /* TOKEN_DIRECTIVE_DBNE  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBEQ = 67,      /* TOKEN_DIRECTIVE_DBEQ  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBVC = 68,      /* TOKEN_DIRECTIVE_DBVC  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBVS = 69,      /* TOKEN_DIRECTIVE_DBVS  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBPL = 70,      /* TOKEN_DIRECTIVE_DBPL  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBMI = 71,      /* TOKEN_DIRECTIVE_DBMI  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBGE = 72,      /* TOKEN_DIRECTIVE_DBGE  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBLT = 73,      /* TOKEN_DIRECTIVE_DBLT  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBGT = 74,      /* TOKEN_DIRECTIVE_DBGT  */
  YYSYMBOL_TOKEN_DIRECTIVE_DBLE = 75,      /* TOKEN_DIRECTIVE_DBLE  */
  YYSYMBOL_TOKEN_DIRECTIVE_BRA = 76,       /* TOKEN_DIRECTIVE_BRA  */
  YYSYMBOL_TOKEN_DIRECTIVE_BSR = 77,       /* TOKEN_DIRECTIVE_BSR  */
  YYSYMBOL_TOKEN_DIRECTIVE_BHI = 78,       /* TOKEN_DIRECTIVE_BHI  */
  YYSYMBOL_TOKEN_DIRECTIVE_BLS = 79,       /* TOKEN_DIRECTIVE_BLS  */
  YYSYMBOL_TOKEN_DIRECTIVE_BCC = 80,       /* TOKEN_DIRECTIVE_BCC  */
  YYSYMBOL_TOKEN_DIRECTIVE_BCS = 81,       /* TOKEN_DIRECTIVE_BCS  */
  YYSYMBOL_TOKEN_DIRECTIVE_BNE = 82,       /* TOKEN_DIRECTIVE_BNE  */
  YYSYMBOL_TOKEN_DIRECTIVE_BEQ = 83,       /* TOKEN_DIRECTIVE_BEQ  */
  YYSYMBOL_TOKEN_DIRECTIVE_BVC = 84,       /* TOKEN_DIRECTIVE_BVC  */
  YYSYMBOL_TOKEN_DIRECTIVE_BVS = 85,       /* TOKEN_DIRECTIVE_BVS  */
  YYSYMBOL_TOKEN_DIRECTIVE_BPL = 86,       /* TOKEN_DIRECTIVE_BPL  */
  YYSYMBOL_TOKEN_DIRECTIVE_BMI = 87,       /* TOKEN_DIRECTIVE_BMI  */
  YYSYMBOL_TOKEN_DIRECTIVE_BGE = 88,       /* TOKEN_DIRECTIVE_BGE  */
  YYSYMBOL_TOKEN_DIRECTIVE_BLT = 89,       /* TOKEN_DIRECTIVE_BLT  */
  YYSYMBOL_TOKEN_DIRECTIVE_BGT = 90,       /* TOKEN_DIRECTIVE_BGT  */
  YYSYMBOL_TOKEN_DIRECTIVE_BLE = 91,       /* TOKEN_DIRECTIVE_BLE  */
  YYSYMBOL_TOKEN_DIRECTIVE_MOVEQ = 92,     /* TOKEN_DIRECTIVE_MOVEQ  */
  YYSYMBOL_TOKEN_DIRECTIVE_DIVU = 93,      /* TOKEN_DIRECTIVE_DIVU  */
  YYSYMBOL_TOKEN_DIRECTIVE_DIVS = 94,      /* TOKEN_DIRECTIVE_DIVS  */
  YYSYMBOL_TOKEN_DIRECTIVE_SBCD = 95,      /* TOKEN_DIRECTIVE_SBCD  */
  YYSYMBOL_TOKEN_DIRECTIVE_OR = 96,        /* TOKEN_DIRECTIVE_OR  */
  YYSYMBOL_TOKEN_DIRECTIVE_SUB = 97,       /* TOKEN_DIRECTIVE_SUB  */
  YYSYMBOL_TOKEN_DIRECTIVE_SUBX = 98,      /* TOKEN_DIRECTIVE_SUBX  */
  YYSYMBOL_TOKEN_DIRECTIVE_SUBA = 99,      /* TOKEN_DIRECTIVE_SUBA  */
  YYSYMBOL_TOKEN_DIRECTIVE_EOR = 100,      /* TOKEN_DIRECTIVE_EOR  */
  YYSYMBOL_TOKEN_DIRECTIVE_CMPM = 101,     /* TOKEN_DIRECTIVE_CMPM  */
  YYSYMBOL_TOKEN_DIRECTIVE_CMP = 102,      /* TOKEN_DIRECTIVE_CMP  */
  YYSYMBOL_TOKEN_DIRECTIVE_CMPA = 103,     /* TOKEN_DIRECTIVE_CMPA  */
  YYSYMBOL_TOKEN_DIRECTIVE_MULU = 104,     /* TOKEN_DIRECTIVE_MULU  */
  YYSYMBOL_TOKEN_DIRECTIVE_MULS = 105,     /* TOKEN_DIRECTIVE_MULS  */
  YYSYMBOL_TOKEN_DIRECTIVE_ABCD = 106,     /* TOKEN_DIRECTIVE_ABCD  */
  YYSYMBOL_TOKEN_DIRECTIVE_EXG = 107,      /* TOKEN_DIRECTIVE_EXG  */
  YYSYMBOL_TOKEN_DIRECTIVE_AND = 108,      /* TOKEN_DIRECTIVE_AND  */
  YYSYMBOL_TOKEN_DIRECTIVE_ADD = 109,      /* TOKEN_DIRECTIVE_ADD  */
  YYSYMBOL_TOKEN_DIRECTIVE_ADDX = 110,     /* TOKEN_DIRECTIVE_ADDX  */
  YYSYMBOL_TOKEN_DIRECTIVE_ADDA = 111,     /* TOKEN_DIRECTIVE_ADDA  */
  YYSYMBOL_TOKEN_DIRECTIVE_ASL = 112,      /* TOKEN_DIRECTIVE_ASL  */
  YYSYMBOL_TOKEN_DIRECTIVE_ASR = 113,      /* TOKEN_DIRECTIVE_ASR  */
  YYSYMBOL_TOKEN_DIRECTIVE_LSL = 114,      /* TOKEN_DIRECTIVE_LSL  */
  YYSYMBOL_TOKEN_DIRECTIVE_LSR = 115,      /* TOKEN_DIRECTIVE_LSR  */
  YYSYMBOL_TOKEN_DIRECTIVE_ROXL = 116,     /* TOKEN_DIRECTIVE_ROXL  */
  YYSYMBOL_TOKEN_DIRECTIVE_ROXR = 117,     /* TOKEN_DIRECTIVE_ROXR  */
  YYSYMBOL_TOKEN_DIRECTIVE_ROL = 118,      /* TOKEN_DIRECTIVE_ROL  */
  YYSYMBOL_TOKEN_DIRECTIVE_ROR = 119,      /* TOKEN_DIRECTIVE_ROR  */
  YYSYMBOL_TOKEN_DIRECTIVE_ORG = 120,      /* TOKEN_DIRECTIVE_ORG  */
  YYSYMBOL_TOKEN_DIRECTIVE_DC = 121,       /* TOKEN_DIRECTIVE_DC  */
  YYSYMBOL_TOKEN_DIRECTIVE_DS = 122,       /* TOKEN_DIRECTIVE_DS  */
  YYSYMBOL_TOKEN_DIRECTIVE_DCB = 123,      /* TOKEN_DIRECTIVE_DCB  */
  YYSYMBOL_TOKEN_DIRECTIVE_REPT = 124,     /* TOKEN_DIRECTIVE_REPT  */
  YYSYMBOL_TOKEN_DIRECTIVE_ENDR = 125,     /* TOKEN_DIRECTIVE_ENDR  */
  YYSYMBOL_TOKEN_DIRECTIVE_MACRO = 126,    /* TOKEN_DIRECTIVE_MACRO  */
  YYSYMBOL_TOKEN_DIRECTIVE_MACROS = 127,   /* TOKEN_DIRECTIVE_MACROS  */
  YYSYMBOL_TOKEN_DIRECTIVE_ENDM = 128,     /* TOKEN_DIRECTIVE_ENDM  */
  YYSYMBOL_TOKEN_DIRECTIVE_INCLUDE = 129,  /* TOKEN_DIRECTIVE_INCLUDE  */
  YYSYMBOL_TOKEN_DIRECTIVE_INCBIN = 130,   /* TOKEN_DIRECTIVE_INCBIN  */
  YYSYMBOL_TOKEN_DIRECTIVE_EQU = 131,      /* TOKEN_DIRECTIVE_EQU  */
  YYSYMBOL_TOKEN_DIRECTIVE_SET = 132,      /* TOKEN_DIRECTIVE_SET  */
  YYSYMBOL_TOKEN_DIRECTIVE_IF = 133,       /* TOKEN_DIRECTIVE_IF  */
  YYSYMBOL_TOKEN_DIRECTIVE_ELSEIF = 134,   /* TOKEN_DIRECTIVE_ELSEIF  */
  YYSYMBOL_TOKEN_DIRECTIVE_ELSE = 135,     /* TOKEN_DIRECTIVE_ELSE  */
  YYSYMBOL_TOKEN_DIRECTIVE_ENDC = 136,     /* TOKEN_DIRECTIVE_ENDC  */
  YYSYMBOL_TOKEN_DIRECTIVE_WHILE = 137,    /* TOKEN_DIRECTIVE_WHILE  */
  YYSYMBOL_TOKEN_DIRECTIVE_ENDW = 138,     /* TOKEN_DIRECTIVE_ENDW  */
  YYSYMBOL_TOKEN_DIRECTIVE_EVEN = 139,     /* TOKEN_DIRECTIVE_EVEN  */
  YYSYMBOL_TOKEN_DIRECTIVE_CNOP = 140,     /* TOKEN_DIRECTIVE_CNOP  */
  YYSYMBOL_TOKEN_DIRECTIVE_INFORM = 141,   /* TOKEN_DIRECTIVE_INFORM  */
  YYSYMBOL_TOKEN_DIRECTIVE_END = 142,      /* TOKEN_DIRECTIVE_END  */
  YYSYMBOL_TOKEN_DIRECTIVE_RS = 143,       /* TOKEN_DIRECTIVE_RS  */
  YYSYMBOL_TOKEN_DIRECTIVE_RSSET = 144,    /* TOKEN_DIRECTIVE_RSSET  */
  YYSYMBOL_TOKEN_DIRECTIVE_RSRESET = 145,  /* TOKEN_DIRECTIVE_RSRESET  */
  YYSYMBOL_TOKEN_SIZE_BYTE = 146,          /* TOKEN_SIZE_BYTE  */
  YYSYMBOL_TOKEN_SIZE_SHORT = 147,         /* TOKEN_SIZE_SHORT  */
  YYSYMBOL_TOKEN_SIZE_WORD = 148,          /* TOKEN_SIZE_WORD  */
  YYSYMBOL_TOKEN_SIZE_LONGWORD = 149,      /* TOKEN_SIZE_LONGWORD  */
  YYSYMBOL_TOKEN_DATA_REGISTER = 150,      /* TOKEN_DATA_REGISTER  */
  YYSYMBOL_TOKEN_ADDRESS_REGISTER = 151,   /* TOKEN_ADDRESS_REGISTER  */
  YYSYMBOL_TOKEN_NUMBER = 152,             /* TOKEN_NUMBER  */
  YYSYMBOL_TOKEN_IDENTIFIER = 153,         /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_LOCAL_IDENTIFIER = 154,   /* TOKEN_LOCAL_IDENTIFIER  */
  YYSYMBOL_TOKEN_STRING = 155,             /* TOKEN_STRING  */
  YYSYMBOL_TOKEN_STATUS_REGISTER = 156,    /* TOKEN_STATUS_REGISTER  */
  YYSYMBOL_TOKEN_CONDITION_CODE_REGISTER = 157, /* TOKEN_CONDITION_CODE_REGISTER  */
  YYSYMBOL_TOKEN_USER_STACK_POINTER_REGISTER = 158, /* TOKEN_USER_STACK_POINTER_REGISTER  */
  YYSYMBOL_TOKEN_PROGRAM_COUNTER = 159,    /* TOKEN_PROGRAM_COUNTER  */
  YYSYMBOL_TOKEN_LOGICAL_AND = 160,        /* TOKEN_LOGICAL_AND  */
  YYSYMBOL_TOKEN_LOGICAL_OR = 161,         /* TOKEN_LOGICAL_OR  */
  YYSYMBOL_TOKEN_EQUALITY = 162,           /* TOKEN_EQUALITY  */
  YYSYMBOL_TOKEN_INEQUALITY = 163,         /* TOKEN_INEQUALITY  */
  YYSYMBOL_TOKEN_LESS_OR_EQUAL = 164,      /* TOKEN_LESS_OR_EQUAL  */
  YYSYMBOL_TOKEN_MORE_OR_EQUAL = 165,      /* TOKEN_MORE_OR_EQUAL  */
  YYSYMBOL_TOKEN_LEFT_SHIFT = 166,         /* TOKEN_LEFT_SHIFT  */
  YYSYMBOL_TOKEN_RIGHT_SHIFT = 167,        /* TOKEN_RIGHT_SHIFT  */
  YYSYMBOL_TOKEN_STRLEN = 168,             /* TOKEN_STRLEN  */
  YYSYMBOL_169_ = 169,                     /* ','  */
  YYSYMBOL_170_ = 170,                     /* '='  */
  YYSYMBOL_171_ = 171,                     /* '.'  */
  YYSYMBOL_172_ = 172,                     /* '('  */
  YYSYMBOL_173_ = 173,                     /* ')'  */
  YYSYMBOL_174_ = 174,                     /* '+'  */
  YYSYMBOL_175_ = 175,                     /* '-'  */
  YYSYMBOL_176_ = 176,                     /* '#'  */
  YYSYMBOL_177_ = 177,                     /* '/'  */
  YYSYMBOL_178_ = 178,                     /* '<'  */
  YYSYMBOL_179_ = 179,                     /* '>'  */
  YYSYMBOL_180_ = 180,                     /* '*'  */
  YYSYMBOL_181_ = 181,                     /* '%'  */
  YYSYMBOL_182_ = 182,                     /* '&'  */
  YYSYMBOL_183_ = 183,                     /* '!'  */
  YYSYMBOL_184_ = 184,                     /* '|'  */
  YYSYMBOL_185_ = 185,                     /* '^'  */
  YYSYMBOL_186_ = 186,                     /* '~'  */
  YYSYMBOL_187_ = 187,                     /* '@'  */
  YYSYMBOL_YYACCEPT = 188,                 /* $accept  */
  YYSYMBOL_statement = 189,                /* statement  */
  YYSYMBOL_expression_list = 190,          /* expression_list  */
  YYSYMBOL_identifier_list = 191,          /* identifier_list  */
  YYSYMBOL_instruction = 192,              /* instruction  */
  YYSYMBOL_full_opcode = 193,              /* full_opcode  */
  YYSYMBOL_opcode = 194,                   /* opcode  */
  YYSYMBOL_size = 195,                     /* size  */
  YYSYMBOL_operand = 196,                  /* operand  */
  YYSYMBOL_register_list = 197,            /* register_list  */
  YYSYMBOL_register_span = 198,            /* register_span  */
  YYSYMBOL_data_or_address_register = 199, /* data_or_address_register  */
  YYSYMBOL_expression = 200,               /* expression  */
  YYSYMBOL_expression1 = 201,              /* expression1  */
  YYSYMBOL_expression2 = 202,              /* expression2  */
  YYSYMBOL_expression3 = 203,              /* expression3  */
  YYSYMBOL_expression4 = 204,              /* expression4  */
  YYSYMBOL_expression5 = 205,              /* expression5  */
  YYSYMBOL_expression6 = 206,              /* expression6  */
  YYSYMBOL_expression7 = 207,              /* expression7  */
  YYSYMBOL_expression8 = 208               /* expression8  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 410 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"


#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int m68kasm_lex(M68KASM_STYPE *yylval_param, void *yyscanner);
void m68kasm_warning(void *scanner, Statement *statement, const char *message);
void m68kasm_error(void *scanner, Statement *statement, const char *message);

static cc_bool DoExpression(Expression *expression, ExpressionType type, Expression *left_expression, Expression *right_expression);
static void DestroyIdentifierList(IdentifierListNode *node);
static void DestroyExpressionList(ExpressionListNode *node);
static void DestroyOperand(Operand *operand);
static void DestroyStatementInstruction(StatementInstruction *instruction);


#line 336 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined M68KASM_STYPE_IS_TRIVIAL && M68KASM_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  193
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  188
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  234
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  322

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   423


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   183,     2,   176,     2,   181,   182,     2,
     172,   173,   180,   174,   169,   175,   171,   177,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     178,   170,   179,     2,   187,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   185,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   184,     2,   186,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168
};

#if M68KASM_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   631,   631,   634,   639,   644,   650,   656,   663,   668,
     676,   683,   691,   696,   700,   705,   710,   715,   720,   724,
     729,   734,   739,   744,   749,   753,   757,   761,   766,   770,
     774,   780,   788,   797,   801,   807,   812,   819,   836,   864,
     881,   909,   915,   921,   930,   935,   941,   949,   953,   957,
     961,   965,   969,   973,   977,   981,   985,   989,   993,   997,
    1001,  1005,  1009,  1013,  1017,  1021,  1025,  1029,  1033,  1037,
    1041,  1045,  1049,  1053,  1057,  1061,  1065,  1069,  1073,  1077,
    1081,  1085,  1089,  1093,  1097,  1101,  1105,  1109,  1113,  1118,
    1123,  1128,  1133,  1138,  1143,  1148,  1153,  1158,  1163,  1168,
    1173,  1178,  1183,  1188,  1193,  1198,  1203,  1208,  1213,  1218,
    1223,  1228,  1233,  1238,  1243,  1248,  1253,  1258,  1263,  1268,
    1273,  1277,  1281,  1286,  1291,  1296,  1301,  1306,  1311,  1316,
    1321,  1326,  1331,  1336,  1341,  1346,  1351,  1355,  1359,  1363,
    1367,  1371,  1375,  1379,  1383,  1387,  1391,  1395,  1399,  1403,
    1407,  1411,  1415,  1419,  1423,  1427,  1431,  1435,  1439,  1443,
    1447,  1451,  1455,  1459,  1466,  1470,  1474,  1478,  1486,  1491,
    1496,  1501,  1507,  1517,  1526,  1537,  1547,  1552,  1561,  1569,
    1579,  1589,  1605,  1609,  1613,  1618,  1624,  1631,  1662,  1666,
    1673,  1677,  1702,  1706,  1719,  1724,  1730,  1738,  1742,  1747,
    1752,  1760,  1764,  1769,  1774,  1779,  1787,  1791,  1796,  1804,
    1808,  1813,  1818,  1826,  1830,  1835,  1840,  1845,  1853,  1857,
    1862,  1870,  1874,  1878,  1883,  1889,  1897,  1902,  1907,  1912,
    1935,  1940,  1944,  1948,  1952
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_DIRECTIVE_ORI",
  "TOKEN_DIRECTIVE_ANDI", "TOKEN_DIRECTIVE_SUBI", "TOKEN_DIRECTIVE_ADDI",
  "TOKEN_DIRECTIVE_EORI", "TOKEN_DIRECTIVE_CMPI", "TOKEN_DIRECTIVE_BTST",
  "TOKEN_DIRECTIVE_BCHG", "TOKEN_DIRECTIVE_BCLR", "TOKEN_DIRECTIVE_BSET",
  "TOKEN_DIRECTIVE_MOVEP", "TOKEN_DIRECTIVE_MOVEA", "TOKEN_DIRECTIVE_MOVE",
  "TOKEN_DIRECTIVE_NEGX", "TOKEN_DIRECTIVE_CLR", "TOKEN_DIRECTIVE_NEG",
  "TOKEN_DIRECTIVE_NOT", "TOKEN_DIRECTIVE_EXT", "TOKEN_DIRECTIVE_NBCD",
  "TOKEN_DIRECTIVE_SWAP", "TOKEN_DIRECTIVE_PEA", "TOKEN_DIRECTIVE_ILLEGAL",
  "TOKEN_DIRECTIVE_TAS", "TOKEN_DIRECTIVE_TST", "TOKEN_DIRECTIVE_TRAP",
  "TOKEN_DIRECTIVE_LINK", "TOKEN_DIRECTIVE_UNLK", "TOKEN_DIRECTIVE_RESET",
  "TOKEN_DIRECTIVE_NOP", "TOKEN_DIRECTIVE_STOP", "TOKEN_DIRECTIVE_RTE",
  "TOKEN_DIRECTIVE_RTS", "TOKEN_DIRECTIVE_TRAPV", "TOKEN_DIRECTIVE_RTR",
  "TOKEN_DIRECTIVE_JSR", "TOKEN_DIRECTIVE_JMP", "TOKEN_DIRECTIVE_MOVEM",
  "TOKEN_DIRECTIVE_LEA", "TOKEN_DIRECTIVE_CHK", "TOKEN_DIRECTIVE_ADDQ",
  "TOKEN_DIRECTIVE_SUBQ", "TOKEN_DIRECTIVE_ST", "TOKEN_DIRECTIVE_SF",
  "TOKEN_DIRECTIVE_SHI", "TOKEN_DIRECTIVE_SLS", "TOKEN_DIRECTIVE_SCC",
  "TOKEN_DIRECTIVE_SCS", "TOKEN_DIRECTIVE_SNE", "TOKEN_DIRECTIVE_SEQ",
  "TOKEN_DIRECTIVE_SVC", "TOKEN_DIRECTIVE_SVS", "TOKEN_DIRECTIVE_SPL",
  "TOKEN_DIRECTIVE_SMI", "TOKEN_DIRECTIVE_SGE", "TOKEN_DIRECTIVE_SLT",
  "TOKEN_DIRECTIVE_SGT", "TOKEN_DIRECTIVE_SLE", "TOKEN_DIRECTIVE_DBT",
  "TOKEN_DIRECTIVE_DBF", "TOKEN_DIRECTIVE_DBHI", "TOKEN_DIRECTIVE_DBLS",
  "TOKEN_DIRECTIVE_DBCC", "TOKEN_DIRECTIVE_DBCS", "TOKEN_DIRECTIVE_DBNE",
  "TOKEN_DIRECTIVE_DBEQ", "TOKEN_DIRECTIVE_DBVC", "TOKEN_DIRECTIVE_DBVS",
  "TOKEN_DIRECTIVE_DBPL", "TOKEN_DIRECTIVE_DBMI", "TOKEN_DIRECTIVE_DBGE",
  "TOKEN_DIRECTIVE_DBLT", "TOKEN_DIRECTIVE_DBGT", "TOKEN_DIRECTIVE_DBLE",
  "TOKEN_DIRECTIVE_BRA", "TOKEN_DIRECTIVE_BSR", "TOKEN_DIRECTIVE_BHI",
  "TOKEN_DIRECTIVE_BLS", "TOKEN_DIRECTIVE_BCC", "TOKEN_DIRECTIVE_BCS",
  "TOKEN_DIRECTIVE_BNE", "TOKEN_DIRECTIVE_BEQ", "TOKEN_DIRECTIVE_BVC",
  "TOKEN_DIRECTIVE_BVS", "TOKEN_DIRECTIVE_BPL", "TOKEN_DIRECTIVE_BMI",
  "TOKEN_DIRECTIVE_BGE", "TOKEN_DIRECTIVE_BLT", "TOKEN_DIRECTIVE_BGT",
  "TOKEN_DIRECTIVE_BLE", "TOKEN_DIRECTIVE_MOVEQ", "TOKEN_DIRECTIVE_DIVU",
  "TOKEN_DIRECTIVE_DIVS", "TOKEN_DIRECTIVE_SBCD", "TOKEN_DIRECTIVE_OR",
  "TOKEN_DIRECTIVE_SUB", "TOKEN_DIRECTIVE_SUBX", "TOKEN_DIRECTIVE_SUBA",
  "TOKEN_DIRECTIVE_EOR", "TOKEN_DIRECTIVE_CMPM", "TOKEN_DIRECTIVE_CMP",
  "TOKEN_DIRECTIVE_CMPA", "TOKEN_DIRECTIVE_MULU", "TOKEN_DIRECTIVE_MULS",
  "TOKEN_DIRECTIVE_ABCD", "TOKEN_DIRECTIVE_EXG", "TOKEN_DIRECTIVE_AND",
  "TOKEN_DIRECTIVE_ADD", "TOKEN_DIRECTIVE_ADDX", "TOKEN_DIRECTIVE_ADDA",
  "TOKEN_DIRECTIVE_ASL", "TOKEN_DIRECTIVE_ASR", "TOKEN_DIRECTIVE_LSL",
  "TOKEN_DIRECTIVE_LSR", "TOKEN_DIRECTIVE_ROXL", "TOKEN_DIRECTIVE_ROXR",
  "TOKEN_DIRECTIVE_ROL", "TOKEN_DIRECTIVE_ROR", "TOKEN_DIRECTIVE_ORG",
  "TOKEN_DIRECTIVE_DC", "TOKEN_DIRECTIVE_DS", "TOKEN_DIRECTIVE_DCB",
  "TOKEN_DIRECTIVE_REPT", "TOKEN_DIRECTIVE_ENDR", "TOKEN_DIRECTIVE_MACRO",
  "TOKEN_DIRECTIVE_MACROS", "TOKEN_DIRECTIVE_ENDM",
  "TOKEN_DIRECTIVE_INCLUDE", "TOKEN_DIRECTIVE_INCBIN",
  "TOKEN_DIRECTIVE_EQU", "TOKEN_DIRECTIVE_SET", "TOKEN_DIRECTIVE_IF",
  "TOKEN_DIRECTIVE_ELSEIF", "TOKEN_DIRECTIVE_ELSE", "TOKEN_DIRECTIVE_ENDC",
  "TOKEN_DIRECTIVE_WHILE", "TOKEN_DIRECTIVE_ENDW", "TOKEN_DIRECTIVE_EVEN",
  "TOKEN_DIRECTIVE_CNOP", "TOKEN_DIRECTIVE_INFORM", "TOKEN_DIRECTIVE_END",
  "TOKEN_DIRECTIVE_RS", "TOKEN_DIRECTIVE_RSSET", "TOKEN_DIRECTIVE_RSRESET",
  "TOKEN_SIZE_BYTE", "TOKEN_SIZE_SHORT", "TOKEN_SIZE_WORD",
  "TOKEN_SIZE_LONGWORD", "TOKEN_DATA_REGISTER", "TOKEN_ADDRESS_REGISTER",
  "TOKEN_NUMBER", "TOKEN_IDENTIFIER", "TOKEN_LOCAL_IDENTIFIER",
  "TOKEN_STRING", "TOKEN_STATUS_REGISTER", "TOKEN_CONDITION_CODE_REGISTER",
  "TOKEN_USER_STACK_POINTER_REGISTER", "TOKEN_PROGRAM_COUNTER",
  "TOKEN_LOGICAL_AND", "TOKEN_LOGICAL_OR", "TOKEN_EQUALITY",
  "TOKEN_INEQUALITY", "TOKEN_LESS_OR_EQUAL", "TOKEN_MORE_OR_EQUAL",
  "TOKEN_LEFT_SHIFT", "TOKEN_RIGHT_SHIFT", "TOKEN_STRLEN", "','", "'='",
  "'.'", "'('", "')'", "'+'", "'-'", "'#'", "'/'", "'<'", "'>'", "'*'",
  "'%'", "'&'", "'!'", "'|'", "'^'", "'~'", "'@'", "$accept", "statement",
  "expression_list", "identifier_list", "instruction", "full_opcode",
  "opcode", "size", "operand", "register_list", "register_span",
  "data_or_address_register", "expression", "expression1", "expression2",
  "expression3", "expression4", "expression5", "expression6",
  "expression7", "expression8", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-251)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     191,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,   -23,    37,
      37,    37,   -23,  -251,  -140,  -140,  -251,  -122,   -98,   -23,
     -23,   -23,   -23,  -251,  -251,   -23,  -251,  -251,   -23,   -23,
    -251,    37,   -23,  -251,   -23,    63,  -251,  -110,   -12,  -251,
     -85,  -251,  -251,   -87,   -23,   -23,   -23,  -251,   -23,   -23,
    -251,   -66,    12,  -160,   -76,  -109,     5,  -116,  -251,  -251,
    -251,  -251,  -251,  -251,   -23,   -23,   -23,   -66,  -251,   -68,
     -68,  -251,   -60,   -66,   -66,   -66,   -66,   -66,   -41,   -14,
     -23,   -66,   -66,  -251,  -251,  -251,  -251,  -251,  -251,   -62,
     185,   -23,   -31,  -251,   -70,   -32,  -105,  -251,  -251,  -251,
     -11,  -135,  -251,  -251,  -251,  -251,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,   -21,   -66,   -66,     7,
      -3,   -23,   -23,    -2,   -66,  -163,   -15,  -124,   -72,   -66,
    -110,   -46,   -46,  -129,   -17,  -251,    12,    12,  -160,  -160,
    -160,   -76,   -76,   -76,   -76,  -109,  -109,     5,     5,     5,
    -116,  -116,  -116,  -116,  -251,  -251,   -23,   -23,  -251,     9,
     -66,    22,   -46,   -16,   -46,    37,   168,  -251,  -251,  -251,
    -138,   -95,  -251,   -66,   -66,   -23,   -23,    -7,  -251,   196,
    -251,  -251,   -46,  -251,   -46,  -251,   -66,   -21,  -251,   181,
    -251,   182,   200,   228,  -251,  -251,  -251,   183,  -251,   189,
    -251,  -251
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,     0,     0,
       0,     0,     0,    13,    14,    16,    18,     0,     0,     0,
       0,     0,    24,    25,    26,     0,    28,    29,     0,     0,
      33,     0,     0,    36,     0,     0,     3,    41,    44,   226,
     227,   228,   230,     0,     0,     0,     0,   231,     0,     0,
     232,     4,   194,   197,   201,   206,   209,   213,   218,   221,
     164,   165,   166,   167,     0,     0,     0,    12,    39,    15,
      17,     8,     9,    19,    20,    22,    23,    27,     0,     0,
       0,    35,    21,     1,   192,   193,   182,   183,   184,     0,
       0,     0,    42,   187,   188,   190,   185,    45,    46,   229,
       0,     0,   222,   223,   225,   224,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,    37,     6,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,   181,
       0,     0,     0,     0,     0,   233,   195,   196,   199,   200,
     198,   203,   205,   202,   204,   207,   208,   211,   210,   212,
     214,   215,   216,   217,   219,   220,     0,     0,    40,    10,
      30,    31,     0,   168,     0,   233,     0,    43,   189,   191,
       0,     0,   234,    38,     7,     0,     0,     0,   169,     0,
     186,   170,     0,   171,     0,   176,    11,    32,   174,     0,
     179,     0,     0,     0,   172,   177,   175,     0,   180,     0,
     173,   178
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -251,  -251,    62,   238,  -251,  -251,  -251,  -120,   114,   115,
    -251,  -250,  -115,  -100,   -47,   157,  -103,   123,   152,  -147,
    -251
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,   145,   236,   179,   146,   147,   148,   174,   202,   203,
     204,   205,   206,   162,   163,   164,   165,   166,   167,   168,
     169
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     175,   176,   289,   161,   221,   222,   282,   177,   212,   213,
     283,   214,   215,   178,   183,   184,   185,   186,   223,   224,
     187,   190,   290,   188,   189,   216,   217,   191,   208,   192,
     291,   302,   297,   181,   299,   303,   216,   217,   255,   211,
     194,   195,   149,   150,   151,   152,   196,   197,   198,   285,
     234,   235,   312,   213,   313,   216,   217,   182,   153,   237,
     238,   239,   199,   193,   155,   200,   201,   253,   227,   209,
     157,   228,   229,   158,   304,   244,   159,   160,   305,   286,
     149,   150,   151,   152,   247,   210,   249,   274,   275,   245,
     149,   150,   151,   152,   216,   217,   153,   246,   225,   226,
     154,   240,   155,   156,   194,   195,   153,   251,   157,   241,
     154,   158,   155,   156,   159,   160,   256,   257,   157,   216,
     217,   158,   265,   266,   159,   160,   279,   280,   242,   149,
     150,   151,   152,   211,   170,   171,   172,   173,   250,   170,
     171,   172,   173,   252,   254,   153,   216,   217,   276,   154,
     278,   155,   156,   281,   284,   243,   292,   157,   298,   207,
     158,   293,   294,   159,   160,   300,   308,   216,   217,   216,
     217,   258,   259,   260,   218,   219,   277,   309,   295,   311,
     306,   237,   220,   170,   171,   172,   173,   230,   231,   232,
     233,   296,   317,   319,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   149,   150,   151,
     152,   301,   170,   171,   172,   173,   170,   171,   172,   173,
     267,   268,   269,   153,   314,   315,   320,   248,   307,   155,
     156,   144,   321,   180,   287,   157,   288,     0,   158,   310,
       0,   159,   160,   316,   170,   171,   172,   173,   261,   262,
     263,   264,   270,   271,   272,   273,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   318
};

static const yytype_int16 yycheck[] =
{
     120,   121,   252,   118,   164,   165,   169,   122,   155,   156,
     173,   158,   159,   153,   129,   130,   131,   132,   178,   179,
     135,   141,   151,   138,   139,   160,   161,   142,   148,   144,
     159,   169,   282,   155,   284,   173,   160,   161,   173,   154,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   173,
     166,   167,   302,   200,   304,   160,   161,   155,   168,   174,
     175,   176,   172,     0,   174,   175,   176,   172,   177,   154,
     180,   180,   181,   183,   169,   190,   186,   187,   173,   151,
     152,   153,   154,   155,   199,   172,   201,   234,   235,   151,
     152,   153,   154,   155,   160,   161,   168,   159,   174,   175,
     172,   169,   174,   175,   150,   151,   168,   177,   180,   169,
     172,   183,   174,   175,   186,   187,   216,   217,   180,   160,
     161,   183,   225,   226,   186,   187,   241,   242,   169,   152,
     153,   154,   155,   248,   146,   147,   148,   149,   169,   146,
     147,   148,   149,   175,   155,   168,   160,   161,   169,   172,
     153,   174,   175,   155,   169,   169,   173,   180,   174,   171,
     183,   276,   277,   186,   187,   285,   173,   160,   161,   160,
     161,   218,   219,   220,   162,   163,   169,   297,   169,   299,
     295,   296,   170,   146,   147,   148,   149,   182,   183,   184,
     185,   169,   312,   313,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   152,   153,   154,
     155,   173,   146,   147,   148,   149,   146,   147,   148,   149,
     227,   228,   229,   168,   173,   173,   173,   172,   296,   174,
     175,   170,   173,   125,   250,   180,   251,    -1,   183,   173,
      -1,   186,   187,   173,   146,   147,   148,   149,   221,   222,
     223,   224,   230,   231,   232,   233,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   173
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   170,   189,   192,   193,   194,   152,
     153,   154,   155,   168,   172,   174,   175,   180,   183,   186,
     187,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     146,   147,   148,   149,   195,   195,   195,   200,   153,   191,
     191,   155,   155,   200,   200,   200,   200,   200,   200,   200,
     195,   200,   200,     0,   150,   151,   156,   157,   158,   172,
     175,   176,   196,   197,   198,   199,   200,   171,   195,   154,
     172,   200,   207,   207,   207,   207,   160,   161,   162,   163,
     170,   164,   165,   178,   179,   174,   175,   177,   180,   181,
     182,   183,   184,   185,   166,   167,   190,   200,   200,   200,
     169,   169,   169,   169,   200,   151,   159,   200,   172,   200,
     169,   177,   175,   172,   155,   173,   201,   201,   202,   202,
     202,   203,   203,   203,   203,   204,   204,   205,   205,   205,
     206,   206,   206,   206,   207,   207,   169,   169,   153,   200,
     200,   155,   169,   173,   169,   173,   151,   196,   197,   199,
     151,   159,   173,   200,   200,   169,   169,   199,   174,   199,
     195,   173,   169,   173,   169,   173,   200,   190,   173,   195,
     173,   195,   199,   199,   173,   173,   173,   195,   173,   195,
     173,   173
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   188,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   190,   190,   191,
     191,   192,   192,   192,   193,   193,   193,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   195,   195,   195,   195,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   197,   197,
     198,   198,   199,   199,   200,   200,   200,   201,   201,   201,
     201,   202,   202,   202,   202,   202,   203,   203,   203,   204,
     204,   204,   204,   205,   205,   205,   205,   205,   206,   206,
     206,   207,   207,   207,   207,   207,   208,   208,   208,   208,
     208,   208,   208,   208,   208
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     1,     2,     3,     3,     5,     2,     2,
       4,     6,     2,     1,     1,     2,     1,     2,     1,     2,
       2,     2,     2,     2,     1,     1,     1,     2,     1,     1,
       4,     4,     6,     1,     3,     2,     1,     1,     3,     1,
       3,     1,     2,     4,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
       4,     4,     6,     7,     5,     6,     4,     6,     7,     5,
       6,     2,     1,     1,     1,     1,     4,     1,     1,     3,
       1,     3,     1,     1,     1,     3,     3,     1,     3,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     2,     2,     2,     2,     1,     1,     1,     2,
       1,     1,     1,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = M68KASM_EMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == M68KASM_EMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, statement, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use M68KASM_error or M68KASM_UNDEF. */
#define YYERRCODE M68KASM_UNDEF


/* Enable debugging if requested.  */
#if M68KASM_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner, statement); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner, Statement *statement)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  YY_USE (statement);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner, Statement *statement)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner, statement);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner, Statement *statement)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner, statement);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner, statement); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !M68KASM_DEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !M68KASM_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner, Statement *statement)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  YY_USE (statement);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_TOKEN_IDENTIFIER: /* TOKEN_IDENTIFIER  */
#line 619 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { free(((*yyvaluep).string)); }
#line 1615 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_TOKEN_LOCAL_IDENTIFIER: /* TOKEN_LOCAL_IDENTIFIER  */
#line 619 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { free(((*yyvaluep).string)); }
#line 1621 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_TOKEN_STRING: /* TOKEN_STRING  */
#line 619 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { free(((*yyvaluep).string)); }
#line 1627 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression_list: /* expression_list  */
#line 621 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpressionList(((*yyvaluep).list_metadata).head); }
#line 1633 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_identifier_list: /* identifier_list  */
#line 622 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyIdentifierList(((*yyvaluep).list_metadata).head); }
#line 1639 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_operand: /* operand  */
#line 620 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyOperand(&((*yyvaluep).operand)); }
#line 1645 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression: /* expression  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1651 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression1: /* expression1  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1657 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression2: /* expression2  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1663 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression3: /* expression3  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1669 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression4: /* expression4  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1675 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression5: /* expression5  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1681 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression6: /* expression6  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1687 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression7: /* expression7  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1693 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

    case YYSYMBOL_expression8: /* expression8  */
#line 623 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
            { DestroyExpression(&((*yyvaluep).expression)); }
#line 1699 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner, Statement *statement)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = M68KASM_EMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == M68KASM_EMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= M68KASM_EOF)
    {
      yychar = M68KASM_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == M68KASM_error)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = M68KASM_UNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = M68KASM_EMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* statement: %empty  */
#line 631 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_EMPTY;
	}
#line 1980 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 3: /* statement: instruction  */
#line 635 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_INSTRUCTION;
		statement->shared.instruction = (yyvsp[0].instruction);
	}
#line 1989 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 4: /* statement: TOKEN_DIRECTIVE_ORG expression  */
#line 640 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ORG;
		statement->shared.org.value = (yyvsp[0].expression);
	}
#line 1998 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 5: /* statement: TOKEN_DIRECTIVE_DC size expression_list  */
#line 645 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_DC;
		statement->shared.dc.size = (yyvsp[-1].size);
		statement->shared.dc.values = (yyvsp[0].list_metadata).head;
	}
#line 2008 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 6: /* statement: TOKEN_DIRECTIVE_DS size expression  */
#line 651 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
    {
        statement->type = STATEMENT_TYPE_DS;
        statement->shared.ds.size = (yyvsp[-1].size);
        statement->shared.ds.value = (yyvsp[0].expression);
    }
#line 2018 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 7: /* statement: TOKEN_DIRECTIVE_DCB size expression ',' expression  */
#line 657 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_DCB;
		statement->shared.dcb.size = (yyvsp[-3].size);
		statement->shared.dcb.repetitions = (yyvsp[-2].expression);
		statement->shared.dcb.value = (yyvsp[0].expression);
	}
#line 2029 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 8: /* statement: TOKEN_DIRECTIVE_INCLUDE TOKEN_STRING  */
#line 664 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_INCLUDE;
		statement->shared.include.path = (yyvsp[0].string);
	}
#line 2038 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 9: /* statement: TOKEN_DIRECTIVE_INCBIN TOKEN_STRING  */
#line 669 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_INCBIN;
		statement->shared.incbin.path = (yyvsp[0].string);
		statement->shared.incbin.start.type = EXPRESSION_NUMBER;
		statement->shared.incbin.start.shared.unsigned_long = 0;
		statement->shared.incbin.has_length = cc_false;
	}
#line 2050 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 10: /* statement: TOKEN_DIRECTIVE_INCBIN TOKEN_STRING ',' expression  */
#line 677 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_INCBIN;
		statement->shared.incbin.path = (yyvsp[-2].string);
		statement->shared.incbin.start = (yyvsp[0].expression);
		statement->shared.incbin.has_length = cc_false;
	}
#line 2061 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 11: /* statement: TOKEN_DIRECTIVE_INCBIN TOKEN_STRING ',' expression ',' expression  */
#line 684 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_INCBIN;
		statement->shared.incbin.path = (yyvsp[-4].string);
		statement->shared.incbin.start = (yyvsp[-2].expression);
		statement->shared.incbin.has_length = cc_true;
		statement->shared.incbin.length = (yyvsp[0].expression);
	}
#line 2073 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 12: /* statement: TOKEN_DIRECTIVE_REPT expression  */
#line 692 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_REPT;
		statement->shared.rept.repetitions = (yyvsp[0].expression);
	}
#line 2082 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 13: /* statement: TOKEN_DIRECTIVE_ENDR  */
#line 697 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ENDR;
	}
#line 2090 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 14: /* statement: TOKEN_DIRECTIVE_MACRO  */
#line 701 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_MACRO;
		statement->shared.macro.parameter_names = NULL;
	}
#line 2099 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 15: /* statement: TOKEN_DIRECTIVE_MACRO identifier_list  */
#line 706 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_MACRO;
		statement->shared.macro.parameter_names = (yyvsp[0].list_metadata).head;
	}
#line 2108 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 16: /* statement: TOKEN_DIRECTIVE_MACROS  */
#line 711 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_MACROS;
		statement->shared.macro.parameter_names = NULL;
	}
#line 2117 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 17: /* statement: TOKEN_DIRECTIVE_MACROS identifier_list  */
#line 716 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_MACROS;
		statement->shared.macro.parameter_names = (yyvsp[0].list_metadata).head;
	}
#line 2126 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 18: /* statement: TOKEN_DIRECTIVE_ENDM  */
#line 721 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ENDM;
	}
#line 2134 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 19: /* statement: TOKEN_DIRECTIVE_EQU expression  */
#line 725 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_EQU;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2143 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 20: /* statement: TOKEN_DIRECTIVE_SET expression  */
#line 730 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_SET;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2152 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 21: /* statement: '=' expression  */
#line 735 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_SET;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2161 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 22: /* statement: TOKEN_DIRECTIVE_IF expression  */
#line 740 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_IF;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2170 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 23: /* statement: TOKEN_DIRECTIVE_ELSEIF expression  */
#line 745 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ELSEIF;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2179 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 24: /* statement: TOKEN_DIRECTIVE_ELSEIF  */
#line 750 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ELSE;
	}
#line 2187 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 25: /* statement: TOKEN_DIRECTIVE_ELSE  */
#line 754 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ELSE;
	}
#line 2195 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 26: /* statement: TOKEN_DIRECTIVE_ENDC  */
#line 758 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ENDC;
	}
#line 2203 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 27: /* statement: TOKEN_DIRECTIVE_WHILE expression  */
#line 762 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_WHILE;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2212 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 28: /* statement: TOKEN_DIRECTIVE_ENDW  */
#line 767 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_ENDW;
	}
#line 2220 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 29: /* statement: TOKEN_DIRECTIVE_EVEN  */
#line 771 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_EVEN;
	}
#line 2228 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 30: /* statement: TOKEN_DIRECTIVE_CNOP expression ',' expression  */
#line 775 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_CNOP;
		statement->shared.cnop.offset = (yyvsp[-2].expression);
		statement->shared.cnop.size_boundary = (yyvsp[0].expression);
	}
#line 2238 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 31: /* statement: TOKEN_DIRECTIVE_INFORM expression ',' TOKEN_STRING  */
#line 781 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(void)(yyvsp[-2].expression);

		/* TODO - Severity level(?) */
		statement->type = STATEMENT_TYPE_INFORM;
		statement->shared.inform.message = (yyvsp[0].string);
	}
#line 2250 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 32: /* statement: TOKEN_DIRECTIVE_INFORM expression ',' TOKEN_STRING ',' expression_list  */
#line 789 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(void)(yyvsp[-4].expression);
		(void)(yyvsp[0].list_metadata);

		/* TODO - Severity level(?) and parameters */
		statement->type = STATEMENT_TYPE_INFORM;
		statement->shared.inform.message = (yyvsp[-2].string);
	}
#line 2263 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 33: /* statement: TOKEN_DIRECTIVE_END  */
#line 798 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_END;
	}
#line 2271 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 34: /* statement: TOKEN_DIRECTIVE_RS size expression  */
#line 802 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_RS;
		statement->shared.rs.size = (yyvsp[-1].size);
		statement->shared.rs.length = (yyvsp[0].expression);
	}
#line 2281 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 35: /* statement: TOKEN_DIRECTIVE_RSSET expression  */
#line 808 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_RSSET;
		statement->shared.expression = (yyvsp[0].expression);
	}
#line 2290 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 36: /* statement: TOKEN_DIRECTIVE_RSRESET  */
#line 813 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		statement->type = STATEMENT_TYPE_RSRESET;
	}
#line 2298 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 37: /* expression_list: expression  */
#line 820 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		ExpressionListNode *node = malloc(sizeof(ExpressionListNode));

		if (node == NULL)
		{
			DestroyExpression(&(yyvsp[0].expression));
			YYNOMEM;
		}
		else
		{
			node->expression = (yyvsp[0].expression);
			node->next = NULL;
		}

		(yyval.list_metadata).head = (yyval.list_metadata).tail = node;
	}
#line 2319 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 38: /* expression_list: expression_list ',' expression  */
#line 837 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		ExpressionListNode *node = malloc(sizeof(ExpressionListNode));

		(yyval.list_metadata) = (yyvsp[-2].list_metadata);

		if (node == NULL)
		{
			DestroyExpressionList((yyvsp[-2].list_metadata).head);
			DestroyExpression(&(yyvsp[0].expression));
			YYNOMEM;
		}
		else
		{
			node->expression = (yyvsp[0].expression);
			node->next = NULL;

			if ((yyval.list_metadata).head == NULL)
				(yyval.list_metadata).head = node;
			else
				((ExpressionListNode*)(yyval.list_metadata).tail)->next = node;

			(yyval.list_metadata).tail = node;
		}
	}
#line 2348 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 39: /* identifier_list: TOKEN_IDENTIFIER  */
#line 865 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		IdentifierListNode *node = malloc(sizeof(IdentifierListNode));

		if (node == NULL)
		{
			free((yyvsp[0].string));
			YYNOMEM;
		}
		else
		{
			node->identifier = (yyvsp[0].string);
			node->next = NULL;
		}

		(yyval.list_metadata).head = (yyval.list_metadata).tail = node;
	}
#line 2369 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 40: /* identifier_list: identifier_list ',' TOKEN_IDENTIFIER  */
#line 882 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		IdentifierListNode *node = malloc(sizeof(IdentifierListNode));

		(yyval.list_metadata) = (yyvsp[-2].list_metadata);

		if (node == NULL)
		{
			DestroyIdentifierList((yyvsp[-2].list_metadata).head);
			free(&(yyvsp[0].string));
			YYNOMEM;
		}
		else
		{
			node->identifier = (yyvsp[0].string);
			node->next = NULL;

			if ((yyval.list_metadata).head == NULL)
				(yyval.list_metadata).head = node;
			else
				((IdentifierListNode*)(yyval.list_metadata).tail)->next = node;

			(yyval.list_metadata).tail = node;
		}
	}
#line 2398 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 41: /* instruction: full_opcode  */
#line 910 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.instruction).opcode = (yyvsp[0].opcode);
		(yyval.instruction).operands[0].type = 0;
		(yyval.instruction).operands[1].type = 0;
	}
#line 2408 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 42: /* instruction: full_opcode operand  */
#line 916 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.instruction).opcode = (yyvsp[-1].opcode);
		(yyval.instruction).operands[0] = (yyvsp[0].operand);
		(yyval.instruction).operands[1].type = 0;
	}
#line 2418 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 43: /* instruction: full_opcode operand ',' operand  */
#line 922 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.instruction).opcode = (yyvsp[-3].opcode);
		(yyval.instruction).operands[0] = (yyvsp[-2].operand);
		(yyval.instruction).operands[1] = (yyvsp[0].operand);
	}
#line 2428 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 44: /* full_opcode: opcode  */
#line 931 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode) = (yyvsp[0].opcode);
		(yyval.opcode).size = SIZE_UNDEFINED;
	}
#line 2437 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 45: /* full_opcode: opcode '.'  */
#line 936 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode) = (yyvsp[-1].opcode);
		(yyval.opcode).size = SIZE_UNDEFINED;
		m68kasm_warning(scanner, statement, "Opcode has a dot but no size; either remove the dot or add an explicit size.");
	}
#line 2447 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 46: /* full_opcode: opcode size  */
#line 942 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode) = (yyvsp[-1].opcode);
		(yyval.opcode).size = (yyvsp[0].size);
	}
#line 2456 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 47: /* opcode: TOKEN_DIRECTIVE_ORI  */
#line 950 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ORI;
	}
#line 2464 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 48: /* opcode: TOKEN_DIRECTIVE_ANDI  */
#line 954 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ANDI;
	}
#line 2472 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 49: /* opcode: TOKEN_DIRECTIVE_SUBI  */
#line 958 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SUBI;
	}
#line 2480 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 50: /* opcode: TOKEN_DIRECTIVE_ADDI  */
#line 962 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ADDI;
	}
#line 2488 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 51: /* opcode: TOKEN_DIRECTIVE_EORI  */
#line 966 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_EORI;
	}
#line 2496 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 52: /* opcode: TOKEN_DIRECTIVE_CMPI  */
#line 970 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_CMPI;
	}
#line 2504 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 53: /* opcode: TOKEN_DIRECTIVE_BTST  */
#line 974 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_BTST_STATIC;
	}
#line 2512 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 54: /* opcode: TOKEN_DIRECTIVE_BCHG  */
#line 978 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_BCHG_STATIC;
	}
#line 2520 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 55: /* opcode: TOKEN_DIRECTIVE_BCLR  */
#line 982 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_BCLR_STATIC;
	}
#line 2528 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 56: /* opcode: TOKEN_DIRECTIVE_BSET  */
#line 986 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_BSET_STATIC;
	}
#line 2536 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 57: /* opcode: TOKEN_DIRECTIVE_MOVEP  */
#line 990 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MOVEP_TO_REG;
	}
#line 2544 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 58: /* opcode: TOKEN_DIRECTIVE_MOVEA  */
#line 994 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MOVEA;
	}
#line 2552 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 59: /* opcode: TOKEN_DIRECTIVE_MOVE  */
#line 998 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MOVE;
	}
#line 2560 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 60: /* opcode: TOKEN_DIRECTIVE_NEGX  */
#line 1002 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_NEGX;
	}
#line 2568 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 61: /* opcode: TOKEN_DIRECTIVE_CLR  */
#line 1006 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_CLR;
	}
#line 2576 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 62: /* opcode: TOKEN_DIRECTIVE_NEG  */
#line 1010 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_NEG;
	}
#line 2584 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 63: /* opcode: TOKEN_DIRECTIVE_NOT  */
#line 1014 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_NOT;
	}
#line 2592 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 64: /* opcode: TOKEN_DIRECTIVE_EXT  */
#line 1018 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_EXT;
	}
#line 2600 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 65: /* opcode: TOKEN_DIRECTIVE_NBCD  */
#line 1022 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_NBCD;
	}
#line 2608 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 66: /* opcode: TOKEN_DIRECTIVE_SWAP  */
#line 1026 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SWAP;
	}
#line 2616 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 67: /* opcode: TOKEN_DIRECTIVE_PEA  */
#line 1030 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_PEA;
	}
#line 2624 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 68: /* opcode: TOKEN_DIRECTIVE_ILLEGAL  */
#line 1034 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ILLEGAL;
	}
#line 2632 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 69: /* opcode: TOKEN_DIRECTIVE_TAS  */
#line 1038 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_TAS;
	}
#line 2640 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 70: /* opcode: TOKEN_DIRECTIVE_TST  */
#line 1042 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_TST;
	}
#line 2648 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 71: /* opcode: TOKEN_DIRECTIVE_TRAP  */
#line 1046 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_TRAP;
	}
#line 2656 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 72: /* opcode: TOKEN_DIRECTIVE_LINK  */
#line 1050 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_LINK;
	}
#line 2664 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 73: /* opcode: TOKEN_DIRECTIVE_UNLK  */
#line 1054 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_UNLK;
	}
#line 2672 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 74: /* opcode: TOKEN_DIRECTIVE_RESET  */
#line 1058 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_RESET;
	}
#line 2680 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 75: /* opcode: TOKEN_DIRECTIVE_NOP  */
#line 1062 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_NOP;
	}
#line 2688 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 76: /* opcode: TOKEN_DIRECTIVE_STOP  */
#line 1066 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_STOP;
	}
#line 2696 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 77: /* opcode: TOKEN_DIRECTIVE_RTE  */
#line 1070 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_RTE;
	}
#line 2704 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 78: /* opcode: TOKEN_DIRECTIVE_RTS  */
#line 1074 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_RTS;
	}
#line 2712 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 79: /* opcode: TOKEN_DIRECTIVE_TRAPV  */
#line 1078 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_TRAPV;
	}
#line 2720 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 80: /* opcode: TOKEN_DIRECTIVE_RTR  */
#line 1082 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_RTR;
	}
#line 2728 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 81: /* opcode: TOKEN_DIRECTIVE_JSR  */
#line 1086 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_JSR;
	}
#line 2736 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 82: /* opcode: TOKEN_DIRECTIVE_JMP  */
#line 1090 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_JMP;
	}
#line 2744 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 83: /* opcode: TOKEN_DIRECTIVE_MOVEM  */
#line 1094 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MOVEM_TO_REGS;
	}
#line 2752 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 84: /* opcode: TOKEN_DIRECTIVE_LEA  */
#line 1098 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_LEA;
	}
#line 2760 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 85: /* opcode: TOKEN_DIRECTIVE_CHK  */
#line 1102 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_CHK;
	}
#line 2768 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 86: /* opcode: TOKEN_DIRECTIVE_ADDQ  */
#line 1106 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ADDQ;
	}
#line 2776 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 87: /* opcode: TOKEN_DIRECTIVE_SUBQ  */
#line 1110 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SUBQ;
	}
#line 2784 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 88: /* opcode: TOKEN_DIRECTIVE_ST  */
#line 1114 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_TRUE;
	}
#line 2793 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 89: /* opcode: TOKEN_DIRECTIVE_SF  */
#line 1119 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_FALSE;
	}
#line 2802 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 90: /* opcode: TOKEN_DIRECTIVE_SHI  */
#line 1124 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_HIGHER;
	}
#line 2811 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 91: /* opcode: TOKEN_DIRECTIVE_SLS  */
#line 1129 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_LOWER_OR_SAME;
	}
#line 2820 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 92: /* opcode: TOKEN_DIRECTIVE_SCC  */
#line 1134 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_CARRY_CLEAR;
	}
#line 2829 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 93: /* opcode: TOKEN_DIRECTIVE_SCS  */
#line 1139 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_CARRY_SET;
	}
#line 2838 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 94: /* opcode: TOKEN_DIRECTIVE_SNE  */
#line 1144 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_NOT_EQUAL;
	}
#line 2847 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 95: /* opcode: TOKEN_DIRECTIVE_SEQ  */
#line 1149 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_EQUAL;
	}
#line 2856 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 96: /* opcode: TOKEN_DIRECTIVE_SVC  */
#line 1154 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_OVERFLOW_CLEAR;
	}
#line 2865 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 97: /* opcode: TOKEN_DIRECTIVE_SVS  */
#line 1159 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_OVERFLOW_SET;
	}
#line 2874 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 98: /* opcode: TOKEN_DIRECTIVE_SPL  */
#line 1164 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_PLUS;
	}
#line 2883 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 99: /* opcode: TOKEN_DIRECTIVE_SMI  */
#line 1169 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_MINUS;
	}
#line 2892 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 100: /* opcode: TOKEN_DIRECTIVE_SGE  */
#line 1174 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_GREATER_OR_EQUAL;
	}
#line 2901 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 101: /* opcode: TOKEN_DIRECTIVE_SLT  */
#line 1179 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_LESS_THAN;
	}
#line 2910 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 102: /* opcode: TOKEN_DIRECTIVE_SGT  */
#line 1184 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_GREATER_THAN;
	}
#line 2919 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 103: /* opcode: TOKEN_DIRECTIVE_SLE  */
#line 1189 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Scc;
		(yyval.opcode).condition = CONDITION_LESS_OR_EQUAL;
	}
#line 2928 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 104: /* opcode: TOKEN_DIRECTIVE_DBT  */
#line 1194 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_TRUE;
	}
#line 2937 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 105: /* opcode: TOKEN_DIRECTIVE_DBF  */
#line 1199 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_FALSE;
	}
#line 2946 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 106: /* opcode: TOKEN_DIRECTIVE_DBHI  */
#line 1204 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_HIGHER;
	}
#line 2955 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 107: /* opcode: TOKEN_DIRECTIVE_DBLS  */
#line 1209 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_LOWER_OR_SAME;
	}
#line 2964 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 108: /* opcode: TOKEN_DIRECTIVE_DBCC  */
#line 1214 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_CARRY_CLEAR;
	}
#line 2973 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 109: /* opcode: TOKEN_DIRECTIVE_DBCS  */
#line 1219 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_CARRY_SET;
	}
#line 2982 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 110: /* opcode: TOKEN_DIRECTIVE_DBNE  */
#line 1224 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_NOT_EQUAL;
	}
#line 2991 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 111: /* opcode: TOKEN_DIRECTIVE_DBEQ  */
#line 1229 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_EQUAL;
	}
#line 3000 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 112: /* opcode: TOKEN_DIRECTIVE_DBVC  */
#line 1234 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_OVERFLOW_CLEAR;
	}
#line 3009 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 113: /* opcode: TOKEN_DIRECTIVE_DBVS  */
#line 1239 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_OVERFLOW_SET;
	}
#line 3018 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 114: /* opcode: TOKEN_DIRECTIVE_DBPL  */
#line 1244 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_PLUS;
	}
#line 3027 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 115: /* opcode: TOKEN_DIRECTIVE_DBMI  */
#line 1249 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_MINUS;
	}
#line 3036 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 116: /* opcode: TOKEN_DIRECTIVE_DBGE  */
#line 1254 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_GREATER_OR_EQUAL;
	}
#line 3045 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 117: /* opcode: TOKEN_DIRECTIVE_DBLT  */
#line 1259 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_LESS_THAN;
	}
#line 3054 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 118: /* opcode: TOKEN_DIRECTIVE_DBGT  */
#line 1264 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_GREATER_THAN;
	}
#line 3063 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 119: /* opcode: TOKEN_DIRECTIVE_DBLE  */
#line 1269 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DBcc;
		(yyval.opcode).condition = CONDITION_LESS_OR_EQUAL;
	}
#line 3072 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 120: /* opcode: TOKEN_DIRECTIVE_BRA  */
#line 1274 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_BRA;
	}
#line 3080 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 121: /* opcode: TOKEN_DIRECTIVE_BSR  */
#line 1278 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_BSR;
	}
#line 3088 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 122: /* opcode: TOKEN_DIRECTIVE_BHI  */
#line 1282 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_HIGHER;
	}
#line 3097 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 123: /* opcode: TOKEN_DIRECTIVE_BLS  */
#line 1287 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_LOWER_OR_SAME;
	}
#line 3106 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 124: /* opcode: TOKEN_DIRECTIVE_BCC  */
#line 1292 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_CARRY_CLEAR;
	}
#line 3115 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 125: /* opcode: TOKEN_DIRECTIVE_BCS  */
#line 1297 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_CARRY_SET;
	}
#line 3124 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 126: /* opcode: TOKEN_DIRECTIVE_BNE  */
#line 1302 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_NOT_EQUAL;
	}
#line 3133 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 127: /* opcode: TOKEN_DIRECTIVE_BEQ  */
#line 1307 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_EQUAL;
	}
#line 3142 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 128: /* opcode: TOKEN_DIRECTIVE_BVC  */
#line 1312 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_OVERFLOW_CLEAR;
	}
#line 3151 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 129: /* opcode: TOKEN_DIRECTIVE_BVS  */
#line 1317 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_OVERFLOW_SET;
	}
#line 3160 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 130: /* opcode: TOKEN_DIRECTIVE_BPL  */
#line 1322 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_PLUS;
	}
#line 3169 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 131: /* opcode: TOKEN_DIRECTIVE_BMI  */
#line 1327 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_MINUS;
	}
#line 3178 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 132: /* opcode: TOKEN_DIRECTIVE_BGE  */
#line 1332 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_GREATER_OR_EQUAL;
	}
#line 3187 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 133: /* opcode: TOKEN_DIRECTIVE_BLT  */
#line 1337 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_LESS_THAN;
	}
#line 3196 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 134: /* opcode: TOKEN_DIRECTIVE_BGT  */
#line 1342 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_GREATER_THAN;
	}
#line 3205 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 135: /* opcode: TOKEN_DIRECTIVE_BLE  */
#line 1347 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_Bcc;
		(yyval.opcode).condition = CONDITION_LESS_OR_EQUAL;
	}
#line 3214 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 136: /* opcode: TOKEN_DIRECTIVE_MOVEQ  */
#line 1352 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MOVEQ;
	}
#line 3222 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 137: /* opcode: TOKEN_DIRECTIVE_DIVU  */
#line 1356 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DIVU;
	}
#line 3230 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 138: /* opcode: TOKEN_DIRECTIVE_DIVS  */
#line 1360 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_DIVS;
	}
#line 3238 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 139: /* opcode: TOKEN_DIRECTIVE_SBCD  */
#line 1364 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SBCD_DATA_REGS;
	}
#line 3246 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 140: /* opcode: TOKEN_DIRECTIVE_OR  */
#line 1368 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_OR_TO_REG;
	}
#line 3254 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 141: /* opcode: TOKEN_DIRECTIVE_SUB  */
#line 1372 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SUB_TO_REG;
	}
#line 3262 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 142: /* opcode: TOKEN_DIRECTIVE_SUBX  */
#line 1376 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SUBX_DATA_REGS;
	}
#line 3270 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 143: /* opcode: TOKEN_DIRECTIVE_SUBA  */
#line 1380 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_SUBA;
	}
#line 3278 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 144: /* opcode: TOKEN_DIRECTIVE_EOR  */
#line 1384 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_EOR;
	}
#line 3286 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 145: /* opcode: TOKEN_DIRECTIVE_CMPM  */
#line 1388 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_CMPM;
	}
#line 3294 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 146: /* opcode: TOKEN_DIRECTIVE_CMP  */
#line 1392 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_CMP;
	}
#line 3302 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 147: /* opcode: TOKEN_DIRECTIVE_CMPA  */
#line 1396 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_CMPA;
	}
#line 3310 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 148: /* opcode: TOKEN_DIRECTIVE_MULU  */
#line 1400 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MULU;
	}
#line 3318 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 149: /* opcode: TOKEN_DIRECTIVE_MULS  */
#line 1404 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_MULS;
	}
#line 3326 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 150: /* opcode: TOKEN_DIRECTIVE_ABCD  */
#line 1408 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ABCD_DATA_REGS;
	}
#line 3334 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 151: /* opcode: TOKEN_DIRECTIVE_EXG  */
#line 1412 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_EXG;
	}
#line 3342 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 152: /* opcode: TOKEN_DIRECTIVE_AND  */
#line 1416 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_AND_TO_REG;
	}
#line 3350 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 153: /* opcode: TOKEN_DIRECTIVE_ADD  */
#line 1420 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ADD_TO_REG;
	}
#line 3358 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 154: /* opcode: TOKEN_DIRECTIVE_ADDX  */
#line 1424 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ADDX_DATA_REGS;
	}
#line 3366 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 155: /* opcode: TOKEN_DIRECTIVE_ADDA  */
#line 1428 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ADDA;
	}
#line 3374 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 156: /* opcode: TOKEN_DIRECTIVE_ASL  */
#line 1432 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ASL_STATIC;
	}
#line 3382 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 157: /* opcode: TOKEN_DIRECTIVE_ASR  */
#line 1436 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ASR_STATIC;
	}
#line 3390 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 158: /* opcode: TOKEN_DIRECTIVE_LSL  */
#line 1440 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_LSL_STATIC;
	}
#line 3398 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 159: /* opcode: TOKEN_DIRECTIVE_LSR  */
#line 1444 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_LSR_STATIC;
	}
#line 3406 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 160: /* opcode: TOKEN_DIRECTIVE_ROXL  */
#line 1448 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ROXL_STATIC;
	}
#line 3414 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 161: /* opcode: TOKEN_DIRECTIVE_ROXR  */
#line 1452 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ROXR_STATIC;
	}
#line 3422 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 162: /* opcode: TOKEN_DIRECTIVE_ROL  */
#line 1456 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ROL_STATIC;
	}
#line 3430 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 163: /* opcode: TOKEN_DIRECTIVE_ROR  */
#line 1460 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.opcode).type = OPCODE_ROR_STATIC;
	}
#line 3438 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 164: /* size: TOKEN_SIZE_BYTE  */
#line 1467 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.size) = SIZE_BYTE;
	}
#line 3446 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 165: /* size: TOKEN_SIZE_SHORT  */
#line 1471 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.size) = SIZE_SHORT;
	}
#line 3454 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 166: /* size: TOKEN_SIZE_WORD  */
#line 1475 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.size) = SIZE_WORD;
	}
#line 3462 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 167: /* size: TOKEN_SIZE_LONGWORD  */
#line 1479 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.size) = SIZE_LONGWORD;
	}
#line 3470 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 168: /* operand: '(' TOKEN_ADDRESS_REGISTER ')'  */
#line 1487 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT;
		(yyval.operand).main_register = (yyvsp[-1].unsigned_long);
	}
#line 3479 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 169: /* operand: '(' TOKEN_ADDRESS_REGISTER ')' '+'  */
#line 1492 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_POSTINCREMENT;
		(yyval.operand).main_register = (yyvsp[-2].unsigned_long);
	}
#line 3488 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 170: /* operand: '-' '(' TOKEN_ADDRESS_REGISTER ')'  */
#line 1497 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_PREDECREMENT;
		(yyval.operand).main_register = (yyvsp[-1].unsigned_long);
	}
#line 3497 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 171: /* operand: expression '(' TOKEN_ADDRESS_REGISTER ')'  */
#line 1502 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT;
		(yyval.operand).literal = (yyvsp[-3].expression);
		(yyval.operand).main_register = (yyvsp[-1].unsigned_long);
	}
#line 3507 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 172: /* operand: '(' TOKEN_ADDRESS_REGISTER ',' data_or_address_register size ')'  */
#line 1508 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal.type = EXPRESSION_NUMBER;
		(yyval.operand).literal.shared.unsigned_long = 0;
		(yyval.operand).main_register = (yyvsp[-4].unsigned_long);
		(yyval.operand).index_register = (yyvsp[-2].unsigned_long) % 8;
		(yyval.operand).size = (yyvsp[-1].size);
		(yyval.operand).index_register_is_address_register = (yyvsp[-2].unsigned_long) / 8 != 0;
	}
#line 3521 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 173: /* operand: expression '(' TOKEN_ADDRESS_REGISTER ',' data_or_address_register size ')'  */
#line 1518 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal = (yyvsp[-6].expression);
		(yyval.operand).main_register = (yyvsp[-4].unsigned_long);
		(yyval.operand).index_register = (yyvsp[-2].unsigned_long) % 8;
		(yyval.operand).size = (yyvsp[-1].size);
		(yyval.operand).index_register_is_address_register = (yyvsp[-2].unsigned_long) / 8 !=0;
	}
#line 3534 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 174: /* operand: '(' TOKEN_ADDRESS_REGISTER ',' data_or_address_register ')'  */
#line 1527 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		m68kasm_warning(scanner, statement, "Index register lacks a size specifier (assuming word-size for now, but you should really add an explicit size).");
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal.type = EXPRESSION_NUMBER;
		(yyval.operand).literal.shared.unsigned_long = 0;
		(yyval.operand).main_register = (yyvsp[-3].unsigned_long);
		(yyval.operand).index_register = (yyvsp[-1].unsigned_long) % 8;
		(yyval.operand).size = SIZE_WORD;
		(yyval.operand).index_register_is_address_register = (yyvsp[-1].unsigned_long) / 8 != 0;
	}
#line 3549 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 175: /* operand: expression '(' TOKEN_ADDRESS_REGISTER ',' data_or_address_register ')'  */
#line 1538 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		m68kasm_warning(scanner, statement, "Index register lacks a size specifier (assuming word-size for now, but you should really add an explicit size).");
		(yyval.operand).type = OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal = (yyvsp[-5].expression);
		(yyval.operand).main_register = (yyvsp[-3].unsigned_long);
		(yyval.operand).index_register = (yyvsp[-1].unsigned_long) % 8;
		(yyval.operand).size = SIZE_WORD;
		(yyval.operand).index_register_is_address_register = (yyvsp[-1].unsigned_long) / 8 !=0;
	}
#line 3563 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 176: /* operand: expression '(' TOKEN_PROGRAM_COUNTER ')'  */
#line 1548 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT;
		(yyval.operand).literal = (yyvsp[-3].expression);
	}
#line 3572 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 177: /* operand: '(' TOKEN_PROGRAM_COUNTER ',' data_or_address_register size ')'  */
#line 1553 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal.type = EXPRESSION_NUMBER;
		(yyval.operand).literal.shared.unsigned_long = 0;
		(yyval.operand).index_register = (yyvsp[-2].unsigned_long) % 8;
		(yyval.operand).size = (yyvsp[-1].size);
		(yyval.operand).index_register_is_address_register = (yyvsp[-2].unsigned_long) / 8 != 0;
	}
#line 3585 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 178: /* operand: expression '(' TOKEN_PROGRAM_COUNTER ',' data_or_address_register size ')'  */
#line 1562 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal = (yyvsp[-6].expression);
		(yyval.operand).index_register = (yyvsp[-2].unsigned_long) % 8;
		(yyval.operand).size = (yyvsp[-1].size);
		(yyval.operand).index_register_is_address_register = (yyvsp[-2].unsigned_long) / 8 != 0;
	}
#line 3597 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 179: /* operand: '(' TOKEN_PROGRAM_COUNTER ',' data_or_address_register ')'  */
#line 1570 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		m68kasm_warning(scanner, statement, "Index register lacks a size specifier (assuming word-size for now, but you should really add an explicit size).");
		(yyval.operand).type = OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal.type = EXPRESSION_NUMBER;
		(yyval.operand).literal.shared.unsigned_long = 0;
		(yyval.operand).index_register = (yyvsp[-1].unsigned_long) % 8;
		(yyval.operand).size = SIZE_WORD;
		(yyval.operand).index_register_is_address_register = (yyvsp[-1].unsigned_long) / 8 != 0;
	}
#line 3611 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 180: /* operand: expression '(' TOKEN_PROGRAM_COUNTER ',' data_or_address_register ')'  */
#line 1580 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		m68kasm_warning(scanner, statement, "Index register lacks a size specifier (assuming word-size for now, but you should really add an explicit size).");
		(yyval.operand).type = OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT_AND_INDEX_REGISTER;
		(yyval.operand).literal = (yyvsp[-5].expression);
		(yyval.operand).index_register = (yyvsp[-1].unsigned_long) % 8;
		(yyval.operand).size = SIZE_WORD;
		(yyval.operand).index_register_is_address_register = (yyvsp[-1].unsigned_long) / 8 != 0;
	}
#line 3624 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 181: /* operand: '#' expression  */
#line 1590 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_LITERAL;
		(yyval.operand).literal = (yyvsp[0].expression);
	}
#line 3633 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 182: /* operand: TOKEN_STATUS_REGISTER  */
#line 1606 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_STATUS_REGISTER;
	}
#line 3641 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 183: /* operand: TOKEN_CONDITION_CODE_REGISTER  */
#line 1610 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_CONDITION_CODE_REGISTER;
	}
#line 3649 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 184: /* operand: TOKEN_USER_STACK_POINTER_REGISTER  */
#line 1614 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_USER_STACK_POINTER_REGISTER;
	}
#line 3657 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 185: /* operand: expression  */
#line 1619 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS;
		(yyval.operand).literal = (yyvsp[0].expression);
		(yyval.operand).size = SIZE_UNDEFINED;
	}
#line 3667 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 186: /* operand: '(' expression ')' size  */
#line 1625 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.operand).type = OPERAND_ADDRESS_ABSOLUTE;
		(yyval.operand).literal = (yyvsp[-2].expression);
		(yyval.operand).size = (yyvsp[0].size);
	}
#line 3677 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 187: /* operand: register_list  */
#line 1632 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		/* Neat trick to check if only one bit is set (yes, I know that it evaluates to true for 0, but that doesn't matter here). */
		if (((yyvsp[0].unsigned_long) & ((yyvsp[0].unsigned_long) - 1)) == 0)
		{
			/* This is a single register. */
			(yyval.operand).main_register = 0;

			while (((yyvsp[0].unsigned_long) & (1 << (yyval.operand).main_register)) == 0)
				++(yyval.operand).main_register;

			if ((yyval.operand).main_register >= 8)
			{
				(yyval.operand).type = OPERAND_ADDRESS_REGISTER;
				(yyval.operand).main_register -= 8;
			}
			else
			{
				(yyval.operand).type = OPERAND_DATA_REGISTER;
			}
		}
		else
		{
			/* This is multiple registers. */
			(yyval.operand).type = OPERAND_REGISTER_LIST;
			(yyval.operand).main_register = (yyvsp[0].unsigned_long); /* Such a hack... */
		}
	}
#line 3709 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 188: /* register_list: register_span  */
#line 1663 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.unsigned_long) = (yyvsp[0].unsigned_long);
	}
#line 3717 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 189: /* register_list: register_span '/' register_list  */
#line 1667 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.unsigned_long) = (yyvsp[-2].unsigned_long) | (yyvsp[0].unsigned_long);
	}
#line 3725 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 190: /* register_span: data_or_address_register  */
#line 1674 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.unsigned_long) = 1 << (yyvsp[0].unsigned_long);
	}
#line 3733 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 191: /* register_span: data_or_address_register '-' data_or_address_register  */
#line 1678 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		unsigned long start;
		unsigned long end;
		unsigned long i;

		if ((yyvsp[-2].unsigned_long) < (yyvsp[0].unsigned_long))
		{
			start = (yyvsp[-2].unsigned_long);
			end = (yyvsp[0].unsigned_long);
		}
		else
		{
			start = (yyvsp[0].unsigned_long);
			end = (yyvsp[-2].unsigned_long);
		}

		(yyval.unsigned_long) = 0;

		for (i = start; i <= end; ++i)
			(yyval.unsigned_long) |= 1 << i;
	}
#line 3759 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 192: /* data_or_address_register: TOKEN_DATA_REGISTER  */
#line 1703 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.unsigned_long) = 0 + (yyvsp[0].unsigned_long);
	}
#line 3767 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 193: /* data_or_address_register: TOKEN_ADDRESS_REGISTER  */
#line 1707 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.unsigned_long) = 8 + (yyvsp[0].unsigned_long);
	}
#line 3775 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 194: /* expression: expression1  */
#line 1720 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3783 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 195: /* expression: expression TOKEN_LOGICAL_AND expression1  */
#line 1725 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_LOGICAL_AND, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3792 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 196: /* expression: expression TOKEN_LOGICAL_OR expression1  */
#line 1731 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_LOGICAL_OR, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3801 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 197: /* expression1: expression2  */
#line 1739 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3809 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 198: /* expression1: expression1 '=' expression2  */
#line 1743 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_EQUALITY, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3818 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 199: /* expression1: expression1 TOKEN_EQUALITY expression2  */
#line 1748 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_EQUALITY, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3827 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 200: /* expression1: expression1 TOKEN_INEQUALITY expression2  */
#line 1753 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_INEQUALITY, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3836 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 201: /* expression2: expression3  */
#line 1761 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3844 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 202: /* expression2: expression2 '<' expression3  */
#line 1765 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_LESS_THAN, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3853 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 203: /* expression2: expression2 TOKEN_LESS_OR_EQUAL expression3  */
#line 1770 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_LESS_OR_EQUAL, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3862 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 204: /* expression2: expression2 '>' expression3  */
#line 1775 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_MORE_THAN, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3871 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 205: /* expression2: expression2 TOKEN_MORE_OR_EQUAL expression3  */
#line 1780 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_MORE_OR_EQUAL, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3880 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 206: /* expression3: expression4  */
#line 1788 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3888 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 207: /* expression3: expression3 '+' expression4  */
#line 1792 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_ADD, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3897 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 208: /* expression3: expression3 '-' expression4  */
#line 1797 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_SUBTRACT, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3906 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 209: /* expression4: expression5  */
#line 1805 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3914 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 210: /* expression4: expression4 '*' expression5  */
#line 1809 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_MULTIPLY, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3923 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 211: /* expression4: expression4 '/' expression5  */
#line 1814 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_DIVIDE, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3932 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 212: /* expression4: expression4 '%' expression5  */
#line 1819 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_MODULO, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3941 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 213: /* expression5: expression6  */
#line 1827 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3949 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 214: /* expression5: expression5 '&' expression6  */
#line 1831 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_BITWISE_AND, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3958 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 215: /* expression5: expression5 '!' expression6  */
#line 1836 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_BITWISE_OR, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3967 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 216: /* expression5: expression5 '|' expression6  */
#line 1841 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_BITWISE_OR, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3976 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 217: /* expression5: expression5 '^' expression6  */
#line 1846 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_BITWISE_XOR, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 3985 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 218: /* expression6: expression7  */
#line 1854 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 3993 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 219: /* expression6: expression6 TOKEN_LEFT_SHIFT expression7  */
#line 1858 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_LEFT_SHIFT, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 4002 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 220: /* expression6: expression6 TOKEN_RIGHT_SHIFT expression7  */
#line 1863 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_RIGHT_SHIFT, &(yyvsp[-2].expression), &(yyvsp[0].expression)))
			YYNOMEM;
	}
#line 4011 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 221: /* expression7: expression8  */
#line 1871 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 4019 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 222: /* expression7: '+' expression7  */
#line 1875 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[0].expression);
	}
#line 4027 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 223: /* expression7: '-' expression7  */
#line 1879 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_NEGATE, &(yyvsp[0].expression), NULL))
			YYNOMEM;
	}
#line 4036 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 224: /* expression7: '~' expression7  */
#line 1884 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_BITWISE_NOT, &(yyvsp[0].expression), NULL))
			YYNOMEM;
	}
#line 4045 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 225: /* expression7: '!' expression7  */
#line 1890 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		if (!DoExpression(&(yyval.expression), EXPRESSION_LOGICAL_NOT, &(yyvsp[0].expression), NULL))
			YYNOMEM;
	}
#line 4054 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 226: /* expression8: TOKEN_NUMBER  */
#line 1898 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_NUMBER;
		(yyval.expression).shared.unsigned_long = (yyvsp[0].unsigned_long);
	}
#line 4063 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 227: /* expression8: TOKEN_IDENTIFIER  */
#line 1903 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_IDENTIFIER;
		(yyval.expression).shared.string = (yyvsp[0].string);
	}
#line 4072 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 228: /* expression8: TOKEN_LOCAL_IDENTIFIER  */
#line 1908 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_IDENTIFIER;
		(yyval.expression).shared.string = (yyvsp[0].string);
	}
#line 4081 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 229: /* expression8: TOKEN_IDENTIFIER TOKEN_LOCAL_IDENTIFIER  */
#line 1913 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		const size_t identifier_length = strlen((yyvsp[-1].string));
		const size_t local_identifier_length = strlen((yyvsp[0].string) + 1);

		(yyval.expression).shared.string = malloc(identifier_length + 1 + local_identifier_length + 1);

		if ((yyval.expression).shared.string == NULL)
		{
			free((yyvsp[-1].string));
			free((yyvsp[0].string));
			YYNOMEM;
		}
		else
		{
			(yyval.expression).type = EXPRESSION_IDENTIFIER;
			memcpy(&(yyval.expression).shared.string[0], (yyvsp[-1].string), identifier_length);
			free((yyvsp[-1].string));
			(yyval.expression).shared.string[identifier_length] = '@';
			memcpy(&(yyval.expression).shared.string[identifier_length + 1], (yyvsp[0].string) + 1, local_identifier_length + 1);
			free((yyvsp[0].string));
		}
	}
#line 4108 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 230: /* expression8: TOKEN_STRING  */
#line 1936 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_STRING;
		(yyval.expression).shared.string = (yyvsp[0].string);
	}
#line 4117 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 231: /* expression8: '*'  */
#line 1941 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_PROGRAM_COUNTER_OF_STATEMENT;
	}
#line 4125 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 232: /* expression8: '@'  */
#line 1945 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_PROGRAM_COUNTER_OF_EXPRESSION;
	}
#line 4133 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 233: /* expression8: '(' expression ')'  */
#line 1949 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression) = (yyvsp[-1].expression);
	}
#line 4141 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;

  case 234: /* expression8: TOKEN_STRLEN '(' TOKEN_STRING ')'  */
#line 1953 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"
        {
		(yyval.expression).type = EXPRESSION_STRLEN;
		(yyval.expression).shared.string = (yyvsp[-1].string);
	}
#line 4150 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"
    break;


#line 4154 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == M68KASM_EMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (scanner, statement, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= M68KASM_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == M68KASM_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner, statement);
          yychar = M68KASM_EMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner, statement);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, statement, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != M68KASM_EMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner, statement);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner, statement);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1959 "/home/mastro/Developing/C/STRAY68K/stray68K/src/assembler/syntactic.y"


static cc_bool DoExpression(Expression *expression, ExpressionType type, Expression *left_expression, Expression *right_expression)
{
	cc_bool success = cc_true;

	expression->type = type;

	expression->shared.subexpressions = malloc(sizeof(Expression) * (right_expression != NULL ? 2 : 1));

	if (expression->shared.subexpressions == NULL)
	{
		DestroyExpression(left_expression);

		if (right_expression != NULL)
			DestroyExpression(right_expression);

		success = cc_false;
	}
	else
	{
		expression->shared.subexpressions[0] = *left_expression;

		if (right_expression != NULL)
			expression->shared.subexpressions[1] = *right_expression;
	}

	return success;
}

void DestroyExpression(Expression *expression)
{
	switch (expression->type)
	{
		case EXPRESSION_SUBTRACT:
		case EXPRESSION_ADD:
		case EXPRESSION_MULTIPLY:
		case EXPRESSION_DIVIDE:
		case EXPRESSION_MODULO:
		case EXPRESSION_LOGICAL_OR:
		case EXPRESSION_LOGICAL_AND:
		case EXPRESSION_BITWISE_OR:
		case EXPRESSION_BITWISE_XOR:
		case EXPRESSION_BITWISE_AND:
		case EXPRESSION_EQUALITY:
		case EXPRESSION_INEQUALITY:
		case EXPRESSION_LESS_THAN:
		case EXPRESSION_LESS_OR_EQUAL:
		case EXPRESSION_MORE_THAN:
		case EXPRESSION_MORE_OR_EQUAL:
		case EXPRESSION_LEFT_SHIFT:
		case EXPRESSION_RIGHT_SHIFT:
			DestroyExpression(&expression->shared.subexpressions[0]);
			DestroyExpression(&expression->shared.subexpressions[1]);
			free(expression->shared.subexpressions);
			break;

		case EXPRESSION_NEGATE:
		case EXPRESSION_BITWISE_NOT:
		case EXPRESSION_LOGICAL_NOT:
			DestroyExpression(&expression->shared.subexpressions[0]);
			free(expression->shared.subexpressions);
			break;

		case EXPRESSION_IDENTIFIER:
		case EXPRESSION_STRING:
		case EXPRESSION_STRLEN:
			free(expression->shared.string);
			break;

		case EXPRESSION_NUMBER:
		case EXPRESSION_PROGRAM_COUNTER_OF_STATEMENT:
		case EXPRESSION_PROGRAM_COUNTER_OF_EXPRESSION:
			break;
	}
}

static void DestroyIdentifierList(IdentifierListNode *node)
{
	while (node != NULL)
	{
		IdentifierListNode* const next_node = node->next;

		free(node->identifier);

		free(node);

		node = next_node;
	}
}

static void DestroyExpressionList(ExpressionListNode *node)
{
	while (node != NULL)
	{
		ExpressionListNode* const next_node = node->next;

		DestroyExpression(&node->expression);

		free(node);

		node = next_node;
	}
}

static void DestroyOperand(Operand *operand)
{
	switch (operand->type)
	{
		case OPERAND_DATA_REGISTER:
		case OPERAND_ADDRESS_REGISTER:
		case OPERAND_ADDRESS_REGISTER_INDIRECT:
		case OPERAND_ADDRESS_REGISTER_INDIRECT_POSTINCREMENT:
		case OPERAND_ADDRESS_REGISTER_INDIRECT_PREDECREMENT:
		case OPERAND_STATUS_REGISTER:
		case OPERAND_CONDITION_CODE_REGISTER:
		case OPERAND_USER_STACK_POINTER_REGISTER:
		case OPERAND_REGISTER_LIST:
			break;

		case OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT:
		case OPERAND_ADDRESS_REGISTER_INDIRECT_WITH_DISPLACEMENT_AND_INDEX_REGISTER:
		case OPERAND_ADDRESS:
		case OPERAND_ADDRESS_ABSOLUTE:
		case OPERAND_LITERAL:
		case OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT:
		case OPERAND_PROGRAM_COUNTER_WITH_DISPLACEMENT_AND_INDEX_REGISTER:
			DestroyExpression(&operand->literal);
			break;
	}
}

static void DestroyStatementInstruction(StatementInstruction *instruction)
{
	size_t i;

	for (i = 0; i < CC_COUNT_OF(instruction->operands); ++i)
		DestroyOperand(&instruction->operands[i]);
}

void DestroyStatement(Statement *statement)
{
	switch (statement->type)
	{
		case STATEMENT_TYPE_EMPTY:
		case STATEMENT_TYPE_ENDR:
		case STATEMENT_TYPE_ENDM:
		case STATEMENT_TYPE_ELSE:
		case STATEMENT_TYPE_ENDC:
		case STATEMENT_TYPE_ENDW:
		case STATEMENT_TYPE_EVEN:
		case STATEMENT_TYPE_END:
		case STATEMENT_TYPE_RSRESET:
		case STATEMENT_TYPE_ORG:
        case STATEMENT_TYPE_DS:
			break;

		case STATEMENT_TYPE_INSTRUCTION:
			DestroyStatementInstruction(&statement->shared.instruction);
			break;

		case STATEMENT_TYPE_DC:
			DestroyExpressionList(statement->shared.dc.values);
			break;

		case STATEMENT_TYPE_DCB:
			DestroyExpression(&statement->shared.dcb.repetitions);
			DestroyExpression(&statement->shared.dcb.value);
			break;

		case STATEMENT_TYPE_INCLUDE:
			free(statement->shared.include.path);
			break;

		case STATEMENT_TYPE_INCBIN:
			free(statement->shared.incbin.path);
			DestroyExpression(&statement->shared.incbin.start);

			if (statement->shared.incbin.has_length)
				DestroyExpression(&statement->shared.incbin.length);

			break;

		case STATEMENT_TYPE_REPT:
			DestroyExpression(&statement->shared.rept.repetitions);
			break;

		case STATEMENT_TYPE_MACRO:
		case STATEMENT_TYPE_MACROS:
			DestroyIdentifierList(statement->shared.macro.parameter_names);
			break;

		case STATEMENT_TYPE_EQU:
		case STATEMENT_TYPE_SET:
		case STATEMENT_TYPE_IF:
		case STATEMENT_TYPE_ELSEIF:
		case STATEMENT_TYPE_WHILE:
		case STATEMENT_TYPE_RSSET:
			DestroyExpression(&statement->shared.expression);
			break;

		case STATEMENT_TYPE_CNOP:
			DestroyExpression(&statement->shared.cnop.offset);
			DestroyExpression(&statement->shared.cnop.size_boundary);
			break;

		case STATEMENT_TYPE_INFORM:
			free(statement->shared.inform.message);
			break;

		case STATEMENT_TYPE_RS:
			DestroyExpression(&statement->shared.rs.length);
			break;
	}
}
