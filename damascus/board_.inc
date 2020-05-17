
IFNDEF BOARD__INC 
       BOARD__INC EQU <1>

ROW1    EQU  ((1 SHL 25) OR (1 SHL 31) OR (1 SHL  5) OR (1 SHL 11))
ROW2    EQU  ((1 SHL 24) OR (1 SHL 30) OR (1 SHL  4) OR (1 SHL 10))
ROW3    EQU  ((1 SHL 17) OR (1 SHL 23) OR (1 SHL 29) OR (1 SHL  3))
ROW4    EQU  ((1 SHL 16) OR (1 SHL 22) OR (1 SHL 28) OR (1 SHL  2))
ROW5    EQU  ((1 SHL  9) OR (1 SHL 15) OR (1 SHL 21) OR (1 SHL 27))
ROW6    EQU  ((1 SHL  8) OR (1 SHL 14) OR (1 SHL 20) OR (1 SHL 26))
ROW7    EQU  ((1 SHL  1) OR (1 SHL  7) OR (1 SHL 13) OR (1 SHL 19))
ROW8    EQU  ((1 SHL  0) OR (1 SHL  6) OR (1 SHL 12) OR (1 SHL 18))

COL1    EQU  ((1 SHL 25) OR (1 SHL 17) OR (1 SHL  9) OR (1 SHL  1))
COL2    EQU  ((1 SHL 24) OR (1 SHL 16) OR (1 SHL  8) OR (1 SHL  0))
COL3    EQU  ((1 SHL 31) OR (1 SHL 23) OR (1 SHL 15) OR (1 SHL  7))
COL4    EQU  ((1 SHL 30) OR (1 SHL 22) OR (1 SHL 14) OR (1 SHL  6))
COL5    EQU  ((1 SHL  5) OR (1 SHL 29) OR (1 SHL 21) OR (1 SHL 13))
COL6    EQU  ((1 SHL  4) OR (1 SHL 28) OR (1 SHL 20) OR (1 SHL 12))
COL7    EQU  ((1 SHL 11) OR (1 SHL  3) OR (1 SHL 27) OR (1 SHL 19))
COL8    EQU  ((1 SHL 10) OR (1 SHL  2) OR (1 SHL 26) OR (1 SHL 18))
                
BLACKBACKROW    EQU   ROW1
WHITEBACKROW    EQU   ROW8

ELSE
    echo ------------------------------------
    echo Duplicate include file board_.inc 
    echo ------------------------------------
ENDIF


