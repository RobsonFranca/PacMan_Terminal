#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void non_canonical_mode() {
    #ifndef _WIN32
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO); // Desliga espera pelo Enter e o eco das teclas
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    #endif
}

void canonical_mode() {
    #ifndef _WIN32
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    #endif
}

void config_term(){
    system("chcp 65001");
    system("mode con cols=100 lines=35");
    printf("\033[8;35;100t");
    non_canonical_mode();
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
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif // EXIST_GETCH

#ifndef EXIST_KBHIT
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Salva as configurações atuais do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Desativa o modo canônico (que espera o Enter) e o eco (mostrar a tecla)
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Torna a leitura do terminal não-bloqueante
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    // Restaura as configurações originais
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin); // Corrigido para ungetc
        return 1;
    }

    return 0;
}
#endif // EXIST_KBHIT
