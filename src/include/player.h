
#ifndef  _PLAYER_H_
#define  _PLAYER_H_
//宣告前進方向列舉函數 
enum Direction {
    STOP,
	RIGHT, 
	LEFT, 
	UP, 
	DOWN
};

class character {
public:
    double x;
    double y;
    int speed;
    Direction dir;
    
    character(int y_in, int x_in, int speedSet);
    void movecharacter(double DeltaTime);
};
#endif