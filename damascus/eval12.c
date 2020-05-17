
#include <stdio.h>
#include "eval.h"
#include "util.h"

int BACK[4]    = {  4, 4, 4, 4};
int CENT[4]    = {  2, 2, 2, 1};
int DOG[4]     = {  4, 4, 4, 4};
int BAL[4]     = {  2, 2, 2, 1};
int TEMPO[4]   = { -2,-1, 0, 1};
int KCENT[4]   = {  6, 6, 6, 6};
int TAIL[4]    = {  5, 5, 5, 5};
int TRAPPED[4] = {100,100,100,100 };
int THEMOVE[4] = {  0,  0,  0,  6};

int eval(BOARD *b, int btm) {

    unsigned int bm,wm,bk,wk,empty;
    int numbm, numwm, numbk, numwk, numblack, numwhite, numpieces;
    int val, score, sign, stage;

    if(btm) sign = 1; else sign = -1;

    bm = b->black & ~b->kings;
    wm = b->white & ~b->kings;
    bk = b->black & b->kings;
    wk = b->white & b->kings;
    empty = ~(b->black | b->white);
    
    numbm = popcount(bm);
    numwm = popcount(wm);
    numbk = popcount(bk);
    numwk = popcount(wk);

    numblack = numbm + numbk;
    numwhite = numwm + numwk;

    numpieces = numblack + numwhite;
    
    if(numpieces >= 20) 
        stage = 0;
    else if(numpieces >= 14)
        stage = 1;
    else if(numpieces >= 10)
        stage = 2;
    else
        stage = 3;

/**********************************************************/

    score = 0;

/**********************************************************/

/* MATERIAL BALANCE */
/* ================ */

    val = MVAL * (numbm - numwm) + KVAL * (numbk - numwk);

#ifdef DEBUG_EVAL
    printf("heuristic: MATERIAL BALANCE score: %d\n", val * sign);
#endif
    
    score += val;


/**********************************************************/

/* EXCHANGE */
/* ======== */

    if(numpieces < 10) {
        val = 8 * (10 - numpieces) * (numblack - numwhite);
    
#ifdef DEBUG_EVAL
    printf("heuristic: EXCHANGE score: %d\n", val * sign);
#endif
    
        score += val;

    }

/**********************************************************/

/* BACK */
/* ==== */

    val = ((bm >> 11) & 1)
        + ((bm >>  5) & 1)
        + ((bm >> 31) & 1)
        - ((bm >> 25) & 1)
        - ((wm >>  0) & 1)
        - ((wm >>  6) & 1)
        - ((wm >> 12) & 1)
        + ((wm >> 18) & 1);

    val = val * BACK[stage];
    
#ifdef DEBUG_EVAL
    printf("heuristic: BACK score: %d\n", val * sign);
#endif

    score += val;

/**********************************************************/

/* CENT */
/* ==== */

    val = popcount(bm & CENTER8) 
        - popcount(wm & CENTER8); 

    val *= CENT[stage];

#ifdef DEBUG_EVAL
    printf("heuristic: CENT score: %d\n", val * sign);
#endif

    score += val;

/**********************************************************/

/* DOGHOLE */
/* ======= */

    val = -(((bm & SQ1)  | (wm & SQ0))  == (SQ1  | SQ0))
          +(((wm & SQ10) | (bm & SQ11)) == (SQ10 | SQ11));

    val *= DOG[stage];

#ifdef DEBUG_EVAL
    printf("heuristic: DOGHOLE score: %d\n", val * sign);
#endif

    score += val;

/**********************************************************/
 
/* BAL */
/* === */

    val = -abs(popcount(bm & LEFT) - popcount(bm & RIGHT))
          +abs(popcount(wm & LEFT) - popcount(wm & RIGHT));

    val = val * BAL[stage];

#ifdef DEBUG_EVAL
    printf("heuristic: BAL score: %d\n", val * sign);
#endif

    score += val;

/**********************************************************/

/* TEMPO */
/* ===== */

    val = 1 * popcount(bm & ROW1) 
        + 2 * popcount(bm & ROW2)
        + 3 * popcount(bm & ROW3)
        + 4 * popcount(bm & ROW4)
        + 5 * popcount(bm & ROW5)
        + 6 * popcount(bm & ROW6)
        + 7 * popcount(bm & ROW7)
        + 8 * popcount(bk)
        - 1 * popcount(wm & ROW8) 
        - 2 * popcount(wm & ROW7)
        - 3 * popcount(wm & ROW6)
        - 4 * popcount(wm & ROW5)
        - 5 * popcount(wm & ROW4)
        - 6 * popcount(wm & ROW3)
        - 7 * popcount(wm & ROW2)
        - 8 * popcount(wk);

    val = val * TEMPO[stage];
 
#ifdef DEBUG_EVAL
    printf("heuristic: TEMPO score: %d\n", val * sign);
#endif

    score += val;

/**********************************************************/

    if(numbk | numwk) {
        
/**********************************************************/

/* KCENT */
/* ===== */

        val = popcount(bk & CENTER4) 
            - popcount(wk & CENTER4);
    
        val *= KCENT[stage];

#ifdef DEBUG_EVAL
    printf("heuristic: KCENT score: %d\n", val * sign);
#endif

        score += val;

/**********************************************************/

/* TAIL HOOKS */
/* ========== */
	
	val = popcount(((_rotl((_rotl(bk, 1) & ~(ROW8 | COL8)) & wm, 1) & ~(ROW8 | COL8)) |
					(_rotl((_rotl(bk, 7) & ~(ROW8 | COL1)) & wm, 7) & ~(ROW8 | COL1))) 
					 & wm)
		
		- popcount(((_rotr((_rotr(wk, 1) & ~(ROW1 | COL1)) & bm, 1) & ~(ROW1 | COL1)) |
				    (_rotr((_rotr(wk, 7) & ~(ROW1 | COL8)) & bm, 7) & ~(ROW1 | COL8))) 
					 & bm);


		val *= TAIL[stage];

#ifdef DEBUG_EVAL
    printf("heuristic: TAIL HOOKS score: %d\n", val * sign);
#endif

        score += val;

/**********************************************************/

/* TRAPPED */
/* ======= */

        val = 0;    
        
        if(bk & ROW8) {
            val -= (((bk & SQ18) | (wm &  SQ12) | (empty & (SQ19 | SQ26)) ) == (SQ18 | SQ12 | SQ19 | SQ26));
            val -= (((bk & SQ12) | (wm & (SQ18 | SQ6)) | (empty & (SQ19 | SQ20 | SQ13))) == (SQ12 | SQ18 | SQ6 | SQ19 | SQ20 | SQ13));
            val -= (((bk & SQ6)  | (wm & (SQ12 | SQ0)) | (empty & (SQ13 | SQ14 | SQ7))) == (SQ6 | SQ12 | SQ0 | SQ13 | SQ14 | SQ7));
            val -= (((bk & SQ0)  | (wm & (SQ6  | SQ1)) | (empty & (SQ7 | SQ8))) == (SQ0 | SQ6| SQ1 | SQ7 | SQ8));
        }

        if(wk & ROW1) {
            val += (((wk & SQ25) | (bm & SQ31) | (empty & (SQ24 | SQ17))) == (SQ25 | SQ31 | SQ24 | SQ17));
            val += (((wk & SQ31) | (bm & (SQ25 | SQ5)) | (empty & (SQ24 | SQ23 | SQ30))) == (SQ31 | SQ25 | SQ5 | SQ24 | SQ23 | SQ30));
            val += (((wk & SQ5)  | (bm & (SQ31 | SQ11)) | (empty & (SQ30 | SQ29 | SQ4)))  == (SQ5 | SQ31 | SQ11 | SQ30 | SQ29 | SQ4));
            val += (((wk & SQ11) | (bm & (SQ5  | SQ10)) | (empty & (SQ3  | SQ4))) == (SQ11 | SQ5| SQ10 | SQ3 | SQ4));
        }



        val = val * TRAPPED[stage];
    
#ifdef DEBUG_EVAL
    printf("heuristic: TRAPPED score: %d\n", val * sign);
#endif

        score += val;

/**********************************************************/

    }

/**********************************************************/

/* THEMOVE */
/* ======= */

    val = 0;

    if(((numbm - numwm) | (numbk - numwk)) == 0) {
        if(btm) {       
            val = parity((b->black | b->white) & BLACK_SYSTEM) ? 1 : -1;
        }
        else {      
            val = parity((b->black | b->white) & WHITE_SYSTEM) ? -1 : 1;
        }
    }

    val = val * THEMOVE[stage];

#ifdef DEBUG_EVAL
    printf("heuristic: THEMOVE score: %d\n", val * sign);
#endif

    score += val;

/**********************************************************/

    score *= sign;

    return score;

}