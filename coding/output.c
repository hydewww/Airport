#include<stdio.h>
#include<stdlib.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

void WinList(FILE*fp, int i) {
	//test
	Window* Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	//
	Passenger* cur = Win[i].WinHead;
	fprintf(fp, "WinList = %d", cur->id);
	do {
		fprintf(fp, " %d", cur->id);
		cur = cur->next;
	} while (cur != Win[i].WinTail);
}
void StatusOutput() {
	//test
	Window* Win = (Window*)malloc(sizeof(Window)*NumOfWin);
	//
	FILE* fp;
	if (!  (fp=fopen("output.txt", "a"))  ) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	//fprintf(fp, "-----------------------------------------------\n");
	fprintf(fp,"T=<%l>\n", TimeNow);								//T=<当前时间（3位）>
	fprintf(fp, "OFFDUTY = %c\n", AirportState == 0 ? "N" : "Y");	//是否下班
	//WIN1 : State = 状态(11位)，WinList = 队列中乘客编号列表，WinListCustCount = 安检口队列人数
	for (int i = 0; i < NumOfWin; i++) {
		fprintf(fp,"WIN%d : State = %11d, ", i, Win[i].WinState);
		WinList(fp,i);
		fprintf(fp, ", WinListCustCount = \n", Win[i].WinTail - Win[i].WinHead + 1);
	}		
	
	fprintf(fp, "ListLines = %d\n", );		//排队缓冲区队首乘客编号，队尾乘客编号
	fprintf(fp, "ListCustCount = %d\n", );	//排队缓冲区总乘客数
	fclose(fp);
}

void EventOutput(char ch,int no) {	//???
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	if (ch == 'Q') {
		fprintf(fp,"接收到下班指令");
		return;
	}
	else if (ch == 'G') {				//??????
		if (OdinWatNum == MaxSeqLen)
			fprintf(fp,"排队缓冲区已满\n");
		else
			fprintf(fp, "%d乘客进入排队缓冲区\n", no);
	}
	else if (ch == 'L') {
		fprintf(fp, "%d乘客完成安检离开\n", no);
	}
}