#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<process.h>
#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

#define CProp 1 //安检口Y边/X边
#define BProp 0.5769 //按钮Y边/X边
#define SProp 0.5643 //状态窗口Y边/X边
//#define Xlong 1300  //屏幕的X轴长短  向右是X
//#define Ylong 1000  //屏幕的Y轴长短 向下是Y
//int lock = 0;
int y00=100;//留白
int Dy; //
int DDy;
int RXlong;
int RYlong;
int Xlong=1500;
int Ylong=800;
int StateXlong;
int StateYlong;


typedef struct ButtonImg {
	IMAGE Onimg; //上班
	IMAGE Offimg; //下班
	IMAGE Comeimg; //来人按钮
	IMAGE ComeDownimg; //来人按钮--按下状态
	IMAGE VIPComeimg;
	IMAGE VIPComeDownimg;
	IMAGE DanComeimg;//危险乘客到来
	IMAGE DanComeDownimg;//危险乘客到来按下

	Pos On;
	Pos Off;
	Pos Come;
	Pos ComeDown;
	Pos VIPCome;
	Pos DanCome;
}ButtonImg;

Pos *OdiWin;
Pos *VipWin;

int CXlong; //安检口
int CYlong;
int BXlong; //按钮
int BYlong;

IMAGE Cimg; //安检口
//IMAGE Rimg; //乘客
ButtonImg Bimg; //各种按钮
IMAGE BBackimg; //按钮背景
IMAGE RBackimg; //乘客背景

typedef struct Stateimg
{
	IMAGE Sclose;
	IMAGE Spreclose;
	IMAGE Sopen;
	IMAGE Sonserve;
	IMAGE Srest;
	IMAGE Sprerest;
};

Stateimg Simg;
void MouseOK(); //鼠标事件可以发生
void SetWin(); //设置安检口
void SetButton(); //设置按钮
/*
void Draw() //以下为---------------------------------------------没什么用的主函数，单纯用来测试初始化安检口功能（没想到把0.0）
{
	MainPara();
	OdiWin = (Pos*)malloc(sizeof(Pos)*NumOfWin);
	VipWin=  (Pos*)malloc(sizeof(Pos)*NumOfVIPWin);

	loadimage(&Rimg, _T("乘客.jpg"), RXlong, RYlong);

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
*/
void SetWin() //--------------------------------------------------------------------画安检口，算坐标，左上角坐标存在OdiWin[]和VipWin[]
{
	OdiWin = (Pos*)malloc(sizeof(Pos)*NumOfWin);
	VipWin = (Pos*)malloc(sizeof(Pos)*NumOfVIPWin);
	int x0 = 0;  //蛮定义以下
	y00 = 100; //上下留白80
	Dy = (Ylong - 2 * y00) / (NumOfWin + NumOfVIPWin); //用来初始化画图的，可以不用管


	if ((NumOfWin + NumOfVIPWin) <= 10)
	{
		CXlong = 62;
		CYlong = CXlong*CProp;
		DDy = (Dy - CYlong) / 2;

	}
	else
	{
		CYlong = Dy*0.8;
		CXlong = CYlong / CProp;
		DDy = (Dy-CYlong)/2;
	}

	loadimage(&Cimg, _T("安检口.jpg"),CXlong ,CYlong);	// 读取图片到 img 对象中
	int i = 0; 
	int x = CYlong/SProp;
	int y = y00+DDy;

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
	RYlong = CYlong*0.8; //根据安检口大小设置乘客大小
	RXlong = RYlong;

}//--------------------------------------------------------------------画安检口，算坐标，左上角坐标存在OdiWin[]和VipWin[]

