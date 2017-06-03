#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

#define CProp 0.2305 //安检口短边/长边
#define Xlong 1300  //屏幕的X轴长短  向右是X
#define Ylong 1000  //屏幕的Y轴长短 向下是Y

extern "C" void Draw();

typedef struct WinPos
{
	int x;
	int y;
}WinPos;
WinPos *OdiWin;
WinPos *VipWin;
int CXlong;
int CYlong;

void SetWin();
void Draw() //以下为---------------------------------------------没什么用的主函数，单纯用来测试初始化安检口功能（没想到把0.0）
{
	MainPara();
	OdiWin = (WinPos*)malloc(sizeof(WinPos)*NumOfWin);
	VipWin=  (WinPos*)malloc(sizeof(WinPos)*NumOfVIPWin);


	initgraph(Xlong, Ylong); //上下留白100
	setbkcolor(WHITE);
	cleardevice();  //设置背景为白

	SetWin(); //画安检口
	
	system("pause");
	closegraph();
}
//以上为---------------------------------------------没什么用的主函数，单纯用来测试初始化安检口功能

void SetWin() //--------------------------------------------------------------------画安检口，算坐标，左上角坐标存在OdiWin[]和VipWin[]
{

	int x0 = 0;  //蛮定义以下
	int y0 = 80; //上下留白80
	int Dy = (Ylong - 2 * y0) / (NumOfWin + NumOfVIPWin); //用来初始化画图的，可以不用管
	int DDy = 0;  //用来初始化画图的,可以不用管

	if ((NumOfWin + NumOfVIPWin) <= 10)
	{
		CXlong = 300;
		CYlong = CXlong*CProp;
		DDy = (Dy - CYlong) / 2;

	}
	else
	{
		CYlong = Dy*0.8;
		CXlong = CYlong / CProp;
		DDy = (Dy-CYlong)/2;
	}

	IMAGE Cimg;	// 定义 IMAGE 对象
	loadimage(&Cimg, _T("C:\\Users\\Mr.Mango\\Desktop\\安检口.jpg"),CXlong ,CYlong);	// 读取图片到 img 对象中
	int i = 0; 
	int x = 0;
	int y = y0+DDy;

	for (i = 0; i < NumOfWin; i++)
	{
		OdiWin[i].y = y;
		OdiWin[i].x = x;
		putimage(x, y,&Cimg);
		y = y + 2 * DDy+CYlong;
	}
	for (i=0; i < NumOfVIPWin; i++)
	{
		VipWin[i].y = y;
		VipWin[i].x = x;
		putimage(x, y, &Cimg);
		y = y + 2 * DDy+CYlong;
	}

}//--------------------------------------------------------------------画安检口，算坐标，左上角坐标存在OdiWin[]和VipWin[]

//十分粗略大概不靠谱的思路模板1.0
/*
{
	While(未下班）------------------------------------------------------------总循环，
	{
		//为了防止部分事件发生太快动画来不及画，将画图事件存在一个循环队列中（不搞链表了，太累了，）
		typedef struct DrawEvent{
		 char Dtype； // 类型
		 int  mans；  //人数
		 int  WinID； //安检口ID
		 int OldorNew； // 防止部分事件间隔太长重复读取
		} DrawEvent;

		选择要画的类型（乘客进入排队缓冲区，从排队缓冲区进入安检口，从安检口安检完毕进入候机厅）------------画图，一种事件能同时让多位乘客一起动
		{
			1.(乘客从大门进入排队缓冲区)
			{
				
			}
			2.（从排队缓冲区进入安检口,同时更新排队缓冲区队伍）
			{

			}
			3.（从安检口安检完毕进入候机厅，同时更新安检口队伍）
			{

			}
			4.(安检失败，同时更新安检口队伍)
			{

			}
			5.（无要画）
			{

			}
		}

		检测鼠标事件（下班，来乘客，休息等）---------------------------------------------鼠标事件
		{
			处理相关事件---------同键盘输入
		}
	}

}



*/