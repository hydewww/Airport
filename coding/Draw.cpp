#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

#define CProp 0.2305 //�����Y��/X��
#define BProp 0.5769 //��ťY��/X��
#define RXlong 30
#define RYlong 30
#define Xlong 1300  //��Ļ��X�᳤��  ������X
#define Ylong 1000  //��Ļ��Y�᳤�� ������Y

extern "C" void Draw();
int AirportState = 0;
int lock = 0;
int y0;//����
int Dy; //

typedef struct Pos
{
	int x;
	int y;
}Pos;

typedef struct ButtonImg {
	IMAGE Onimg; //�ϰ�
	IMAGE Offimg; //�°�
	IMAGE Comeimg; //���˰�ť
	IMAGE ComeDownimg; //���˰�ť--����״̬

	Pos On;
	Pos Off;
	Pos Come;
	Pos ComeDown;
}ButtonImg;

Pos *OdiWin;
Pos *VipWin;

int CXlong; //�����
int CYlong;
int BXlong; //��ť
int BYlong;

IMAGE Cimg; //�����
IMAGE Rimg; //�˿�
ButtonImg Bimg; //���ְ�ť
IMAGE BBackimg; //��ť����
IMAGE RBackimg; //�˿ͱ���

void MouseOK(); //����¼����Է���
void MouseEvent(); //����¼�
void SetWin(); //���ð����
void SetButton(); //���ð�ť
void Draw() //����Ϊ---------------------------------------------ûʲô�õ��������������������Գ�ʼ������ڹ��ܣ�û�뵽��0.0��
{
	MainPara();
	OdiWin = (Pos*)malloc(sizeof(Pos)*NumOfWin);
	VipWin=  (Pos*)malloc(sizeof(Pos)*NumOfVIPWin);

	loadimage(&Rimg, _T("C:\\Users\\Mr.Mango\\Desktop\\�˿�.jpg"), RXlong, RYlong);

	initgraph(Xlong, Ylong); //��������100
	setbkcolor(WHITE);
	cleardevice();  //���ñ���Ϊ��

	SetWin(); //�������
	SetButton(); //����ť
	MouseEvent(); //����¼�
	
	system("pause");
	closegraph();
}
//����Ϊ---------------------------------------------ûʲô�õ��������������������Գ�ʼ������ڹ���

