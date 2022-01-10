#ifndef  _COREHEADER_H_
#define  _COREHEADER_H_
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "mingw.thread.h"
#include "player.h"
#include <iostream>
#define SCREEN_HEIGHT 500 //設定遊戲視窗高度 
#define SCREEN_WIDTH 500 //設定遊戲視窗寬度
#define GRID_SIDE 40 //設定遊戲方陣每邊格子數量 
#define LEFT_MARGINE 30 //設定左邊界 
#define TOP_MARGINE 40 //設定上邊界 
#define RESOURCE_AMOUNT 1 //設定每次產生資源數量 
#define PER_RESOURCE_KILL 5 //設定多少資源數量可以殺掉一隻喪屍 
#define INIT_SPEED  80 //設定初始移動速度 
#define MAX_QUEUE_SIZE 1600 //設定柱列大小 
using namespace std;


//宣告遊戲場出現物體列舉函數 
enum Object {
	EMPTY, //空白 
	WALL, //牆或障礙物 
	RESOURCE //資原 
};

//宣告喪屍身體節點結構 
struct Node {
	int row; //節點位在第幾行 
	int col; //節點位在第幾列 
	Direction direct; //該節點的前進方向 
	struct Node *next;	//指向下一個節點 
}; 
//定義指向節點結構的指標變數 
typedef struct Node *NodePointer;

//定義座標結構 
struct Location {
	int row;
	int col;
};

typedef struct PathNode *PathPointer;

//定義路徑節點結構，用來建立移動路徑 
struct PathNode {
	int cost; //距離原點的步數 
	int steps; //距離目標的步數 
	Location loc;
	PathPointer parent;
	PathPointer next;
};
void openWindow(); //開啟游戲視窗 
void closeGame(vector<character> &zombies); //處理遊戲結束邏輯 
int playGame(int field[][GRID_SIDE], vector<character> &zombies, character &Player); //遊戲進行邏輯 
bool IsGameOver(vector<character> &zombies, character &Player, int field[][GRID_SIDE]); //(生存者死亡條件：撞牆和撞到喪屍) 
int showGameOverMsg(); //遊戲結束訊息
void showInfo(); //顯示遊戲相關資訊 
void drawGameField(int field[][GRID_SIDE]); //繪製遊戲區域 
void drawSquare(int row, int col, int color); //繪製方塊 
void playerCollectResource(int field[][GRID_SIDE], character &Player, vector<character> &zombies);
void controlZombieDirection(int field[][GRID_SIDE], vector<character> zombies, character &Player); //讀取AI輸入，並設定到所有喪屍節點 
void controlPlayerDirection(int field[][GRID_SIDE], character &Player); //讀取鍵盤方向輸入，或者AI輸入 
void moveZombie(int field[][GRID_SIDE], character zombies); //繪製喪屍群前進一步的改變    
void createResource(int field[][GRID_SIDE], vector<character> &zombies); //產生資源
bool IsAtWall(int field[][GRID_SIDE], int row, int col); //判斷是否撞到牆  
bool IsAtZombie(vector<character> &zombies, int row, int col); //判斷是否撞到喪屍的身體
bool IsCloseZombie(vector<character> &zombies, int row, int col);//判斷是否撞到喪屍
void characterCollectResource(int field[][GRID_SIDE], character &Player, vector<character> &zombies); //處理生存者收集到資源邏輯 
void addZombie(int field[][GRID_SIDE], vector<character> &zombies, character &Player); //增加喪屍數量 
void killZombie(vector<character> &zombies); //隨機殺掉一隻喪屍 
Location nextStepLoc(character current, Direction direct); //計算下一步的座標 
Location findNearestResource(int field[][GRID_SIDE], character Player); //尋找最接近資源的座標 
//生存者如果無法找到有效路徑，暫時決定一個安全方向
Direction safeDirect(int field[][GRID_SIDE], character &Player, vector<character> &zombies);
//喪屍如果無法找到有效路徑，暫時決定一個安全方向
Direction safeDirect4Zombie(int field[][GRID_SIDE], character zombies);

//喪屍尋找兩點之間可到達的路徑，不需考慮會不會撞到其他喪屍或者生存者，只需考慮不能撞到牆 
PathPointer zombieFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc);  
//生存者尋找兩點之間可到達的路徑，必須考慮不能撞到喪屍或者牆 
PathPointer playerFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc, vector<character> &zombies);
void addPathQueue(PathNode pathNode); //將之後要拜訪的節點放入佇列裡 
PathPointer popPathQueue(); //傳回路徑佇列中的元素，並將它從佇列中刪除 
bool isPathQueueEmpty(); //判斷佇列是否為空 
void resetPathQueue(); //重設佇列 
void sortPathQueue(); //對佇列中的元素進行排序 
bool IsInPathQueue(PathNode pathNode); //判斷該元素是否在佇列之中 
PathPointer buildPath(PathPointer goal); //回傳到目標位置的路徑串列 
int calcSteps(Location start, Location goal); //計算兩點之間需要移動的步數 
bool visited(Location loc); //判斷是否該節點已經拜訪過 
Direction getDirectionByPath(character zombies, PathPointer path); //從路徑資料判斷下一步方向 

Direction zombieAI(int field[][GRID_SIDE], character zombie, Location target); //喪屍AI 
Direction playerAI(int field[][GRID_SIDE], character &Player, vector<character> &zombies); //生存者AI

void updateScrean(character& Player, vector<character> &zombiess, int field[][GRID_SIDE]);
int menu();
void animate_light(int d_time, int set_time);

#endif  