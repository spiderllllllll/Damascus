
#ifndef BOARD_H
#define BOARD_H

typedef unsigned int BITBOARD; 

typedef struct {
    BITBOARD black;
    BITBOARD white;
    BITBOARD kings;
} BOARD;

#define BLACK        1
#define WHITE        2
#define KING         4
#define EMPTY        0
#define BLACKMAN     1
#define BLACKKING    5
#define WHITEMAN     2
#define WHITEKING    6
#define INVALID     -1

#define ROW1 ((1 << 25) | (1 << 31) | (1 <<  5) | (1 << 11))
#define ROW2 ((1 << 24) | (1 << 30) | (1 <<  4) | (1 << 10))
#define ROW3 ((1 << 17) | (1 << 23) | (1 << 29) | (1 <<  3))
#define ROW4 ((1 << 16) | (1 << 22) | (1 << 28) | (1 <<  2))
#define ROW5 ((1 <<  9) | (1 << 15) | (1 << 21) | (1 << 27))
#define ROW6 ((1 <<  8) | (1 << 14) | (1 << 20) | (1 << 26))
#define ROW7 ((1 <<  1) | (1 <<  7) | (1 << 13) | (1 << 19))
#define ROW8 ((1 <<  0) | (1 <<  6) | (1 << 12) | (1 << 18))

#define COL1 ((1 << 25) | (1 << 17) | (1 <<  9) | (1 <<  1))
#define COL2 ((1 << 24) | (1 << 16) | (1 <<  8) | (1 <<  0))
#define COL3 ((1 << 31) | (1 << 23) | (1 << 15) | (1 <<  7))
#define COL4 ((1 << 30) | (1 << 22) | (1 << 14) | (1 <<  6))
#define COL5 ((1 <<  5) | (1 << 29) | (1 << 21) | (1 << 13))
#define COL6 ((1 <<  4) | (1 << 28) | (1 << 20) | (1 << 12))
#define COL7 ((1 << 11) | (1 <<  3) | (1 << 27) | (1 << 19))
#define COL8 ((1 << 10) | (1 <<  2) | (1 << 26) | (1 << 18))

#define BLACKBACKROW    ROW1
#define WHITEBACKROW    ROW8

void newboard(BOARD *b);
void printboard(BOARD *b, int flip);
void clearboard(BOARD *b);
BOARD *copyboard(BOARD *dst, BOARD *src);
int boardequals(BOARD *b1, BOARD *b2);
int piece_from_char(int c);
int piece_to_char(int piece);
void setpiece(BOARD *b, unsigned int square, int piece);
int getpiece(BOARD *b, unsigned int square);

#endif


