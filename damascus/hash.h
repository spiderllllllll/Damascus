
#ifndef HASH_H
#define HASH_H

#include "board.h"

typedef struct {
    int occupied;
    BOARD key;
    int score;
    int depth;
    short int type;
    short int age;
    int move;
} TTBUCKET;

typedef struct {
    int occupied;
    BOARD key;
} RTBUCKET;

#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

extern TTBUCKET *TT;
extern RTBUCKET *RT;

extern int TTSIZE;
extern int RTSIZE;
extern int TTAGE;

unsigned int hash(BOARD *key);
void store(BOARD *key, int btm, int depth, int score, int type, int move);
int probe(BOARD *key, int btm, int depth, int *score, int *type, int *move);
void setrep(BOARD *key, int btm);
int repchk(BOARD *key, int btm);
void delrep(BOARD *key, int btm);

#endif