void SetButton()
{
	BXlong = 120;
	BYlong = BXlong*BProp;
	loadimage(&Bimg.Onimg, _T("上班.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Offimg, _T("下班.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Comeimg, _T("来人.jpg"), BXlong, BYlong);
	loadimage(&Bimg.ComeDownimg, _T("来人2.jpg"), BXlong, BYlong);
	loadimage(&Bimg.VIPComeimg, _T("来VIP.jpg"), BXlong, BYlong);
	loadimage(&Bimg.VIPComeDownimg, _T("来VIP2.jpg"), BXlong, BYlong);
	loadimage(&Bimg.DanComeimg, _T("来危险乘客.jpg"), BXlong, BYlong);
	loadimage(&Bimg.DanComeDownimg, _T("来危险乘客2.jpg"), BXlong, BYlong);

	Bimg.Come.x = Xlong - 30 - BXlong;
	Bimg.Come.y = Ylong - 30 - BYlong;
	Bimg.ComeDown.x = Xlong - 30 - BXlong;
	Bimg.ComeDown.y = Ylong - 30 - BYlong;

	Bimg.VIPCome.x= Xlong - 30 - BXlong;
	Bimg.VIPCome.y = Bimg.Come.y - 10 - BYlong;

	Bimg.DanCome.x= Xlong - 30 - BXlong;
	Bimg.DanCome.y = Bimg.VIPCome.y - 10 - BYlong;

	Bimg.On.x = Xlong - 30 - BXlong;
	Bimg.On.y = Bimg.DanCome.y - 10 - BYlong;
	Bimg.Off.x = Xlong - 30 - BXlong;
	Bimg.Off.y = Bimg.DanCome.y - 10 - BYlong;

	getimage(&BBackimg, Bimg.On.x, Bimg.On.y, BXlong, BYlong); //取背景，为了之后的覆盖更新

	putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.Comeimg);
	putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Offimg);
	putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &Bimg.VIPComeimg);
	putimage(Bimg.DanCome.x, Bimg.DanCome.y, &Bimg.DanComeimg);

}


unsigned _stdcall MouseEvent(void *p)
{
	int x = 0;
	int y = 0;
	int n = 0;
	MOUSEMSG m;
	while(AirportState != OffWork&&AirportState != ShutDown)
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
						
						MouseOK(); //图画界面瞬时相应，内部有延迟
						
						thisEvent.type = 'Q';
						thisEvent.ev_valid = 0;
						_endthreadex(0);
						return 0;
					}
					else if (AirportState == OnWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //还原背景
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Onimg);
						
						MouseOK(); //图画界面瞬时相应，内部有延迟
						
						thisEvent.type = 'Q';
						thisEvent.ev_valid = 0;
						_endthreadex(0);
						return 0;
					}
				}
				else if (m.x >= Bimg.Come.x&&m.x <= (Bimg.Come.x + BXlong) && m.y >= Bimg.Come.y&&m.y <= (Bimg.Come.y + BYlong)) //来乘客按钮
				{
					putimage(Bimg.Come.x, Bimg.Come.y, &BBackimg); //还原背景
					putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.ComeDownimg);	
					
					MouseOK();

					//发生事件
					thisEvent.type = 'G';
					thisEvent.mans = 1;
					thisEvent.check = 0;
					thisEvent.ev_valid = 0;
					
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
					
					MouseOK(); //图画界面瞬时相应，内部有延迟
					n = ((m.y - y00) / Dy + 1);
					
					thisEvent.type = 'X';
					thisEvent.check = n; //算出休息的安检口
					thisEvent.ev_valid = 0;
					
					//putimage(OdiWin[n - 1].x + 100, OdiWin[n - 1].y+15 , &Bimg.Comeimg);	
				}
				else if (m.x >= Bimg.VIPCome.x&&m.x <= (Bimg.VIPCome.x + BXlong) && m.y >= Bimg.VIPCome.y&&m.y <= (Bimg.VIPCome.y + BYlong))//来VIP
				{
					putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &BBackimg); //还原背景
					putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &Bimg.VIPComeDownimg);

					MouseOK();

					//发生事件
					thisEvent.type = 'V';
					thisEvent.mans = 1;
					thisEvent.check = 0;
					thisEvent.ev_valid = 0;

					while (1)
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONUP)
						{
							putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &BBackimg); //还原背景
							putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &Bimg.VIPComeimg);
							break;
						}
					}
				}
				else if (m.x >= Bimg.DanCome.x&&m.x <= (Bimg.DanCome.x + BXlong) && m.y >= Bimg.DanCome.y&&m.y <= (Bimg.DanCome.y + BYlong)) //来危险乘客
				{
					putimage(Bimg.DanCome.x, Bimg.DanCome.y, &BBackimg); //还原背景
					putimage(Bimg.DanCome.x, Bimg.DanCome.y, &Bimg.DanComeDownimg);

					MouseOK();

					//发生事件
					thisEvent.type = 'G';
					thisEvent.mans = 1;
					thisEvent.check = 4;
					thisEvent.ev_valid = 0;

					while (1)
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONUP)
						{
							putimage(Bimg.DanCome.x, Bimg.DanCome.y, &BBackimg); //还原背景
							putimage(Bimg.DanCome.x, Bimg.DanCome.y, &Bimg.DanComeimg);
							break;
						}
					}
				}
			}//if(鼠标有按下）
		}//if(鼠标有状态变化)
	}//while(AirportState!=Offwork)
	_endthreadex(0);
	return 0;
}

