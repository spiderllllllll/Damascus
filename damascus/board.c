
#include <stdio.h>
#include "board.h"

#define WHITE_START_POSITION    ((1 << 0)  | (1 << 6)  | (1 << 12) | (1 << 18) | (1 <<  1) | (1 << 7)  | (1 << 13) | (1 << 19) | (1 << 8)  | (1 << 14) | (1 << 20) | (1 << 26))
#define BLACK_START_POSITION    ((1 << 11) | (1 << 5)  | (1 << 31) | (1 << 25) | (1 << 10) | (1 << 4)  | (1 << 30) | (1 << 24) | (1 << 3)  | (1 << 29) | (1 << 23) | (1 << 17))

int piece_to_char(int piece) {
    
    switch(piece) {
        case BLACKMAN:
            return 'b';
        case WHITEMAN:
            return 'w';
        case BLACKKING:
            return 'B';
        case WHITEKING:
            return 'W';
        case EMPTY:
            return ' ';
        default:
            return ' ';
    }
}

int piece_from_char(int c) {
    
    switch(c) {
        case 'b':
            return BLACKMAN;
        case 'w':
            return WHITEMAN;
        case 'B':
            return BLACKKING;
        case 'W':
            return WHITEKING;
        case 'e':
            return EMPTY;
        default:
            return -1;
    }
}


void newboard(BOARD *b) {
    b->black = BLACK_START_POSITION;
    b->white = WHITE_START_POSITION;
    b->kings = 0;
}

void printboard(BOARD *b, int flip) {

    char c[32]; 

    int i;

    for(i = 0; i < 32; i++) {
        c[i] = (char) piece_to_char(getpiece(b, i));
    }

    if(flip) {
        printf("          32      31      30      29      \n");
        printf("    ---------------------------------\n");
        printf("    | . | %c | . | %c | . | %c | . | %c |   \n", c[0], c[6], c[12], c[18]); 
        printf("    ---------------------------------\n");
        printf(" 28 | %c | . | %c | . | %c | . | %c | . | 25\n", c[1], c[7], c[13], c[19]); 
        printf("    ---------------------------------\n");
        printf(" 24 | . | %c | . | %c | . | %c | . | %c | 21\n", c[8], c[14], c[20], c[26]); 
        printf("    ---------------------------------\n");
        printf(" 20 | %c | . | %c | . | %c | . | %c | . | 17\n", c[9], c[15], c[21], c[27]); 
        printf("    ---------------------------------\n");
        printf(" 16 | . | %c | . | %c | . | %c | . | %c | 13\n", c[16], c[22], c[28], c[2]); 
        printf("    ---------------------------------\n");
        printf(" 12 | %c | . | %c | . | %c | . | %c | . |  9\n", c[17], c[23], c[29], c[3]); 
        printf("    ---------------------------------\n");
        printf("  8 | . | %c | . | %c | . | %c | . | %c |  5\n", c[24], c[30], c[4], c[10]); 
        printf("    ---------------------------------\n");
        printf("    | %c | . | %c | . | %c | . | %c | . |   \n", c[25], c[31], c[5], c[11]); 
        printf("    ---------------------------------\n");
        printf("      4       3       2       1         \n");
    }
    else {
        printf("          1       2       3       4      \n");
        printf("    ---------------------------------\n");
        printf("    | . | %c | . | %c | . | %c | . | %c |   \n", c[11], c[5], c[31], c[25]); 
        printf("    ---------------------------------\n");
        printf("  5 | %c | . | %c | . | %c | . | %c | . |  8\n", c[10], c[4], c[30], c[24]); 
        printf("    ---------------------------------\n");
        printf("  9 | . | %c | . | %c | . | %c | . | %c | 12\n", c[3], c[29], c[23], c[17]); 
        printf("    ---------------------------------\n");
        printf(" 13 | %c | . | %c | . | %c | . | %c | . | 16\n", c[2], c[28], c[22], c[16]); 
        printf("    ---------------------------------\n");
        printf(" 17 | . | %c | . | %c | . | %c | . | %c | 20\n", c[27], c[21], c[15], c[9]); 
        printf("    ---------------------------------\n");
        printf(" 21 | %c | . | %c | . | %c | . | %c | . | 24\n", c[26], c[20], c[14], c[8]); 
        printf("    ---------------------------------\n");
        printf(" 25 | . | %c | . | %c | . | %c | . | %c | 28\n", c[19], c[13], c[7], c[1]); 
        printf("    ---------------------------------\n");
        printf("    | %c | . | %c | . | %c | . | %c | . |   \n", c[18], c[12], c[6], c[0]); 
        printf("    ---------------------------------\n");
        printf("      29      30      31      32         \n");
    }

}

void clearboard(BOARD *b) {
    b->black = 0;
    b->white = 0;
    b->kings = 0;
}

BOARD *copyboard(BOARD *dst, BOARD *src) {
    dst->black = src->black;
    dst->white = src->white;
    dst->kings = src->kings;
    return dst;
}

int boardequals(BOARD *b1, BOARD *b2) {
    if(b1->black != b2->black) return 0;
    if(b1->white != b2->white) return 0;
    if(b1->kings != b2->kings) return 0;
    return 1;
}

void setpiece(BOARD *b, unsigned int square, int piece) {

    unsigned int bit;

    if(square < 32) {

        bit = (1 << square);

        b->black &= ~bit;
        b->white &= ~bit;
        b->kings &= ~bit;

        if(piece & BLACK) {
            b->black |= bit;
        }
        else if(piece & WHITE) {
            b->white |= bit;    
        }
        if(piece & KING) {
            b->kings |= bit;
        }
    }
        
}


int getpiece(BOARD *b, unsigned int square) {

    unsigned int bit;

    if(square < 32) {
        bit = (1 << square);
        if(b->black & bit) {
            if(b->kings & bit) {
                return BLACKKING;
            }
            else {
                return BLACKMAN;
            }
        }
        else if(b->white & bit) {
            if(b->kings & bit) {
                return WHITEKING;
            }
            else {
                return WHITEMAN;
            }
        }
        else {
            return EMPTY;
        }
    }
    else {
        return INVALID;
    }

}

