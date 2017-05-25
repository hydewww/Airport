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
int		PassengerArriveTask;	 /*没用过*/
int lock = 0;

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

	MainPara();
	//窗口初始化
	Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	VIPWin = (Window*)malloc(sizeof(Window)*NumOfVIPWin);
	WinNum = MinCheck;
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
		StatusOutput();
		lock = 0;
	}
	time(&TimeFinish);
	if (AirportState == OffWork)
	{	
		FinalOutput();
	}
	WaitForSingleObject(KeyBoard, INFINITE);
	CloseHandle(KeyBoard);
	system("pause");
	return 0;
}

