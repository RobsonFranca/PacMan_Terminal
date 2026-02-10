#ifndef GAME_H
#define GAME_H

#ifdef _WIN32
    #include <windows.h>
    #define _sleep(x) Sleep(x)
#else
    #include <unistd.h>
    #define _sleep(x) usleep((x)*1000)
#endif

void update();
void setStatus(int n);
void loop(char show_info);
void key_event(char key, char exp);

#endif // GAME_H
