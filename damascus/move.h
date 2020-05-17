
#ifndef MOVE_H
#define MOVE_H

typedef struct {
    unsigned char path[12];
    int pathlen;
} MOVE;

MOVE *move_from_string(char *s, MOVE *m);
char *move_to_string(MOVE *m, char *s);
int movecmp(MOVE *m1, MOVE *m2);

#endif
