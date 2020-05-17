
#include "hash.h"

/* Transposition Table and Repitition Table must be initialized to a size
/* 2^n where n > 0 */

TTBUCKET *TT;
RTBUCKET *RT;

int TTSIZE;
int RTSIZE;

int TTAGE;

unsigned int hash(BOARD *key) {
    unsigned int a,b,c;
    a = key->black + 0xcafecafe;
    b = key->white + 0xcafecafe;
    c = key->kings + 0xcafecafe;
    mix(a,b,c);
    return c;
}


void store(BOARD *key, int btm, int depth, int score, int type, int move) {
    
    unsigned int i;
    
	if(!TT)
		return;

    if(btm) {
        i = (2 * hash(key) + 0) & (TTSIZE - 1);
    }
    else {
        i = (2 * hash(key) + 1) & (TTSIZE - 1);
    }

    if(!TT[i].occupied || TT[i].age < TTAGE || depth >= TT[i].depth) {
        TT[i].occupied = 1;
        TT[i].key = *key;
        TT[i].depth = depth;
        TT[i].score = score;
        TT[i].type = type;
        TT[i].move = move;
        TT[i].age = TTAGE;
    }

}

int probe(BOARD *key, int btm, int depth, int *score, int *type, int *move) {

    unsigned int i;

	if(!TT)
		return 0;

    if(btm) {
        i = (2 * hash(key) + 0) & (TTSIZE - 1);
    }
    else {
        i = (2 * hash(key) + 1) & (TTSIZE - 1);
    }

	if(TT[i].occupied && TT[i].key.black == key->black && TT[i].key.white == key->white && TT[i].key.kings == key->kings) {
        if(TT[i].age < TTAGE) TT[i].age = TTAGE;
        *move = TT[i].move;
        if(TT[i].depth >= depth) {
            *score = TT[i].score;
            *type = TT[i].type;
            return 2;
        }
        return 1;
    }
    return 0;
}


void setrep(BOARD *key, int btm) {
    
    unsigned int i;
	unsigned int h;

	if(!RT)
		return;

    if(btm) {
        h = (2 * hash(key) + 0) & (RTSIZE - 1);
    }
    else {
        h = (2 * hash(key) + 1) & (RTSIZE - 1);
    }
    
	i = h;

    for(;;) {

		if(!RT[i].occupied) {
            RT[i].occupied = 1;
            RT[i].key = *key;
            return;
        }

		i = (i + 2) & (RTSIZE - 1);

		if(i == h)
			return;
    }

}


int repchk(BOARD *key, int btm) {
    
    unsigned int i;
    unsigned int h;

	if(!RT)
		return 0;

    if(btm) {
        h = (2 * hash(key) + 0) & (RTSIZE - 1);
    }
    else {
        h = (2 * hash(key) + 1) & (RTSIZE - 1);
    }

	i = h;

	for(;;) {
		
		if(RT[i].occupied == 0) 
			return 0;

		if(RT[i].key.black == key->black && \
		   RT[i].key.white == key->white && \
		   RT[i].key.kings == key->kings) 
			return 1;

		i = (i + 2) & (RTSIZE - 1);
	   
		if(i == h)
			return 0;
    
	}

}


void delrep(BOARD *key, int btm) {
    
    unsigned int i;
    unsigned int h;

	if(!RT)
		return;

    if(btm) {
        h = (2 * hash(key) + 0) & (RTSIZE - 1);
    }
    else {
        h = (2 * hash(key) + 1) & (RTSIZE - 1);
    }

	i = h;

	for(;;) {
	
		if(RT[i].occupied == 0) 
			return;

		if(RT[i].key.black == key->black && \
		   RT[i].key.white == key->white && \
		   RT[i].key.kings == key->kings) {
			RT[i].occupied = 0;
			return;
		}

		i = (i + 2) & (RTSIZE - 1);
		
		if(i == h)
			return;
    
	}

}

