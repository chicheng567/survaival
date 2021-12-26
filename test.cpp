#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
int main()
{
    clock_t DeltaTime;
    clock_t totalTime;
    clock_t lastClock;
    while(1)
    {
        clock_t TimeTMP = clock();
        DeltaTime = TimeTMP - lastClock;
        totalTime += DeltaTime;
        lastClock = totalTime;
        
    }
}