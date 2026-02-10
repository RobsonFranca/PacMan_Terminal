#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <sys/time.h>

void config_term(){
    system("chcp 65001");
    system("mode con cols=100 lines=35");
    printf("\033[8;35;100t");
    gotoxy(0,0);
}

struct timeval get_current_time()
{
	 struct timeval tv;
	 gettimeofday( &tv, NULL );
	 return tv;
}

int get_current_time_int()
{
	 struct timeval start_time = get_current_time();
	 int t1 = (int)start_time.tv_sec + ( start_time.tv_usec / 1000000 );
	 return t1;
}

#ifndef EXIST_GETCH
char getch(void) {
    struct termios oldt, newt;
    char c;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return c;
}
#endif // EXIST_GETCH
