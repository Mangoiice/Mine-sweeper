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
	printf("---------------ɨ����Ϸ---------------\n");
	int i = 0;
	//��ӡ��������һ�е�����������
	for (i = 0; i <= row; i++) {
		printf("%d ", i);
	}
	printf("\n");

	for (i = 0; i < row; i++) {
		printf("%d ", i + 1);//��ӡ�������һ�е�������
		int j = 0;
		for (j = 0; j < col; j++) {
			printf("%c ", board[i + 1][j + 1]);
		}
		printf("\n");
	}
	printf("---------------ɨ����Ϸ---------------\n");
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
	if (get_mine_count(mine, x, y) == 0 && mine[x][y] == '0') {//��Ϊget����û�п�������Ϊ�׵��������������Ҫ�������겻��Ϊ��

		show[x][y] = ' ';//������ʾ0������ֱ����ʾ�ո�
		*p += 1;
		int i = 0;
		int j = 0;
		for (i = -1; i <= 1; i++) {
			for (j = -1; j <= 1; j++) {
				if (flag[x + i][y + j] == 0 && x+i != 0 && x+i != 10 && y + j != 0 && y + j != 10) {//��ֹ��ǽ�ƹ�ȥ
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
	int count = 0;//����ܹ��Ų��˶��ٸ�λ��
	int* p = &count;
	int lose = 0;//�ж���Ϸ��Ӯ
	while (count < row * col - easy_count) {

		printf("������Ҫ�Ų������:>");
		scanf("%d %d", &x, &y);

		if (show[x][y] != '*') {
			printf("���������Ų飬�����ظ��Ų飬����������\n");
		}

		else {
			if (x >= 1 && x <= row && y >= 1 && y <= col) {

				if (mine[x][y] == '1') {
					DisplayBoard(show, ROW, COL);
					printf("���ź����㱻ը����\n");
					lose = 1;
					show[x][y] = 'B';					
					break;
				}

				else {
					
					//չ��һƬ
					int flag[ROWS][COLS] = { 1 };//��������Ƿ��Ų�
					show_zero_zone(mine, show, flag, x, y, p);
					DisplayBoard(show, ROW, COL);
				}
			}
			else {
				printf("�����������Ƿ�������������\n");
			}
		}
	}
	if (count = row * col - easy_count && lose == 0) {
		printf("����ţ�ƣ�����ɨ��\n");
	}
}