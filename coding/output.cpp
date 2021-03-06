#include "global.h"
#include "passenger.h"
#include "window.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <process.h>


void StatusOutputCmd();
void StatusOutputFile();
void StatusOutput() {
	StatusOutputCmd();
	StatusOutputFile();
}


void FinalOutputCmd();
void FinalOutputFile();
void FinalOutputGraph();
void FinalOutput() {
	FinalOutputGraph();
	FinalOutputFile();
}


/*StatusOutputCmd调用函数*/
void QueuePrint();//仿图形界面蛇形缓冲区
void WinPrint(Window win);//窗口状态
/*over*/

//cmd状态输出 1s
//time_t PreCmd; //记录上次输出时间---------------------------------------
clock_t PreCmd=0; //修改用clock()函数
clock_t NowCmd=0;
void StatusOutputCmd() {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*time(&TimeNow);
	//距上次输出过了1秒  & 机场正在工作  => 继续
	if (((difftime(TimeNow, PreCmd)) < 2) && (AirportState != OffWork))
		//return;
	PreCmd = TimeNow;	//记录时间*/

	NowCmd=clock(); //修改用clock函数，
	if (((NowCmd - PreCmd) / CLOCKS_PER_SEC) < 1.5 && (AirportState != OffWork))
		return;
	PreCmd = NowCmd;


	system("CLS");
	//printf("当前事件：%d", thisEvent.no);/* test */
	printf("\n时间 : %s", ctime(&TimeNow));
	//机场状态
	printf("机场状态 = ");
	switch (AirportState) {
	case 0:    SetConsoleTextAttribute(hOut, FOREGROUND_RED); printf("下班\n");   
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;	
	case 1:  SetConsoleTextAttribute(hOut, FOREGROUND_GREEN); printf("正在工作\n"); 
		SetConsoleTextAttribute(hOut,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case 2: SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN); printf("准备下班\n");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	default: printf("机场状态异常"); exit(EXIT_FAILURE);
	}
	puts("");
	//窗口状态
	for (int i = 0; i < NumOfWin; i++) {
		//窗口n
		printf("WIN%02d  ", i+1);
		//窗口状态
		WinPrint(Win[i]);
	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//窗口n
		printf("VIP%02d  ", i + 1);
		//窗口状态
		WinPrint(VIPWin[i]);
	}

	//排队缓冲区状态
	if (OdinQueue->QueueHead->next != NULL) 
		QueuePrint(); //仿图形界面蛇形缓冲区
	else
		puts("\n排队缓冲区无人");
}

//cmd下班输出
void FinalOutputCmd() {
	system("cls");
	printf("下班啦！！！！！！！！！！！！！！！！！！！！\n\n");
	printf("上班时间：%s", ctime(&TimeStart));
	printf("下班时间: %s", ctime(&TimeFinish));
	printf("今日服务总人数: %d  总共营业时间: %02d:%02d\n\n\n", OdinQueue->SumNum+VipQueue->SumNum, (TimeFinish - TimeStart) / 60, (TimeFinish - TimeStart) % 60);
	for (int i = 0; i < NumOfWin; i++) {
		//窗口n
		printf("WIN%02d  ", i + 1);
		//窗口状态
		printf("总共服务人数: %3d  总共服务时间: %02d:%02d\n", Win[i].TotalSer, Win[i].TotalTime/60,Win[i].TotalTime%60);
	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//窗口n
		printf("VIP%02d  ", i + 1);
		//窗口状态
		printf("总共服务人数: %3d  总共服务时间: %02d:%02d\n", VIPWin[i].TotalSer, VIPWin[i].TotalTime/60,VIPWin[i].TotalTime%60);
	}
}

void FinalOutputGraph() {
	

	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 28;                      // 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, "宋体");    // 设置字体为“宋体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式


	char tems[150];
	char temNum[6];

	outtextxy(WINDOWS_X/2-50,40,"下班啦!!!!!!!!");

	char OriginalStr[][100] = { 
		"Start Time : ",
		"Finish Time : ",
		"Number of Passengers Served today : ",
		"Total Run Time : ",
		"WIN",
		"VIP",

	};

	strcpy(tems,OriginalStr[0]);
	strcat(tems, ctime(&TimeStart));
	outtextxy(40, 150, tems);

	strcpy(tems, OriginalStr[1]);
	strcat(tems, ctime(&TimeFinish));
	outtextxy(40, 200, tems);

	strcpy(tems, OriginalStr[2]);
	strcat(tems, itoa(OdinQueue->SumNum + VipQueue->SumNum,temNum,10));
	outtextxy(40, 350, tems);

	strcpy(tems, OriginalStr[3]);
	strcat(tems, itoa(TimeFinish - TimeStart, temNum, 10));
	outtextxy(40, 450, tems);

	for (int i = 0; i < NumOfWin; i++) {
		//窗口n
		strcpy(tems,OriginalStr[4]);
		strcat(tems, itoa(i,temNum,10));
		strcat(tems, "Serve Number : ");
		strcat(tems, itoa(Win[i].TotalSer, temNum, 10));
		strcat(tems, "Serve Time : ");
		sprintf(temNum, "%d", Win[i].TotalTime);
		strcat(tems,temNum);

		outtextxy(650, 150+35*i, tems);
		//窗口状态

	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//窗口n
		strcpy(tems, OriginalStr[5]);
		strcat(tems, itoa(i, temNum, 10));
		strcat(tems, "Serve Number : ");
		strcat(tems, itoa(VIPWin[i].TotalSer, temNum, 10));
		strcat(tems, "Serve Time : ");
		strcat(tems, itoa(VIPWin[i].TotalTime, temNum, 10));

		outtextxy(650, 550, tems);
		//窗口状态
	}
}


