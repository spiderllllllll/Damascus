
#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

struct move2 {
    short n;
    int m[8];
};

struct coor {
    int x;
    int y;
};

struct CBmove {
    int ismove;          
    int newpiece;        
    int oldpiece;        
    struct coor from,to; 
    struct coor path[12]; 
    struct coor del[12]; 
    int delpiece[12];    
} GCBmove;

#define DRAW 0
#define WIN 1
#define LOSS 2
#define UNKNOWN 3

#endif