void InitState()
{
	StateYlong = CYlong;
	StateXlong = StateYlong / SProp;
	loadimage(&Simg.Sclose, _T("关闭.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Spreclose, _T("准备关闭.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Sopen, _T("空闲.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Sonserve, _T("服务中.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Srest, _T("休息中.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Sprerest, _T("准备休息.jpg"), StateXlong, StateYlong);

	for (int i = 0; i < NumOfWin; i++)
	{
		putimage(0, OdiWin[i].y,&Simg.Sclose);
	}
	for (int i = 0; i < NumOfVIPWin; i++)
	{
		putimage(0, VipWin[i].y, &Simg.Sclose);
	}
	
}

void UpdateState()
{
	int i = 0;
	for (i = 0; i < NumOfWin; i++)
	{
		switch (Win[i].WinState)
		{
		case CloseWin:
			putimage(0, OdiWin[i].y, &Simg.Sclose);
			break;
		case ReadyClosWin:
			putimage(0, OdiWin[i].y, &Simg.Spreclose);
			break;
		case OpenWin:
			putimage(0, OdiWin[i].y, &Simg.Sopen);
			break;
		case OnSerWin:
			putimage(0, OdiWin[i].y, &Simg.Sonserve);
			break;
		case RestWin:
			putimage(0, OdiWin[i].y, &Simg.Srest);
			break;
		case ReadyRestWin:
			putimage(0, OdiWin[i].y, &Simg.Sprerest);
			break;
		}
	}
	for (i = 0; i < NumOfVIPWin; i++)
	{
		switch (VIPWin[i].WinState)
		{
		case CloseWin:
			putimage(0, VipWin[i].y, &Simg.Sclose);
			break;
		case ReadyClosWin:
			putimage(0, VipWin[i].y, &Simg.Spreclose);
			break;
		case OpenWin:
			putimage(0, VipWin[i].y, &Simg.Sopen);
			break;
		case OnSerWin:
			putimage(0, VipWin[i].y, &Simg.Sonserve);
			break;
		}
	}
}

void ShowID(int id,int x,int y)
{
	TCHAR ID[5];
	//settextcolor(BLACK);
	//outtextxy(40, 40, ID);
	int i = 0;
	int ii = 0;
	char temp;
	for (i = 0; id > 0; id /= 10, i++)
	{
		ID[i] = (id % 10) + '0';
	}
	ID[i] = '\0';
	i--;
	for (ii = 0; i>ii; i--, ii++)
	{
		temp = ID[ii];
		ID[ii] = ID[i];
		ID[i] = temp;
	}
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	outtextxy(x + 0.3*RXlong, y + 0.3*RYlong, ID);

}



void MouseOK()
{
	while (lock != 0)
	{
		;
	}
	lock = 1;
}