void SetWin() //--------------------------------------------------------------------������ڣ������꣬���Ͻ��������OdiWin[]��VipWin[]
{

	int x0 = 0;  //����������
	y0 = 80; //��������80
	Dy = (Ylong - 2 * y0) / (NumOfWin + NumOfVIPWin); //������ʼ����ͼ�ģ����Բ��ù�

	int DDy = 0;  //������ʼ����ͼ��,���Բ��ù�

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

	loadimage(&Cimg, _T("C:\\Users\\Mr.Mango\\Desktop\\�����.jpg"),CXlong ,CYlong);	// ��ȡͼƬ�� img ������
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

}//--------------------------------------------------------------------������ڣ������꣬���Ͻ��������OdiWin[]��VipWin[]
void SetButton()
{
	BXlong = 130;
	BYlong = BXlong*BProp;
	loadimage(&Bimg.Onimg, _T("C:\\Users\\Mr.Mango\\Desktop\\�ϰ�.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Offimg, _T("C:\\Users\\Mr.Mango\\Desktop\\�°�.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Comeimg, _T("C:\\Users\\Mr.Mango\\Desktop\\����.jpg"), BXlong, BYlong);
	loadimage(&Bimg.ComeDownimg, _T("C:\\Users\\Mr.Mango\\Desktop\\����2.jpg"), BXlong, BYlong);

	Bimg.Come.x = Xlong - 30 - BXlong;
	Bimg.Come.y = Ylong - 30 - BYlong;
	Bimg.ComeDown.x = Xlong - 30 - BXlong;
	Bimg.ComeDown.y = Ylong - 30 - BYlong;

	Bimg.On.x = Xlong - 30 - BXlong;
	Bimg.On.y= Ylong - 30*2 - BYlong*2;
	Bimg.Off.x = Xlong - 30 - BXlong;
	Bimg.Off.y = Ylong - 30 * 2 - BYlong * 2;

	getimage(&BBackimg, Bimg.On.x, Bimg.On.y, BXlong, BYlong); //ȡ������Ϊ��֮��ĸ��Ǹ���

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
				if (m.x >= Bimg.Off.x&&m.x <= (Bimg.Off.x + BXlong) && m.y >= Bimg.Off.y&&m.y <= (Bimg.Off.y + BYlong)) //���°ఴť
				{

					if (AirportState == OffWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //��ԭ����
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Offimg);
						/*
						MouseOK(); //ͼ������˲ʱ��Ӧ���ڲ����ӳ�
						*/
						AirportState = OnWork;
					}
					else if (AirportState == OnWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //��ԭ����
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Onimg);
						/*
						MouseOK(); //ͼ������˲ʱ��Ӧ���ڲ����ӳ�
						*/
						AirportState == ShutDown;
					}
				}
				else if (m.x >= Bimg.Come.x&&m.x <= (Bimg.Come.x + BXlong) && m.y >= Bimg.Come.y&&m.y <= (Bimg.Come.y + BYlong)) //���˿Ͱ�ť
				{
					putimage(Bimg.Come.x, Bimg.Come.y, &BBackimg); //��ԭ����
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
							putimage(Bimg.Come.x, Bimg.Come.y, &BBackimg); //��ԭ����
							putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.Comeimg);
							break;
						}
					}
				}
				else if (m.x >= OdiWin[0].x&&m.x <= (OdiWin[0].x + CXlong) && m.y >= OdiWin[0].y&&m.y <= (VipWin[NumOfVIPWin - 1].y + CYlong)) //�������Ϣ
				{
					/*
					MouseOK(); //ͼ������˲ʱ��Ӧ���ڲ����ӳ�
					*/
					/*
					thisEvent.type = 'X';
					thisEvent.check = ;
					thisEvent.ev_valid = 0;
					*/
					n= ((m.y - y0) / Dy + 1);
					putimage(OdiWin[n - 1].x + 100, OdiWin[n - 1].y+15 , &Rimg);

					

				}
			}//if(����а��£�
		}//if(�����״̬�仯)
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
//ʮ�ִ��Դ�Ų����׵�˼·ģ��1.0
/*
{
	While(δ�°ࣩ------------------------------------------------------------��ѭ����
	{
		//Ϊ�˷�ֹ�����¼�����̫�춯����������������ͼ�¼�����һ��ѭ�������У����������ˣ�̫���ˣ���
		typedef struct DrawEvent{
		 char Dtype�� // ����
		 int  mans��  //����
		 int  WinID�� //�����ID
		 int OldorNew�� // ��ֹ�����¼����̫���ظ���ȡ
		} DrawEvent;

		ѡ��Ҫ�������ͣ��˿ͽ����Ŷӻ����������Ŷӻ��������밲��ڣ��Ӱ���ڰ�����Ͻ���������------------��ͼ��һ���¼���ͬʱ�ö�λ�˿�һ��
		{
			1.(�˿ʹӴ��Ž����Ŷӻ�����)
			{
				
			}
			2.�����Ŷӻ��������밲���,ͬʱ�����Ŷӻ��������飩
			{

			}
			3.���Ӱ���ڰ�����Ͻ���������ͬʱ���°���ڶ��飩
			{

			}
			4.(����ʧ�ܣ�ͬʱ���°���ڶ���)
			{

			}
			5.����Ҫ����
			{

			}
		}

		�������¼����°࣬���˿ͣ���Ϣ�ȣ�---------------------------------------------����¼�
		{
			��������¼�---------ͬ��������
		}
	}

}



*/