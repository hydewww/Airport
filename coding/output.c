#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

void StatusOutputFile() {
	time(&TimeNow);
	if ( ((int)difftime(TimeStart,TimeNow)) %3!=0)
		return;
	FILE* fp;
	if (!  (fp=fopen("output.txt", "a"))  ) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	fprintf(fp,"T=<%l>\n", TimeNow);								//T=<当前时间（3位）>
	fprintf(fp, "OFFDUTY = %c\n", AirportState == 0 ? "N" : "Y");	//是否下班
	//WIN1 : State = 状态(11位)，WinList = 队列中乘客编号列表，WinListCustCount = 安检口队列人数
	for (int i = 0; i < NumOfWin; i++) {
		fprintf(fp,"WIN%d : State = %11d, ", i, Win[i].WinState);
		Passenger* cur = Win[i].WinHead;
		do {
			cur = cur->next;
			fprintf(fp, " %d", cur->id);
		} while (cur != Win[i].WinTail);
		fprintf(fp, ", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead);
	}		
	
	fprintf(fp, "ListLines = %d\n", Queuehead->next->id);		//排队缓冲区队首乘客编号，队尾乘客编号
	fprintf(fp, "ListCustCount = %d\n", Queuetail->id);	//排队缓冲区总乘客数
	fclose(fp);
}

void EventOutputFile(char event,int PasID,int WinID) {	//PasID乘客 WinID安检口
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	switch (event) {
	case 'G':fprintf(fp, "%d号乘客进入排队缓冲区\n", PasID); break;
	case 'F':fprintf(fp, "排队缓冲区已满\n"); break;
	case 'C':fprintf(fp, "%d号乘客进入%d号安检口\n", PasID, WinID); break;
	case 'L':fprintf(fp, "%d号乘客完成安检离开\n", PasID); break;
	case 'O':fprintf(fp, "%d号安检口开启\n", WinID); break;
	case 'S':fprintf(fp, "%d号安检口关闭\n", WinID); break;
	case 'X':fprintf(fp, "%d号安检口申请休息\n", WinID); break;
	case 'K':fprintf(fp, "%d号安检口开始休息\n", WinID); break;
	case 'J':fprintf(fp, "%d号安检口结束休息\n", WinID); break;
	case 'Q':fprintf(fp, "接收到下班指令\n"); break;
	default:fprintf(fp, "接收到未知事件\n"); break;
	}
	fclose(fp);
}
time_t t1;
time_t t2;

void StatusOutputCmd() {
	t1 = t2;
	time(&t2);
	if (((int)difftime(t2,t1 )) !=1 )
		return;
	puts("--------------------------------------");
	printf("时间 : %s", ctime(&TimeNow));	
	//机场状态
	switch (AirportState) {
	case 0:printf("工作状态 = 下班\n"); break;
	case 1:printf("工作状态 = 工作中  \n"); break;
	case 2:printf("工作状态 = 准备下班\n"); break;
	default: printf("机场状态异常"); exit(1);
	}
	//排队缓冲区状态
	if (Queuehead->next != NULL)
		printf("排队缓冲区总人数: %d ,首乘客: %d , 尾乘客: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id);		//排队缓冲区队首乘客编号，队尾乘客编号
	else
		puts("排队缓冲区总人数: 0");
	puts("");
	//窗口状态
	for (int i = 0; i < NumOfWin; i++) {
		//窗口id
		printf("WIN%d  ", i);
		//状态
		switch (Win[i].WinState) {
		case 0:printf("    关闭"); break;
		case 1:printf("    开启"); break;
		case 2:printf("  服务中"); break;
		case 3:printf("    休息"); break;
		case 4:printf("准备休息"); break;
		case 5:printf("准备关闭"); break;
		default:printf("状态异常"); exit(1); break;
		}
		//正在安检乘客
		if (Win[i].NowPas) {
			printf("\t正在安检: %2d ", Win[i].NowPas->id);
		}
		else {
			printf("\t正在安检: 无 ");
		}
		//窗口队列
		if (Win[i].WinHead != Win[i].WinTail) {	//判空
			printf(" , 队列:");
			Passenger* cur = Win[i].WinHead;	
			do {
				cur = cur->next;
				printf(" %d", cur->id);
			} while (cur != Win[i].WinTail);	
		}
		printf("\n");
	}

	printf("现在发生事件:%d\n", thisEvent.no);
}