//file事件输出
void EventOutputFile(char event, int PasID, int WinID) {	//PasID乘客 WinID安检口
															//StatusOutputFile();
	FILE * fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(EXIT_FAILURE);
	}
	switch (event) {
	case 'G':fprintf(fp, "%d号乘客进入排队缓冲区\n", PasID); printf("%d号乘客进入排队缓冲区\n", PasID); break;
	case 'F':fprintf(fp, "排队缓冲区已满\n"); printf( "排队缓冲区已满\n"); break;
	case 'C':fprintf(fp, "%d号乘客进入%d号安检口\n", PasID, WinID); printf("%d号乘客进入%d号安检口\n", PasID, WinID); break;
	case 'c':fprintf(fp, "%d号Vip进入%d号Vip安检口\n", PasID, WinID); printf("%d号Vip进入%d号Vip安检口\n", PasID, WinID); break;
	case 'L':fprintf(fp, "%d号乘客完成安检离开\n", PasID); printf("%d号乘客完成安检离开\n", PasID); break;
	case 'B':fprintf(fp, "[Warning] %d号乘客安检失败!\n", PasID);printf("[Warning] %d号乘客安检失败!\n", PasID); break;
	case 'O':fprintf(fp, "%d号安检口开启\n", WinID); printf("%d号安检口开启\n", WinID); break;
	case 'S':fprintf(fp, "%d号安检口关闭\n", WinID);printf("%d号安检口关闭\n", WinID); break;
	case 'X':fprintf(fp, "%d号安检口申请休息\n", WinID);printf("%d号安检口申请休息\n", WinID); break;
	case 'K':fprintf(fp, "%d号安检口开始休息\n", WinID);printf("%d号安检口开始休息\n", WinID); break;
	case 'J':fprintf(fp, "%d号安检口结束休息\n", WinID);printf("%d号安检口结束休息\n", WinID); break;
	case 'Q':fprintf(fp, "接收到下班指令\n"); printf("接收到下班指令\n"); break;
	default:fprintf(fp, "接收到未知事件\n");printf("接收到未知事件\n"); break;
	}
	fflush(fp);
	fclose(fp);
}

//file下班输出  类似cmd
void FinalOutputFile() {
	FILE* fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "-------------------------------------------------------\n");

	fprintf(fp,"下班啦！！！！！！！！！！！！！！！！！！！！\n\n");
	fprintf(fp,"上班时间：%s", ctime(&TimeStart));
	fprintf(fp,"下班时间: %s", ctime(&TimeFinish));
	fprintf(fp,"今日服务总人数: %d  总共营业时间: %02d:%02d\n\n\n", OdinQueue->SumNum + VipQueue->SumNum, (TimeFinish - TimeStart) / 60, (TimeFinish - TimeStart) % 60);
	for (int i = 0; i < NumOfWin; i++) {
		//窗口n
		fprintf(fp,"WIN%02d  ", i + 1);
		//窗口状态
		fprintf(fp,"总共服务人数: %3d  总共服务时间: %02d:%02d\n", Win[i].TotalSer, Win[i].TotalTime / 60, Win[i].TotalTime % 60);
	}
	for (int i = 0; i < NumOfVIPWin; i++) {
		//窗口n
		fprintf(fp,"VIP%02d  ", i + 1);
		//窗口状态
		fprintf(fp,"总共服务人数: %3d  总共服务时间: %02d:%02d\n", VIPWin[i].TotalSer, VIPWin[i].TotalTime / 60, VIPWin[i].TotalTime % 60);
	}
	
	fprintf(fp, "-------------------------------------------------------\n");
	fflush(fp);
	fclose(fp);
}

