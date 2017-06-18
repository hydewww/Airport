#include <windows.h>
#include<process.h>	
#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#include<conio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "passenger.h"
#include "window.h"
#include "queue.h"

#define BOX_WIDTH 100	//选项盒的宽
#define BOX_HEGIHT 50	//选项盒的高

Window* Win;
Window* VIPWin;
int		WinNum;
int		VipWinNum;
time_t	TimeStart;
time_t	TimeNow;
time_t	TimeFinish;
int		AirportState;
int		lock = 0;
Queue*  OdinQueue;
Queue*  VipQueue;

Queue* QueueEstablish();//创建队列
void FreeMem();	//释放malloc内存

void InitWin(Window* win) //窗口初始化
{
	win->TotalSer = 0;
	win->TotalTime = 0;
	win->WaitNum = 0;
	win->WinHead = (Passenger*)malloc(sizeof(Passenger));
	win->WinHead->next = NULL;
	win->WinTail = win->WinHead;
	win->NowPas = NULL;
}


void SetAndBegin() 
{
	//InitInterface();
	//MainPara();
	//窗口初始化
	Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	VIPWin = (Window*)malloc(sizeof(Window)*NumOfVIPWin);
	WinNum = MinCheck;
	VipWinNum = NumOfVIPWin;
	for (int i = 0; i < NumOfWin; i++)
	{
		if (i < MinCheck)
			Win[i].WinState = OpenWin;
		else
			Win[i].WinState = CloseWin;
		InitWin(&Win[i]);
		Win[i].type = 'O';
	}
	for (int i = 0; i < NumOfVIPWin; i++) 
	{
		VIPWin[i].WinState = OpenWin;
		InitWin(&VIPWin[i]);
		VIPWin[i].type = 'V';
	}
	//初始化Win数组over

	fclose(fopen("output.txt", "w"));//清空output.txt
	MainInput();//生成事件
	OdinQueue = QueueEstablish();
	VipQueue = QueueEstablish();

	AirportState = OnWork;
	time(&TimeStart);
}


Queue* QueueEstablish()//创建队列头指针函数
{
	Queue* queue;
	if (!(queue = (Queue*)malloc(sizeof(Queue))) || !(queue->QueueHead = (Passenger*)malloc(sizeof(Passenger)))) {
		puts("申请缓冲区内存失败!");
		exit(EXIT_FAILURE);
	}
	queue->QueueHead->next = NULL;//开始无乘客
	queue->QueueTail = queue->QueueHead;//尾指针和头指针同指
	queue->SumNum = 0;
	queue->WaitNum = 0;
	return queue;
}

void FreeMem() {
	for (int i = 0; i < NumOfWin; i++) {
		free(Win[i].WinHead);
	}
	free(Win);
	for (int i = 0; i < NumOfVIPWin; i++) {
		free(VIPWin[i].WinHead);
	}
	free(VIPWin);
	
	free(OdinQueue->QueueHead);
	free(OdinQueue);
	free(VipQueue->QueueHead);
	free(VipQueue);
}

bool judgeButton(int x, int y, int bx, int by,int width, int height) {
	if (x >= bx&&x <= bx + width&&y >= by&&y <= by + height)
		return true;
	return false;
}

void BeginServe() {
	
	lock = 0;
	SetAndBegin();
	InitDraw();
	HANDLE Mouse;
	HANDLE KeyBoard;
	Mouse = (HANDLE)_beginthreadex(NULL, 0, MouseEvent, NULL, 0, NULL);
	KeyBoard= (HANDLE)_beginthreadex(NULL, 0, KeyEvent, NULL, 0, NULL);
	while (AirportState != OffWork)
	{
		AirportOnServe();
		StateTrans(&thisEvent);
		StatusOutput();
		toy();
		lock = 0;
	}
	time(&TimeFinish);
	closegraph();
	fflush(stdin);
	initgraph(WINDOWS_X, WINDOWS_Y);
	InitFinalStar();
	setcolor(WHITE);
	while (true) {
		cleardevice();
		if (kbhit()) {
			char c = getch();
			if (c == '\r')
				break;
		}
		MoveFinalStar();
		FinalOutput();
		Sleep(100);
	}
	FreeMem();//释放malloc内存
	FreeToy();
	closegraph();



	WaitForSingleObject(KeyBoard, INFINITE);
	CloseHandle(KeyBoard);
	WaitForSingleObject(Mouse, INFINITE);
	CloseHandle(Mouse);

	exit(0);

	//system("pause");
}

int InitInterCheck() {

	MOUSEMSG msg;
	while (true) {
		if (MouseHit())// 当有鼠标消息的时候执行
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (judgeButton(msg.x, msg.y, 1100, 300, BOX_WIDTH, BOX_HEGIHT)) {		//开始进行安检
					TCHAR s[10];
					InputBox(s, 10, _T("请输入事件个数"));
					EventNum = _ttoi(s);
					BeginServe();
				}
				if (judgeButton(msg.x, msg.y, 1100, 400, BOX_WIDTH, BOX_HEGIHT)) {		//修改配置文件
					MainPara();
				}
				if (judgeButton(msg.x, msg.y, 1100, 500, BOX_WIDTH, BOX_HEGIHT)) {		//退出程序
					closegraph();
					exit(0);
				}
			}
		}
	}
}

int main() {

	lock = 0;
	mciSendString(TEXT("open 警报2.mp3 alias music"), NULL, 0, NULL);
	ParaData();
	//HANDLE KeyBoard;
	InitInter();
	InitInterCheck();

	//KeyBoard = (HANDLE)_beginthreadex(NULL, 0, KeyEvent, NULL, 0, NULL);

	return 0;
}
