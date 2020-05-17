

static int _brd2sqr_[33] = {-1,11,5,31,25,10,4,30,24,3,29,23,17,2,28,22,16,27,21,15,9,26,20,14,8,19,13,7,1,18,12,6,0};
static int _sqr2brd_[32] = {32,28,13,9,6,2,31,27,24,20,5,1,30,26,23,19,16,12,29,25,22,18,15,11,8,4,21,17,14,10,7,3};

int brd2sqr(int square) {

    if(square < 1 || square > 32)   
        return -1;
    else
        return _brd2sqr_[square];

}


int sqr2brd(int square) {
    
    if(square < 0 || square > 31)   
        return -1;
    else
        return _sqr2brd_[square];

}

