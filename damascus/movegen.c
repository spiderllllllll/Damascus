
#include <intrin.h>
#include "movegen.h"

extern int getblackmovers(BOARD *b);
extern int getwhitemovers(BOARD *b);
extern int getblackjumpers(BOARD *b);
extern int getwhitejumpers(BOARD *b);

static void _getblackkingjumps_(BITBOARD white, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count);
static void _getwhitekingjumps_(BITBOARD black, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count);
static void _getblackmanjumps_(BITBOARD white, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count);
static void _getwhitemanjumps_(BITBOARD black, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count);

int movegen(BOARD *b, int btm, MOVE m[]) {

    int x;

    if(btm) {
        if(x = getblackjumpers(b))  
			return getblackjumps(b, x, m);
        else if(x = getblackmovers(b)) 
            return getblackmoves(b, x, m);
		else
			return 0;
    }
    else {
        if(x = getwhitejumpers(b))  
            return getwhitejumps(b, x, m);
        else if(x = getwhitemovers(b)) 
            return getwhitemoves(b, x, m);
		else
			return 0;
    }

}

int getjumps(BOARD *b, int btm, MOVE m[]) {

    int x;

    if(btm) {
        if(x = getblackjumpers(b))  
            return getblackjumps(b, x, m);
		else
			return 0;
    }
    else {
        if(x = getwhitejumpers(b))  
            return getwhitejumps(b, x, m);
		else
			return 0;
    }

}

int getmoves(BOARD *b, int btm, MOVE m[]) {

    int x;

    if(btm) {
        if(x = getblackmovers(b))  
            return getblackmoves(b, x, m);
		else
			return 0;
    }
    else {
        if(x = getwhitemovers(b))  
			return getwhitemoves(b, x, m);
		else
			return 0;
    }

}

int getblackmoves(BOARD *b, int x, MOVE m[]) {

    unsigned int empty;
    unsigned int srcbit, dstbit;
	unsigned int src, dst;
    unsigned int count;

    empty = ~(b->black | b->white);

    count = 0;

    while(x) {
		srcbit = x & -x;
		if(b->kings & srcbit) {
			dstbit = _rotr(srcbit, 1);
			dstbit = dstbit & ~(ROW1 | COL1);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotr(srcbit, 7);
			dstbit = dstbit & ~(ROW1 | COL8);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotl(srcbit, 7);
			dstbit = dstbit & ~(ROW8 | COL1);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotl(srcbit, 1);
			dstbit = dstbit & ~(ROW8 | COL8);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
        }
        else {
			dstbit = _rotr(srcbit, 1);
			dstbit = dstbit & ~(ROW1 | COL1);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotr(srcbit, 7);
			dstbit = dstbit & ~(ROW1 | COL8);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
		}
		x = x & (x - 1);
	}

    return count;

}


int getwhitemoves(BOARD *b, int x, MOVE m[]) {
    
    unsigned int empty;
    unsigned int srcbit, dstbit;
    unsigned int src, dst;
    unsigned int count;

    empty = ~(b->black | b->white);

    count = 0;

	while(x) {
		srcbit = x & -x;
		if(b->kings & srcbit) {
			dstbit = _rotl(srcbit, 1);
			dstbit = dstbit & ~(ROW8 | COL8);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotl(srcbit, 7);
			dstbit = dstbit & ~(ROW8 | COL1);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotr(srcbit, 7);
			dstbit = dstbit & ~(ROW1 | COL8);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotr(srcbit, 1);
			dstbit = dstbit & ~(ROW1 | COL1);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
        }
        else {
			dstbit = _rotl(srcbit, 1);
			dstbit = dstbit & ~(ROW8 | COL8);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
			dstbit = _rotl(srcbit, 7);
			dstbit = dstbit & ~(ROW8 | COL1);
			if(empty & dstbit) {
				_BitScanForward(&src, srcbit);
				_BitScanForward(&dst, dstbit);
				m[count].path[0] = src;
				m[count].path[1] = dst;
				m[count].pathlen = 2;
				count++;		
			}
		}
		x = x & (x - 1);
	}


    return count;

}


