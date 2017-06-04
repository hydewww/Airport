#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

#define CProp 0.2305 //安检口Y边/X边
#define BProp 0.5769 //按钮Y边/X边
#define RXlong 30
#define RYlong 30
#define Xlong 1300  //屏幕的X轴长短  向右是X
#define Ylong 1000  //屏幕的Y轴长短 向下是Y

extern "C" void Draw();
int AirportState = 0;
int lock = 0;
int y0;//留白
int Dy; //

typedef struct Pos
{
	int x;
	int y;
}Pos;

typedef struct ButtonImg {
	IMAGE Onimg; //上班
	IMAGE Offimg; //下班
	IMAGE Comeimg; //来人按钮
	IMAGE ComeDownimg; //来人按钮--按下状态

	Pos On;
	Pos Off;
	Pos Come;
	Pos ComeDown;
}ButtonImg;

Pos *OdiWin;
Pos *VipWin;

int CXlong; //安检口
int CYlong;
int BXlong; //按钮
int BYlong;

IMAGE Cimg; //安检口
IMAGE Rimg; //乘客
ButtonImg Bimg; //各种按钮
IMAGE BBackimg; //按钮背景
IMAGE RBackimg; //乘客背景

void MouseOK(); //鼠标事件可以发生
void MouseEvent(); //鼠标事件
void SetWin(); //设置安检口
void SetButton(); //设置按钮
void Draw() //以下为---------------------------------------------没什么用的主函数，单纯用来测试初始化安检口功能（没想到把0.0）
{
	MainPara();
	OdiWin = (Pos*)malloc(sizeof(Pos)*NumOfWin);
	VipWin=  (Pos*)malloc(sizeof(Pos)*NumOfVIPWin);

	loadimage(&Rimg, _T("C:\\Users\\Mr.Mango\\Desktop\\乘客.jpg"), RXlong, RYlong);

	initgraph(Xlong, Ylong); //上下留白100
	setbkcolor(WHITE);
	cleardevice();  //设置背景为白

	SetWin(); //画安检口
	SetButton(); //画按钮
	MouseEvent(); //鼠标事件
	
	system("pause");
	closegraph();
}
//以上为---------------------------------------------没什么用的主函数，单纯用来测试初始化安检口功能

void SetWin() //--------------------------------------------------------------------画安检口，算坐标，左上角坐标存在OdiWin[]和VipWin[]
{

	int x0 = 0;  //蛮定义以下
	y0 = 80; //上下留白80
	Dy = (Ylong - 2 * y0) / (NumOfWin + NumOfVIPWin); //用来初始化画图的，可以不用管

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
void SetButton()
{
	BXlong = 130;
	BYlong = BXlong*BProp;
	loadimage(&Bimg.Onimg, _T("C:\\Users\\Mr.Mango\\Desktop\\上班.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Offimg, _T("C:\\Users\\Mr.Mango\\Desktop\\下班.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Comeimg, _T("C:\\Users\\Mr.Mango\\Desktop\\来人.jpg"), BXlong, BYlong);
	loadimage(&Bimg.ComeDownimg, _T("C:\\Users\\Mr.Mango\\Desktop\\来人2.jpg"), BXlong, BYlong);

	Bimg.Come.x = Xlong - 30 - BXlong;
	Bimg.Come.y = Ylong - 30 - BYlong;
	Bimg.ComeDown.x = Xlong - 30 - BXlong;
	Bimg.ComeDown.y = Ylong - 30 - BYlong;

	Bimg.On.x = Xlong - 30 - BXlong;
	Bimg.On.y= Ylong - 30*2 - BYlong*2;
	Bimg.Off.x = Xlong - 30 - BXlong;
	Bimg.Off.y = Ylong - 30 * 2 - BYlong * 2;

	getimage(&BBackimg, Bimg.On.x, Bimg.On.y, BXlong, BYlong); //取背景，为了之后的覆盖更新

	putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.Comeimg);
	putimage(Bimg.On.x, Bimg.On.y, &Bimg.Onimg);

}
void MouseEvent()
{
	int x = 0;
	int y = 0;
	int n = 0;
	MOUSEMSG m;
	while(1/*AirportState!=OffWork*/)
	{
		if (MouseHit())
		{
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (m.x >= Bimg.Off.x&&m.x <= (Bimg.Off.x + BXlong) && m.y >= Bimg.Off.y&&m.y <= (Bimg.Off.y + BYlong)) //上下班按钮
				{

					if (AirportState == OffWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //还原背景
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Offimg);
						/*
						MouseOK(); //图画界面瞬时相应，内部有延迟
						*/
						AirportState = OnWork;
					}
					else if (AirportState == OnWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //还原背景
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Onimg);
						/*
						MouseOK(); //图画界面瞬时相应，内部有延迟
						*/
						AirportState == ShutDown;
					}
				}
				else if (m.x >= Bimg.Come.x&&m.x <= (Bimg.Come.x + BXlong) && m.y >= Bimg.Come.y&&m.y <= (Bimg.Come.y + BYlong)) //来乘客按钮
				{
					putimage(Bimg.Come.x, Bimg.Come.y, &BBackimg); //还原背景
					putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.ComeDownimg);
					/*
						thisEvent.type = 'G';
						thisEvent.mans = 1;
						thisEvent.check = 0;
						thisEvent.ev_valid = 0;
					*/
					while (1)
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONUP)
						{
							putimage(Bimg.Come.x, Bimg.Come.y, &BBackimg); //还原背景
							putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.Comeimg);
							break;
						}
					}
				}
				else if (m.x >= OdiWin[0].x&&m.x <= (OdiWin[0].x + CXlong) && m.y >= OdiWin[0].y&&m.y <= (VipWin[NumOfVIPWin - 1].y + CYlong)) //安检口休息
				{
					/*
					MouseOK(); //图画界面瞬时相应，内部有延迟
					*/
					/*
					thisEvent.type = 'X';
					thisEvent.check = ;
					thisEvent.ev_valid = 0;
					*/
					n= ((m.y - y0) / Dy + 1);
					putimage(OdiWin[n - 1].x + 100, OdiWin[n - 1].y+15 , &Rimg);

					

				}
			}//if(鼠标有按下）
		}//if(鼠标有状态变化)
	}//while(AirportState!=Offwork)
}

void MouseOK()
{
	while (lock != 0)
	{
		;
	}
	lock = 1;
}
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