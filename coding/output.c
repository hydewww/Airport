#include"global.h"
#include"passenger.h"
#include"window.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>

//窗口状态
void WinPrint(Window* win) {
	//状态
	switch (win->WinState) {
	case 0:printf("    关闭"); break;
	case 1:printf("  空闲中"); break;
	case 2:printf("  服务中"); break;
	case 3:printf("  休息中"); break;
	case 4:printf("准备休息"); break;
	case 5:printf("准备关闭"); break;
	default:printf("\n窗口状态异常！\n"); exit(1); break;
	}
	//正在安检乘客
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
	fflush(fp);
	fclose(fp);
}

time_t PreCmd; //记录上次输出时间
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
	//printf("当前事件：%d", thisEvent.no);/* test */
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
		printf("WIN%02d  ", i+1);
		//窗口状态
		WinPrint(&Win[i]);
		printf("\n");
	}

	//排队缓冲区状态
	if (Queuehead->next != NULL) {
		int line = (OdinLineWaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine;// 行数
		printf("\n\t\t排队缓冲区\n总人数: %d ,首乘客: %d , 尾乘客: %d , 队列数: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id, line);		//排队缓冲区队首乘客编号，队尾乘客编号
		Passenger* CurPas = Queuehead->next;
		//第一行
		printf("|");
		for (int i = 0; i < MaxCustSingleLine; i++) {
			printf("----");
		}
		printf("|\n "); //换行后的空格是缓冲区的开头
		/*第一行over*/

		int flag = 1;	//1=正 0=倒
		for (int i = 0; i<line-1; i++) {
			//输出乘客队列
			if (flag)
				for (int j = 0; j < MaxCustSingleLine; j++) {
					printf("%3d ", CurPas->id);
					CurPas = CurPas->next;
				}
			else 
				for (int j = 0; j < MaxCustSingleLine; j++) {
					printf("\b\b\b\b%3d\b\b\b", CurPas->id);	//倒着输出
					CurPas = CurPas->next;
				}
			//输出围栏
			if (flag) {//上行是正
				printf("|\n");
				//|---------    |
				printf("|");
				for (int j = 0; j < MaxCustSingleLine - 1; j++)
					printf("----");
				printf("    |\n");

				// \n |   .xxx.xxx.xxx.xxx|
				printf("|");//first
				for (int j = 0; j < MaxCustSingleLine; j++)
					printf("    ");
				printf(">\b");//last
			
			}
			else {//上行是倒
				printf("\n");
				//|    ---------|
				printf("|    ");
				for (int j = 0; j < MaxCustSingleLine -1; j++)
					printf("----");
				printf("|\n");

				//\n |xxx  xxx  xxx  xxx      |
				printf("<");
			}
			flag = !flag;
		}//for
		
		//倒数第二
		if (!flag) {//上行是正
			// xxx xxx xxx
			while (CurPas != NULL) {
				printf("\b\b\b\b%3d\b\b\b", CurPas->id);	//倒着输出
				CurPas = CurPas->next;
			}
			printf("\n");
		}
		else {//上行是倒
			  //\n |xxx  xxx  xxx  xxx      |
			for (int j = 0; j < MaxCustSingleLine; j++) {
				if (CurPas != NULL) {
					printf("%3d ", CurPas->id);
					CurPas = CurPas->next;
				}
				else
					printf("    ");
			}
			printf("|\n");
		}
		/*倒数第二行over*/

		//最后一行
		printf("|");
		for (int i = 0; i < MaxCustSingleLine; i++) {
			printf("----");
		}
		printf("|\n "); //换行后的空格是缓冲区的开头
		/*最后一行over*/

		printf("\n");
	}//if
	else
		puts("\n排队缓冲区无人");
	//puts("--------------------------------------");
}

//每3秒当前状态写入txt
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
	fprintf(fp, "-------------------------------------------------------\n");
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
		fprintf(fp, "WIN%02d  ", i + 1);
		//窗口状态
		switch (Win[i].WinState) {
		case 0:fprintf(fp, "    关闭"); break;
		case 1:fprintf(fp, "  空闲中"); break;
		case 2:fprintf(fp, "  服务中"); break;
		case 3:fprintf(fp, "  休息中"); break;
		case 4:fprintf(fp, "准备休息"); break;
		case 5:fprintf(fp, "准备关闭"); break;
		default:fprintf(fp, "\n窗口状态异常！\n"); exit(1); break;
		}
		//正在安检
		if (Win[i].NowPas) {
			fprintf(fp, "\t正在安检: %3d ", Win[i].NowPas->id);
		}
		else {
			fprintf(fp, "\t正在安检:  无 ");
		}
		//窗口队列
		if (Win[i].WinHead != Win[i].WinTail) {	//判空
			fprintf(fp, " , 队列:");
			Passenger* cur = Win[i].WinHead;
			do {
				cur = cur->next;
				fprintf(fp, " %3d", cur->id);
			} while (cur != Win[i].WinTail);
		}
		fprintf(fp, "\n");
	}

	//排队缓冲区状态
	if (Queuehead->next != NULL){
		fprintf(fp, "\n\t\t排队缓冲区\n总人数: %d ,首乘客: %d , 尾乘客: %d , 队列数: %d\n", OdinLineWaitNum, Queuehead->next->id, Queuetail->id, (OdinLineWaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine);		//排队缓冲区队首乘客编号，队尾乘客编号
		//Passenger* CurPas = Queuehead->next;
		//int flag = 1;
		//for (int i = 0; i<OdinLineWaitNum; i++) {
		//	if (flag)
		//		fprintf(fp,"%3d ", CurPas->id);
		//	else
		//		fprintf(fp,"\b\b\b\b%3d\b\b\b", CurPas->id);
		//	if ((i + 1) % MaxCustSingleLine == 0) {
		//		flag = !flag;
		//		fprintf(fp,"\n");
		//		if (!flag)
		//			for (int j = 0; j < MaxCustSingleLine; j++)
		//				fprintf(fp,"    ");
		//	}//if
		//	CurPas = CurPas->next;
		//}//for
		fprintf(fp,"\n");
	}//if
	else
		fprintf(fp, "\n排队缓冲区总人数: 0\n");

	fprintf(fp, "-------------------------------------------------------\n");
	fflush(fp);
	fclose(fp);
}