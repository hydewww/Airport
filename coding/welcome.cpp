#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include "global.h"

#define BOX_WIDTH 100	//选项盒的宽
#define BOX_HEGIHT 50	//选项盒的高
#define BBLACK 80		//空格大小



void drawButton(int x, int y,int width,int height ,char *str) {

	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 48;                      // 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, "宋体");    // 设置字体为“宋体”
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
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
	loadimage(&airport,"机场.jpg",WINDOWS_X,WINDOWS_Y);
	putimage(0,0,&airport);
	
	drawButton(1000, 300,BOX_WIDTH,BOX_HEGIHT, "开始安检 ");
	drawButton(1000, 400, BOX_WIDTH,BOX_HEGIHT,"修改配置文件");
	drawButton(1000, 500, BOX_WIDTH,BOX_HEGIHT," 退出安检 ");
}

