#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<process.h>
#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

#define CProp 1 //�����Y��/X��
#define BProp 0.5769 //��ťY��/X��
#define SProp 0.5643 //״̬����Y��/X��
//#define Xlong 1300  //��Ļ��X�᳤��  ������X
//#define Ylong 1000  //��Ļ��Y�᳤�� ������Y
//int lock = 0;
int y00=100;//����
int Dy; //
int DDy;
int RXlong;
int RYlong;
int Xlong=1500;
int Ylong=800;
int StateXlong;
int StateYlong;


typedef struct ButtonImg {
	IMAGE Onimg; //�ϰ�
	IMAGE Offimg; //�°�
	IMAGE Comeimg; //���˰�ť
	IMAGE ComeDownimg; //���˰�ť--����״̬
	IMAGE VIPComeimg;
	IMAGE VIPComeDownimg;
	IMAGE DanComeimg;//Σ�ճ˿͵���
	IMAGE DanComeDownimg;//Σ�ճ˿͵�������

	Pos On;
	Pos Off;
	Pos Come;
	Pos ComeDown;
	Pos VIPCome;
	Pos DanCome;
}ButtonImg;

Pos *OdiWin;
Pos *VipWin;

int CXlong; //�����
int CYlong;
int BXlong; //��ť
int BYlong;

IMAGE Cimg; //�����
//IMAGE Rimg; //�˿�
ButtonImg Bimg; //���ְ�ť
IMAGE BBackimg; //��ť����
IMAGE RBackimg; //�˿ͱ���

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
void MouseOK(); //����¼����Է���
void SetWin(); //���ð����
void SetButton(); //���ð�ť
/*
void Draw() //����Ϊ---------------------------------------------ûʲô�õ��������������������Գ�ʼ������ڹ��ܣ�û�뵽��0.0��
{
	MainPara();
	OdiWin = (Pos*)malloc(sizeof(Pos)*NumOfWin);
	VipWin=  (Pos*)malloc(sizeof(Pos)*NumOfVIPWin);

	loadimage(&Rimg, _T("�˿�.jpg"), RXlong, RYlong);

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
*/
void SetWin() //--------------------------------------------------------------------������ڣ������꣬���Ͻ��������OdiWin[]��VipWin[]
{
	OdiWin = (Pos*)malloc(sizeof(Pos)*NumOfWin);
	VipWin = (Pos*)malloc(sizeof(Pos)*NumOfVIPWin);
	int x0 = 0;  //����������
	y00 = 100; //��������80
	Dy = (Ylong - 2 * y00) / (NumOfWin + NumOfVIPWin); //������ʼ����ͼ�ģ����Բ��ù�


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

	loadimage(&Cimg, _T("�����.jpg"),CXlong ,CYlong);	// ��ȡͼƬ�� img ������
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
	RYlong = CYlong*0.8; //���ݰ���ڴ�С���ó˿ʹ�С
	RXlong = RYlong;

}//--------------------------------------------------------------------������ڣ������꣬���Ͻ��������OdiWin[]��VipWin[]

