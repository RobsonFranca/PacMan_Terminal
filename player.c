#define _gotoxy_p(x,y) printf("\033[%d;%dH", (y+1), (x+1))

enum DIRECTION {
    UP,RIGHT,LEFT,DOWN,STOP
};
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

Player p = {13,13,23,23,STOP,STOP,0,3};
int interator = 0;

void initPlayer()
{
    p.x_ant = p.x;
    p.y_ant = p.y;
    p.x = 13;
    p.y = 23;
    p.dir = STOP;
    p.pre_dir = STOP;
    p.is_power = 0;
    renderPlayer();
}

void gotoxy_p(int x, int y)
{
    _gotoxy_p(x,y);
}

void renderPlayer()
{
    gotoxy_p(p.x_ant+p.x_ant,p.y_ant);
    printf(" ");
    if(p.is_power){
    printf("[34m");
    } else {
    printf("[1;33m");
    }
    printf("[1m");
    gotoxy_p(p.x+p.x,p.y);
    printf("●");
    printf("[0m");
}

void movePlayer(char key)
{
    enum DIRECTION dir_aux;
    switch(key){
    case 72:// UP
        dir_aux = UP;
        break;
    case 77: // RIGHT
        dir_aux = RIGHT;
        break;
    case 80: // DOWN
        dir_aux = DOWN;
        break;
    case 75: // LEFT
        dir_aux = LEFT;
        break;
    default:
        break;
    }
    char addInPre = -1;
    switch(dir_aux){
    case LEFT:
        addInPre = isWall(p.x+p.x-2,p.y);
        break;
    case DOWN:
        addInPre = isWall(p.x+p.x,p.y+1);
        break;
    case RIGHT:
        addInPre = isWall(p.x+p.x+2,p.y);
        break;
    case UP:
        addInPre = isWall(p.x+p.x,p.y-1);
        break;
    default:
        break;
    }
    if(addInPre){
        p.pre_dir = dir_aux;
    } else {
        p.dir = dir_aux;
        interator = 0;
    }
}

void updatePlayer()
{
    debugPlayer();
    if(p.dir != STOP){
        if(interator == 10){
            interator = 0;

            switch(p.dir){
            case LEFT:
                p.x_ant = p.x;
                p.y_ant = p.y;
                p.x -= 1;
                break;
            case DOWN:
                p.x_ant = p.x;
                p.y_ant = p.y;
                p.y += 1;
                break;
            case RIGHT:
                p.x_ant = p.x;
                p.y_ant = p.y;
                p.x += 1;
                break;
            case UP:
                p.x_ant = p.x;
                p.y_ant = p.y;
                p.y -= 1;
                break;
            default:
                break;
            }

            switch(p.pre_dir){
            case LEFT:
                if(!isWall(p.x+p.x-2,p.y)){
                    p.dir = p.pre_dir;
                    p.pre_dir = STOP;
                }
                break;
            case DOWN:
                if(!isWall(p.x+p.x,p.y+1)){
                    p.dir = p.pre_dir;
                    p.pre_dir = STOP;
                }
                break;
            case RIGHT:
                if(!isWall(p.x+p.x+2,p.y)){
                    p.dir = p.pre_dir;
                    p.pre_dir = STOP;
                }
                break;
            case UP:
                if(!isWall(p.x+p.x,p.y-1)){
                    p.dir = p.pre_dir;
                    p.pre_dir = STOP;
                }
                break;
            default:
                break;
            }

            if(p.x < 0){
                p.x = 27;
            }
            if(p.x > 27){
                p.x = 0;
            }
            if(isWall(p.x+p.x,p.y)){
                p.x = p.x_ant;
                p.y = p.y_ant;
                p.dir = p.pre_dir;
                p.pre_dir = STOP;
            }
            renderPlayer();
        }
        interator++;
    }
    int point_aux = getPoint(p.x+p.x,p.y);
    p.point += point_aux;
    if(p.is_power && get_current_time_int()>p.power_time){
        p.is_power = 0;
    }
    if(point_aux == 50){
        p.is_power = 1;
        p.power_time = get_current_time_int()+15;
        renderPlayer();
    }
    if(isDeadPlayer(p.x,p.y)){
        if(!p.is_power){
            initPlayer();
            setStatus(0);
            p.life--;
        } else {
            deadGhost(p.x,p.y);
            p.point += 100;
        }
    }
}

void debugPlayer()
{
    _gotoxy_p(60,2);
    printf("X:%d,Y:%d  ",(int)(p.x+p.x),(int)p.y);
    _gotoxy_p(60,3);
    printf("X_ANT:%d,Y_ANT:%d  ",p.x_ant+p.x_ant,p.y_ant);
    _gotoxy_p(60,4);
    printf("DIRECTION:");
    switch(p.dir){
    case LEFT:
        printf("LEFT ");
        break;
    case DOWN:
        printf("DOWN ");
        break;
    case RIGHT:
        printf("RIGHT");
        break;
    case UP:
        printf("UP   ");
        break;
    default:
        printf("STOP ");
        break;
    }
    _gotoxy_p(60,5);
    printf("PRE DIRECTION:");
    switch(p.pre_dir){
    case LEFT:
        printf("LEFT ");
        break;
    case DOWN:
        printf("DOWN ");
        break;
    case RIGHT:
        printf("RIGHT");
        break;
    case UP:
        printf("UP   ");
        break;
    default:
        printf("STOP ");
        break;
    }
    _gotoxy_p(60,6);
    printf("SCORE:%d  ",p.point);
    _gotoxy_p(60,7);
    printf("LIFE:%d  ",p.life);
    _gotoxy_p(60,8);
    printf("POWER:");
    if(p.is_power){
    printf("TRUE  ");
    } else {
    printf("FALSE ");
    }
}

char getIsPowerPlayer()
{
    return p.is_power;
}

char getHasLifePlayer()
{
    return p.life > 0;
}
