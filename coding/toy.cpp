#include"global.h"
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
int checklock = 0;//------这个lock用安检口是否满人代替
#define SleepTime 50


int  DeltaS =1; //----------------------小格精细程度 一人可分为几个小格
#define RXlong 20
#define RYlong 20
IMAGE  Rimg;
IMAGE VRimg;


//地图中的每一个小格
typedef struct Position {
	//int CheckNo;
	int x;
	int y;
	int Used;
}Position;
typedef Position* Map;


//----------------------------------------------------------------------------------------------排队缓冲区map
extern int MaxCustSingleLine;// 单队列最大等待乘客数
extern int MaxLines;// 蛇形缓冲区最多由MaxLines个直队组成
//int MaxCustSingleLine = 10;
//int MaxLines = 5;
int SingleLinePos; //每列的身位
Map LineMap;
void CreateLineMap() {

	LineMap = (Position*)malloc( SingleLinePos * MaxLines * sizeof(Position));
	if (LineMap==NULL) {
		exit(1);
	}
	int NowX = 160;	//--------------------左上角X
	int NowY = 40;	//--------------------左上角Y

	int mode = 1;	
	int reverse=1;

	for (int i = 0; i < MaxLines * SingleLinePos; i++) {
		//赋初值
		LineMap[i].x = NowX;
		LineMap[i].y = NowY;
		//LineMap[i].CheckNo = i;
		LineMap[i].Used = 0;
		//改变模式
		if ( (i+DeltaS)  % SingleLinePos == 0) {	//拐弯
			mode = 0;
		}
		else if (i  % SingleLinePos == 0) {		//直线
			mode =reverse;
			reverse = -reverse;
		}
		//位置变化
		switch(mode){
		case -1: NowY -= RYlong / DeltaS; break;	//向上
		case 0: NowX += RXlong / DeltaS; break;		//向右
		case 1:NowY += RYlong / DeltaS; break;		//向下
		}
	}//end of for
}
//排队缓冲区map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//-----------------------------------------------------------------------------------------------安检口map
extern int NumOfWin;
//int NumOfWin = 10;
Map* CheckMap;
int* last;
extern int  CXlong;
extern int MaxCustCheck;
//int CXlong = 300;
//int MaxCustCheck = 5;

#define MinStep 12

void CreateSingleCheckMap(int no) {
	CheckMap[no] = (Position*)malloc((MinStep+no)*DeltaS * sizeof(Position));//--------------

	int NowX = - (RXlong / DeltaS);//-------------------------
	int NowY = 40+no*RYlong;//-----------------------

	int i=0;

	//setcolor(BLACK);
	//rectangle(NowX+RXlong, NowY + RYlong, NowX + RXlong + RXlong, NowY + RYlong + RYlong);
	//向右
	for (int j = 0; j < (MaxCustCheck+2)*DeltaS; i++,j++) {
		NowX += RXlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX,NowY, &Rimg);

	//向上
	for (int j = 0; j < (2+no)*DeltaS; i++, j++) {	
		NowY -= RYlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX, NowY, &Rimg);

	//向右
	for (int j = 0; j < 2 * DeltaS; i++, j++) {
		NowX += RXlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX, NowY, &Rimg);

	//向下
	for (int j = 0; j <  DeltaS; i++, j++) {
		NowY += RXlong / DeltaS;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		//CheckMap[no][i].CheckNo = i;
		CheckMap[no][i].Used = 0;

	}
	//putimage(NowX, NowY, &Rimg);

	last[no] = i-1;
}

void CreateCheckMap() {
	CheckMap = (Map*)malloc(NumOfWin * sizeof(Map));
	last = (int*)malloc(NumOfWin * sizeof(int));
	for (int i = 0; i < NumOfWin; i++) {
		CreateSingleCheckMap(i);
	}
}

//安检口map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------GoGOGO
//移动！
void MoveRun(Position* New, Position* Old) {
	setcolor(WHITE);
	fillellipse(Old->x, Old->y, Old->x + RXlong, Old->y + RYlong);
	putimage(New->x, New->y, &Rimg);
	Old->Used = 0;
	New->Used = 1;
}

