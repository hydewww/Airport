#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

Window* Win;
Window* WinVip;
int WinNum;
time_t TimeStart;
time_t TimeNow;
time_t TimeFinish;
int AirportState;
int PassengerArriveTask;

void InitWin(Window* win) {
	win->TotalSer = 0;
	win->TotalTime = 0;
	win->WaitNum = 0;
	win->WinHead = (Passenger*)malloc(sizeof(Passenger));
	win->WinHead->next = NULL;
	win->WinTail = win->WinHead;
	win->NowPas = NULL;
}
void SetAndBegin() {
	
	MainPara();
	Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	WinVip = (Window*)malloc(sizeof(Window));
	//--------------------------------------以下部分为新增（初始化Win数组）------------
	int i = 0;
	WinNum = MinCheck;
	for (i = 0; i < NumOfWin; i++)
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
		//Win[i].TotalSer = 0;
		//Win[i].TotalTime = 0;
		//Win[i].WaitNum = 0;
		//Win[i].WinHead=(Passenger*)malloc(sizeof(Passenger));
		//Win[i].WinHead->next = NULL;
		//Win[i].WinTail = Win[i].WinHead;
		//Win[i].NowPas = NULL;
	}
	WinVip->WinState = OpenWin;
	InitWin(WinVip);
	//--------------------------------------以上部分为新增（初始化Win数组）------------
	//memset(Win, 0, sizeof(Win[0]));
	fclose(fopen("output.txt", "w"));
	MainInput();
	time(&TimeStart);
	AirportState = OnWork;
	QueueEstablish();

}

 main() {
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
}

