#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <Windows.h>

#define gotoxy_p(x,y) printf("\033[%d;%dH", (y), (x))

const MAX_FPS = 30;
int run_game = 0;

void config_term(){
    system("chcp 65001");
    system("mode con cols=100 lines=32");
    gotoxy_p(0,0);
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

char run = 1;
void loop(char show_info)
{
    int start_t = get_current_time_int(), current_t = get_current_time_int();
    int fps = 0;
    int sleep = 1;
    int load = 1;
    while(run){
        if(load == 0){
            update();
            if(kbhit()){
                char c = _getch();
                if(c == -32){
                    key_event(_getch(),1);
                } else {
                    key_event(c,0);
                }
            }
        }

        fps++;
        Sleep(sleep);
        current_t = get_current_time_int();
        if(current_t-start_t > 0){
            //if(show_info)printf("SLEEP: %d\n",sleep);
            if(fps>MAX_FPS){
                sleep += fps%MAX_FPS;
            } else if(fps<MAX_FPS){
                sleep -= MAX_FPS%fps;
                if(sleep<=0)sleep = 1;
            }
            if(show_info){
                gotoxy_p(60,1);
                printf("FPS: %d\n",fps);
            }
            fps = 0;
            start_t = get_current_time_int();
            if(load != 0 && load<5) {
                gotoxy_p(1,1);
                for(int j=0;j<5;j++){
                    if(load>j){
                        printf("███");
                    } else {
                        printf("░░░");
                    }
                }
                printf("load");
                if(fps>fps-5 && fps<fps+5){
                    load++;
                }
            } else if(load==5){
                load = 0;
                gotoxy_p(1,1);
                renderMap();
                initPlayer();
                initGhost();
            }
        }
    }

}

void update()
{
    if(run_game){
        updateGhost();
        updatePlayer();

        if(!(getHasFood() && getHasLifePlayer())){
            run = 0;
        }
    }
}

void key_event(char key, char exp)
{
    if(exp){
        movePlayer(key);
        if(!run_game){
            initGhost();
            run_game = 1;
        }
    }
}

void setStatus(int n)
{
    run_game = 0;
}

int main()
{
    config_term();
    loop(1);
    while(0){
    char c =_getch();
    printf("%d",c);
    }
    return 0;
}
