#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void InitBoard(char board[ROWS][COLS], int row, int col, char sign) {
	int i = 0;
	for (i = 0; i < row; i++) {
		int j = 0;
		for (j = 0; j < col; j++) {
			board[i][j] = sign;
		}
	}
}


void DisplayBoard(char board[ROWS][COLS], int row, int col) {
	printf("---------------扫雷游戏---------------\n");
	int i = 0;
	//打印棋盘上面一行的列索引数字
	for (i = 0; i <= row; i++) {
		printf("%d ", i);
	}
	printf("\n");

	for (i = 0; i < row; i++) {
		printf("%d ", i + 1);//打印棋盘左侧一列的行索引
		int j = 0;
		for (j = 0; j < col; j++) {
			printf("%c ", board[i + 1][j + 1]);
		}
		printf("\n");
	}
	printf("---------------扫雷游戏---------------\n");
}


void SetMine(char mine[ROWS][COLS], int row, int col) {
	int count = easy_count;
	while (count) {
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0') {
			mine[x][y] = '1';
			count--;
		}
	}
}


int get_mine_count(char mine[ROWS][COLS], int x, int y) {
	
	int count = 0;
	int i = 0;
	int j = 0;
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			count += mine[x+i][y+j];
		}
	}
	return count - 9 * '0';
}


void show_zero_zone(char mine[ROWS][COLS], char show[ROWS][COLS],int flag[ROWS][COLS],int x, int y, int* p) {
	
	flag[x][y] = 1;
	if (get_mine_count(mine, x, y) == 0 && mine[x][y] == '0') {//因为get函数没有考虑坐标为雷的情况，所以这里要考虑坐标不能为雷

		show[x][y] = ' ';//不再显示0，而是直接显示空格
		*p += 1;
		int i = 0;
		int j = 0;
		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				if (flag[x + i][y + j] == 0 && x+i != 0 && x+i != 10 && y + j != 0 && y + j != 10) {//防止从墙绕过去
					show_zero_zone(mine, show, flag, x + i, y + j, p);
				}
			}
		}
	}
	else {
		show[x][y] = get_mine_count(mine, x, y) + '0';
		*p += 1;
	}
}


void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col) {	
	int x = 0;
	int y = 0;
	int count = 0;//标记总共排查了多少个位置
	int* p = &count;
	int lose = 0;//判断游戏输赢
	while (count < row * col - easy_count) {

		printf("请输入要排查的坐标:>");
		scanf("%d %d", &x, &y);

		if (show[x][y] != '*') {
			printf("该坐标已排查，不能重复排查，请重新输入\n");
		}

		else {
			if (x >= 1 && x <= row && y >= 1 && y <= col) {

				if (mine[x][y] == '1') {
					DisplayBoard(show, ROW, COL);
					printf("很遗憾，你被炸死了\n");
					lose = 1;
					show[x][y] = 'B';					
					break;
				}

				else {
					
					//展开一片
					int flag[ROWS][COLS] = { 1 };//标记坐标是否被排查
					show_zero_zone(mine, show, flag, x, y, p);
					DisplayBoard(show, ROW, COL);
				}
			}
			else {
				printf("你输入的坐标非法，请重新输入\n");
			}
		}
	}
	if (count = row * col - easy_count && lose == 0) {
		printf("你真牛逼，会玩扫雷\n");
	}
}