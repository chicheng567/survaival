
#include "include/coreHeader.h"
#include "include/Clock.h"
#include "include/player.h"
#include "include/MenuBtn.h"
#include "include/screen.h"
struct PathNode pathQueue[MAX_QUEUE_SIZE]; //宣告將要拜訪的節點柱列 
int front; //queue 第一個元素的前一個位置 
int rear; //queue 最後一個元素的位置

int scoreSum = 0; //紀錄分數 
int killedCount = 0; //殺死喪屍數量 
int totalTime = 0; //紀錄遊戲時間 
int stepCount = 0; //步數計數器 
int const scorePerResource = 1; //每一份資源可得分數 
bool IFPlayAI = false; //是否開啟AI模式 
bool IFPause = false; //是否暫停
GameClock gameClock;

//menu
int MenuBuffer = 0;
//mouse
int mouseX, mouseY;
POINT CursorPosition;
MenuBtn startBtn(150, 330, 280, 120), exitBtn(230, 390, 280, 120);//menu全部按鈕
vector<MenuBtn> btn = {startBtn, exitBtn};
//screen
screen SCREEN;
// 主程式      
int main(){  	
	openWindow();
	int key;
	int x = 50;
	while(TRUE){
		
		key = menu();
		if(key == 1){
			break;
		}
		else if(key == 2){
			exit(1);
		}
		// if(kbhit()) key = getch();
		// if(key == 'g') break;
		// key = 0;
		// setfillstyle(SOLID_FILL, YELLOW);
		// bar(x-50, 0, x, 200);
		// if(kbhit()) key = getch();
		// if(key == 't') x+=1;



		// else if(key == 'g') break;//if start clicked
		// delay(5);
		// cleardevice();
	}
	cleardevice();

	while(TRUE){
		
		//設定遊戲場和障礙物 
	   	int field[GRID_SIDE][GRID_SIDE] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		   								   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1},
										   {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}; 
	   	
		character mainPlayer(2, 4, 8); //設定勇者初始位置和方向 
		character zombie(15, 15, 10);
		vector<character> zombies;
		zombies.push_back(zombie);
		char key;
		key = playGame(field, zombies, mainPlayer); //進行遊戲
		if (key == 'q' || key == 'Q')
			closeGame(zombies); //如果生存者輸入'q'離開遊戲	
		else if (key == 's' || key == 'S') {
			mainPlayer.dir = RIGHT;
			continue; //如果生存者輸入's' 繼續遊戲
		}
			 		    
	}
}

