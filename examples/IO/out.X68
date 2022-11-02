    ORG     $1000

    LEA     out,A0
    TRAP    #15

out:    DC.B    'Hi, i am a string with placeholder and escape!\n%LX1\n',0