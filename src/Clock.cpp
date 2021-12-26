#include"include/Clock.h"
#include<stdio.h>
GameClock::GameClock() {
    totalTime = 0;
    DeltaTime = 0;
    lastClock = clock();
}
void GameClock::updateClock() {
    clock_t TimeTMP = clock();
    printf("time :%f\ntime last: %f\n", (double)TimeTMP / CLOCKS_PER_SEC, (double)lastClock / CLOCKS_PER_SEC);
    DeltaTime = TimeTMP - lastClock;
    totalTime += DeltaTime;
    lastClock = TimeTMP;
}
void GameClock::initClock() {
    lastClock = clock();
    totalTime = 0;
    DeltaTime = 0;
}
clock_t GameClock::getTotalTime() {
    return totalTime;
}
clock_t GameClock::getDeltaTime() {
    return DeltaTime;
}