//開啟游戲視窗
void openWindow(){
	initwindow(SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Hungry zombie Game");
}

//處理遊戲結束邏輯 
void closeGame(vector<character> &zombies){
	zombies.clear();
	exit(0);
}

//遊戲進行邏輯
int playGame(int field[][GRID_SIDE], vector<character> &zombies, character &Player) {
	killedCount = 0; 
	bool killed = true;
	srand((unsigned)time(NULL)); //取目前系統時間作為亂數種子
	gameClock.initClock();
	createResource(field, zombies); //產生第一份資源
	
	while(true){
		gameClock.updateClock();
		SCREEN.update();
		cleardevice();
		//kb control
		controlPlayerDirection(field, Player);
		controlZombieDirection(field, zombies, Player);
		updateScrean(Player, zombies, field);
		
		if(IsGameOver(zombies, Player, field)) {
			return showGameOverMsg();
		}
	}
}

void updateScrean(character& Player, vector<character> &zombies, int field[][GRID_SIDE]) {
	
	drawGameField(field);
	showInfo();
	int x_o = (int)Player.x;
	int y_o = (int)Player.y;
	Player.movecharacter(gameClock.getDeltaTime());
		drawSquare(y_o, x_o, BLACK);
		drawSquare((int)Player.y, (int)Player.x, BLUE);
	if(x_o != (int)Player.x || y_o != (int)Player.y) {
		playerCollectResource(field, Player, zombies);
	}
	/*
	for(character i:zombies) {
		
		x_o = (int)i.x;
		y_o = (int)i.y;
		i.movecharacter(gameClock.getDeltaTime());
		drawSquare(y_o, x_o, BLACK);
		drawSquare((int)i.y, (int)i.x, RED);
	}
	*/
}

//繪製遊戲區域，依據遊戲場矩陣設定繪製物件 
void drawGameField(int field[][GRID_SIDE]){
   	int row = 0, col = 0;
   	cleardevice(); //清理螢幕畫面 
	for(row = 0; row < GRID_SIDE; row ++){
   		for(col = 0; col <  GRID_SIDE; col++){
				switch(field[row][col])	{
					case WALL: //牆在矩陣中的值是1 
						drawSquare(row, col, YELLOW);
						break;
					case RESOURCE: //資源在矩陣中的值是2
						drawSquare(row, col, GREEN);
						break;	
				}	
		   }
	}
}

//繪製方塊
void drawSquare(int row, int col, int color){
	//row as y
	//col as x

	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
   	bar(left , top, right, bottom);	//設定繪製方塊的位置 
}

//判斷生存者是否死亡(死亡條件：撞牆和撞到自己身體) 
bool IsGameOver(vector<character> &zombies, character &Player, int field[][GRID_SIDE]){

	//檢查是否AI撞到喪屍 
	if(IsAtZombie(zombies, Player.y, Player.x))
			return true;
	
	
	return false;
}

//判斷是否撞到牆
bool IsAtWall(int field[][GRID_SIDE], int row, int col){
		if (field[row][col] == WALL)
			return true;
		return false;
}

//判斷是否撞到喪屍
bool IsAtZombie(vector<character> &zombies, int row, int col){

	for(character i : zombies) {
		if (row == i.y && col == i.x)
			return true;
	}		
	return false;
}

//遊戲結束訊息
int showGameOverMsg(){
   	/*cleardevice(); //清理所有螢幕資料，如果希望只顯示訊息時，取消註解 */
	int i = 0;
	char msg1[15] = "Game Over!!";
	char msg2[40] = "press [q] to quit or [s] to restart!!";
   	for(; ; i++){
		if(!(i%16))	continue;	
	   	setcolor(i%16);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 70, msg2);
	   	
	   	delay(200);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);	   
		   	
	   	if (GetAsyncKeyState('Q')){
			printf("\n\n\nQ pressed\n\n\n\n");
			return 'q';
		}
		else if(GetAsyncKeyState('S')){
			printf("\n\n\nS pressed\n\n\n\n");
			return 's';
		}
	}	
}

//顯示遊戲相關資訊
void showInfo(){
	char timeMsg[45] = " Time:";
	char scoreMsg[45] = "Score:";
	char killedMsg[50] = "Killed Zombie:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart or";
	char optMsg2[50] = "press [a] to change mode.";
	
	char time[10];
	char score[10];
	char killed[10];
	sprintf(time, "%5d", gameClock.getTotalTime() / CLOCKS_PER_SEC);
	strcat(timeMsg, time);
	strcat(timeMsg, " sec.");
	
	setcolor(WHITE); //設定文字顏色 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //設定字型，水平或垂直和字型大小 
   	outtextxy(0, 0, timeMsg); //依據坐標輸出文字到螢幕	
	
	sprintf(score, "%5d", scoreSum);
	strcat(scoreMsg, score);
	strcat(scoreMsg, " point.");

	setcolor(WHITE);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, 19, scoreMsg);
   	
 	sprintf(killed, "%3d", killedCount);
	strcat(killedMsg, killed);  	
   	
   	setcolor(WHITE);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(250, 19, killedMsg);
   	
   	if(IFPlayAI){
   		strcat(modeMsg, "AI Mode    ");
	}else{
   		strcat(modeMsg, "Player Mode");
	}
			
   	setcolor(LIGHTMAGENTA);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_HEIGHT - LEFT_MARGINE * 2, 0, modeMsg);
   	
   	setcolor(LIGHTGREEN);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE, optMsg1);
	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE + 20, optMsg2);	      	
}

