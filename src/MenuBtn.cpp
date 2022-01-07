#include"include/coreHeader.h"
#include"include/MenuBtn.h"
#include "include/screen.h"
#include "include/Clock.h"
MenuBtn::MenuBtn(int x, int y, int WIDTH, int HEIGHT) {//constructor
    startX = x;
    startY = y;
    width = WIDTH;
    height = HEIGHT;
}

//-------------------------------------------------
//initMenu

//for title and dot animation
int duration1 = 0, duration2 = 0;
int titleColor[3] = {RED, BLUE, GREEN};
int xStep = 0, yStep = 0, xf = 0, yf = 0, zombXStep = 0, zombYStep = 0;

//turn on light animation
int animation_duration[20], frame = 0;
bool play_animation = false, light_on = false;
int title_light = 0;

//options choose
int currentButton = 1;
extern screen SCREEN;
extern GameClock gameClock;
extern bool IFPause;
extern vector<MenuBtn> btn;

//menu頁面
int menu(){
	settextstyle(BOLD_FONT, HORIZ_DIR , 6);
	SCREEN.update();
	cleardevice();
	gameClock.updateClock();
	//light animation

	if(GetAsyncKeyState(VK_RIGHT)&&light_on){
		light_on = false;
		play_animation = false;
		for(int u =0;u<10;u++){
			animation_duration[u] = 0;
		}
	}
	if(GetAsyncKeyState(VK_SPACE)){
		return currentButton;
	}
	if(!play_animation&&GetAsyncKeyState(VK_LEFT)){
		play_animation = true;
		frame = 0;
	}
	if(play_animation){
		animation_duration[frame] += gameClock.getDeltaTime();
		switch (frame)
		{
		case 0:
			animate_light(animation_duration[0], 250);
			break;
		case 1:
			if(animation_duration[1]>250) frame++;
			break;
		case 2:
			animate_light(animation_duration[2], 60);
			break;
		case 3:
			animate_light(animation_duration[3], 60);
			break;
		case 4:
			animate_light(animation_duration[4], 150);
			break;
		case 5:
			animate_light(animation_duration[5], 100);
			break;
		case 6:
			animate_light(animation_duration[6], 70);
			break;
		case 7:
			if(animation_duration[7]>250) frame++;//要黑畫面，所以不進function，而是不做反應，直到達到設定時間，進到下一個frame
			break;
		case 8:
			animate_light(animation_duration[8], 280);
			break;
		case 9:
			if(animation_duration[9]>330) frame++;
			break;
		case 10:
			// animate_light(animation_duration[9], );
			light_on = true;
		default:
			break;
		}
	}
	if(light_on){
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 0, SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);	
	}
	
	duration1 += gameClock.getDeltaTime();
	duration2 += gameClock.getDeltaTime();
	//SET and PRINT TITLE: ZOMBIE SURVIVAL
	if(duration1 >= 800){
		duration1 = 0;//reset
		setcolor(titleColor[title_light]);
		if(title_light == 2) title_light = 0;
		else title_light++;
	}else setcolor(titleColor[title_light]);
	outtextxy(130, 130, "ZOMBIE");
	outtextxy(180, 200, "SURVIVAL");

	//option
	outtextxy(btn[1].startX, btn[1].startY, "Quit");
	outtextxy(btn[0].startX, btn[0].startY, "StartGame");
	if(GetAsyncKeyState(VK_UP)){//選項壞掉
		currentButton = 1;
	}else if(GetAsyncKeyState(VK_DOWN)){
		currentButton = 2;
	}

	settextstyle(BOLD_FONT, HORIZ_DIR , 6);
	if(currentButton == 1){//current == start
		setcolor(WHITE);
		outtextxy(btn[0].startX, btn[0].startY, "->StartGame");
		setcolor(LIGHTGRAY);
		outtextxy(btn[1].startX, btn[1].startY, "Quit");
	}else{
		setcolor(WHITE);
		outtextxy(btn[1].startX, btn[1].startY, "->Quit");
		setcolor(LIGHTGRAY);
		outtextxy(btn[0].startX, btn[0].startY, "StartGame");
	}
	

	//dot animation
	setfillstyle(SOLID_FILL, WHITE);
	int xsteps[100]{1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1
	, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, -1, -1, -1, -1, -1, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
	int ysteps[100]{0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
	int zombiestepsX[100]{0, 0, 1, 1, 1, 1, 1, 0, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
	int zombiestepsY[100]{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 , 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
	if(duration2 >= 300){
		duration2 = 0;
		
		//human
		switch (xsteps[xf])
		{
		case 1:
			/* code */
			xStep++;
			break;
		case -1:
			xStep--;
			break;
		default:
			break;
		}
		switch (ysteps[yf])
		{
		case 1:
			/* code */
			break;
		case -1:
			yStep--;
			break;
		default:
			break;
		}

		//zombie
		switch (zombiestepsX[xf])
		{
		case 1:
			/* code */
			zombXStep++;
			break;
		case -1:
			zombXStep--;
			break;
		default:
			break;
		}
		switch (zombiestepsY[yf])
		{
		case 1:
			/* code */
			zombYStep++;
			break;
		case -1:
			zombYStep--;
			break;
		default:
			break;
		}

		xf++;
		yf++;
	}
	drawSquare(yStep, xStep, BLUE);
	drawSquare(zombYStep, zombXStep, RED);


	int col = -2, row = -7;
	for(col; col < 50; col++){
		drawSquare(-3, col, YELLOW);
		drawSquare(43.5, col, YELLOW);
	}
	for(row; row < 50; row++){
		drawSquare(row, -2, YELLOW);
		drawSquare(row, 42, YELLOW);
	}
	// GetCursorPos(&CursorPosition);
	// mouseX = CursorPosition.x;
	// mouseY = CursorPosition.y;

	// printf("mouse:(%d, %d\n)", mouseX, mouseY);

	//PRINT BUTTON
	//int i;
	// for(i = 0; i < 2; i++){
	// 	setfillstyle(SOLID_FILL, btn[i].color);
	// 	bar(btn[i].startX, btn[i].startY, btn[i].startX + btn[i].width, btn[i].startY + btn[i].height);
	// }
	
	// for(i = 0; i < 2; i++){//偵測按鈕的hover跟click
		
	// 	printf("%d:%d, %d, %d, %d\n", i+1, btn[i].startX, btn[i].startY, btn[i].width,  btn[i].height);
	// 	setfillstyle(SOLID_FILL, LIGHTGREEN);
	// 	if(mouseX > btn[i].startX && mouseY > btn[i].startY && mouseX < (btn[i].startX + btn[i].width) && mouseY < (btn[i].startY + btn[i].height)){
	// 		btn[i].color = LIGHTGRAY;
	// 		setfillstyle(SOLID_FILL,btn[i].color);
	// 		if(i == 0 && GetAsyncKeyState(VK_LBUTTON)){
	// 			return 1;
	// 		}
	// 		else if(i == 1 && GetAsyncKeyState(VK_LBUTTON)){
	// 			return 2;
	// 		}
	// 		}
	// }
	// MenuBuffer = 1 - MenuBuffer;
	return 0;
}
void animate_light(int d_time, int set_time){
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);		
	if(d_time >= set_time){
		setfillstyle(SOLID_FILL, BLACK);
		bar(0, 0, SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);
		frame++;
	}
}
void PauseDetect(){
	while (IFPause)//暫停觸發
	{
		if(kbhit()) {
			char cont;
			cont = getch();
			if(cont == 'f') IFPause = !IFPause;
		}
	}
}
//-------------------------------------------------

