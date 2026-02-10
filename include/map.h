#ifndef MAP_H
#define MAP_H

typedef struct{
    int x;
    int y;
    int point;
    char hidden;
} Food;

typedef struct{
    int x;
    int y;
} Intersection;

char *getFoodPosition(int x, int y);
char isWall(int x, int y);
char isIntersection(int x, int y);
int getPoint(int x, int y);
void renderMap();
char getHasFood();

#endif // MAP_H
