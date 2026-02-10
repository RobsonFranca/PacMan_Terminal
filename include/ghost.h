#ifndef GHOST_H
#define GHOST_H

#include "utils.h"

typedef struct {
    int x;
    int x_ant;
    int y;
    int y_ant;
    int x_stop;
    int y_stop;
    enum DIRECTION dir;
    char color[10];
    int start_in;
    int interator;
} Ghost;

void renderGhost(Ghost g_aux);
char isDeadPlayer(int x, int y);
void deadGhost(int x, int y);
void initGhost();
void updateGhost();

#endif // GHOST_H
