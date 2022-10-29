; IO tester.
;
; Author: Stefano Fattore aka MastroGibbs 
;
; assemble: ./stray68K -a -i scripts/io.X68 -o scripts/io.B68 
; run:      ./stray68K -e scripts/io.B68 -q

    ORG $1000

	MOVE.L  #$7CC,(SP)

	BSR	    PASS_PARAM_VIA_STACK
	JMP     EXIT

PASS_PARAM_VIA_STACK:
	; save curr RTS address in D7
	MOVE.L (SP),D7

	; print welcome message
	LEA		welcome,A0
	TRAP	#15  ; aka print

	; transfer (SP) into D1
	MOVE.L  (SP),D1

	; scan 2 int
	LEA		scan,A0
	TRAP	#14  ; aka scan

	; print formatted str
	LEA		print,A0
	TRAP	#15

	; set RTS address from D7 into (SP)
	MOVE.L  D7,(SP)

	RTS

EXIT:
	;print byebye message
	LEA		byebye,A0
	TRAP	#15

	; HALT

welcome		DC.B	'Insert two integers\n',0
scan:		DC.B	'%LD2%LD3',0
print:      DC.B    'Values:\nFrom SP -> %LD1\nFirst int entered -> %LD2\nSecond int entered -> %LD3\n',0
byebye:		DC.B	'\nBye bye from \033[91mstray68K\033[0m\n',0