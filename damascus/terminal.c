
#include "board.h"

extern int getblackmovers(BOARD *b);
extern int getblackjumpers(BOARD *b);
extern int getwhitemovers(BOARD *b);
extern int getwhitejumpers(BOARD *b);

int terminal(BOARD *b, int btm) {

    if(btm) { 
        return ((b->white == 0) || (getblackmovers(b) == 0 && getblackjumpers(b) == 0));
    }
    else {
        return ((b->black == 0) || (getwhitemovers(b) == 0 && getwhitejumpers(b) == 0));
    }

}