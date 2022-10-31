;
; Do a loop from 0 to 0xFFFF.
; Get chrono.
; Wuold you compare it with python? :)
;   
; Author: Stefano Fattore aka MastroGibbs
;

    ORG     $1000

    MOVE.L  #$0000FFFF,D1
    MOVE.L  #$FFFFFFFF,D0

_LOOP:
    ADDQ.L  #1,D0
    CMP.L   D1,D0
    BLT     _LOOP