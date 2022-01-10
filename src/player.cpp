#include"include/player.h"
#include <iostream>
#define playerSpeed 8
#define monsterSpeed 4
character::character(int y_in, int x_in, int speedSet): dir(STOP), x(x_in), y(y_in), speed(speedSet) {}

void character::movecharacter(double DeltaTime) {
    if(dir != STOP) {
       double DeltaMove = DeltaTime * speed / 1000;
       if(dir == RIGHT) x += DeltaTime;
       else if(dir == LEFT)  x -= DeltaTime;
       else if(dir == UP)    y -= DeltaTime;
       else if(dir == DOWN)  y += DeltaTime;
    }
}