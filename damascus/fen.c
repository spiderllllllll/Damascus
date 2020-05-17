
/* by kind permission of Ed Gilbert */

#include <ctype.h>
#include <string.h>
#include "board.h"
#include "square.h"

#define MAXSQUARE 32

int square_to_bitmask(int square)
{
    return(1 << brd2sqr(square));
}


int parse_fen(char *buf, BOARD *board, int *btm)
{
    int square;
    int color;
    int kings;
    char *lastp;

    /* Get the color. */
    if (toupper(*buf) == 'B')
        *btm = 1;
    else if (toupper(*buf) == 'W')
        *btm = 0;
    else
        return(1);

    memset(board, 0, sizeof(BOARD));

    /* Skip the colon. */
    buf += 2;
    lastp = buf;
    while (*buf) {
        kings = 0;
        if (*buf == '"') {
            ++buf;
            continue;
        }
        if (toupper(*buf) == 'W') {
            color = WHITE;
            ++buf;
            continue;
        }
        if (toupper(*buf) == 'B') {
            color = BLACK;
            ++buf;
            continue;
        }
        if (toupper(*buf) == 'K') {
            kings = 1;
            ++buf;
        }
        for (square = 0; isdigit(*buf); ++buf)
            square = 10 * square + (*buf - '0');

        if (square < 1 || square > MAXSQUARE)
            return(1);

        if (*buf == ',' || *buf == ':' || *buf == '.')
            ++buf;

        if (square) {
            if (color == WHITE)
                board->white |= square_to_bitmask(square);
            else
                board->black |= square_to_bitmask(square);
            if (kings)
                board->kings |= square_to_bitmask(square);
        }
        if (lastp == buf)
            break;
        lastp = buf;
    }
    return(0);
}

