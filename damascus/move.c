
#include <string.h>
#include <stdlib.h>

#include "move.h"
#include "square.h"

int movecmp(MOVE *m1, MOVE *m2) {

    int i;

    if(m1->pathlen != m2->pathlen) 
        return 0;

    for(i = 0; i < m1->pathlen; i++) {
        if(m1->path[i] != m2->path[i])
            return 0;
    }

    return 1;
}


MOVE *move_from_string(char *s, MOVE *m) {

    char *endptr;
    int i;
    
    if(brd2sqr((int)strtol(s, &endptr, 10)) == -1) 
        return 0;

    for(i = 1; *endptr == '-'; i++) {
        if(brd2sqr((int)strtol(endptr + 1, &endptr, 10)) == -1)  
            return 0;
    }

    if(*endptr != '\0' || i < 2 || i > 10)
        return 0;

    m->path[0] = brd2sqr((int)strtol(s, &endptr, 10));

    for(i = 1; *endptr == '-'; i++) {
        m->path[i] = brd2sqr((int)strtol(endptr + 1, &endptr, 10));
    }

    m->pathlen = i;

    return m;

}


char *move_to_string(MOVE *m, char *s) {

    int i;
    char temp[8];

    strcpy(s, _itoa(sqr2brd(m->path[0]), temp, 10));
    
    for(i = 1; i < m->pathlen; i++) {
        strcat(s, "-");
        strcat(s, _itoa(sqr2brd(m->path[i]), temp, 10));
    }

    return s;

}

