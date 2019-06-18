#pragma once
typedef struct tagVertex{
	int row;
	int col;
	int info;
}Vertex;
#define BLANK -1
#define MAX_ROW 10
#define MAX_COL 8
#define MAX_VERTEX_NUM 80
#define MAX_PIC_NUM 10
#define REPEAT_NUM 8
#define MAP_TOP 50
#define MAP_LEFT 50
#define PIC_WIDTH 40
#define PIC_HEIGHT 40
#define PLAY_TIMER_ID      1     //��ʱ���ı��

#define GAME_LOSE           -1   //ʧ��
#define GAME_SUCCESS        0    //��ʤ
#define GAME_PLAY           1    //��Ϸ���ڽ���