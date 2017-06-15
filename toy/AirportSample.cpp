/*
Lģ�ⰲ���lock
0-9ģ����䰲���
*/

#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>

int checklock = 0;//------���lock�ð�����Ƿ����˴���
#define SleepTime 50


int  DeltaS = 1; //----------------------С��ϸ�̶� һ�˿ɷ�Ϊ����С��
#define RXlong 20
#define RYlong 20
IMAGE  Rimg;


//��ͼ�е�ÿһ��С��
typedef struct Position {
	//int CheckNo;
	int x;
	int y;
	int Used;
}Position;
typedef Position* Map;


//----------------------------------------------------------------------------------------------�Ŷӻ�����map
//extern int MaxCustSingleLine;// ���������ȴ��˿���
//extern int MaxLines;// ���λ����������MaxLines��ֱ�����
int MaxCustSingleLine = 10;
int MaxLines = 5;
int SingleLinePos = MaxCustSingleLine * DeltaS; //ÿ�е���λ
Map LineMap;
void CreateLineMap() {

	LineMap = (Position*)malloc(SingleLinePos * MaxLines * sizeof(Position));
	if (LineMap == NULL) {
		exit(1);
	}
	int NowX = 160;	//--------------------���Ͻ�X
	int NowY = 40;	//--------------------���Ͻ�Y

	int mode = 1;
	int reverse = 1;

	for (int i = 0; i < 5 * SingleLinePos; i++) {
		//����ֵ
		LineMap[i].x = NowX;
		LineMap[i].y = NowY;
		//LineMap[i].CheckNo = i;
		LineMap[i].Used = 0;
		//�ı�ģʽ
		if ((i + DeltaS) % SingleLinePos == 0) {	//����
			mode = 0;
		}
		else if (i  % SingleLinePos == 0) {		//ֱ��
			mode = reverse;
			reverse = -reverse;
		}
		//λ�ñ仯
		switch (mode) {
		case -1: NowY -= RYlong / DeltaS; break;	//����
		case 0: NowX += RXlong / DeltaS; break;		//����
		case 1:NowY += RYlong / DeltaS; break;		//����
		}
	}//end of for
}
//�Ŷӻ�����map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//-----------------------------------------------------------------------------------------------�����map
//extern int NumOfWin;
int NumOfWin = 10;
Map* CheckMap;
int* last;
//extern CXlong;
//extern int MaxCustCheck;
int CXlong = 300;
int MaxCustCheck = 5;

#define MinStep 12

void CreateSingleCheckMap(int no) {
	CheckMap[no] = (Position*)malloc((MinStep + no)*DeltaS * sizeof(Position));//--------------

	int NowX = -(RXlong / DeltaS);//-------------------------
	int NowY = 40 + no*RYlong;//-----------------------

	int i = 0;

	//setcolor(BLACK);
	//rectangle(NowX+RXlong, NowY + RYlong, NowX + RXlong + RXlong, NowY + RYlong + RYlong);
	//����
	for (int j = 0; j < (MaxCustCheck + 2)*DeltaS; i++, j++) {
		NowX += RXlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX,NowY, &Rimg);

	//����
	for (int j = 0; j < (2 + no)*DeltaS; i++, j++) {
		NowY -= RYlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX, NowY, &Rimg);

	//����
	for (int j = 0; j < 2 * DeltaS; i++, j++) {
		NowX += RXlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX, NowY, &Rimg);

	//����
	for (int j = 0; j < DeltaS; i++, j++) {
		NowY += RXlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX, NowY, &Rimg);

	last[no] = i - 1;
}

void CreateCheckMap() {
	CheckMap = (Map*)malloc(NumOfWin * sizeof(Map));
	last = (int*)malloc(NumOfWin * sizeof(int));
	for (int i = 0; i < NumOfWin; i++) {
		CreateSingleCheckMap(i);
	}
}

//�����map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------GoGOGO
//�ƶ���
void MoveRun(Position* New, Position* Old) {
	setcolor(WHITE);
	fillellipse(Old->x, Old->y, Old->x + RXlong, Old->y + RYlong);
	putimage(New->x, New->y, &Rimg);
	Old->Used = 0;
	New->Used = 1;
}

//׼���ƶ���
void Move(Map map, int NumOfPos) {
	//int NumOfPos = SingleLinePos;
	int go = 0; //���ܲ����ƶ�

	for (int i = 0; i < NumOfPos; i++) {
		if (map[i].Used) {
			if (go) {
				MoveRun(&map[i - 1], &map[i]);	//��������ܶ� ����������!��
			}
			else {
				i += DeltaS - 1;	//������˲��ܶ� ���Ѿ� ȥ�¸������
				go = 0;
			}
		}
		else {
			go = 1;	//����û�� �칥������
		}
	}
}
//GoGoGo^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------------------------------------------------------------��ͼ״̬ת��
//����������
void EnterMap(Map map, int NumOfPos) {
	//int NumOfPos = LineMapPos;
	int last = NumOfPos - DeltaS;	//����Ǹ���

									//�жϻ᲻���ص�
	for (int i = last - DeltaS + 1; i < last; i++) {
		if (map[i].Used)
			return;
	}

	putimage(map[last].x, map[last].y, &Rimg);
	map[last].Used = 1;
}

//ȥ���������
void EnCheck(int no) {
	//��������ͷ �����ܲ�����
	if (checklock && LineMap[0].Used) {			//�����δ�� & ��ͷ����
		MoveRun(&CheckMap[no][last[no]], &LineMap[0]);	//����
		LineMap[0].Used = 0;
		CheckMap[no][last[no]].Used = 1;
	}
}

void DeCheck(int no) {
	CheckMap[no][0].Used = 0;
}
//��ͼ״̬ת��^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^






int main() {
	initgraph(1200, 600);
	loadimage(&Rimg, _T("�˿�.jpg"), RXlong, RYlong);
	setbkcolor(WHITE);
	cleardevice();
	CreateLineMap();
	CreateCheckMap();
	char c;
	while (1) {
		for (int i = 0; i < NumOfWin; i++) {
			Move(CheckMap[i], (MinStep + i) * DeltaS);//����ڶ�
		}
		//EnCheck(0);						//������ͷ��
		Move(LineMap, SingleLinePos*MaxLines);//��������

		if (kbhit()) {
			c = getch();
			if (c == 'l')
				checklock = !checklock;
			else if (c <= '9'&&c >= '0') {
				c = c - '0';
				EnCheck(c);
			}
			else
				EnterMap(LineMap, SingleLinePos*MaxLines);
		}
		Sleep(SleepTime);
	}
	if (getch());
}