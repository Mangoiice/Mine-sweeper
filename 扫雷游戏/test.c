#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void menu() {
	printf("**********************************\n");
	printf("******     1��ɨ����Ϸ      ******\n");
	printf("******     0���˳���Ϸ      ******\n");
	printf("**********************************\n");
}

void game() {
	char mine[ROWS][COLS] = { 0 };
	char show[ROWS][COLS] = { 0 };
	//��ʼ������
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	//չʾ����
	DisplayBoard(show, ROW, COL);
	
	//������
	SetMine(mine, ROW, COL);
	DisplayBoard(mine, ROW, COL);
	//�Ų���
	FindMine(mine, show, ROW, COL);
	
}





int main() {
	//������������������
	srand((unsigned int)time(NULL));

	int input = 0;
	do {
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);

		switch(input) {
		case 1:
			printf("����ɨ����Ϸ\n");
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("ѡ��Ƿ���������ѡ��");
			break;
		}
	} while (input);
}