//讀取鍵盤方向輸入，並設定到生存者節點 
void controlPlayerDirection(int field[][GRID_SIDE], character &Player) {
	
	Direction playerDirect = Player.dir;
	//get key code by pressing keybord
	if(GetAsyncKeyState(VK_UP)){
		if (IsAtWall(field, Player.y - 1, Player.x)){
			playerDirect = STOP;
		}
		else{
			playerDirect = UP;
		}
	
	}
	else if(GetAsyncKeyState(VK_DOWN)){
		if (IsAtWall(field, Player.y + 1, Player.x)){
			playerDirect = STOP;
		}
		else{
			playerDirect = DOWN;
		}
	}
	else if(GetAsyncKeyState(VK_LEFT)){
		if (IsAtWall(field, Player.y, Player.x - 1)){
			playerDirect = STOP;
		}
		else{
			playerDirect = LEFT;
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT)){
		if (IsAtWall(field, Player.y, Player.x + 1)){
			playerDirect = STOP;
		}
		else{
			playerDirect = RIGHT;
		}
	}
	else {
		playerDirect = STOP;
	}
		
	//decide zombie's moving direction	
	
	
		
	/*if (IFPlayAI)
		playerDirect = playerAI(field, player, zombie);*/
	
	
	Player.dir = playerDirect;
	
}


//讀取鍵盤方向輸入，並設定到所有喪屍節點 
void controlZombieDirection(int field[][GRID_SIDE], vector<character> zombies, character &Player) {
	int count = 0;
	for(character i: zombies){
		Location target = {Player.y + count, Player.x + count};
		Direction zombieDirect = zombieAI(field, i, target);
		i.dir = zombieDirect;
		count += 2;
	}	
}

//產生資源
void createResource(int field[][GRID_SIDE], vector<character> &zombies){
	int row, col, i, amount = RESOURCE_AMOUNT;

	for(i=0; i< amount; i++){
		//如果亂數產生的位置是在牆和喪屍身體重疊，則重新產生，直到符合條件為止 
		do{
			row = rand() % GRID_SIDE;
			col = rand() % GRID_SIDE;	
		}while(IsAtWall(field, row, col) || IsAtZombie(zombies, row, col));
	
		field[row][col] = RESOURCE;
		drawSquare(row,col, GREEN);			
	}
}


//系統處理生存者收集到資源邏輯
void playerCollectResource(int field[][GRID_SIDE], character &Player, vector<character> &zombies){
	//如果生存者與資源位置重疊，就是收集到資源
	if(field[(int)Player.y][(int)Player.x] == RESOURCE){
		field[(int)Player.y][(int)Player.x] = EMPTY; //將該資源清空 
		printf("The player has eaten food at row: %d, col: %d\n", Player.y, Player.x);
		scoreSum += scorePerResource; //紀錄分數 
		createResource(field, zombies); //產生新的資源
		
		//收集一定數量的資源可以消滅一隻喪屍 
		if(scoreSum % PER_RESOURCE_KILL == 0) 
			killZombie(zombies);
	}
}

//增加喪屍數量 
void addZombie(int field[][GRID_SIDE], vector<character> &zombies, character &Player){
	int row, col;	
	do{
		row = rand() % GRID_SIDE;
		col = rand() % GRID_SIDE;	
	}while(IsAtWall(field, row, col) || IsAtZombie(zombies, row, col) || (Player.y == row && Player.x == col));	
	
	character newZombie(col, row, 4);
	zombies.push_back(newZombie);
}

//殺掉一隻喪屍
void killZombie(vector<character> &zombies){
	if(zombies.size() > 1) {
		zombies.pop_back();
	}
}
//喪屍的AI控制 
Direction zombieAI(int field[][GRID_SIDE], character zombie, Location target) {
	Direction zombieDirect = zombie.dir;
	Location start = {zombie.y, zombie.x};


	PathPointer path = zombieFindPath(field, start, target);
	if(path){
		zombieDirect = getDirectionByPath(zombie, path);
	}	
	else
		zombieDirect = safeDirect4Zombie(field, zombie);	

	return zombieDirect;
}

