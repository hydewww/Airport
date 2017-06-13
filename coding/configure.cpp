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

 int NumOfWin;			//1.��ͨ�������Ŀ
 int NumOfVIPWin;		//2.VIP�������Ŀ
 int MinCheck;			//3.���ٿ��Ű��������
 int MaxCustCheck;		//4.����ڶ�����󳤶�
 int MinRestSec;		//5.�������С��Ϣʱ��
 int MaxRestSec;		//6.����������Ϣʱ��
 int MaxSec;			//7.�������󰲼�ʱ�� ��λ����
 int MinSec;			//8.�������С����ʱ�� ��λ����
 int MaxCustSingleLine;	//9.���������������˿���
 int MaxLines;			//10.���λ����������MaxLines��ֱ�����
 int MaxSeqLen;			//11.�������ȴ�����
 int EasySeqLen;		//12.���ڵȴ�����

int ParaData()
{
	FILE * fp; //�ļ�ָ��
	if ((fp = fopen("para.dat", "rb")) == NULL) //��ֻ����ʽ�������ļ�para.dat
	{
		printf("Error! Can not open para.dat!\n");  //���޷��򿪣��򱨴�
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_SET); //���ļ�ָ�����ļ�ͷ��
	//�������ļ���ȡ����
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
	fclose(fp);//�ر��ļ�ָ��
}

void PrintPara(int *NumOfData,TCHAR num[][3],TCHAR *tems) {
	
	IMAGE airport;

	TCHAR s[12][50] = {
		"1.��ͨ�������Ŀ:",
		"2.VIP�������Ŀ:",
		"3.���ٿ��Ű��������:",
		"4.����ڶ�����󳤶�:",
		"5.�������С��Ϣʱ��:",
		"6.����������Ϣʱ��:",
		"7.�������󰲼�ʱ��:",
		"8.�������С����ʱ��:",
		"9.���������������˿���:",
		"10.���λ�������ֱ����:",
		"11.�������ȴ�����:",
		"12.���ڵȴ�����:",
	};

	loadimage(&airport, _T("����.jpg"), WINDOWS_X, WINDOWS_Y);
	putimage(0, 0, &airport);
	for (int i = 0; i < 12; i++) {
		if (i < 6) {
			itoa(NumOfData[i], num[i], 10);
			lstrcpy(tems, s[i]);
			lstrcat(tems, num[i]);
			drawButton(200, 50 + 80 * i, BOX_WIDTH, BOX_HEGIHT, tems);
		}
		else {
			itoa(NumOfData[i], num[i], 10);
			lstrcpy(tems, s[i]);
			lstrcat(tems, num[i]);
			drawButton(740, 50 + 80 * (i - 6), BOX_WIDTH, BOX_HEGIHT, tems);
		}
	}
	drawButton(1200,500 ,100 ,50 , "����");
	drawButton(1350, 500, 100, 50, "��ʼ����");
}

void MainPara() {

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
	

	TCHAR num[12][3] = { 0 };
	
	TCHAR temstr[3]; //���޸ĵ��ַ���
	TCHAR tems[30];

	PrintPara(NumOfData,num,tems);

	FILE * fp; //�ļ�ָ��
	if ((fp = fopen("para.dat", "rb+")) == NULL) //��ֻ����ʽ�������ļ�para.dat
	{
		printf("Error! Can not open para.dat!\n");  //���޷��򿪣��򱨴�
		exit(EXIT_FAILURE);
	}
	fseek(fp, 0, SEEK_SET); //���ļ�ָ�����ļ�ͷ��

	
	MOUSEMSG msg;
	while (true) {
		if (MouseHit())// ���������Ϣ��ʱ��ִ��
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (judgeButton(msg.x, msg.y, 200, 50, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					NumOfWin = _ttoi(temstr);
					NumOfData[0] = NumOfWin;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 0, SEEK_SET);
					fwrite(&NumOfWin, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 130, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					NumOfVIPWin = _ttoi(temstr);
					NumOfData[1] = NumOfVIPWin;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 1, SEEK_SET);
					fwrite(&NumOfVIPWin, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 210, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MinCheck = _ttoi(temstr);
					NumOfData[2] = MinCheck;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 2, SEEK_SET);
					fwrite(&MinCheck, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 290, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MaxCustCheck = _ttoi(temstr);
					NumOfData[3] = MaxCustCheck;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 3, SEEK_SET);
					fwrite(&MaxCustCheck, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 370, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MaxRestSec = _ttoi(temstr);
					NumOfData[4] = MaxRestSec;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 4, SEEK_SET);
					fwrite(&MaxRestSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 200, 450, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MinRestSec = _ttoi(temstr);
					NumOfData[5] = MinRestSec;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 5, SEEK_SET);
					fwrite(&MinRestSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 740, 50, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MaxSec = _ttoi(temstr);
					NumOfData[6] = MaxSec;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 6, SEEK_SET);
					fwrite(&MaxSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 740, 130, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MinSec = _ttoi(temstr);
					NumOfData[7] = MinSec;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 7, SEEK_SET);
					fwrite(&MinSec, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 740, 210, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MaxCustSingleLine = _ttoi(temstr);
					NumOfData[8] = MaxCustSingleLine;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 8, SEEK_SET);
					fwrite(&MaxCustSingleLine, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 740, 290, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MaxLines = _ttoi(temstr);
					NumOfData[9] = MaxLines;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 9, SEEK_SET);
					fwrite(&MaxLines, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 740, 370, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					MaxSeqLen = _ttoi(temstr);
					NumOfData[10] = MaxSeqLen;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 10, SEEK_SET);
					fwrite(&MaxSeqLen, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 740, 450, BOX_WIDTH, BOX_HEGIHT)) {
					InputBox(temstr, 3, "������Ҫ�޸ĵ�ֵ:");
					EasySeqLen = _ttoi(temstr);
					NumOfData[11] = EasySeqLen;
					PrintPara(NumOfData, num, tems);
					fseek(fp, sizeof(int) * 11, SEEK_SET);
					fwrite(&EasySeqLen, sizeof(int), 1, fp);
				}
				if (judgeButton(msg.x, msg.y, 1200, 500, 100, 50)) {
					closegraph();
					InitInter();
					InitInterCheck();
				}
				if (judgeButton(msg.x, msg.y, 1350, 500, 100, 50)) {
					TCHAR s[10];
					InputBox(s, 10, _T("�������¼�����"));
					EventNum = _ttoi(s);
					closegraph();
					BeginServe();
				}
			}
		}
	}
	fclose(fp);
}