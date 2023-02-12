    org     $1000

    lea     arr,a0
    move.w  #5,(a0)+
    move.w  #10,(a0)+
    move.w  #15,(a0)+
    move.w  #20,(a0)+
    move.w  #25,(a0) 

arr:    ds.w    5