//從路徑資料判斷下一步方向 
Direction getDirectionByPath(character current, PathPointer path){
	PathPointer nextPath = path->next;
	int horizontal = nextPath->loc.col - current.x;
	int vertical = nextPath->loc.row - current.y;
	if(horizontal == 1)
		return RIGHT;
	else if(horizontal == -1)
		return LEFT;
	
	if(vertical == 1)
		return DOWN;
	else if(vertical == -1)
		return UP;
	return 	current.dir;		
}

//喪屍如果無法找到有效路徑，暫時決定一個安全方向

Direction safeDirect4Zombie(int field[][GRID_SIDE], character zombie){
	int i;
	int dirSize = 4;
	Location loc;
	
	loc = nextStepLoc(zombie, UP);
	if(!IsAtWall(field, loc.row, loc.col))
		return UP;
	loc = nextStepLoc(zombie, DOWN);
	if(!IsAtWall(field, loc.row, loc.col))
		return DOWN;
	loc = nextStepLoc(zombie, RIGHT);
	if(!IsAtWall(field, loc.row, loc.col))
		return RIGHT;
	loc = nextStepLoc(zombie, LEFT);
	if(!IsAtWall(field, loc.row, loc.col))
		return LEFT;						
	return zombie.dir;
}

//喪屍尋找兩點之間可到達的路徑，不需考慮會不會撞到其他喪屍或者生存者
PathPointer zombieFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};
	addPathQueue(start);
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col)){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}				
			}
		}
	}
	return NULL;
}

//將之後要拜訪的節點放入佇列裡
void addPathQueue(PathNode pathNode){
	if(rear == MAX_QUEUE_SIZE - 1){
		printf("the queue is full");
		return;
	}
	rear += 1;
	pathQueue[rear]	= pathNode;
}

//傳回佇列中的路徑座標節點，並將它從佇列中刪除
PathPointer popPathQueue(){
	if(front == rear){
		printf("the queue is empty");
		return NULL;
	}
	front ++;
	PathPointer node = (PathPointer)malloc(sizeof(PathNode));
	node->cost = pathQueue[front].cost;
	node->steps = pathQueue[front].steps;
	node->loc = pathQueue[front].loc;
	node->parent = pathQueue[front].parent;
	node->next = pathQueue[front].next;
	return node;
}

//判斷佇列是否為空
bool isPathQueueEmpty(){
	return front == rear;
}

//重設佇列 
void resetPathQueue(){
	front = -1;
	rear = -1;	
}

//對佇列中的元素進行排序 
void sortPathQueue(){
	if(front == rear)
		return;
	int i, j;
	int nowTotal, nextTotal;	
	for(i=front + 1; i<rear; i++){
		for(j=i+1; j<=rear; j++){

			nowTotal = pathQueue[i].cost + pathQueue[i].steps;
			nextTotal = pathQueue[j].cost + pathQueue[j].steps;

			if(nowTotal > nextTotal){
				PathNode temp =  pathQueue[i];
				pathQueue[i] = pathQueue[j];
				pathQueue[j] = temp;
			}
		}
	}		
}

//判斷該元素是否在佇列之中
bool IsInPathQueue(PathNode pathNode){
	int i;
	if(front == rear)
		return false;
	for(i=front;i<=rear;i++){
		if(pathQueue[i].loc.row == pathNode.loc.row && pathQueue[i].loc.col == pathNode.loc.col)
			return true;
	}
	return false;
}

//回傳到目標位置的路徑串列 
PathPointer buildPath(PathPointer goal){
	printf("buildPath ");
	printf("(%d, %d)\n", goal->loc.row, goal->loc.col);
	if(goal == NULL || goal->parent == NULL)
		return NULL;
	PathPointer head = goal;
	head->next = NULL;
	PathPointer temp = head;
	
	while(head->parent){
		if(head == NULL)
			return NULL;
		printf("node (%d, %d)->", head->loc.row, head->loc.col);	
		head = head->parent; 
		head->next = temp;
		temp = head;
	}
	printf("NULL\n");
	return head;
}

//計算兩點之間需要移動的步數 
int calcSteps(Location start, Location goal){
	int steps = abs(start.row - goal.row) + abs(start.col - goal.col);
	return steps;
}

