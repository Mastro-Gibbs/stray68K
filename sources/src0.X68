    org $1000


    lea    in,a0
    lea    name,a1
    move.b #50,d0
    trap   #14

    lea    out,a0
    trap   #15

    lea    name,a0
    trap   #15

    lea    pe,a0
    trap   #15

in:      dc.b    "%s1",0
out:     dc.b    "Ciao ",0
pe:      dc.b    "!\n",0
name:    ds.b    50