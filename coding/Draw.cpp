#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<Windows.h>
#include<stdio.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

#define CProp 0.2305 //����ڶ̱�/����
#define Xlong 1300  //��Ļ��X�᳤��  ������X
#define Ylong 1000  //��Ļ��Y�᳤�� ������Y

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
void Draw() //����Ϊ---------------------------------------------ûʲô�õ��������������������Գ�ʼ������ڹ��ܣ�û�뵽��0.0��
{
	MainPara();
	OdiWin = (WinPos*)malloc(sizeof(WinPos)*NumOfWin);
	VipWin=  (WinPos*)malloc(sizeof(WinPos)*NumOfVIPWin);


	initgraph(Xlong, Ylong); //��������100
	setbkcolor(WHITE);
	cleardevice();  //���ñ���Ϊ��

	SetWin(); //�������
	
	system("pause");
	closegraph();
}
//����Ϊ---------------------------------------------ûʲô�õ��������������������Գ�ʼ������ڹ���

void SetWin() //--------------------------------------------------------------------������ڣ������꣬���Ͻ��������OdiWin[]��VipWin[]
{

	int x0 = 0;  //����������
	int y0 = 80; //��������80
	int Dy = (Ylong - 2 * y0) / (NumOfWin + NumOfVIPWin); //������ʼ����ͼ�ģ����Բ��ù�
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

	IMAGE Cimg;	// ���� IMAGE ����
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