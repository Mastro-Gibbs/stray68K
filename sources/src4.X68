    org    $1000

    move.b #1,d0
    add.b  d0,d0
    muls   d0,d0


    lea    str,a0
    trap   #15


str:    dc.b    "ciao sono eseguito su un server e reindirizzato qui!\ndiocane\n",0    