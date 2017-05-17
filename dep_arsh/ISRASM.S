;--------------------------
;Name:  Joel v
;       Kieran K
;       
;Module: israsm
;--------------------------

MFP_ISRB    equ         $FFFA11     ;address of the isrb register on the MFP


            xdef        _vblisr
            xdef        _ikbdisr
            xdef        _setipl
            
            xref        _procSync
            xref        _readIKBD
            
            
            
;--------------------------
;Name: vblisr
;Purpose: the custom vbl isr, calls procSync from the dep_arsh module
;--------------------------
_vblisr:    movem.l     d0-d2/a0-a2,-(sp)
            jsr         _procSync
            movem.l     (sp)+,d0-d2/a0-a2
            rte


;--------------------------
;Name: ikbdisr
;Purpose: the custom IKBD isr, calls readIKBD from the IKBD module
;Details: clears the isrb register on the MFP at the end to indicate the interrupt is over
;--------------------------
_ikbdisr:   movem.l     d0-d2/a0-a2,-(sp)
            jsr         _readIKBD
            movem.l     (sp)+,d0-d2/a0-a2
            bclr.b      #6,MFP_ISRB         ;clear the one bit to it that the isr is done
            rte
            
            
;--------------------------
;Name: setipl
;Purpose: sets IPL = mask, returns old IPL (interrupt priority level)
;Details: Must be called from supervisor mode
;--------------------------         
_setipl:    move.w  sr,d0
            move.w  d0,-(sp)    ; place orig. sr on stack

            lsr.w   #8,d0       ; will return orig. ipl
            and.w   #$0007,d0   ; ... in d0.w
            
            andi.w  #$F8FF,(sp)
            move.w  d1,-(sp)
            move.w  8(sp),d1    ; place new ipl in d1.w
            lsl.w   #8,d1
            and.w   #$0700,d1
            or.w    d1,2(sp)    ; insert it into sr on stack
            move.w  (sp)+,d1

            rte                 ; trick: when returning,
                                ; ... install modified sr
                                ; ... from stack!