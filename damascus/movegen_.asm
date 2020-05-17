
.486 
.MODEL FLAT,C

INCLUDE board_.inc

.DATA
.DATA?
.CODE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                            ;
;  NAME: getblackmovers                                      ;  
;                                                            ;
;  PARAMS:                                                   ;
;                                                            ;
;     BOARD *b                                               ;
;                                                            ;
;  DESCRIPTION:                                              ;
;                                                            ;
;   Returns the location of all Black pieces that can move   ;
;                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

getblackmovers PROC
                
            PUSH    EBP
            PUSH    EBX
            PUSH    EDI
            PUSH    ESI

            MOV     EBP,    DWORD PTR [ESP+20]

            MOV     EBX,    DWORD PTR [EBP+00]
            MOV     EDI,    DWORD PTR [EBP+04]
            MOV     ESI,    DWORD PTR [EBP+08]
                        
            MOV     EDX,    EBX
            OR      EDX,    EDI
            NOT     EDX

            XOR     EAX,    EAX
            
            ; move NW
            
            MOV     ECX,    EDX
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
            AND     ECX,    EBX
            
            OR      EAX,    ECX
            
            ; move NE
            
            MOV     ECX,    EDX
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
            AND     ECX,    EBX
            
            OR      EAX,    ECX

            ; move SW
            
            MOV     ECX,    EDX
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
            AND     ECX,    EBX
            AND     ECX,    ESI
            
            OR      EAX,    ECX

            ; move SE
            
            MOV     ECX,    EDX
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
            AND     ECX,    EBX
            AND     ECX,    ESI
            
            OR      EAX,    ECX

            POP     ESI
            POP     EDI
            POP     EBX
            POP     EBP
            RET
                                
getblackmovers ENDP


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                            ;
;  NAME: getwhitemovers                                      ;  
;                                                            ;
;  PARAMS:                                                   ;
;                                                            ;
;     BOARD *b                                               ;
;                                                            ;
;  DESCRIPTION:                                              ;
;                                                            ;
;   Returns the location of all White pieces that can move   ;
;                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

getwhitemovers PROC
                
            PUSH    EBP
            PUSH    EBX
            PUSH    EDI
            PUSH    ESI

            MOV     EBP,    DWORD PTR [ESP+20]

            MOV     EBX,    DWORD PTR [EBP+00]
            MOV     EDI,    DWORD PTR [EBP+04]
            MOV     ESI,    DWORD PTR [EBP+08]
                        
            MOV     EDX,    EBX
            OR      EDX,    EDI
            NOT     EDX

            XOR     EAX,    EAX
            
            ; move SW
            
            MOV     ECX,    EDX
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
            AND     ECX,    EDI
            
            OR      EAX,    ECX
            
            ; move SE
            
            MOV     ECX,    EDX
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
            AND     ECX,    EDI
            
            OR      EAX,    ECX
            
            ; move NW
            
            MOV     ECX,    EDX
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
            AND     ECX,    EDI
            AND     ECX,    ESI
            
            OR      EAX,    ECX
            
            ; move NE
            
            MOV     ECX,    EDX
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
            AND     ECX,    EDI
            AND     ECX,    ESI
                        
            OR      EAX,    ECX
                    
            POP     ESI
            POP     EDI
            POP     EBX
            POP     EBP
            RET

getwhitemovers ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                            ;
;  NAME: getblackjumpers                                     ;  
;                                                            ;
;  PARAMS:                                                   ;
;                                                            ;
;     BOAR\D *b                                               ;
;                                                            ;
;  DESCRIPTION:                                              ;
;                                                            ;
;   Returns the location of all Black pieces that can        ;
;   perform a jump                                           ;
;                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

getblackjumpers PROC
                
            PUSH    EBP
            PUSH    EBX
            PUSH    EDI
            PUSH    ESI

            MOV     EBP,    DWORD PTR [ESP+20]

            MOV     EBX,    DWORD PTR [EBP+00]
            MOV     EDI,    DWORD PTR [EBP+04]
            MOV     ESI,    DWORD PTR [EBP+08]
                        
            MOV     EDX,    EBX
            OR      EDX,    EDI
            NOT     EDX

            XOR     EAX,    EAX
            
            ; jump NW
            
            MOV     ECX,    EDX
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
    
            AND     ECX,    EDI
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
    
            AND     ECX,    EBX
            
            OR      EAX,    ECX
            
            ; jump NE
            
            MOV     ECX,    EDX
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
    
            AND     ECX,    EDI
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
    
            AND     ECX,    EBX
            
            OR      EAX,    ECX

            ; jump SW
            
            MOV     ECX,    EDX
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
    
            AND     ECX,    EDI
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
    
            AND     ECX,    EBX
    
            AND     ECX,    ESI
            
            OR      EAX,    ECX

            ; jump SE
            
            MOV     ECX,    EDX
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
    
            AND     ECX,    EDI
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
    
            AND     ECX,    EBX
    
            AND     ECX,    ESI
            
            OR      EAX,    ECX

            POP     ESI
            POP     EDI
            POP     EBX
            POP     EBP
            RET

getblackjumpers ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                            ;
;  NAME: getwhitejumpers                                     ;  
;                                                            ;
;  PARAMS:                                                   ;
;                                                            ;
;     BOARD *b                                               ;
;                                                            ;
;  DESCRIPTION:                                              ;
;                                                            ;
;   Returns the location of all White pieces that can        ;
;   perform a jump                                           ;
;                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


getwhitejumpers PROC
                
            PUSH    EBP
            PUSH    EBX
            PUSH    EDI
            PUSH    ESI

            MOV     EBP,    DWORD PTR [ESP+20]

            MOV     EBX,    DWORD PTR [EBP+00]
            MOV     EDI,    DWORD PTR [EBP+04]
            MOV     ESI,    DWORD PTR [EBP+08]
                        
            MOV     EDX,    EBX
            OR      EDX,    EDI
            NOT     EDX

            XOR     EAX,    EAX
            
            ; move SW
            
            MOV     ECX,    EDX
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
            
            AND     ECX,    EBX
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
            
            AND     ECX,    EDI
            
            OR      EAX,    ECX
            
            ; move SE
            
            MOV     ECX,    EDX
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
            
            AND     ECX,    EBX
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
            
            AND     ECX,    EDI
            
            OR      EAX,    ECX
            
            ; move NW
            
            MOV     ECX,    EDX
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
            
            AND     ECX,    EBX
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
            
            AND     ECX,    EDI
            
            AND     ECX,    ESI
            
            OR      EAX,    ECX
            
            ; move NE
            
            MOV     ECX,    EDX
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
            
            AND     ECX,    EBX
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
            
            AND     ECX,    EDI
            
            AND     ECX,    ESI
                        
            OR      EAX,    ECX
                    
            POP     ESI
            POP     EDI
            POP     EBX
            POP     EBP
            RET

getwhitejumpers ENDP

END
