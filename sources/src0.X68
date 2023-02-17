    org $1000
    
    move.l    #100000,d0
    move.l    #5,d1

    lea       in,a0
    trap      #14

loop:
    subi.b    #1,d5
    trap      #13
    cmpi.b    #0,d5
    bgt       loop

in:    dc.b    "%ld5",0