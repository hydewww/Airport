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

#define BOX_WIDTH 100	//ѡ��еĿ�
#define BOX_HEGIHT 50	//ѡ��еĸ�

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

Queue* QueueEstablish();//��������
void FreeMem();	//�ͷ�malloc�ڴ�

void InitWin(Window* win) //���ڳ�ʼ��
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
	//���ڳ�ʼ��
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
	//��ʼ��Win����over

	fclose(fopen("output.txt", "w"));//���output.txt
	MainInput();//�����¼�
	OdinQueue = QueueEstablish();
	VipQueue = QueueEstablish();

	AirportState = OnWork;
	time(&TimeStart);
}


Queue* QueueEstablish()//��������ͷָ�뺯��
{
	Queue* queue;
	if (!(queue = (Queue*)malloc(sizeof(Queue))) || !(queue->QueueHead = (Passenger*)malloc(sizeof(Passenger)))) {
		puts("���뻺�����ڴ�ʧ��!");
		exit(EXIT_FAILURE);
	}
	queue->QueueHead->next = NULL;//��ʼ�޳˿�
	queue->QueueTail = queue->QueueHead;//βָ���ͷָ��ָͬ
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
	FreeMem();//�ͷ�malloc�ڴ�
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
		if (MouseHit())// ���������Ϣ��ʱ��ִ��
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (judgeButton(msg.x, msg.y, 1100, 300, BOX_WIDTH, BOX_HEGIHT)) {		//��ʼ���а���
					TCHAR s[10];
					InputBox(s, 10, _T("�������¼�����"));
					EventNum = _ttoi(s);
					BeginServe();
				}
				if (judgeButton(msg.x, msg.y, 1100, 400, BOX_WIDTH, BOX_HEGIHT)) {		//�޸������ļ�
					MainPara();
				}
				if (judgeButton(msg.x, msg.y, 1100, 500, BOX_WIDTH, BOX_HEGIHT)) {		//�˳�����
					closegraph();
					exit(0);
				}
			}
		}
	}
}

int main() {

	lock = 0;
	mciSendString(TEXT("open ����2.mp3 alias music"), NULL, 0, NULL);
	ParaData();
	//HANDLE KeyBoard;
	InitInter();
	InitInterCheck();

	//KeyBoard = (HANDLE)_beginthreadex(NULL, 0, KeyEvent, NULL, 0, NULL);

	return 0;
}
