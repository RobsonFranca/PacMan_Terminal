#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include "include/game.h"
#include "include/utils.h"

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
