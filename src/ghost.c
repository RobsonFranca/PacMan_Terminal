#include "../include/ghost.h"
#include "../include/utils.h"
#include "../include/map.h"
#include "../include/player.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

Ghost g[4] = {
    {13,13,11,11,15,14,INI,"[1;31m"},
    {12,12,14,14,12,14,STOP,"[1;36m"},
    {13,13,14,14,13,14,STOP,"[1;35m"},
    {14,14,14,14,14,14,STOP,"[33m"}
};

void initGhost()
{
    for(int n=0;n<4;n++){
        Ghost *g_aux = &g[n];
        g_aux->start_in = get_current_time_int()+(n*5);
        g_aux->interator = 0;
        g_aux->x_ant = g_aux->x;
        g_aux->y_ant = g_aux->y;
        g_aux->dir = STOP;
        g_aux->x = g_aux->x_stop;
        g_aux->y = g_aux->y_stop;
    }
    g[0].dir = INI;
    for(int n=0;n<4;n++){
        renderGhost(g[n]);
    }
}

void initOnlyGhost(Ghost *g_aux)
{
    g_aux->start_in = get_current_time_int()+10;
    g_aux->interator = 0;
    g_aux->x_ant = g_aux->x;
    g_aux->y_ant = g_aux->y;
    g_aux->dir = STOP;
    g_aux->x = g_aux->x_stop;
    g_aux->y = g_aux->y_stop;
    renderGhost(*g_aux);
}

void gotoxy_g(int x, int y)
{
    gotoxy(x,y);
}

void renderGhost(Ghost g_aux)
{
    printf("[1;37m");
    printf("[1m");
    gotoxy_g(g_aux.x_ant+g_aux.x_ant,g_aux.y_ant);
    printf(getFoodPosition(g_aux.x_ant+g_aux.x_ant,g_aux.y_ant));
    if(getIsPowerPlayer()){
    printf("[1;34m");
    } else  {
    printf(g_aux.color);
    }
    gotoxy_g(g_aux.x+g_aux.x,g_aux.y);
    printf("M");
    printf("[0m");
}

double calcDist(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

double fakeMove(Ghost g_aux)
{
    int px,py;
    getPosPlayer(&px, &py);

    switch(g_aux.dir){
        case LEFT:
            g_aux.x_ant = g_aux.x;
            g_aux.y_ant = g_aux.y;
            g_aux.x -= 1;
            break;
        case DOWN:
            g_aux.x_ant = g_aux.x;
            g_aux.y_ant = g_aux.y;
            g_aux.y += 1;
            break;
        case RIGHT:
            g_aux.x_ant = g_aux.x;
            g_aux.y_ant = g_aux.y;
            g_aux.x += 1;
            break;
        case UP:
            g_aux.x_ant = g_aux.x;
            g_aux.y_ant = g_aux.y;
            g_aux.y -= 1;
            break;
        default:
            break;
    }

    return calcDist(px, py, g_aux.x, g_aux.y);
}

void updateGhost()
{
    int r = rand()%10;
    for(int n=0;n<4;n++){
        Ghost *g_aux = &g[n];
        if(g_aux->dir == INI){
            g_aux->x_ant = g_aux->x;
            g_aux->y_ant = g_aux->y;
            g_aux->x = 13;
            g_aux->y = 11;

            srand(time(NULL));
            r = (rand()+r)%10;
            if(r < 5){
                g_aux->dir = LEFT;
            } else {
                g_aux->dir = RIGHT;
            }
        }else if(g_aux->dir != STOP){
            if(g_aux->interator == 15){
                g_aux->interator = 0;

                switch(g_aux->dir){
                case LEFT:
                    g_aux->x_ant = g_aux->x;
                    g_aux->y_ant = g_aux->y;
                    g_aux->x -= 1;
                    break;
                case DOWN:
                    g_aux->x_ant = g_aux->x;
                    g_aux->y_ant = g_aux->y;
                    g_aux->y += 1;
                    break;
                case RIGHT:
                    g_aux->x_ant = g_aux->x;
                    g_aux->y_ant = g_aux->y;
                    g_aux->x += 1;
                    break;
                case UP:
                    g_aux->x_ant = g_aux->x;
                    g_aux->y_ant = g_aux->y;
                    g_aux->y -= 1;
                    break;
                default:
                    break;
                }

                if(isIntersection(g_aux->x+g_aux->x,g_aux->y)){
                    int posibilities = 0;
                    int sides[3];
                    if(g_aux->dir != DOWN && !isWall(g_aux->x+g_aux->x,g_aux->y-1)){
                        sides[posibilities++] = UP;
                    }
                    if(g_aux->dir != LEFT && !isWall(g_aux->x+g_aux->x+2,g_aux->y)){
                        sides[posibilities++] = RIGHT;
                    }
                    if(g_aux->dir != UP && !isWall(g_aux->x+g_aux->x,g_aux->y+1)){
                        sides[posibilities++] = DOWN;
                    }
                    if(g_aux->dir != RIGHT && !isWall(g_aux->x+g_aux->x-2,g_aux->y)){
                        sides[posibilities++] = LEFT;
                    }

                    if(getIsPowerPlayer()){
                        double max_dis = 0;
                        int max_index = 0;
                        for(int selected = 0; selected < posibilities; selected++){
                            g_aux->dir = sides[selected];
                            double aux_max_dis = fakeMove(*g_aux);
                            if(aux_max_dis > max_dis){
                                max_dis = aux_max_dis;
                                max_index = selected;
                            }
                        }
                        g_aux->dir = sides[max_index];
                    } else {
                        double min_dis = 1000;
                        int min_index = 0;
                        for(int selected = 0; selected < posibilities; selected++){
                            g_aux->dir = sides[selected];
                            double aux_min_dis = fakeMove(*g_aux);
                            if(aux_min_dis < min_dis){
                                min_dis = aux_min_dis;
                                min_index = selected;
                            }
                        }
                        g_aux->dir = sides[min_index];
                    }
                }

                if(g_aux->x+g_aux->x < 0){
                    g_aux->x = 27;
                }
                if(g_aux->x+g_aux->x > 54){
                    g_aux->x = 0;
                }
            }
            g_aux->interator++;
        } else {
            if(get_current_time_int()>g_aux->start_in){
                g_aux->dir = INI;
            }
        }
        renderGhost(*g_aux);
    }
}

char isDeadPlayer(int x, int y)
{
    for(int n=0;n<4;n++){
        int r = g[n].x == x && g[n].y == y;
        if(r) return 1;
    }
    return 0;
}

void deadGhost(int x, int y)
{
    for(int n=0;n<4;n++){
        int r = g[n].x == x && g[n].y == y;
        if(r){
            initOnlyGhost(&g[n]);
        }
    }
}
