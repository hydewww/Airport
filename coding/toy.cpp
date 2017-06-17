#include"global.h"
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#define FlashTime 100
#define Odin 0
#define Vip  1
//#define RXlong 30
//#define RYlong 30
IMAGE  Rimg;
IMAGE VRimg;
IMAGE BACKimg;

int EventNum;

//地图中的每一个小格
typedef struct Position {
	int x;
	int y;
	int Used;
}Position;
typedef Position* Map;


//----------------------------------------------------------------------------------------------排队缓冲区map
extern int MaxCustSingleLine;// 单队列最大等待乘客数
extern int MaxLines;// 蛇形缓冲区最多由MaxLines个直队组成
#define Thickness 4	//缓冲区边框粗细
Map LineMap;
void CreateLineMap() {

	LineMap = (Position*)malloc(MaxCustSingleLine * MaxLines * sizeof(Position));
	if (LineMap == NULL) {
		exit(1);
	}
	//int NowX = RXlong * 8;	//--------------------左上角X
	//int NowY = RYlong * 2;	//--------------------左上角Y

	int NowX = OdiWin[0].x +  (MaxCustCheck+4)* RXlong+0.2*CXlong; 
	int NowY = OdiWin[0].y + 0.1*CYlong;

	int mode = 1;
	int reverse = 1;

	//画边框
	setlinestyle(PS_SOLID, Thickness, NULL, 0);
	setcolor(BLACK);
	//line(NowX+ (Thickness + RXlong), NowY, NowX + MaxLines*(Thickness + RXlong), NowY);//最上
	line(NowX + (Thickness + RXlong), NowY, NowX + MaxLines*(Thickness + RXlong + 2), NowY);//最上

	line(NowX, NowY+MaxCustSingleLine*(Thickness+RYlong)+Thickness, NowX+MaxLines*(Thickness+RXlong+2), NowY + MaxCustSingleLine*(Thickness + RYlong) + Thickness);//最下
		

	for (int i = 1; i < MaxLines; i++) {
		line(NowX + i*(Thickness + RXlong+2), NowY, NowX+ i*(Thickness + RXlong+2), NowY+ MaxCustSingleLine*(Thickness + RYlong));//中间
	}

	NowX += Thickness/2+1;
	NowY += Thickness;
	
	for (int i = 0; i < MaxLines * MaxCustSingleLine; i++) {
		//赋初值
		LineMap[i].x = NowX;
		LineMap[i].y = NowY;
		LineMap[i].Used = 0;

		//改变模式
		if ((i + 1) % MaxCustSingleLine == 0) {	//拐弯
			mode = 0;
		}
		else if (i  % MaxCustSingleLine == 0) {	//直线
			mode = reverse;
			reverse = -reverse;
			setcolor(WHITE);
			line(NowX-Thickness+1, NowY-1, NowX-Thickness+1, NowY + RYlong);
		}

		//位置变化
		switch (mode) {
		case -1: NowY -= (RYlong+Thickness); break;		//向上
		case 0: NowX += (RXlong+Thickness+2); break;		//向右
		case 1:NowY += (RYlong+Thickness); break;		//向下
		}
	}//end of for
	//setlinecolor(RED);
	//画缓冲区入口
	if ( MaxLines % 2 == 0 )
		line(NowX - RXlong - 2*Thickness, NowY - Thickness , NowX - RXlong + RXlong, NowY -Thickness);
	else
		line(NowX - RXlong - 2*Thickness, NowY +RYlong + Thickness, NowX - Thickness, NowY+RYlong + Thickness );

	//画最左最右
	setcolor(BLACK);
	NowY = OdiWin[0].y + 0.1*CYlong;
	line(NowX, NowY, NowX, NowY + MaxCustSingleLine*(Thickness + RYlong) + Thickness);//最右

	NowX = OdiWin[0].x  + (MaxCustCheck+4)*RXlong + 0.2*CXlong;
	line(NowX-Thickness , NowY, NowX-Thickness , NowY + MaxCustSingleLine*(Thickness + RYlong)+Thickness);//最左
}
//排队缓冲区map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//-----------------------------------------------------------------------------------------------安检口map
extern int NumOfWin;	//安检口数
extern int NumOfVIPWin;	//vip安检口数
extern int CXlong;		//安检口宽度
extern int MaxCustCheck;//安检口最多乘客
extern int DDy;
extern int Xlong;
extern int Ylong;

#define MinStep MaxCustCheck+5//------------------需要修改
Map* CheckMap;	//安检口map数组
int* last;		//安检口最后一格数组 

