#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"

#define TECLA_CIMA     0x1
#define TECLA_BAIXO    0x2
#define TECLA_ESQUERDA 0x3
#define TECLA_DIREITA  0x4

enum STATUS_GAME{RUNING,STOPED};

typedef struct {
    int x;
    int x_ant;
    int y;
    int y_ant;
    enum DIRECTION dir;
    enum DIRECTION pre_dir;
    int point;
    int life;
    int power_time;
    char is_power;
} Player;

char getIsPowerPlayer();
void renderPlayer();
void debugPlayer();
void initPlayer();
void updatePlayer();
char getHasLifePlayer();
void movePlayer(char key);
void getPosPlayer(int*x, int*y);

#endif // PLAYER_H
