
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winuser.h>
#include <math.h>

#include "board.h"
#include "search.h"
#include "makemove.h"
#include "move.h"
#include "checkerboard.h"
#include "movegen.h"
#include "hash.h"
#include "util.h"
#include "fen.h"
#include "eval.h"

int WINAPI getmove(int b[8][8], int color, double maxtime, char str[255], int *playnow, int info, int unused, struct CBmove *move);
int WINAPI enginecommand(char str[256], char reply[256]);

static int contains(BOARD b[], int n, BOARD *item);
static int boardgen(BOARD *b, int btm, BOARD succ[]);

#define MEGABYTE            (1 << 20)
#define KILOBYTE            (1 << 10)

static int col[32] =    {   1, 0, 7, 6, 5, 4, 3, 2, 
                1, 0, 7, 6, 5, 4, 3, 2, 
                1, 0, 7, 6, 5, 4, 3, 2, 
                1, 0, 7, 6, 5, 4, 3, 2 };  
        
static int row[32] =    {   7, 6, 3, 2, 1, 0, 7, 6, 
                5, 4, 1, 0, 7, 6, 5, 4, 
                3, 2, 7, 6, 5, 4, 3, 2, 
                1, 0, 5, 4, 3, 2, 1, 0 };
        
static int sq[8][8] ={
    
    25, -1, 17, -1,  9, -1,  1, -1,
    -1, 24, -1, 16, -1,  8, -1,  0,
    31, -1, 23, -1, 15, -1,  7, -1,
    -1, 30, -1, 22, -1, 14, -1,  6,
     5, -1, 29, -1, 21, -1, 13, -1,
    -1,  4, -1, 28, -1, 20, -1, 12,
    11, -1,  3, -1, 27, -1, 19, -1,
    -1, 10, -1,  2, -1, 26, -1, 18 };

    
static int cb_piece[16] = { 0, 6, 5, 0, 0, 10, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static int db_piece[16] = { 0, 0, 0, 0, 0, 2, 1, 0, 0, 6, 5, 0, 0, 0, 0, 0 };

static int initialized;

BOOL WINAPI DllEntryPoint (HANDLE hDLL, DWORD dwReason, LPVOID lpReserved) {

    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_PROCESS_DETACH:
            free(TT);
            free(RT);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        default:
            break;
        }
    return 1;
}


int WINAPI enginecommand(char str[256], char reply[256]) {
    
    char command[256];
    char param1[256];
    char param2[256];
    int btm; 
    int score; 
    BOARD b; 
    int nmegs;
    char *endptr;
    TTBUCKET *temp;
    int size;

    sscanf(str,"%s %s %s", command, param1, param2);

    if(strcmp(command, "name") == 0) {
        sprintf(reply, "damascus");
        return 1;
    }

    if(strcmp(command, "about") == 0) {
        sprintf(reply, "damascus");
        return 1;
    }

    if(strcmp(command,"help") == 0) {
        sprintf(reply, "?");
        return 0;
    }

    if (strcmp(command, "staticevaluation") == 0) {
        parse_fen(param1, &b, &btm);
        score = eval(&b, btm);
        sprintf(reply, "value %d", score);
        return 1;
    }

    if(strcmp(command, "set") == 0) {
        if(strcmp(param1, "hashsize") == 0) {
            nmegs = strtol(param2, &endptr, 10);
            if(nmegs > 0) {
                size = (nmegs * MEGABYTE) / sizeof(TTBUCKET);
                if((temp = (TTBUCKET *) malloc(sizeof(TTBUCKET)*size)) != 0) {
                    memset(temp, 0, sizeof(TTBUCKET)*size);
                    free(TT);
                    TT = temp;
                    TTSIZE = size;
                    TTAGE = 0;
                }
            }
            sprintf(reply, "%d", (sizeof(TTBUCKET)*TTSIZE)/MEGABYTE);
            return 1;
        }
        if(strcmp(param1,"book") == 0) {
            sprintf(reply, "?");
            return 0;
        }
    }
    
    if(strcmp(command,"get")==0) {
        if(strcmp(param1, "hashsize") == 0) {
            sprintf(reply, "%d", (sizeof(TTBUCKET)*TTSIZE)/MEGABYTE);
            return 1;
        }
        if(strcmp(param1, "book") == 0) {
            sprintf(reply, "?");
            return 0;
        }
        if(strcmp(param1,"protocolversion") == 0) {
            sprintf(reply, "2");
            return 1;
        }
        if(strcmp(param1, "gametype") == 0) {
            sprintf(reply, "21");
            return 1;
        }
    }
    
    sprintf(reply, "?");
    return 0;
}


int WINAPI getmove(int cb[8][8], int color, double maxtime, char str[255], int *playnow, int info, int unused, struct CBmove *move) {

    BOARD b;
    int btm;
    MOVE m;
    int i,j;
	static BOARD lastboard;
	static int lastbtm;
	BOARD succ[64];


    if(!initialized) {

		if(!TT) {
			TTSIZE = 1 * MEGABYTE;
			TT = (TTBUCKET *) malloc(sizeof(TTBUCKET)*TTSIZE);
		}
        
		RTSIZE = 2 * KILOBYTE;
		RT = (RTBUCKET *) malloc(sizeof(RTBUCKET)*RTSIZE);

		if(!TT || !RT) {
			free(TT);
			free(RT);
			return UNKNOWN;
		}

        memset(TT, 0, sizeof(TTBUCKET)*TTSIZE);
        memset(RT, 0, sizeof(RTBUCKET)*RTSIZE);

        TTAGE = 0;

        initialized = 1;

    }
    
    for(j = 0; j < 8; j++) { 
        for(i = j & 1; i < 8; i++, i++) {
            setpiece(&b, sq[i][j], db_piece[cb[i][j]]); 
        }
    } 

    if(color == 2) btm = 1; else btm = 0;

	if(!(boardequals(&lastboard, &b) && lastbtm == btm)) {
		if(!contains(succ, boardgen(&lastboard, lastbtm, succ), &b)) {
			memset(TT, 0, sizeof(TTBUCKET)*TTSIZE);
			memset(RT, 0, sizeof(RTBUCKET)*RTSIZE);
			TTAGE = 0;
		}
	}
	
	TTAGE++;

	if(!repchk(&b, btm)) {
        setrep(&b, btm);
    }

    if(search(&b, btm, maxtime, str, playnow, &m) != 0) { 
        makemove(&b, &m);
        btm = !btm;
    }

    if(!repchk(&b, btm)) {
        setrep(&b, btm);
    }

    for(i = 0; i < 32; i++) {
        cb[col[i]][row[i]] = cb_piece[getpiece(&b, i)];
    }

	lastboard = b;
	lastbtm = btm;

    return UNKNOWN;

}


static int contains(BOARD b[], int n, BOARD *item) {
    
    int i;

    for(i = 0; i < n; i++) {
        if(boardequals(&b[i], item))
            return 1;
    }

    return 0;

}


static int boardgen(BOARD *b, int btm, BOARD succ[]) {

    MOVE m[64];
    int i, n;

    n = movegen(b, btm, m);

    for(i = 0; i < n; i++) {
        makemove(copyboard(&succ[i], b), &m[i]);
    }

    return n;

}
