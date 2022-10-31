; IO tester.
;
; Author: Stefano Fattore aka MastroGibbs 
;
; assemble: ./stray68K -a -i examples/scripts/io.X68 -o examples/scripts/io.B68 
; run:      ./stray68K -e examples/scripts/io.B68 -q

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
	LEA		Sprint,A0
	TRAP	#15

	; print formatted str
	LEA		Uprint,A0
	TRAP	#15

	; print formatted str
	LEA		Xprint,A0
	TRAP	#15

	; print formatted str
	LEA		Aprint,A0
	TRAP	#15

	; set RTS address from D7 into (SP)
	MOVE.L  D7,(SP)

	RTS

EXIT:
	;print byebye message
	LEA		byebye,A0
	TRAP	#15

	; HALT

; simple str for printer
welcome		DC.B	'Insert two integers\n',0

; ftm for scannner
scan:		DC.B	'%LD2%LD3',0

; ftm for printer
Sprint:     DC.B    '\nSigned values:\n-From SP -> %L1\n-First int entered -> %L2\n-Second int entered -> %L3\n',0
Uprint:     DC.B    '\nUnsigned values:\n-From SP -> %LD1\n-First int entered -> %LD2\n-Second int entered -> %LD3\n',0
Xprint:     DC.B    '\nHex values:\n-From SP -> 0x%LX1\n-First int entered -> 0x%LX2\n-Second int entered -> 0x%LX3\n',0
Aprint:     DC.B    '\nA0 address -> 0x%LA0\n',0

; ansi escape ftm str for printer
byebye:		DC.B	'\n\033[92m\033[1mBye bye\033[0m \033[1mfrom\033[0m \033[91m\033[5m\033[1mstray68K\033[0m\n',0