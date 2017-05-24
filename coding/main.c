#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

Window* Win;
Window* VIPWin;
int		WinNum;
time_t	TimeStart;
time_t	TimeNow;
time_t	TimeFinish;
int		AirportState;
int		PassengerArriveTask;
int lock = 0;

void InitWin(Window* win) 
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
	MainPara();
	Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	VIPWin = (Window*)malloc(sizeof(Window)*NumOfVIPWin);
	//--------------------------------------以下部分为新增（初始化Win数组）------------
	WinNum = MinCheck;
	for (int i = 0; i < NumOfWin; i++)
	{
		if (i < MinCheck)
		{
			Win[i].WinState = OpenWin;
		}
		else
		{
			Win[i].WinState = CloseWin;
		}
		InitWin(&Win[i]);
		Win[i].type = 'O';
	}
	for (int i = 0; i < NumOfVIPWin; i++) 
	{
		VIPWin[i].WinState = OpenWin;
		InitWin(&VIPWin[i]);
		VIPWin[i].type = 'V';
	}
	//--------------------------------------以上部分为新增（初始化Win数组）------------
	//memset(Win, 0, sizeof(Win[0]));
	fclose(fopen("output.txt", "w"));
	MainInput();
	time(&TimeStart);
	AirportState = OnWork;
	QueueEstablish();
}

int main() {
	lock = 0;
	SetAndBegin();
	mciSendString(TEXT("open 警报2.mp3 alias music"), NULL, 0, NULL);
	HANDLE KeyBoard;
	KeyBoard = (HANDLE)_beginthreadex(NULL, 0, KeyEvent, NULL, 0, NULL);
	while (AirportState!=OffWork)
	{
		lock = 1;
		AirportOnServe();
		StateTrans(&thisEvent);
		StatusOutputCmd();
		//time(&TimeFinish);
		StatusOutputFile();
		lock = 0;
	}
	time(&TimeFinish);
	//StatusOutputFile();
	WaitForSingleObject(KeyBoard, INFINITE);
	CloseHandle(KeyBoard);
	if (AirportState == OffWork)
	{
		printf("下班拉！！！！！！！！！！！！！！！！！！！！\n");
	}
	system("pause");
	return 0;
}

