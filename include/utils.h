#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y+1), (x+1))

#ifdef _WIN32
    #include <conio.h>
    #define EXIST_GETCH
#else
    #include <termios.h>
    #include <unistd.h>
    char getch(void);
#endif

enum DIRECTION {
    UP,RIGHT,LEFT,DOWN,STOP,INI
};

void config_term();
struct timeval get_current_time();
int get_current_time_int();

#endif // UTILS_H