//判斷是否該節點已經拜訪過 
bool visited(Location loc){
	int i;
	for(i=0;i<=front;i++){
		if(pathQueue[i].loc.row == loc.row && pathQueue[i].loc.col == loc.col)
			return true;
	}
	return false;
}

//尋找最接近資源
Location findNearestResource(int field[][GRID_SIDE], character Player){
	int rowDis, colDis, row, col, nearest = 100000;
	Location nearestFood = {-1, -1};
	for(row = 0; row < GRID_SIDE; row++){
		for(col = 0; col < GRID_SIDE; col++){
			if(field[row][col] == RESOURCE){
				rowDis = abs(row - Player.y);
				colDis = abs(col - Player.x);
				if(nearest > (rowDis + colDis)){
					nearest = (rowDis + colDis);
					nearestFood.row = row;
					nearestFood.col = col;
				}
			}
		}
	}
	return nearestFood;
}

//實作生存者AI 
/*
Direction playerAI(int field[][GRID_SIDE], player &Player, NodePointer zombie){
	Direction playerDirect = Player.dir;
	Location start = {Player.y, Player.x};
	Location nearestResource = findNearestResource(field, Player);
	if(nearestResource.row != -1 || nearestResource.col != -1){
		PathPointer path = playerFindPath(field, start, nearestResource, zombie);
		if(path){
			playerDirect = getDirectionByPath(Player, path);
		}
		else
			playerDirect = safeDirect(field, Player, zombie);
	}else{printf("no resource");}
	
	return playerDirect;
}

//生存者如果無法找到有效路徑，暫時決定一個安全方向 
Direction safeDirect(int field[][GRID_SIDE], player &Player, NodePointer zombie){
	int i;
	int dirSize = 4;
	Location loc;
	
	loc = nextStepLoc(Player, UP);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseZombie(zombie, loc.row, loc.col))
		return UP;
	loc = nextStepLoc(Player, DOWN);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseZombie(zombie, loc.row, loc.col))
		return DOWN;
	loc = nextStepLoc(Player, RIGHT);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseZombie(zombie, loc.row, loc.col))
		return RIGHT;
	loc = nextStepLoc(Player, LEFT);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseZombie(zombie, loc.row, loc.col))
		return LEFT;						
	return Player.dir;
}
*/
//計算下一步的座標 

Location nextStepLoc(character current, Direction direct){
	int currRow =  current.y;
	int currCol = current.x;
	int nextRow, nextCol;
	Location loc;
	switch(direct){
		case RIGHT:
			nextRow = currRow;
			nextCol = currCol + 1;
			break;	
		case LEFT:
			nextRow = currRow;
			nextCol = currCol - 1;
			break;
		case UP:
			nextRow = currRow - 1;
			nextCol = currCol;
			break;				
		case DOWN:
			nextRow = currRow + 1;
			nextCol = currCol;		
			break;	
	}
	loc.row = nextRow;
	loc.col = nextCol;
	return loc;
}
/*
//生存者尋找兩點之間可到達的路徑，必須考慮會不會撞到牆或者喪屍 
PathPointer playerFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc, NodePointer zombie){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};
	addPathQueue(start);
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current == NULL)
			return NULL;
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col) && !IsCloseZombie(zombie, neighborLoc.row, neighborLoc.col)){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}				
			}
		}
	}
	return NULL;
}

//判斷是否會撞到喪屍
bool IsCloseZombie(NodePointer zombie, int row, int col){

	if(zombie == NULL)
		return NULL;
	NodePointer head = zombie;
	while(zombie != NULL){
		if (row == zombie->row && col == zombie->col)
			return true;
		zombie = zombie -> next;
	}
	int dirSize = 4;
	int iDir[] = {1, 0, -1, 0};
	int jDir[] = {0, 1, 0, -1};
	int i,j;
	while(head != NULL){
		for(i=0, j=0; i<dirSize; i++, j++){
			if (row == (head->row + iDir[i]) && (col == head->col  + jDir[j]))
				return true;
		}
		head = head -> next;		
	}

	return false;
}
*/