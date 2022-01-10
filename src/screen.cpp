#include"include/screen.h"
#include<stdio.h>
#include<graphics.h>
screen::screen() {//constructor
    page = 0;
}

void screen::update(){
    setactivepage(page);
    setvisualpage(1-page);
    page = 1-page;
    delay(5);
}

void screen::swap(){
    page = 1-page;
}
