    
#include "makemove.h"

static int getmiddle(int square1, int square2);


void makemove(BOARD *b, MOVE *m) {

    int i;
    unsigned int srcbit, dstbit;
    unsigned int bit;

    if(m->path[0] != m->path[m->pathlen-1]) {

        srcbit = (1 << m->path[0]);
        dstbit = (1 << m->path[m->pathlen-1]);

        if(b->black & srcbit) 
            b->black |= dstbit;
        if(b->white & srcbit)
            b->white |= dstbit;
        if(b->kings & srcbit)
            b->kings |= dstbit;

        b->black &= ~srcbit;
        b->white &= ~srcbit;
        b->kings &= ~srcbit;

        b->kings |= (b->black & WHITEBACKROW) | (b->white & BLACKBACKROW);

    }
 
    if(((m->path[0] - m->path[1]) & 1) == 0) {
        
        for(i = 0; i < m->pathlen - 1; i++) {
            bit = (1 << getmiddle(m->path[i], m->path[i+1]));
            b->black &= ~bit;
            b->white &= ~bit;
            b->kings &= ~bit;
        }
    }

}



static int getmiddle(int square1, int square2) {
    
    if(abs(square1 - square2) == 18) 
        return ((square1 + square2 + 32) / 2) & 31;
    else
        return (square1 + square2) / 2;

}


