#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>


int  DeltaS =10; //��ͼ��ϸ�̶� 1Ϊһ��һ�� 2Ϊһ��0.5��
#define RXlong 20
#define RYlong 20
IMAGE  Rimg;


int checklock=0;

//��ͼ�е�ÿһ��С��
typedef struct Position {
	int no;
	int x;
	int y;
	int Used;
}Position;
typedef Position* Map;

//��ͼ��λ����

Map TestMap;
int NumOfTestMap = 50; //��ͼ�г˿��������
int TestMapPos = NumOfTestMap * DeltaS;

int CustNum = 10;
int LineNum = 5;

//������ͼ
//void CreateTestMap() {
//	
//	TestMap = (Position*)malloc(TestMapPos *sizeof(Position));
//	int NowX = 0;
//	int NowY = 0;
//	int reverse = 0;
//
//	for (int i = 0; i < 5*(10*DeltaS);i++) {
//		TestMap[i].x = NowX;
//		TestMap[i].y = NowY;
//		TestMap[i].no = i;
//		TestMap[i].Used = 0;
//		
//
//		if ((i+1) % (10*DeltaS) == 0) {
//			NowY += RYlong;
//			reverse = !reverse;
//			continue;
//		}
//
//		if (reverse) {
//			NowX -= RXlong / DeltaS;
//		}
//		else {
//			NowX += RXlong / DeltaS;
//		}
//
//	}
//
//}




void CreateTestMap() {

	TestMap = (Position*)malloc(TestMapPos * sizeof(Position));
	int NowX = 200;
	int NowY = 0;
	int mode = 1;
	int reverse=1;

	for (int i = 0; i < 5 * (CustNum * DeltaS); i++) {
		TestMap[i].x = NowX;
		TestMap[i].y = NowY;
		TestMap[i].no = i;
		TestMap[i].Used = 0;


		if ( (i+DeltaS)  % (CustNum * DeltaS) == 0) {
			mode = 0;
		}
		else if (i  % (CustNum*DeltaS) == 0) {
			mode =reverse;
			reverse = -reverse;
		}

		switch(mode){
		case -1: NowX -= RXlong / DeltaS; break;
		case 0: NowY += RYlong / DeltaS; break;
		case 1:NowX += RXlong / DeltaS; break;
		}

	}

}
Position checklast;
Map CheckMap;
void CreateCheckMap() {
	CheckMap = (Position*)malloc(10*DeltaS * sizeof(Position));

	int NowX = 0;
	int NowY = 0;

	for (int i = 0; i < 10*DeltaS; i++) {
		CheckMap[i].x = NowX;
		CheckMap[i].y = NowY;
		CheckMap[i].no = i;
		CheckMap[i].Used = 0;
		NowX += RXlong / DeltaS;
	}
	checklast = CheckMap[10 * DeltaS -1];
}



//�ƶ���
void MoveRun(Position* New, Position* Old) {
	setcolor(WHITE);
	fillellipse(Old->x, Old->y, Old->x + RXlong, Old->y + RYlong);
	putimage(New->x, New->y, &Rimg);
	Old->Used = 0;
	New->Used = 1;
}

//�������ŵ�ͼ
void Move(Map map,Position checklast) {
	int NumOfPos = TestMapPos;
	int go=0; //���ܲ����ƶ�

	//����ͷ
	if (checklock)
		MoveRun(&checklast, &map[0]);
	
	for (int i = 0; i < NumOfPos; i++) {
		if (map[i].Used) {	
			if (go) {	
				MoveRun(&map[i - 1], &map[i]);	//��������+�ܶ� ����������
			}
			else {
				i += DeltaS-1;	//�������ˣ������ܶ���ȥ�¸������
				go = 0;
			}
		}
		else {
			go = 1;	//����û�� �칥������
		}
	}
}

void EnterMap(Map map) {
	int NumOfPos = TestMapPos;
	int last = NumOfPos - DeltaS ;	//����Ǹ���
	
	//�����ص�
	for (int i = last - DeltaS + 1; i < last; i++) {
		if (map[i].Used)
			return;
	}

	putimage(map[last].x, map[last].y, &Rimg);
	map[last].Used = 1;
}




int main() {
	initgraph(1500, 800);
	loadimage(&Rimg, _T("�˿�.jpg"), RXlong, RYlong);
	setbkcolor(WHITE);
	cleardevice();
	CreateTestMap();
	CreateCheckMap();
	//MOUSEMSG m;
	char c;
	while (1) {

		Move(TestMap,checklast);
		if (kbhit()) {
			c=getch();
			if (c == 'l')
				checklock = !checklock;
			else
				EnterMap(TestMap);
		}
		Sleep(50);
	}
	if (getch());
}