int getblackjumps(BOARD *b, int x, MOVE m[]) {

	unsigned int empty;
    unsigned int srcbit, jumpedbit, dstbit;
	unsigned int src, dst;
    unsigned int count;

    empty = ~(b->black | b->white);

    count = 0;

    while(x) {
		srcbit = x & -x;
		if(b->kings & srcbit) {
			jumpedbit = _rotr(srcbit, 1);
			jumpedbit = jumpedbit & ~(ROW1 | COL1);
			if(b->white & jumpedbit) {
				dstbit = _rotr(jumpedbit, 1);
				dstbit = dstbit & ~(ROW1 | COL1);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getblackkingjumps_(b->white ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
			jumpedbit = _rotr(srcbit, 7);
			jumpedbit = jumpedbit & ~(ROW1 | COL8);
			if(b->white & jumpedbit) {
				dstbit = _rotr(jumpedbit, 7);
				dstbit = dstbit & ~(ROW1 | COL8);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getblackkingjumps_(b->white ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
			jumpedbit = _rotl(srcbit, 7);
			jumpedbit = jumpedbit & ~(ROW8 | COL1);
			if(b->white & jumpedbit) {
				dstbit = _rotl(jumpedbit, 7);
				dstbit = dstbit & ~(ROW8 | COL1);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getblackkingjumps_(b->white ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
			jumpedbit = _rotl(srcbit, 1);
			jumpedbit = jumpedbit & ~(ROW8 | COL8);
			if(b->white & jumpedbit) {
				dstbit = _rotl(jumpedbit, 1);
				dstbit = dstbit & ~(ROW8 | COL8);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getblackkingjumps_(b->white ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
		}
        else {
			jumpedbit = _rotr(srcbit, 1);
			jumpedbit = jumpedbit & ~(ROW1 | COL1);
			if(b->white & jumpedbit) {
				dstbit = _rotr(jumpedbit, 1);
				dstbit = dstbit & ~(ROW1 | COL1);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getblackmanjumps_(b->white, empty, dstbit, m, &count);
				}
			}
			jumpedbit = _rotr(srcbit, 7);
			jumpedbit = jumpedbit & ~(ROW1 | COL8);
			if(b->white & jumpedbit) {
				dstbit = _rotr(jumpedbit, 7);
				dstbit = dstbit & ~(ROW1 | COL8);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getblackmanjumps_(b->white, empty, dstbit, m, &count);
				}
			}
		}
		x = x & (x - 1);
	}

    return count;


}


int getwhitejumps(BOARD *b, int x, MOVE m[]) {

    unsigned int empty;
    unsigned int srcbit, dstbit, jumpedbit;
    unsigned int src, dst;
    unsigned int count;

    empty = ~(b->black | b->white);

    count = 0;

	while(x) {
		srcbit = x & -x;
		if(b->kings & srcbit) {
			jumpedbit = _rotl(srcbit, 1);
			jumpedbit = jumpedbit & ~(ROW8 | COL8);
			if(b->black & jumpedbit) {
				dstbit = _rotl(jumpedbit, 1);
				dstbit = dstbit & ~(ROW8 | COL8);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getwhitekingjumps_(b->black ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
			jumpedbit = _rotl(srcbit, 7);
			jumpedbit = jumpedbit & ~(ROW8 | COL1);
			if(b->black & jumpedbit) {
				dstbit = _rotl(jumpedbit, 7);
				dstbit = dstbit & ~(ROW8 | COL1);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getwhitekingjumps_(b->black ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
			jumpedbit = _rotr(srcbit, 7);
			jumpedbit = jumpedbit & ~(ROW1 | COL8);
			if(b->black & jumpedbit) {
				dstbit = _rotr(jumpedbit, 7);
				dstbit = dstbit & ~(ROW1 | COL8);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getwhitekingjumps_(b->black ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
			jumpedbit = _rotr(srcbit, 1);
			jumpedbit = jumpedbit & ~(ROW1 | COL1);
			if(b->black & jumpedbit) {
				dstbit = _rotr(jumpedbit, 1);
				dstbit = dstbit & ~(ROW1 | COL1);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getwhitekingjumps_(b->black ^ jumpedbit, empty ^ srcbit, dstbit, m, &count);
				}
			}
        }
        else {
			jumpedbit = _rotl(srcbit, 1);
			jumpedbit = jumpedbit & ~(ROW8 | COL8);
			if(b->black & jumpedbit) {
				dstbit = _rotl(jumpedbit, 1);
				dstbit = dstbit & ~(ROW8 | COL8);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getwhitemanjumps_(b->black, empty, dstbit, m, &count);
				}
			}
			jumpedbit = _rotl(srcbit, 7);
			jumpedbit = jumpedbit & ~(ROW8 | COL1);
			if(b->black & jumpedbit) {
				dstbit = _rotl(jumpedbit, 7);
				dstbit = dstbit & ~(ROW8 | COL1);
				if(empty & dstbit) {
					_BitScanForward(&src, srcbit);
					_BitScanForward(&dst, dstbit);
					m[count].path[0] = src;
					m[count].path[1] = dst;
					m[count].pathlen = 2;
					_getwhitemanjumps_(b->black, empty, dstbit, m, &count);
				}
			}
		}
		x = x & (x - 1);
	}


    return count;


}


static void _getblackkingjumps_(BITBOARD white, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count) {

	unsigned int jumpedbit, dstbit;
    unsigned int dst;
    int jump;
    MOVE m2;

    m2 = m[*count];

    jump = 0;

	jumpedbit = _rotr(srcbit, 1);
	jumpedbit = jumpedbit & ~(ROW1 | COL1);
	if(white & jumpedbit) {
		dstbit = _rotr(jumpedbit, 1);
		dstbit = dstbit & ~(ROW1 | COL1);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getblackkingjumps_(white ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotr(srcbit, 7);
	jumpedbit = jumpedbit & ~(ROW1 | COL8);
	if(white & jumpedbit) {
		dstbit = _rotr(jumpedbit, 7);
		dstbit = dstbit & ~(ROW1 | COL8);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getblackkingjumps_(white ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotl(srcbit, 7);
	jumpedbit = jumpedbit & ~(ROW8 | COL1);
	if(white & jumpedbit) {
		dstbit = _rotl(jumpedbit, 7);
		dstbit = dstbit & ~(ROW8 | COL1);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getblackkingjumps_(white ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotl(srcbit, 1);
	jumpedbit = jumpedbit & ~(ROW8 | COL8);
	if(white & jumpedbit) {
		dstbit = _rotl(jumpedbit, 1);
		dstbit = dstbit & ~(ROW8 | COL8);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getblackkingjumps_(white ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	if(jump == 0) {
        (*count)++;
    }
}


static void _getwhitekingjumps_(BITBOARD black, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count) {

	unsigned int jumpedbit, dstbit;
    unsigned int dst;
    int jump;
    MOVE m2;

    m2 = m[*count];

    jump = 0;

	jumpedbit = _rotl(srcbit, 1);
	jumpedbit = jumpedbit & ~(ROW8 | COL8);
	if(black & jumpedbit) {
		dstbit = _rotl(jumpedbit, 1);
		dstbit = dstbit & ~(ROW8 | COL8);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getwhitekingjumps_(black ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotl(srcbit, 7);
	jumpedbit = jumpedbit & ~(ROW8 | COL1);
	if(black & jumpedbit) {
		dstbit = _rotl(jumpedbit, 7);
		dstbit = dstbit & ~(ROW8 | COL1);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getwhitekingjumps_(black ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotr(srcbit, 7);
	jumpedbit = jumpedbit & ~(ROW1 | COL8);
	if(black & jumpedbit) {
		dstbit = _rotr(jumpedbit, 7);
		dstbit = dstbit & ~(ROW1 | COL8);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getwhitekingjumps_(black ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotr(srcbit, 1);
	jumpedbit = jumpedbit & ~(ROW1 | COL1);
	if(black & jumpedbit) {
		dstbit = _rotr(jumpedbit, 1);
		dstbit = dstbit & ~(ROW1 | COL1);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getwhitekingjumps_(black ^ jumpedbit, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	if(jump == 0) {
        (*count)++;
    }
}


static void _getblackmanjumps_(BITBOARD white, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count) {

	unsigned int jumpedbit, dstbit;
    unsigned int dst;
    int jump;
    MOVE m2;

    m2 = m[*count];

    jump = 0;

	jumpedbit = _rotr(srcbit, 1);
	jumpedbit = jumpedbit & ~(ROW1 | COL1);
	if(white & jumpedbit) {
		dstbit = _rotr(jumpedbit, 1);
		dstbit = dstbit & ~(ROW1 | COL1);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getblackmanjumps_(white, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotr(srcbit, 7);
	jumpedbit = jumpedbit & ~(ROW1 | COL8);
	if(white & jumpedbit) {
		dstbit = _rotr(jumpedbit, 7);
		dstbit = dstbit & ~(ROW1 | COL8);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getblackmanjumps_(white, empty, dstbit, m, count);
            jump = 1;
		}
	}
    
    if(jump == 0) {
        (*count)++;
    }
}




static void _getwhitemanjumps_(BITBOARD black, BITBOARD empty, unsigned int srcbit, MOVE *m, int *count) {

	unsigned int jumpedbit, dstbit;
    unsigned int dst;
    int jump;
    MOVE m2;

    m2 = m[*count];
    
    jump = 0;

	jumpedbit = _rotl(srcbit, 1);
	jumpedbit = jumpedbit & ~(ROW8 | COL8);
	if(black & jumpedbit) {
		dstbit = _rotl(jumpedbit, 1);
		dstbit = dstbit & ~(ROW8 | COL8);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getwhitemanjumps_(black, empty, dstbit, m, count);
            jump = 1;
		}
	}
	
	jumpedbit = _rotl(srcbit, 7);
	jumpedbit = jumpedbit & ~(ROW8 | COL1);
	if(black & jumpedbit) {
		dstbit = _rotl(jumpedbit, 7);
		dstbit = dstbit & ~(ROW8 | COL1);
		if(empty & dstbit) {
			_BitScanForward(&dst, dstbit);
            m[*count] = m2;
            m[*count].path[m[*count].pathlen++] = dst;
            _getwhitemanjumps_(black, empty, dstbit, m, count);
            jump = 1;
		}
	}

	if(jump == 0) {
        (*count)++;
    }
}


