#include"include/player.h"
#include <iostream>
#define playerSpeed 8
#define monsterSpeed 4
character::character(int y_in, int x_in, int speedSet): dir(RIGHT), x(x_in), y(y_in), speed(speedSet) {}

void character::movecharacter(double DeltaTime) {
    if(dir != STOP) {
       double DeltaMove = DeltaTime * speed / 1000;
       
       if(dir == RIGHT) x += DeltaMove;
       if(dir == LEFT)  x -= DeltaMove;
       if(dir == UP)    y -= DeltaMove;
       if(dir == DOWN)  y += DeltaMove;
       printf("(%f, %f) %d\nDeltaMove: %f\n", x, y, dir, DeltaMove);
    }
}