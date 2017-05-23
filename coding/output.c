#include"global.h"
#include"passenger.h"
#include"window.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>

void WinPrint(Window* win) {
	switch (win->WinState) {
	case 0:printf("    关闭"); break;
	case 1:printf("  空闲中"); break;
	case 2:printf("  服务中"); break;
	case 3:printf("  休息中"); break;
	case 4:printf("准备休息"); break;
	case 5:printf("准备关闭"); break;
	default:printf("\n窗口状态异常！\n"); exit(1); break;
	}
	//正在安检
	if (win->NowPas) {
		printf("\t正在安检: %3d ", win->NowPas->id);
	}
	else {
		printf("\t正在安检:  无 ");
	}
	//窗口队列
	if (win->WinHead != win->WinTail) {	//判空
		printf(" , 队列:");
		Passenger* cur = win->WinHead;
		do {
			cur = cur->next;
			printf(" %3d", cur->id);
		} while (cur != win->WinTail);
	}

}


extern int ii;
time_t PreFile;
void StatusOutputFile() {
	time(&TimeNow);
	double wtf;
	wtf = difftime(TimeNow, PreFile);
	if (wtf <3)
		return;
	PreFile = TimeNow;
	FILE* fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(1);
	}
	fprintf(fp, "-----------------------------------------------\n");
	fprintf(fp, "时间 : %s", ctime(&TimeNow));
	//机场状态
	switch (AirportState) {
	case 0:fprintf(fp, "工作状态 = 下班\n"); break;
	case 1:fprintf(fp, "工作状态 = 正在工作\n"); break;
	case 2:fprintf(fp, "工作状态 = 准备下班\n"); break;
	default: fprintf(fp, "机场状态异常"); exit(1);
	}

	//窗口状态
	for (int i = 0; i < NumOfWin; i++) {
		//窗口n
		fprintf(fp,"WIN%d  ", i + 1);
		//窗口状态
		switch (Win[i].WinState) {
		case 0:fprintf(fp,"    关闭"); break;
		case 1:fprintf(fp,"  空闲中"); break;
		case 2:fprintf(fp,"  服务中"); break;
		case 3:fprintf(fp,"  休息中"); break;
		case 4:fprintf(fp,"准备休息"); break;
		case 5:fprintf(fp,"准备关闭"); break;
		default:fprintf(fp,"\n窗口状态异常！\n"); exit(1); break;
		}
		//正在安检
		if (Win[i].NowPas) {
			fprintf(fp,"\t正在安检: %3d ", Win[i].NowPas->id);
		}
		else {
			fprintf(fp,"\t正在安检:  无 ");
		}
		//窗口队列
		if (Win[i].WinHead != Win[i].WinTail) {	//判空
			fprintf(fp," , 队列:");
			Passenger* cur = Win[i].WinHead;
			do {
				cur = cur->next;
				fprintf(fp," %3d", cur->id);
			} while (cur != Win[i].WinTail);
		}
		fprintf(fp,"\n");
	}

	//排队缓冲区状态
	if (Queuehead->next != NULL) 
		fprintf(fp,"\n\t\t排队缓冲区\n总人数: %d ,首乘客: %d , 尾乘客: %d , 队列数: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id, (OdinLineWaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine);		//排队缓冲区队首乘客编号，队尾乘客编号
	else
		fprintf(fp,"\n排队缓冲区总人数: 0\n");

	fprintf(fp, "-----------------------------------------------\n");
}

void EventOutputFile(char event, int PasID, int WinID) {	//PasID乘客 WinID安检口
	//StatusOutputFile();
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

time_t PreCmd; //记录上次输出时间
extern int ii;
extern int OdinLineWaitNum;

//每秒在cmd打印当前状态
void StatusOutputCmd() {
	StatusOutputFile();
	time(&TimeNow);
	//距上次输出过了1秒  & 机场正在工作  => 继续
	if (((difftime(TimeNow, PreCmd)) < 1) && (AirportState != OffWork))
		return;
	PreCmd = TimeNow;	//记录时间
	//puts("--------------------------------------");
	system("CLS");
	printf("现在正在发生第%d个事件\n", ii);//
	printf("时间 : %s", ctime(&TimeNow));
	//机场状态
	switch (AirportState) {
	case 0:printf("工作状态 = 下班\n"); break;
	case 1:printf("工作状态 = 正在工作\n"); break;
	case 2:printf("工作状态 = 准备下班\n"); break;
	default: printf("机场状态异常"); exit(1);
	}
	//窗口状态
	for (int i = 0; i < NumOfWin; i++) {
		//窗口n
		printf("WIN%d  ", i+1);
		////窗口状态
		//switch (Win[i].WinState) {
		//case 0:printf("    关闭"); break;
		//case 1:printf("  空闲中"); break;
		//case 2:printf("  服务中"); break;
		//case 3:printf("  休息中"); break;
		//case 4:printf("准备休息"); break;
		//case 5:printf("准备关闭"); break;
		//default:printf("\n窗口状态异常！\n"); exit(1); break;
		//}
		////正在安检
		//if (Win[i].NowPas) {
		//	printf("\t正在安检: %3d ", Win[i].NowPas->id);
		//}
		//else {
		//	printf("\t正在安检:  无 ");
		//}
		////窗口队列
		//if (Win[i].WinHead != Win[i].WinTail) {	//判空
		//	printf(" , 队列:");
		//	Passenger* cur = Win[i].WinHead;
		//	do {
		//		cur = cur->next;
		//		printf(" %3d", cur->id);
		//	} while (cur != Win[i].WinTail);
		//}
		WinPrint(&Win[i]);
		printf("\n");
	}

	//排队缓冲区状态
	if (Queuehead->next != NULL) {
		printf("\n\t\t排队缓冲区\n总人数: %d ,首乘客: %d , 尾乘客: %d , 队列数: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id, (OdinLineWaitNum+MaxCustSingleLine-1) / MaxCustSingleLine);		//排队缓冲区队首乘客编号，队尾乘客编号
		Passenger* CurPas = Queuehead->next;
		int flag = 1;
		for (int i = 0; i<OdinLineWaitNum; i++) {
			if (flag)
				printf("%3d ", CurPas->id);
			else 
				printf("\b\b\b\b%3d\b\b\b", CurPas->id);
			if ((i + 1) % MaxCustSingleLine == 0) {
				flag = !flag;
				printf("\n");
				if (!flag) 
					for (int j = 0; j < MaxCustSingleLine; j++) 
						printf("    ");
			}//if
			CurPas = CurPas->next;
		}//for
		printf("\n");
	}//if
	else
		puts("\n排队缓冲区总人数: 0");
	//puts("--------------------------------------");
}
