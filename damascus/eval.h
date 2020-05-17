
#ifndef EVAL_H
#define EVAL_H

#include "board.h"

#define MVAL 200
#define KVAL 300

/* formations */
#define BLACK_BACK_ROW_BRIDGE   ((1 << 31) | (1 << 11)) 
#define WHITE_BACK_ROW_BRIDGE   ((1 << 12) | (1 <<  0))
#define BLACK_TRIANGLE_OF_OREO  ((1 << 31) | (1 << 30) | (1 << 5)) 
#define WHITE_TRIANGLE_OF_OREO  ((1 << 12) | (1 << 13) | (1 << 6)) 
#define BLACK_SHORT_DYKE        ((1 << 17) | (1 << 16) | (1 << 15)) 
#define WHITE_SHORT_DYKE        ((1 << 26) | (1 << 27) | (1 << 28)) 
#define BLACK_LONG_DYKE         ((1 << 5)  | (1 << 11) | (1 << 4) | (1 << 29) | (1 << 22) | (1 << 15))
#define WHITE_LONG_DYKE         ((1 << 6)  | (1 <<  0) | (1 << 7) | (1 << 14) | (1 << 21) | (1 << 28)) 

#define BLACK_SYSTEM (COL1 | COL3 | COL5 | COL7)
#define WHITE_SYSTEM (COL2 | COL4 | COL6 | COL8)

#define CENTER4                 ((1 << 28) | (1 << 22) | (1 << 21) | (1 << 15)) 
#define CENTER8                 ((1 << 29) | (1 << 23) | (1 << 28) | (1 << 22) | (1 << 21) | (1 << 15) | (1 << 20) | (1 << 14)) 

#define LEFT  (COL1 | COL2 | COL3 | COL4)
#define RIGHT (COL5 | COL6 | COL7 | COL8)

#define SQ0     (1 << 0)
#define SQ1     (1 << 1)
#define SQ2     (1 << 2)
#define SQ3     (1 << 3)
#define SQ4     (1 << 4)
#define SQ5     (1 << 5)
#define SQ6     (1 << 6)
#define SQ7     (1 << 7)
#define SQ8     (1 << 8)
#define SQ9     (1 << 9)
#define SQ10    (1 << 10)
#define SQ11    (1 << 11)
#define SQ12    (1 << 12)
#define SQ13    (1 << 13)
#define SQ14    (1 << 14)
#define SQ15    (1 << 15)
#define SQ16    (1 << 16)
#define SQ17    (1 << 17)
#define SQ18    (1 << 18)
#define SQ19    (1 << 19)
#define SQ20    (1 << 20)
#define SQ21    (1 << 21)
#define SQ22    (1 << 22)
#define SQ23    (1 << 23)
#define SQ24    (1 << 24)
#define SQ25    (1 << 25)
#define SQ26    (1 << 26)
#define SQ27    (1 << 27)
#define SQ28    (1 << 28)
#define SQ29    (1 << 29)
#define SQ30    (1 << 30)
#define SQ31    (1 << 31)

int eval(BOARD *b, int btm);

#endif
