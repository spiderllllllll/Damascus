
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <winuser.h>

#include "movegen.h"
#include "terminal.h"
#include "square.h"
#include "eval.h"
#include "makemove.h"
#include "hash.h"

static void rate_moves(MOVE m[], int n, int ttmove, int ply, int rate[]);
static int pick(int score[], int n, int *k);
static int quiscence(BOARD *b, int btm, int alpha, int beta, int ply);
static int negamax(BOARD *b, int btm, int alpha, int beta, int depth, int ply, int *playnow);
static int searchroot(BOARD *b, int btm, int alpha, int beta, int depth, MOVE m[], int n, int *playnow, MOVE *best);
static char *pv_to_string(char *s);
static char *short_move_to_string(int move, char *s);
static int get_short_move(MOVE *m);

#define MAXDEPTH        64
#define MAXPLY          64

#define INFINITY        1000000

#define TTMOVE_SCORE    3000
#define PVMOVE_SCORE    2000
#define KILLER_1_SCORE  1000
#define KILLER_2_SCORE  500

#define UPPERBOUND  0
#define LOWERBOUND  1
#define EXACT       2

#define SRC(x)  (((x) >> 5) & 0x1f) 
#define DST(x)  ((x) & 0x1f)

static int pv[MAXPLY][MAXPLY];
static int killer[MAXPLY][2];
static int pvlen[MAXPLY];

static int terminate;
static int nodecount;
static double endtime;

MOVE *search(BOARD *b, int btm, double maxtime, char str[256], int *playnow, MOVE *best) {
    
    MOVE m[64];
    MOVE rootbest; 
    char s[512];
    int depth;
    int score;
    int i;
    int j;
    int n;

    n = movegen(b, btm, m);
    
    if(n == 0) {
        return 0;
    }

    *best = m[0];
    
    if(n == 1) {
        return best;
    }

    for(i = 0; i < MAXPLY; i++) {
    for(j = 0; j < MAXPLY; j++) {
        pv[i][j] = 0;           
    }
    }
        
    for(i = 0; i < MAXPLY; i++) {
        pvlen[i] = 0;
    }
    
    for(i = 0; i < MAXPLY; i++) {
        killer[i][0] = 0;
        killer[i][1] = 0;
    }

    terminate = 0;
    nodecount = 0;
    endtime = (double)clock() + maxtime * CLOCKS_PER_SEC; 

    for(depth = 2; depth <= MAXDEPTH; depth += 2) {
        score = searchroot(b, btm, -INFINITY, +INFINITY, depth, m, n, playnow, &rootbest);
	    if(terminate) {
            break;
        }
        else {
            *best = rootbest;       
            sprintf(str, "Node Count %d Depth %d Score %d Best %s", nodecount, depth, score, short_move_to_string(get_short_move(&rootbest), s));
		}
    }

    return best;
}



static char *short_move_to_string(int move, char *s) {

    char temp[16];
    
    s[0] = '\0';

    strcat(s, _itoa(sqr2brd(SRC(move)), temp, 10));
    strcat(s, "-");
    strcat(s, _itoa(sqr2brd(DST(move)), temp, 10));
    
    return s;
}



static int get_short_move(MOVE *m) {
    return (m->path[0] << 5) | m->path[m->pathlen-1];
}



static char *pv_to_string(char *s) {
        
    int i;
    char temp[16];

    s[0] = '\0';

    for(i = 0; i < pvlen[0]; i++) {
        strcat(s, short_move_to_string(pv[0][i], temp));
        strcat(s, ";");
    }

    return s;
    
}


static int searchroot(BOARD *b, int btm, int alpha, int beta, int depth, MOVE m[], int n, int *playnow, MOVE *rootbest) {

	int rate[64];
    int original_alpha;
    int score;
    int k;
    int i;
    int best;
    int ttmove;
    int type;
    BOARD b2;

	if((++nodecount & 0xfff) == 0 && ((double)clock() >= endtime || *playnow)) {
        terminate = 1;
        return 0;
    }

	if(probe(b, btm, depth, &score, &type, &ttmove) == 0) {
		ttmove = 0;
	}

	rate_moves(m, n, ttmove, 0, rate);

	original_alpha = alpha;

	for(i = 0; i < n; i++) {
		pick(rate, n, &k);
        makemove(copyboard(&b2, b), &m[k]);
		if(i == 0) {
			score = -negamax(&b2, !btm, -beta, -alpha, depth - 1, 1, playnow);
		}
		else {
			score = -negamax(&b2, !btm, -(alpha + 1), -alpha, depth - 1, 1, playnow);
			if(score > alpha && score < beta) {
				score = -negamax(&b2, !btm, -beta, -alpha, depth - 1, 1, playnow);
			}
		}
		if(score > alpha) {
			alpha = score;
			best = get_short_move(&m[k]);
			*rootbest = m[k];
			if(alpha >= beta) {
				break;
			}
		}
	}

	if(alpha >= beta) {
        killer[0][1] = killer[0][0];
        killer[0][0] = best;
    }
    else if(alpha > original_alpha) {
        pv[0][0] = best;
        for(i = 1; i <= pvlen[1]; i++) 
            pv[0][i] = pv[1][i];
        pvlen[0] = pvlen[1] + 1;
    }

    if(alpha >= beta) {
        store(b, btm, depth, beta, LOWERBOUND, best); 
        return beta;
    }
    else if(alpha > original_alpha) {
        store(b, btm, depth, alpha, EXACT, best); 
        return alpha;
    }
    else {
        store(b, btm, depth, alpha, UPPERBOUND, 0); 
        return alpha;
    }



}