//file状态输出 3s 类似cmd
time_t PreFile;
void StatusOutputFile() {
	time(&TimeNow);
	if (difftime(TimeNow, PreFile)<3)
		return;
	PreFile = TimeNow;
	FILE* fp;
	if (!(fp = fopen("output.txt", "a"))) {
		puts("Error: cannot open the file \"output.txt\".");
		exit(EXIT_FAILURE);
	}
	fprintf(fp, "-------------------------------------------------------\n");
	fprintf(fp, "时间 : %s", ctime(&TimeNow));
	//机场状态
	switch (AirportState) {
	case 0:fprintf(fp, "机场状态 = 下班\n"); break;
	case 1:fprintf(fp, "机场状态 = 正在工作\n"); break;
	case 2:fprintf(fp, "机场状态 = 准备下班\n"); break;
	default: fprintf(fp, "机场状态异常"); exit(EXIT_FAILURE);
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
		default:fprintf(fp, "\n窗口状态异常！\n"); exit(EXIT_FAILURE); break;
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

	for (int i = 0; i < NumOfVIPWin; i++) {
		//窗口n
		fprintf(fp, "VIP%02d  ", i + 1);
		//窗口状态
		switch (VIPWin[i].WinState) {
		case 0:fprintf(fp, "    关闭"); break;
		case 1:fprintf(fp, "  空闲中"); break;
		case 2:fprintf(fp, "  服务中"); break;
		case 3:fprintf(fp, "  休息中"); break;
		case 4:fprintf(fp, "准备休息"); break;
		case 5:fprintf(fp, "准备关闭"); break;
		default:fprintf(fp, "\n窗口状态异常！\n"); exit(EXIT_FAILURE); break;
		}
		//正在安检
		if (VIPWin[i].NowPas) {
			fprintf(fp, "\t正在安检: %3d ", VIPWin[i].NowPas->id);
		}
		else {
			fprintf(fp, "\t正在安检:  无 ");
		}
		//窗口队列
		if (VIPWin[i].WinHead != VIPWin[i].WinTail) {	//判空
			fprintf(fp, " , 队列:");
			Passenger* cur = VIPWin[i].WinHead;
			do {
				cur = cur->next;
				fprintf(fp, " %3d", cur->id);
			} while (cur != VIPWin[i].WinTail);
		}
		fprintf(fp, "\n");
	}

	//排队缓冲区状态
	if (OdinQueue->QueueHead->next != NULL) {
		fprintf(fp, "排队缓冲区总人数: %d ,首乘客: %d , 尾乘客: %d , 队列数: %d\n", OdinQueue->WaitNum, OdinQueue->QueueHead->next->id, OdinQueue->QueueTail->id, (OdinQueue->WaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine);		//排队缓冲区队首乘客编号，队尾乘客编号
	}//if
	else
		fprintf(fp, "排队缓冲区总人数: 0\n");

	fprintf(fp, "-------------------------------------------------------\n");
	fflush(fp);
	fclose(fp);
}

/*StatusOutputCmd调用函数*/
  //仿图形界面蛇形缓冲区
void QueuePrint() {	
	int line = (OdinQueue->WaitNum + MaxCustSingleLine - 1) / MaxCustSingleLine;// 行数
	printf("\n\t\t排队缓冲区\n总人数: %d ,首乘客: %d , 尾乘客: %d , 队列数: %d\n", OdinQueue->WaitNum, OdinQueue->QueueHead->next->id, OdinQueue->QueueTail->id, line);		//排队缓冲区队首乘客编号，队尾乘客编号
	
	Passenger* CurPas = OdinQueue->QueueHead->next;

	//第一行
	printf("|");
	for (int i = 0; i < MaxCustSingleLine; i++) {
		printf("----");
	}
	printf("|\n "); //换行后的空格是缓冲区的开头
	/*第一行over*/

	int flag = 1;	//记录当前行是顺序还是逆序 1=正 0=倒
	//打印前line-1行
	for (int i = 0; i<line - 1; i++) {
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
			for (int j = 0; j < MaxCustSingleLine - 1; j++)
				printf("----");
			printf("|\n");
			//\n |xxx  xxx  xxx  xxx      |
			printf("<");
		}
		flag = !flag;
	}//打印前line-1行over

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

	puts("");
}
  //窗口状态
void WinPrint(Window win) {
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//状态
	switch (win.WinState) {
	case 0:SetConsoleTextAttribute(hOut, FOREGROUND_RED); printf("    关闭");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case 1:SetConsoleTextAttribute(hOut, FOREGROUND_GREEN); printf("  空闲中");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case 2:SetConsoleTextAttribute(hOut, FOREGROUND_GREEN); printf("  服务中");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case 3:SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN); printf("  休息中");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case 4:SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN); printf("准备休息");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	case 5:SetConsoleTextAttribute(hOut, FOREGROUND_RED); printf("准备关闭");
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
	default:printf("\n窗口状态异常！\n"); exit(EXIT_FAILURE); break;
	}
	//正在安检乘客
	if (win.NowPas) {
		printf("\t正在安检: %3d ", win.NowPas->id);
	}
	else {
		printf("\t正在安检:  无 ");
	}
	//窗口队列
	if (win.WinHead != win.WinTail) {	//判空
		printf(" , 队列:");
		Passenger* cur = win.WinHead;
		do {
			cur = cur->next;
			printf(" %3d", cur->id);
		} while (cur != win.WinTail);
	}
	puts("");
}

void InitInterface() //欢迎界面
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
			printf("欢迎来到DKY48机场！");
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
	while (getchar() != '\n')
		;
	system("CLS");

}