    org    $1000

    lea    arr,a0

    move.b #5, (a0)+
    move.b #10,(a0)+
    move.b #15,(a0)+
    move.b #20,(a0)+
    move.b #25,(a0)

    lea    head,a0
    trap   #15

    lea    cont,a0

    lea    arr,a1
    move.b (a1)+,d0
    trap   #15

    move.b (a1)+,d0
    trap   #15 

    move.b (a1)+,d0
    trap   #15 

    move.b (a1)+,d0
    trap   #15 

    move.b (a1),d0
    trap   #15     

    lea    nl,a0
    trap   #15    

arr:     ds.b     5


head:    dc.b     "array: ",0    
cont:    dc.b     "%ld0",0
nl:      dc.b     "\n",0




