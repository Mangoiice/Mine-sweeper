#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void menu() {
	printf("**********************************\n");
	printf("******     1、扫雷游戏      ******\n");
	printf("******     0、退出游戏      ******\n");
	printf("**********************************\n");
}

void game() {
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	//初始化棋盘
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//展示棋盘
	DisplayBoard(show, ROW, COL);
	
	//布置雷
	SetMine(mine, ROW, COL);
	DisplayBoard(mine, ROW, COL);
	//排查雷
	FindMine(mine, show, ROW, COL);
	
}





int main() {
	//设置随机数的生成起点
	srand((unsigned int)time(NULL));

	int input = 0;
	do {
		menu();
		printf("请选择:>");
		scanf("%d", &input);

		switch(input) {
		case 1:
			printf("进行扫雷游戏\n");
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择非法，请重新选择");
			break;
		}
	} while (input);
}