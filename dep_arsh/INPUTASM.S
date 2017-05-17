;--------------------------
;Name:  Joel v
;       Kieran K
;       
;Module: inputasm
;--------------------------

    xdef _setVideoBaseAsm

    
;--------------------------
;Name: setVideoBaseAsm
;Purpose: sets the video base register with the input address
;Input: the top and middle bytes of the address, type UINT16
;--------------------------

_setVideoBaseAsm:
    link    a6,#0
    move.l  #$00FF8201,a0
    move.w  8(a6),d0
    movep.w d0,(a0)

    unlk    a6
    rts