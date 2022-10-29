;	TEST FILE (MAIN)
;	
;	This file include other sources for testing specific OPs
;	 
;Author: Stefano Fattore	

	ORG       $1000	

	INCLUDE   roller.X68
	INCLUDE   bit_setter.X68

;testing LEA & SWAP
	LEA		  initval,A0
	MOVE.B    (A0),D0
	LEA		  subval,A0
	MOVE.B    (A0),D1
	
	LEA		  addval,A0
	SWAP	  D1
	MOVE.B    (A0),D1
	SWAP      D1

;testing BSR
	BSR       subtraction
	SWAP      D1
	BSR       addiction

;testing Addressing Mode With Displacement
	LEA		  output,A1
	MOVE.B	  D0,1(A1)
	
;testing JUMP
	JMP       exit

;testing routines
subtraction:
	SUB.B     D1,D0
	TST.B     D0
	BGT       subtraction
	RTS

addiction:
	ADD.B     D1,D0
	CMPI.B    #$19,D0
	BNE       addiction
	RTS

exit:
	; printing
	MOVE.B	  1(A1),D7
	LEA 	  str,A0
	trap	  #15


;SIMHALT

;testing DECLARE CONSTANT
initval:	DC.B	6
subval:		DC.B	1
addval:		DC.B	5

;testing DESERVE SPACE
output:		DS.W	1

; str with placeholder (D7)
str:		DC.B	'From memory with displacement: %LX7\n',0