static int negamax(BOARD *b, int btm, int alpha, int beta, int depth, int ply, int *playnow) {

    MOVE m[64];
    int rate[64];
    int original_alpha;
    int score;
    int k;
    int i;
    int n;
    int best;
    int ttmove;
    int RESULT;
    int type;
    BOARD b2;

    if((++nodecount & 0xfff) == 0 && ((double)clock() >= endtime || *playnow)) {
        terminate = 1;
        return 0;
    }

    if(terminal(b, btm)) {
        if(-INFINITY + ply <= alpha) {
            return alpha;
        }
        else if(-INFINITY + ply >= beta) {
            return beta;
        }
        else {
            return -INFINITY + ply;
        }
    }

    if(repchk(b, btm)) {
        if(0 <= alpha)
            return alpha;
        else if(0 >= beta)
            return beta;
        else 
            return 0;
    }

    RESULT = probe(b, btm, depth, &score, &type, &ttmove); 

	if(RESULT == 2) {
		if(alpha + 1 == beta) {
			if(type == LOWERBOUND) {
			    if(score >= beta) {
				    return beta;
				}
			}
	        else if(type == UPPERBOUND) {
		        if(score <= alpha) {
			        return alpha;
				}
			}
			else if(score <= alpha) {
				return alpha;
			}
			else {
				return beta;
	        }
        }
    }
    else if(RESULT == 0) {
        ttmove = 0;
    }

    if(depth == 0) {
		return quiscence(b, btm, alpha, beta, ply);
	}

	if(depth > 3 && alpha + 1 == beta) {
        if(beta < (INFINITY - MAXPLY - 180)) {
            if((score = negamax(b, btm, beta + 180 - 1, beta + 180, depth / 2, ply, playnow)) >= beta + 180) {
                return beta;
            }
        }
    }

	setrep(b, btm);

    n = movegen(b, btm, m);

    rate_moves(m, n, ttmove, ply, rate);

    original_alpha = alpha;

    for(i = 0; i < n; i++) {
        pick(rate, n, &k);
		makemove(copyboard(&b2, b), &m[k]);
        if(i == 0) {
            score = -negamax(&b2, !btm, -beta, -alpha, depth - 1, ply + 1, playnow);
        }
        else {
			score = -negamax(&b2, !btm, -(alpha + 1), -alpha, depth - 1, ply + 1, playnow);
            if(score > alpha && score < beta) {
                score = -negamax(&b2, !btm, -beta, -alpha, depth - 1, ply + 1, playnow);
            }
        }
        if(terminate) {
			delrep(b, btm);
            return 0;
        }
        if(score > alpha) {
            alpha = score;     
            best = get_short_move(&m[k]); 
            if(alpha >= beta)   
                break;
        }
    }

    delrep(b, btm);
    
    if(alpha >= beta) {
        if(ply < MAXPLY) {
            killer[ply][1] = killer[ply][0];
            killer[ply][0] = best;
        }
    }
    else if(alpha > original_alpha) {
        if(ply < MAXPLY) {
            pv[ply][ply] = best;
            if(ply < (MAXPLY - 1)) {
                for(i = 1; i <= pvlen[ply+1]; i++) 
                    pv[ply][ply+i] = pv[ply+1][ply+i];
                pvlen[ply] = pvlen[ply+1] + 1;
            }
        }
    }

    if(alpha >= beta) {
        store(b, btm, depth, beta, LOWERBOUND, best); 
        return beta;
    }
    else if(alpha > original_alpha) {
        store(b, btm, depth, alpha, EXACT, best); 
        return alpha;
    }
    else {
        store(b, btm, depth, alpha, UPPERBOUND, 0); 
        return alpha;
    }

}


static int pick(int score[], int n, int *k) {

    int bestscore;
    int bestindex; 
    int i;
    
    bestscore = -1;
    bestindex = -1;
    
    for(i = 0; i < n; i++) {
        if(score[i] > bestscore) {
            bestscore = score[i];
            bestindex = i;
        }
    }
    
    if(bestindex != -1) {
        score[bestindex] = -1;
        *k = bestindex;
        return 1;
    }
    
    return 0;
}


static int quiscence(BOARD *b, int btm, int alpha, int beta, int ply) {

    MOVE m[64];
    int i;
    int n;
    int score;
    BOARD b2;

    if((n = getjumps(b, btm, m)) == 0) {
        if(terminal(b, btm)) {
            if(-INFINITY + ply <= alpha) {
                return alpha;
            }
            else if(-INFINITY + ply >= beta) {
                return beta;
            }
            else {
                return -INFINITY + ply;
            }
        }
        score = eval(b, btm);
        if(score <= alpha)
            return alpha;
        else if(score >= beta)
            return beta;
        else 
            return score;
    }

    for(i = 0; i < n; i++) {
        makemove(copyboard(&b2, b), &m[i]);
        score = -quiscence(&b2, !btm, -beta, -alpha, ply + 1);
        if(score > alpha) {
            alpha = score;
            if(alpha >= beta)
                return beta;
        }
    }
    
    return alpha;

}


static void rate_moves(MOVE m[], int n, int ttmove, int ply, int rate[]) {
    
    int i;

    for(i = 0; i < n; i++) {
        if(get_short_move(&m[i]) == ttmove)  
            rate[i] = TTMOVE_SCORE;
        else if(get_short_move(&m[i]) == pv[0][ply])  
            rate[i] = PVMOVE_SCORE;
        else if(get_short_move(&m[i]) == killer[ply][0]) 
            rate[i] = KILLER_1_SCORE; 
        else if(get_short_move(&m[i]) == killer[ply][1]) 
            rate[i] = KILLER_2_SCORE;
        else 
            rate[i] = 0;
    }
}