//普通安检口map
void CreateSingleCheckMap(int no) {
	CheckMap[no] = (Position*)malloc((MinStep + no) * sizeof(Position));
	if (CheckMap[no] == NULL) {
		exit(1);
	}
	int NowX = OdiWin[no].x + 0.2*CXlong;//-------------------------
	int NowY = OdiWin[no].y + 0.1*CYlong;//-----------------------

	int i = 0;

	//setcolor(BLACK);
	//rectangle(NowX+RXlong, NowY + RYlong, NowX + RXlong + RXlong, NowY + RYlong + RYlong);

	//向右
	for (int j = 0; j < MaxCustCheck + 2; i++, j++) {
		NowX += RXlong;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	//putimage(NowX,NowY, &Rimg);

	//向上
	for (int j = 0; j < (1 + no); i++, j++) {
		//NowY -= RYlong;
		NowY -= (CYlong + 2 * DDy);
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	//putimage(NowX, NowY, &Rimg);

	//向右
	for (int j = 0; j < 2; i++, j++) {
		NowX += RXlong;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	//putimage(NowX, NowY, &Rimg);

	//向下
	//for (int j = 0; j < 0; i++, j++) {
	//	//NowY += RXlong;
	//	NowY += (CYlong + 2 * DDy);
	//	CheckMap[no][i].x = NowX;
	//	CheckMap[no][i].y = NowY;
	//	CheckMap[no][i].Used = 0;
	//}
	//putimage(NowX, NowY, &Rimg);

	last[no] = i - 1;
}

//vip安检口map
void CreateSingleVipMap(int no) {
	no = no + NumOfWin;

	CheckMap[no] = (Position*)malloc((MaxCustCheck + 1) * sizeof(Position));
	//int NowX = -(RXlong);//-------------------------
	//int NowY = RYlong * 2 + no*RYlong;//-----------------------
	int NowX = VipWin[0].x + 0.2*CXlong;
	int NowY = VipWin[0].y + 0.1*CYlong;
	int i;
	for (i = 0; i < (MaxCustCheck + 1); i++) {
		NowX += RXlong;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	last[no] = i - 1;
}

void CreateCheckMap() {
	CheckMap = (Map*)malloc((NumOfWin + NumOfVIPWin) * sizeof(Map));
	last = (int*)malloc((NumOfWin + NumOfVIPWin) * sizeof(int));
	//建立普通安检口map
	for (int i = 0; i < NumOfWin; i++) {
		CreateSingleCheckMap(i);
	}
	//建立vip安检口map
	for (int i = 0; i < NumOfVIPWin; i++) {
		CreateSingleVipMap(i);
	}
}

//安检口map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------GoGOGO
//移动！
void MoveRun(Position* New, Position* Old) {
	//setcolor(WHITE);
	//fillrectangle(Old->x, Old->y, Old->x + RXlong, Old->y + RYlong);	//用背景色填充
	IMAGE MoveImg;
	getimage(&MoveImg, Old->x, Old->y, RXlong, RYlong);
	putimage(Old->x, Old->y, &BACKimg);
	putimage(New->x, New->y, &MoveImg);
	Old->Used = 0;
	New->Used = 1;
}

//准备移动！
void Move(Map map,int NumOfPos) {
	//int NumOfPos = MaxCustSingleLine;
	int go=0; //看能不能移动

	for (int i = 0; i < NumOfPos; i++) {
		if (map[i].Used) {	
			if (go) {	
				MoveRun(&map[i - 1], &map[i]);	//这里的人能动 红红果我们走!！
			}
			else {
				go = 0;//这里的人不能动 是友军 去下个人那里！
			}
		}
		else {
			go = 1;	//这里没人 快攻陷这里
		}
	}
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++很迷很迷很迷的安检口id攻略法*/
int SpecialMap[20];
int Splast;
void SpecialMove() {
	int posid, winid;
	for (int i = 0; i < Splast; i++) {
		if (SpecialMap[i] == -1) {
			continue;
		}
		posid = SpecialMap[i] + (MaxCustCheck + 1) - (NumOfWin - i) - 1;
		winid = SpecialMap[i];

		MoveRun(&(CheckMap[winid][posid - 1]), &(CheckMap[winid][posid]));

		SpecialMap[i] = -1;
		if (i > 0 && posid>MaxCustCheck+1) {
			SpecialMap[i - 1] = winid;
		}
	}
}
//GoGoGo^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------------------------------------------------------------地图状态转化
//到机场啦！
extern void ShowID(int id, int x, int y);//新增显示ID函数
int EnLine() {
	int NumOfPos = MaxCustSingleLine*MaxLines;
	int last = NumOfPos - 1 ;	//最后那个点
	static int id = 0;
	//判断会不会重叠
	if (LineMap[last].Used)
		return 0;
	id++;

	putimage(LineMap[last].x, LineMap[last].y, &Rimg);
	LineMap[last].Used = 1;
	ShowID(id, LineMap[last].x, LineMap[last].y);
	return 1;
}

int EnVip(int no);
//去安检口啦！
int EnCheck(int no) {
	//普通乘客
	if (no < NumOfWin) {
		if (LineMap[0].Used) {			//队头有人
			MoveRun(&CheckMap[no][last[no]], &LineMap[0]);	//走你
			LineMap[0].Used = 0;
			CheckMap[no][last[no]].Used = 1;

			SpecialMap[Splast-1] = no;/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
			return 1;
		}
		return 0;
	}
	//Vip乘客 没有缓冲区 直接进安检口 操作不太一样
	else {
		EnVip(no);
	}
}

//Vip乘客 没有缓冲区 直接进安检口 操作不太一样
int EnVip(int no) {
	int last = MaxCustCheck;	//最后那个点
	static int Vipid = 0;
	//判断会不会重叠
	if (CheckMap[no][last].Used)
		return 0;
	Vipid++;
	putimage(CheckMap[no][last].x, CheckMap[no][last].y, &VRimg);
	CheckMap[no][last].Used = 1;
	ShowID(Vipid, CheckMap[no][last].x, CheckMap[no][last].y);
	return 1;
}

//滚蛋！！！！！
int DeCheck(int no) {
	if (CheckMap[no][0].Used) {
		setcolor(WHITE);
		//fillellipse(CheckMap[no][0].x, CheckMap[no][0].y, CheckMap[no][0].x + RXlong, CheckMap[no][0].y + RYlong);	//背景色填充
		putimage(CheckMap[no][0].x, CheckMap[no][0].y,  &BACKimg);
		CheckMap[no][0].Used = 0;
		return 1;
	}
	return 0;
}

//安检时间延迟
int BeginOK(int i) //到位后才设置时间
{
	if (CheckMap[i][1].Used == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//地图状态转化^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------缓存
Cache  EnCheckCache, DeCheckCache;
int EnLineCache;//缓冲区cache

void ResetCheckCache() {
	EnCheckCache.head %= CacheNum;
	EnCheckCache.tail %= CacheNum;
	DeCheckCache.head %= CacheNum;
	DeCheckCache.tail %= CacheNum;
}

void PreEnLine() {
	if(EnLineCache)
		if (EnLine())	//成功进入缓冲区
			EnLineCache--;		
}

void PreEnCheck() {
	if (EnCheckCache.head != EnCheckCache.tail) {
		if (EnCheck(EnCheckCache.no[EnCheckCache.head]))	//成功进入安检口
			EnCheckCache.head++;		//缓存-1
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
	initgraph(Xlong, Ylong,SHOWCONSOLE);
	//loadimage(&Rimg, _T("乘客.jpg"), RXlong, RYlong);
	//loadimage(&VRimg, _T("乘客new.jpg"), RXlong, RYlong);
	setbkcolor(WHITE);
	cleardevice();
	//安检口图片初始化
	SetWin();
	//安检口状态初始化
	InitState();
	//按键初始化
	SetButton();
	loadimage(&Rimg, _T("小人.jpg"), RXlong, RYlong);
	loadimage(&VRimg, _T("vip小人.jpg"), RXlong, RYlong);
	loadimage(&BACKimg, _T("背景.jpg"), RXlong, RYlong);
	//地图初始化
	CreateLineMap();
	CreateCheckMap();

	//Cache初始化
	EnLineCache = 0;
	EnCheckCache.head = EnCheckCache.tail = 0;
	DeCheckCache.head = DeCheckCache.tail = 0;

	//Starclock初始化
	InitStar();

	//++++++++++++++++++++++++++++++++++++++++++++SpecialMap初始化
	Splast = NumOfWin + 5;
	for (int i = 0; i < Splast; i++) {
		SpecialMap[i] = -1;
	}
}

clock_t PreMoveTime;
clock_t NowMoveTime;
void toy() {
	NowMoveTime = clock();
	//这里顺序不能变！！！ 有玄学的奥秘！！！
	if ((NowMoveTime - PreMoveTime) > FlashTime) {
		PreMoveTime = NowMoveTime;	//更新时间
		StarClock();
		PreDeCheck();	//出安检口
		UpdateState();//安检状态更新
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		for (int i = 0; i < NumOfWin; i++) {
			Move(CheckMap[i], MaxCustCheck+1);//普通安检口动 前6格
		}
		SpecialMove();
		/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
		for (int i = 0; i < NumOfVIPWin; i++) {
			Move(CheckMap[i+NumOfWin], (MaxCustCheck + 1));//vip安检口动
		}
		PreEnCheck();	//进安检口
		Move(LineMap, MaxCustSingleLine*MaxLines);//缓冲区动
		PreEnLine();	//进缓冲区
	}
}
