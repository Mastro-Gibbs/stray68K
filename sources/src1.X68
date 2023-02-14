    org $1000

    lea  in,a0
    trap #14

    lea  out,a0
    trap #15

in:    dc.b    "%ld0",0
out:   dc.b    "%ld0\n",0