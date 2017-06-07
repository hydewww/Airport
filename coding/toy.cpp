#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>


int  DeltaS = 10;
#define RXlong 30
#define RYlong 30
IMAGE  Rimg;



//地图精细程度 1为一次一格 2为一次0.5格

//地图中的每一个小格
typedef struct Position {
	int no;
	int x;
	int y;
	int Used;
}Position;
typedef Position* Map;

//地图中位置数

Map TestMap;
int NumOfTestMap = 40; //地图中乘客最大人数
int TestMapPos = NumOfTestMap * DeltaS;

//建立地图
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
		NowX += RXlong / DeltaS; //--------会不会有点奇怪
	}

}

//移动！
void MoveRun(Position* New, Position* Old) {
	setcolor(WHITE);
	fillellipse(Old->x, Old->y, Old->x + RXlong, Old->y + RYlong);
	putimage(New->x, New->y, &Rimg);
	Old->Used = 0;
	New->Used = 1;
}

//处理整张地图
void Move(Map map) {
	int NumOfPos = TestMapPos;
	int go=0; //看能不能移动
	for (int i = 0; i < NumOfPos; i++) {
		if (map[i].Used) {	
			if (go) {	
				MoveRun(&map[i - 1], &map[i]);	//这里有人+能动 红红果我们走
			}
			else {
				i += DeltaS-1;	//这里有人？还不能动？去下个人那里！
				go = 0;
			}
		}
		else {
			go = 1;	//这里没人 快攻陷这里
		}
	}
}

void EnterMap(Map map) {
	int NumOfPos = TestMapPos;
	int last = NumOfPos - DeltaS - 1;	//最后那个点
	
	//不能重叠
	for (int i = last - DeltaS + 1; i < last; i++) {
		if (map[i].Used)
			return;
	}

	putimage(map[last].x, map[last].y, &Rimg);
	map[last].Used = 1;
}




int main() {
	initgraph(1500, 800);
	loadimage(&Rimg, _T("乘客.jpg"), RXlong, RYlong);
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
