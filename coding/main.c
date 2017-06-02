#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "passenger.h"
#include "window.h"
#include "queue.h"

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

void InitInterface() //��ӭ����
{
	printf("\n\n\n\n");

	for (int j = 0; j < 8; j++) {
		printf(" ");
	}
	for (int i = 0; i < 100; i++) {
		printf("*");
	}
		printf("*\n");

	for (int i = 0; i < 20; i++) {

		if (i == 9) {
			for (int j = 0; j < 8; j++) {
				printf(" ");
			}
			printf("*");
			for (int j = 0; j < 40; j++) {
				printf(" ");
			}
			printf("��ӭ����DKY48������");
			for (int j = 0; j < 40; j++) {
				printf(" ");
			}
			printf("*\n");
		}
		else {
			for (int j = 0; j < 8; j++) {
				printf(" ");
			}
			printf("*");
			for (int j = 0; j < 99; j++)
				printf(" ");
			printf("*\n");
		}
	
	}

	for (int j = 0; j < 8; j++) {
		printf(" ");
	}

	for (int i = 0; i < 100; i++)
		printf("*");
	printf("*\n\n\n");

	getchar();
	system("CLS");
	while (getchar() != '\n')
		;
}

void SetAndBegin() 
{
	InitInterface();
	MainPara();
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

int main() {

	lock = 0;
	mciSendString(TEXT("open ����2.mp3 alias music"), NULL, 0, NULL);
	HANDLE KeyBoard;
	SetAndBegin();
	KeyBoard = (HANDLE)_beginthreadex(NULL, 0, KeyEvent, NULL, 0, NULL);

	while (AirportState!=OffWork)
	{
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
	FreeMem();//�ͷ�malloc�ڴ�
	system("pause");
	return 0;
}
