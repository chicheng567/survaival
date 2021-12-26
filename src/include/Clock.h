#include<time.h>
class GameClock {
private:
    //attributes
    clock_t totalTime;
    clock_t DeltaTime;
    clock_t lastClock;
public:
    //constructor and functions
    GameClock();
    void updateClock();
    void initClock();
    clock_t getTotalTime();
    clock_t getDeltaTime();
};