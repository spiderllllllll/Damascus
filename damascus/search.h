
#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"
#include "move.h"

MOVE *search(BOARD *b, int btm, double maxtime, char str[256], int *playnow, MOVE *best);

#endif
