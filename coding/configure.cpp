#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include "global.h"
#include "passenger.h"
#include "window.h"


#define BOX_WIDTH	200
#define BOX_HEGIHT	70

 int NumOfWin;			//1.普通安检口数目
 int NumOfVIPWin;		//2.VIP安检口数目
 int MinCheck;			//3.最少开放安检口数量
 int MaxCustCheck;		//4.安检口队伍最大长度
 int MinRestSec;		//5.安检口最小休息时长
 int MaxRestSec;		//6.安检口最大休息时长
 int MaxSec;			//7.安检口最大安检时长 单位是秒
 int MinSec;			//8.安检口最小安检时长 单位是秒
 int MaxCustSingleLine;	//9.缓冲区单队列最大乘客数
 int MaxLines;			//10.蛇形缓冲区最多由MaxLines个直队组成
 int MaxSeqLen;			//11.最大允许等待长度
 int EasySeqLen;		//12.短期等待长度

int ParaData()
{
	FILE * fp; //文件指针
	if ((fp = fopen("para.dat", "rb")) == NULL) //以只读方式打开配置文件para.dat
	{
		printf("Error! Can not open para.dat!\n");  //若无法打开，则报错
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_SET); //置文件指针于文件头部
	//从配置文件读取数据
	fread(&NumOfWin, sizeof(int), 1, fp);
	fread(&NumOfVIPWin, sizeof(int), 1, fp);
	fread(&MinCheck, sizeof(int), 1, fp);
	fread(&MaxCustCheck, sizeof(int), 1, fp);
	fread(&MaxRestSec, sizeof(int), 1, fp);
	fread(&MinRestSec, sizeof(int), 1, fp);
	fread(&MaxSec, sizeof(int), 1, fp);
	fread(&MinSec, sizeof(int), 1, fp);
	fread(&MaxCustSingleLine, sizeof(int), 1, fp);
	fread(&MaxLines, sizeof(int), 1, fp);
	fread(&MaxSeqLen, sizeof(int), 1, fp);
	fread(&EasySeqLen, sizeof(int), 1, fp);
	fclose(fp);//关闭文件指针
}


void MainPara() {


	IMAGE airport;
	char * str[20];

	int NumOfData[12];

	NumOfData[0] = NumOfWin;
	NumOfData[1] = NumOfVIPWin;
	NumOfData[2] = MinCheck;
	NumOfData[3] = MaxCustCheck;
	NumOfData[4] = MaxRestSec;
	NumOfData[5] = MinRestSec;
	NumOfData[6] = MaxSec;
	NumOfData[7] = MinSec;
	NumOfData[8] = MaxCustSingleLine;
	NumOfData[9] = MaxLines;
	NumOfData[10] = MaxSeqLen;
	NumOfData[11] = EasySeqLen;
	

	TCHAR s[12][50] = {
		"1.普通安检口数目:",
		"2.VIP安检口数目:",
		"3.最少开放安检口数量:",
		"4.安检口队伍最大长度:",
		"5.安检口最小休息时长:",
		"6.安检口最大休息时长:",
		"7.安检口最大安检时长:",
		"8.安检口最小安检时长:",
		"9.缓冲区单队列最大乘客数:",
		"10.蛇形缓冲区个直队数:",
		"11.最大允许等待长度:",
		"12.短期等待长度:",
	};

	TCHAR num[12][3] = { 0 };
	
	TCHAR temstr[3]; //待修改的字符串

	for (int i = 0; i < 12; i++) {
		itoa(NumOfData[i], num[i],10);
	}

	for (int i = 0; i < 12; i++) {
		lstrcat(s[i],num[i]);
	}

	loadimage(&airport, _T("机场.jpg"), WINDOWS_X, WINDOWS_Y);
	putimage(0, 0, &airport);
	for (int i = 0; i < 12; i++) {
		if (i < 6) {
			drawButton(200, 50+80*i, BOX_WIDTH, BOX_HEGIHT, s[i]);
		}
		else {
			drawButton(740, 50+80 * (i-6), BOX_WIDTH, BOX_HEGIHT, s[i]);
		}
	}


	FILE * fp; //文件指针
	if ((fp = fopen("para.dat", "rb+")) == NULL) //以只读方式打开配置文件para.dat
	{
		printf("Error! Can not open para.dat!\n");  //若无法打开，则报错
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_SET); //置文件指针于文件头部

	
	MOUSEMSG msg;
	while (true) {
		if (MouseHit())// 当有鼠标消息的时候执行
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (judgeButton(msg.x, msg.y, 200, 50, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					NumOfWin = _ttoi(temstr);
					fseek(fp, sizeof(int) * 0, SEEK_SET);
					fwrite(&NumOfWin, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 130, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					NumOfVIPWin = _ttoi(temstr);
					fseek(fp, sizeof(int) * 1, SEEK_SET);
					fwrite(&NumOfVIPWin, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 210, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MinCheck = _ttoi(temstr);
					fseek(fp, sizeof(int) * 2, SEEK_SET);
					fwrite(&MinCheck, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 290, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MaxCustCheck = _ttoi(temstr);
					fseek(fp, sizeof(int) * 3, SEEK_SET);
					fwrite(&MaxCustCheck, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 370, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MaxRestSec = _ttoi(temstr);
					fseek(fp, sizeof(int) * 4, SEEK_SET);
					fwrite(&MaxRestSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 450, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MinRestSec = _ttoi(temstr);
					fseek(fp, sizeof(int) * 5, SEEK_SET);
					fwrite(&MinRestSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 50, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MaxSec = _ttoi(temstr);
					fseek(fp, sizeof(int) * 6, SEEK_SET);
					fwrite(&MaxSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 130, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MinSec = _ttoi(temstr);
					fseek(fp, sizeof(int) * 7, SEEK_SET);
					fwrite(&MinSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 210, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MaxCustSingleLine = _ttoi(temstr);
					fseek(fp, sizeof(int) * 8, SEEK_SET);
					fwrite(&MaxCustSingleLine, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 290, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MaxLines = _ttoi(temstr);
					fseek(fp, sizeof(int) * 9, SEEK_SET);
					fwrite(&MaxLines, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 370, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					MaxSeqLen = _ttoi(temstr);
					fseek(fp, sizeof(int) * 10, SEEK_SET);
					fwrite(&MaxSeqLen, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 450, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "请输入要修改的值:");
					EasySeqLen = _ttoi(temstr);
					fseek(fp, sizeof(int) * 11, SEEK_SET);
					fwrite(&EasySeqLen, sizeof(int), 1, fp);
				}
			}
		}
	}
	fclose(fp);
}