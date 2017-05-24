#include <stdio.h>
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
	SetAndBegin();
	while (AirportState!=OffWork)
	{
		AirportOnServe();
		StateTrans(&thisEvent);
		StatusOutputCmd();
		//time(&TimeFinish);
		StatusOutputFile();
	}
	time(&TimeFinish);
	//StatusOutputFile();
	if (AirportState == OffWork)
	{
		printf("下班拉！！！！！！！！！！！！！！！！！！！！\n");
	}
	system("pause");
	return 0;
}

