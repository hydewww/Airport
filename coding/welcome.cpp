#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include "global.h"

#define BOX_WIDTH 100	//ѡ��еĿ�
#define BOX_HEGIHT 50	//ѡ��еĸ�
#define BBLACK 80		//�ո��С



void drawButton(int x, int y,int width,int height ,char *str) {

	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 48;                      // ��������߶�Ϊ 48
	_tcscpy_s(f.lfFaceName, "����");    // ��������Ϊ�����塱
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);                     // ����������ʽ
	setbkmode(TRANSPARENT);
	RECT r1 = { x, y,x + width,y + height };
	rectangle(x, y, x + width, y + height);
	settextstyle(13, 0, _T(""));
	settextcolor(WHITE);
	drawtext(str, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}	

void InitInter() {

	IMAGE airport;

	initgraph(WINDOWS_X, WINDOWS_Y);
	loadimage(&airport,"����.jpg",WINDOWS_X,WINDOWS_Y);
	putimage(0,0,&airport);
	
	drawButton(1000, 300,BOX_WIDTH,BOX_HEGIHT, "��ʼ���� ");
	drawButton(1000, 400, BOX_WIDTH,BOX_HEGIHT,"�޸������ļ�");
	drawButton(1000, 500, BOX_WIDTH,BOX_HEGIHT," �˳����� ");
}

