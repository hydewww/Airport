#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>


int  DeltaS = 10;
#define RXlong 30
#define RYlong 30
IMAGE  Rimg;



//��ͼ��ϸ�̶� 1Ϊһ��һ�� 2Ϊһ��0.5��

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
int NumOfTestMap = 40; //��ͼ�г˿��������
int TestMapPos = NumOfTestMap * DeltaS;

//������ͼ
void CreateTestMap() {
	
	TestMap = (Position*)malloc(TestMapPos *sizeof(Position));
	int NowX = 0;
	int NowY = 0;

	for (int i = 0; i < TestMapPos; i++) {
		TestMap[i].x = NowX;
		TestMap[i].y = NowY;
		TestMap[i].no = i;
		TestMap[i].Used = 0;
		setcolor(BLACK);
		//Sleep(10);
		//line(NowX, NowY, NowX, NowY + RYlong);
		NowX += RXlong / DeltaS; //--------�᲻���е����
	}

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
void Move(Map map) {
	int NumOfPos = TestMapPos;
	int go=0; //���ܲ����ƶ�
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
	int last = NumOfPos - DeltaS - 1;	//����Ǹ���
	
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
	MOUSEMSG m;
	while (1) {

		Move(TestMap);
		if (kbhit()) {
			getch();
			EnterMap(TestMap);
		}
		Sleep(10);
	}
	if (getch());
}
