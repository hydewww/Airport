#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

Window* Win;
int WinNum;
time_t TimeStart;
time_t TimeNow;
time_t TimeFinish;
int AirportState;
int PassengerArriveTask;

void SetAndBegin() {

	MainPara();
	Win = (Window*)malloc(sizeof(Window)*NumOfWin);
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
		Win[i].TotalSer = 0;
		Win[i].TotalTime = 0;
		Win[i].WaitNum = 0;
		Win[i].WinHead=(Passenger*)malloc(sizeof(Passenger));
		Win[i].WinHead->next = NULL;
		Win[i].WinTail = Win[i].WinHead;
		//Win[i].WinState = NULL;
		Win[i].NowPas = NULL;
	}
	//--------------------------------------以上部分为新增（初始化Win数组）------------
	//memset(Win, 0, sizeof(Win[0]));
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
		//StatusOutputFile();
	}
	//time(&TimeFinish);
	//StatusOutputFile();
	if (AirportState == OffWork)
	{
		printf("下班拉！！！！！！！！！！！！！！！！！！！！\n");
	}
	system("pause");
}

