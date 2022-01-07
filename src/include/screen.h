
#ifndef  _SCREEN_H_
#define  _SCREEN_H_
class screen
{
private:
    /* data */
    int page;
public:
    screen(/* args */);
    void update();
    void swap();
};
#endif