void SetButton()
{
	BXlong = 120;
	BYlong = BXlong*BProp;
	loadimage(&Bimg.Onimg, _T("�ϰ�.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Offimg, _T("�°�.jpg"), BXlong, BYlong);
	loadimage(&Bimg.Comeimg, _T("����.jpg"), BXlong, BYlong);
	loadimage(&Bimg.ComeDownimg, _T("����2.jpg"), BXlong, BYlong);
	loadimage(&Bimg.VIPComeimg, _T("��VIP.jpg"), BXlong, BYlong);
	loadimage(&Bimg.VIPComeDownimg, _T("��VIP2.jpg"), BXlong, BYlong);
	loadimage(&Bimg.DanComeimg, _T("��Σ�ճ˿�.jpg"), BXlong, BYlong);
	loadimage(&Bimg.DanComeDownimg, _T("��Σ�ճ˿�2.jpg"), BXlong, BYlong);

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

	getimage(&BBackimg, Bimg.On.x, Bimg.On.y, BXlong, BYlong); //ȡ������Ϊ��֮��ĸ��Ǹ���

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
				if (m.x >= Bimg.Off.x&&m.x <= (Bimg.Off.x + BXlong) && m.y >= Bimg.Off.y&&m.y <= (Bimg.Off.y + BYlong)) //���°ఴť
				{

					if (AirportState == OffWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //��ԭ����
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Offimg);
						
						MouseOK(); //ͼ������˲ʱ��Ӧ���ڲ����ӳ�
						
						thisEvent.type = 'Q';
						thisEvent.ev_valid = 0;
						_endthreadex(0);
						return 0;
					}
					else if (AirportState == OnWork)
					{
						putimage(Bimg.Off.x, Bimg.Off.y, &BBackimg); //��ԭ����
						putimage(Bimg.Off.x, Bimg.Off.y, &Bimg.Onimg);
						
						MouseOK(); //ͼ������˲ʱ��Ӧ���ڲ����ӳ�
						
						thisEvent.type = 'Q';
						thisEvent.ev_valid = 0;
						_endthreadex(0);
						return 0;
					}
				}
				else if (m.x >= Bimg.Come.x&&m.x <= (Bimg.Come.x + BXlong) && m.y >= Bimg.Come.y&&m.y <= (Bimg.Come.y + BYlong)) //���˿Ͱ�ť
				{
					putimage(Bimg.Come.x, Bimg.Come.y, &BBackimg); //��ԭ����
					putimage(Bimg.Come.x, Bimg.Come.y, &Bimg.ComeDownimg);	
					
					MouseOK();

					//�����¼�
					thisEvent.type = 'G';
					thisEvent.mans = 1;
					thisEvent.check = 0;
					thisEvent.ev_valid = 0;
					
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
					
					MouseOK(); //ͼ������˲ʱ��Ӧ���ڲ����ӳ�
					n = ((m.y - y00) / Dy + 1);
					
					thisEvent.type = 'X';
					thisEvent.check = n; //�����Ϣ�İ����
					thisEvent.ev_valid = 0;
					
					//putimage(OdiWin[n - 1].x + 100, OdiWin[n - 1].y+15 , &Bimg.Comeimg);	
				}
				else if (m.x >= Bimg.VIPCome.x&&m.x <= (Bimg.VIPCome.x + BXlong) && m.y >= Bimg.VIPCome.y&&m.y <= (Bimg.VIPCome.y + BYlong))//��VIP
				{
					putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &BBackimg); //��ԭ����
					putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &Bimg.VIPComeDownimg);

					MouseOK();

					//�����¼�
					thisEvent.type = 'V';
					thisEvent.mans = 1;
					thisEvent.check = 0;
					thisEvent.ev_valid = 0;

					while (1)
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONUP)
						{
							putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &BBackimg); //��ԭ����
							putimage(Bimg.VIPCome.x, Bimg.VIPCome.y, &Bimg.VIPComeimg);
							break;
						}
					}
				}
				else if (m.x >= Bimg.DanCome.x&&m.x <= (Bimg.DanCome.x + BXlong) && m.y >= Bimg.DanCome.y&&m.y <= (Bimg.DanCome.y + BYlong)) //��Σ�ճ˿�
				{
					putimage(Bimg.DanCome.x, Bimg.DanCome.y, &BBackimg); //��ԭ����
					putimage(Bimg.DanCome.x, Bimg.DanCome.y, &Bimg.DanComeDownimg);

					MouseOK();

					//�����¼�
					thisEvent.type = 'G';
					thisEvent.mans = 1;
					thisEvent.check = 4;
					thisEvent.ev_valid = 0;

					while (1)
					{
						m = GetMouseMsg();
						if (m.uMsg == WM_LBUTTONUP)
						{
							putimage(Bimg.DanCome.x, Bimg.DanCome.y, &BBackimg); //��ԭ����
							putimage(Bimg.DanCome.x, Bimg.DanCome.y, &Bimg.DanComeimg);
							break;
						}
					}
				}
			}//if(����а��£�
		}//if(�����״̬�仯)
	}//while(AirportState!=Offwork)
	_endthreadex(0);
	return 0;
}

void InitState()
{
	StateYlong = CYlong;
	StateXlong = StateYlong / SProp;
	loadimage(&Simg.Sclose, _T("�ر�.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Spreclose, _T("׼���ر�.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Sopen, _T("����.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Sonserve, _T("������.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Srest, _T("��Ϣ��.jpg"), StateXlong, StateYlong);
	loadimage(&Simg.Sprerest, _T("׼����Ϣ.jpg"), StateXlong, StateYlong);

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
