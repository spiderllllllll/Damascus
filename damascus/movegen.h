
#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"
#include "move.h"

int movegen(BOARD *b, int btm, MOVE m[]);
int getjumps(BOARD *b, int btm, MOVE m[]);
int getmoves(BOARD *b, int btm, MOVE m[]);
int getblackmoves(BOARD *b, int x, MOVE m[]);
int getwhitemoves(BOARD *b, int x, MOVE m[]);
int getblackjumps(BOARD *b, int x, MOVE m[]);
int getwhitejumps(BOARD *b, int x, MOVE m[]);

#endif

