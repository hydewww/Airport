#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"passenger.h"
#include"window.h"
#include<Windows.h>
#include<process.h>

void WinList(FILE*fp, int i) {
	Passenger* cur = Win[i].WinHead;
	do {
		cur = cur->next;
		fprintf(fp, " %d", cur->id);
	} while (cur != Win[i].WinTail);
}
void StatusOutput() {
	StartTimer(100);
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
		WinList(fp,i);
		fprintf(fp, ", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead);
	}		
	
	fprintf(fp, "ListLines = %d\n", Queuehead->next->id);		//排队缓冲区队首乘客编号，队尾乘客编号
	fprintf(fp, "ListCustCount = %d\n", Queuetail->id);	//排队缓冲区总乘客数
	fclose(fp);
}

void EventOutput(char event,int id,int no) {	//id乘客 no安检口
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	switch (event) {
	case 'G':fprintf(fp, "%d号乘客进入排队缓冲区\n", id); break;
	case 'F':fprintf(fp, "排队缓冲区已满\n"); break;
	case 'C':fprintf(fp, "%d号乘客进入%d号安检口\n", id, no); break;
	case 'L':fprintf(fp, "%d号乘客完成安检离开\n", id); break;
	case 'O':fprintf(fp, "%d号安检口开启", no); break;
	case 'S':fprintf(fp, "%d号安检口关闭", no); break;
	case 'X':fprintf(fp, "%d号安检口申请休息", no); break;
	case 'K':fprintf(fp, "%d号安检口开始休息", no); break;
	case 'J':fprintf(fp, "%d号安检口结束休息", no); break;
	case 'Q':fprintf(fp, "接收到下班指令\n"); break;
	default:fprintf(fp, "接收到未知事件\n"); break;
	}
	fclose(fp);
}