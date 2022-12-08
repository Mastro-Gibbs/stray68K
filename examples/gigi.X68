    ORG     $1000

    MOVE.L  #$10,D0

    BSR     gigi_sr

    LEA     STR,A0


gigi_rt:
    TRAP    #15
    SUBQ.L  #1,D0
    TST.B   D0
    BGT     gigi_rt
    JMP     exit


gigi_sr:
    LEA     in,A0
    TRAP    #14
    LEA     STR2,A0
    TRAP    #15
    RTS


exit:
    TRAP    #1


STR:    DC.B    'Il valore in d0 è %LD0\n',0  
in:     DC.B    '%T1',0  
STR2:   DC.B    'Sono una subroutine e il tempo è %LX1\n',0    

