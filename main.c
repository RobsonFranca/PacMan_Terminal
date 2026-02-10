#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "include/game.h"
#include "include/utils.h"

int main()
{
    config_term();
    loop(1);
    while(0){
        char c = getch();
        printf("%d",c);
    }
    canonical_mode();
    return 0;
}
