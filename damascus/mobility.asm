
.486 
.MODEL FLAT,C
                            
INCLUDE board_.inc

.DATA
.DATA?
.CODE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                            ;
;  NAME: black_total_mobility                                ;  
;                                                            ;
;  PARAMS:                                                   ;
;                                                            ;
;     BOARD *b                                               ;
;                                                            ;
;  DESCRIPTION:                                              ;
;                                                            ;
;   Returns all the squares that Black can move to           ;
;                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

black_total_mobility PROC
                
            PUSH    EBP
            PUSH    EBX
            PUSH    EDI
            PUSH    ESI
            
            MOV     EBP,    DWORD PTR [ESP+20]
            
            MOV     EBX,    DWORD PTR [EBP+00]
            MOV     EDI,    DWORD PTR [EBP+04]
            MOV     ESI,    DWORD PTR [EBP+08]

            MOV     EDX,    EBX
             OR     EDX,    EDI
            NOT     EDX

            XOR     EAX,    EAX
            
            ; move NW
            
            MOV     ECX,    EBX
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
            AND     ECX,    EDX
            
            OR      EAX,    ECX
            
            ; move NE
            
            MOV     ECX,    EBX
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
            AND     ECX,    EDX
            
            OR      EAX,    ECX

            ; move SW
            
            MOV     ECX,    EBX
            AND     ECX,    ESI
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
            AND     ECX,    EDX
            
            OR      EAX,    ECX

            ; move SE
            
            MOV     ECX,    EBX
            AND     ECX,    ESI
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
            AND     ECX,    EDX
            
            OR      EAX,    ECX

            POP     ESI
            POP     EDI
            POP     EBX
            POP     EBP
            RET
                                
black_total_mobility ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                            ;
;  NAME: white_total_mobility                                ;  
;                                                            ;
;  PARAMS:                                                   ;
;                                                            ;
;     BOARD *b                                               ;
;                                                            ;
;  DESCRIPTION:                                              ;
;                                                            ;
;   Returns all the squares that White can move to           ;
;                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

white_total_mobility PROC
                
            PUSH    EBP
            PUSH    EBX
            PUSH    EDI
            PUSH    ESI
            
            MOV     EBP,    DWORD PTR [ESP+20]
            
            MOV     EBX,    DWORD PTR [EBP+00]
            MOV     EDI,    DWORD PTR [EBP+04]
            MOV     ESI,    DWORD PTR [EBP+08]

            MOV     EDX,    EBX
             OR     EDX,    EDI
            NOT     EDX
            
            XOR     EAX,    EAX
                        
            ; move SW
            
            MOV     ECX,    EDI
            ROL     ECX,    1
            AND     ECX,    NOT (ROW8 OR COL8)
            AND     ECX,    EDX
            
            OR      EAX,    ECX
            
            ; move SE
            
            MOV     ECX,    EDI
            ROL     ECX,    7
            AND     ECX,    NOT (ROW8 OR COL1)
            AND     ECX,    EDX
            
            OR      EAX,    ECX
            
            ; move NW
            
            MOV     ECX,    EDI
            AND     ECX,    ESI
            ROR     ECX,    7
            AND     ECX,    NOT (ROW1 OR COL8)
            AND     ECX,    EDX
            
            OR      EAX,    ECX
            
            ; move NE
            
            MOV     ECX,    EDI
            AND     ECX,    ESI 
            ROR     ECX,    1
            AND     ECX,    NOT (ROW1 OR COL1)
            AND     ECX,    EDX
                        
            OR      EAX,    ECX
                    
            POP     ESI
            POP     EDI
            POP     EBX
            POP     EBP
            RET
            
white_total_mobility ENDP

END
