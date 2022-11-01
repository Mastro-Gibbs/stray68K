;
; Do a loop from 0 to 0xFFFF.
; Get chrono.
; Would you compare it with python? run 'time python3 speed.py' :)
;   
; Author: Stefano Fattore aka MastroGibbs
;
; assemble: ./stray68K -a -i ../examples/SpeedTest/speed.X68 -o ../examples/SpeedTest/speed.B68 
; run:      ./stray68K -e ../examples/SpeedTest/speed.B68 -q -t

    ORG     $1010

    MOVE.L  #$0000FFFF,D1
    MOVE.L  #$FFFFFFFF,D0

_LOOP:
    ADDQ.L  #1,D0
    CMP.L   D1,D0
    BLT     _LOOP