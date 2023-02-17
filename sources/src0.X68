    org    $1000

    lea    qry,a0
    trap   #15

    lea    in,a0
    lea    nome,a1
    move.b #99,d0
    trap   #14

    move.l #100000,d0
    move.l #5,d1
    trap   #13

    clr.l  d0
    clr.l  d1

    lea    out1,a0
    trap   #15
    lea    nome,a0
    trap   #15
    lea    out2,a0
    trap   #15
    
    lea    in,a0
    lea    come,a1
    move.b #99,d0
    trap   #14

    move.l #100000,d0
    move.l #8,d1
    trap   #13

    clr.l  d0
    clr.l  d1

    lea    out3,a0
    trap   #15
    lea    come,a0
    trap   #15
    lea    out4,a0
    trap   #15
    
    

qry:   dc.b    "Io sono Stray68K, tu come ti chiami? :)\n",0

in:    dc.b    "%s1",0
nome:  ds.b    100
come:  ds.b    100

out1:  dc.b    "Ciao ",0
out2:  dc.b    ", come stai?\n",0
out3:  dc.b    "Io pure ",0
out4:  dc.b    "\n",0