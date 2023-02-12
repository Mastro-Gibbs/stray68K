    ORG     $1000

    LEA     ph,A0
    LEA     str,A1
    MOVE.B  #50,D0
    TRAP    #14

    LEA     rand,A0
    TRAP    #14

    CLR.W   D1
    SWAP    D1
    DIVU    #7,D1
    CLR.W   D1
    SWAP    D1

    LEA     str,A0
    TRAP    #15



rand:   DC.B    '%T1',0
ph:     DC.B    '%S1',0
str:    DS.B    50