//准备移动！
void Move(Map map,int NumOfPos) {
	//int NumOfPos = SingleLinePos;
	int go=0; //看能不能移动

	for (int i = 0; i < NumOfPos; i++) {
		if (map[i].Used) {	
			if (go) {	
				MoveRun(&map[i - 1], &map[i]);	//这里的人能动 红红果我们走!！
			}
			else {
				i += DeltaS-1;	//这里的人不能动 是友军 去下个人那里！
				go = 0;
			}
		}
		else {
			go = 1;	//这里没人 快攻陷这里
		}
	}
}
//GoGoGo^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------------------------------------------------------------地图状态转化
//到机场啦！
int EnLine() {
	int NumOfPos = SingleLinePos*MaxLines;
	int last = NumOfPos - DeltaS ;	//最后那个点
	
	//判断会不会重叠
	for (int i = last - DeltaS + 1; i < last; i++) {	
		if (LineMap[i].Used)
			return 0;
	}

	putimage(LineMap[last].x, LineMap[last].y, &Rimg);
	LineMap[last].Used = 1;
	return 1;
}

//去安检口啦！
int EnCheck(int no) {
	//处理缓冲区头 看看能不能走
	//if (checklock && LineMap[0].Used) {			//安检口未满 & 队头有人
	if (LineMap[0].Used) {			//队头有人
		MoveRun(&CheckMap[no][last[no]], &LineMap[0]);	//走你
		LineMap[0].Used = 0;
		CheckMap[no][last[no]].Used = 1;
		return 1;
	}
	return 0;
}


//滚蛋！！！！！
int DeCheck(int no) {
	if (CheckMap[no][0].Used) {
		fillellipse(CheckMap[no][0].x, CheckMap[no][0].y, CheckMap[no][0].x + RXlong, CheckMap[no][0].y + RYlong);
		CheckMap[no][0].Used = 0;
		return 1;
	}
	return 0;
}
//地图状态转化^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------缓存
struct En_Check_Cache  EnCheckCache, DeCheckCache;

void ResetCheckCache() {
	EnCheckCache.head %= CacheNum;
	EnCheckCache.tail %= CacheNum;
	DeCheckCache.head %= CacheNum;
	DeCheckCache.tail %= CacheNum;
}

int EnLineCache;//缓冲区cache
void PreEnLine() {
	if(EnLineCache)
		if (EnLine())
			EnLineCache--;
}


void PreEnCheck() {
	if (EnCheckCache.head != EnCheckCache.tail) {
		if (EnCheck(EnCheckCache.no[EnCheckCache.head]))
			EnCheckCache.head++;
	}
	ResetCheckCache();
}

void PreDeCheck() {
	if (DeCheckCache.head != DeCheckCache.tail) {
		if (DeCheck(DeCheckCache.no[DeCheckCache.head]))
			DeCheckCache.head++;
	}
	ResetCheckCache();
}
//缓存^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


void InitDraw() {
	initgraph(1200, 600);
	loadimage(&Rimg, _T("乘客.jpg"), RXlong, RYlong);
	loadimage(&VRimg, _T("乘客new.jpg"), RXlong, RYlong);
	setbkcolor(WHITE);
	cleardevice();
	CreateLineMap();
	CreateCheckMap();

	EnLineCache = 0;
	EnCheckCache.head = EnCheckCache.tail = 0;
	DeCheckCache.head = DeCheckCache.tail = 0;

	
}

clock_t PreMove;
clock_t NowMove;
void toy() {
	NowMove = clock();
	//这里顺序不能变！！！ 有玄学的奥秘！！！
	if ((NowMove - PreMove) > 100) {
		PreDeCheck();
		PreMove = NowMove;
		for (int i = 0; i < NumOfWin; i++) {
			Move(CheckMap[i], (MinStep + i) * DeltaS);//安检口动
		}
		PreEnCheck();
		Move(LineMap, SingleLinePos*MaxLines);//缓冲区动
		PreEnLine();
	}
}


//单文件调试用
//void main() {
//	initgraph(1200, 600);
//	loadimage(&Rimg, _T("乘客.jpg"), RXlong, RYlong);
//	setbkcolor(WHITE);
//	cleardevice();
//	CreateLineMap();
//	CreateCheckMap();
//	char c;
//	while (1) {
		//for (int i = 0; i < NumOfWin; i++) {
		//	Move(CheckMap[i], (MinStep+i) * DeltaS);//安检口动
		//}
//		//EnCheck(0);						//缓冲区头动
//		Move(LineMap, SingleLinePos*MaxLines);//缓冲区动
//
//		if (kbhit()) {
//			c=getch();
//			if (c == 'l')
//				checklock = !checklock;
//			else if (c <= '9'&&c >= '0') {
//				c = c - '0';
//				EnCheck(c);
//			}
//			else if (c == 'a')
//				DeCheck(rand() % 10);
//			else
//				EnLine();
//		}
//		Sleep(SleepTime);
//	}
//	if (getch());
//}
