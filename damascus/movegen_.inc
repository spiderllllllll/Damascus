
IFNDEF MOVEGEN__INC 
       MOVEGEN__INC EQU <1>

EXTERNDEF getblackmovers:NEAR
EXTERNDEF getwhitemovers:NEAR
EXTERNDEF getblackjumpers:NEAR
EXTERNDEF getwhitejumpers:NEAR

ELSE
    echo ------------------------------------
    echo Duplicate include file movegen_.inc 
    echo ------------------------------------
ENDIF


