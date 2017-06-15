#include"global.h"
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#define FlashTime 50
#define Odin 0
#define Vip  1
//#define RXlong 30
//#define RYlong 30
IMAGE  Rimg;
IMAGE VRimg;
IMAGE BACKimg;

int EventNum;

//��ͼ�е�ÿһ��С��
typedef struct Position {
	int x;
	int y;
	int Used;
}Position;
typedef Position* Map;


//----------------------------------------------------------------------------------------------�Ŷӻ�����map
extern int MaxCustSingleLine;// ���������ȴ��˿���
extern int MaxLines;// ���λ����������MaxLines��ֱ�����
#define Thickness 4	//�������߿��ϸ
Map LineMap;
void CreateLineMap() {

	LineMap = (Position*)malloc(MaxCustSingleLine * MaxLines * sizeof(Position));
	if (LineMap == NULL) {
		exit(1);
	}
	//int NowX = RXlong * 8;	//--------------------���Ͻ�X
	//int NowY = RYlong * 2;	//--------------------���Ͻ�Y

	int NowX = OdiWin[0].x +  9* RXlong+0.2*CXlong; 
	int NowY = OdiWin[0].y + 0.1*CYlong;

	int mode = 1;
	int reverse = 1;

	//���߿�
	setlinestyle(PS_SOLID, Thickness, NULL, 0);
	setcolor(BLACK);
	line(NowX+ (Thickness + RXlong), NowY, NowX + MaxLines*(Thickness + RXlong), NowY);//����
	line(NowX, NowY+MaxCustSingleLine*(Thickness+RYlong)+Thickness, NowX+MaxLines*(Thickness+RXlong+2), NowY + MaxCustSingleLine*(Thickness + RYlong) + Thickness);//����
		

	for (int i = 1; i < MaxLines; i++) {
		line(NowX + i*(Thickness + RXlong+2), NowY, NowX+ i*(Thickness + RXlong+2), NowY+ MaxCustSingleLine*(Thickness + RYlong));//�м�
	}

	NowX += Thickness/2+1;
	NowY += Thickness;
	
	for (int i = 0; i < MaxLines * MaxCustSingleLine; i++) {
		//����ֵ
		LineMap[i].x = NowX;
		LineMap[i].y = NowY;
		LineMap[i].Used = 0;

		//�ı�ģʽ
		if ((i + 1) % MaxCustSingleLine == 0) {	//����
			mode = 0;
		}
		else if (i  % MaxCustSingleLine == 0) {	//ֱ��
			mode = reverse;
			reverse = -reverse;
			setcolor(WHITE);
			line(NowX-Thickness+1, NowY-1, NowX-Thickness+1, NowY + RYlong);
		}

		//λ�ñ仯
		switch (mode) {
		case -1: NowY -= (RYlong+Thickness); break;		//����
		case 0: NowX += (RXlong+Thickness+2); break;		//����
		case 1:NowY += (RYlong+Thickness); break;		//����
		}
	}//end of for

	//�����������
	if(!mode)
		line(NowX - RXlong-Thickness, NowY-Thickness, NowX - Thickness, NowY-Thickness);
	else
		line(NowX-RXlong, NowY - RYlong, NowX - RXlong + RXlong, NowY - RYlong);
	
	//����������
	setcolor(BLACK);
	line(NowX, NowY-Thickness, NowX, NowY + MaxCustSingleLine*(Thickness + RYlong));//����

	NowX = OdiWin[0].x  + 9*RXlong + 0.2*CXlong;
	NowY = OdiWin[0].y + 0.1*CYlong;
	line(NowX-Thickness , NowY, NowX-Thickness , NowY + MaxCustSingleLine*(Thickness + RYlong)+Thickness);//����
}
//�Ŷӻ�����map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//-----------------------------------------------------------------------------------------------�����map
extern int NumOfWin;	//�������
extern int NumOfVIPWin;	//vip�������
extern int CXlong;		//����ڿ��
extern int MaxCustCheck;//��������˿�
extern int DDy;
extern int Xlong;
extern int Ylong;

#define MinStep 10//------------------��Ҫ�޸�

Map* CheckMap;	//�����map����
int* last;		//��������һ������ 

//��ͨ�����map
void CreateSingleCheckMap(int no) {
	CheckMap[no] = (Position*)malloc((MinStep + no) * sizeof(Position));
	if (CheckMap[no] == NULL) {
		exit(1);
	}
	int NowX = OdiWin[no].x + 0.2*CXlong;//-------------------------
	int NowY = OdiWin[no].y + 0.1*CYlong;//-----------------------

	int i = 0;

	//setcolor(BLACK);
	//rectangle(NowX+RXlong, NowY + RYlong, NowX + RXlong + RXlong, NowY + RYlong + RYlong);

	//����
	for (int j = 0; j < MaxCustCheck + 2; i++, j++) {
		NowX += RXlong;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	//putimage(NowX,NowY, &Rimg);

	//����
	for (int j = 0; j < (1 + no); i++, j++) {
		//NowY -= RYlong;
		NowY -= (CYlong + 2 * DDy);
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	//putimage(NowX, NowY, &Rimg);

	//����
	for (int j = 0; j < 2; i++, j++) {
		NowX += RXlong;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	//putimage(NowX, NowY, &Rimg);

	//����
	//for (int j = 0; j < 0; i++, j++) {
	//	//NowY += RXlong;
	//	NowY += (CYlong + 2 * DDy);
	//	CheckMap[no][i].x = NowX;
	//	CheckMap[no][i].y = NowY;
	//	CheckMap[no][i].Used = 0;
	//}
	//putimage(NowX, NowY, &Rimg);

	last[no] = i - 1;
}

//vip�����map
void CreateSingleVipMap(int no) {
	no = no + NumOfWin;

	CheckMap[no] = (Position*)malloc((MaxCustCheck + 1) * sizeof(Position));
	//int NowX = -(RXlong);//-------------------------
	//int NowY = RYlong * 2 + no*RYlong;//-----------------------
	int NowX = VipWin[0].x + 0.2*CXlong;
	int NowY = VipWin[0].y + 0.1*CYlong;
	int i;
	for (i = 0; i < (MaxCustCheck + 1); i++) {
		NowX += RXlong;
		CheckMap[no][i].x = NowX;
		CheckMap[no][i].y = NowY;
		CheckMap[no][i].Used = 0;
	}
	last[no] = i - 1;
}

void CreateCheckMap() {
	CheckMap = (Map*)malloc((NumOfWin + NumOfVIPWin) * sizeof(Map));
	last = (int*)malloc((NumOfWin + NumOfVIPWin) * sizeof(int));
	//������ͨ�����map
	for (int i = 0; i < NumOfWin; i++) {
		CreateSingleCheckMap(i);
	}
	//����vip�����map
	for (int i = 0; i < NumOfVIPWin; i++) {
		CreateSingleVipMap(i);
	}
}

//�����map^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------GoGOGO
//�ƶ���
void MoveRun(Position* New, Position* Old, int IsVip) {
	//setcolor(WHITE);
	//fillrectangle(Old->x, Old->y, Old->x + RXlong, Old->y + RYlong);	//�ñ���ɫ���
	IMAGE MoveImg;
	getimage(&MoveImg, Old->x, Old->y, RXlong, RYlong);
	putimage(Old->x, Old->y, &BACKimg);
	putimage(New->x, New->y, &MoveImg);
	Old->Used = 0;
	New->Used = 1;
}

//׼���ƶ���
void Move(Map map,int NumOfPos,int IsVip) {
	//int NumOfPos = MaxCustSingleLine;
	int go=0; //���ܲ����ƶ�

	for (int i = 0; i < NumOfPos; i++) {
		if (map[i].Used) {	
			if (go) {	
				MoveRun(&map[i - 1], &map[i],IsVip);	//��������ܶ� ����������!��
			}
			else {
				go = 0;//������˲��ܶ� ���Ѿ� ȥ�¸������
			}
		}
		else {
			go = 1;	//����û�� �칥������
		}
	}
}
//GoGoGo^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//--------------------------------------------------------------------------------------------------------��ͼ״̬ת��
//����������
int EnLine() {
	int NumOfPos = MaxCustSingleLine*MaxLines;
	int last = NumOfPos - 1 ;	//����Ǹ���
	
	//�жϻ᲻���ص�
	if (LineMap[last].Used)
		return 0;

	putimage(LineMap[last].x, LineMap[last].y, &Rimg);
	LineMap[last].Used = 1;
	return 1;
}


int EnVip(int no);
//ȥ���������
int EnCheck(int no) {
	//��ͨ�˿�
	if (no < NumOfWin) {
		if (LineMap[0].Used) {			//��ͷ����
			MoveRun(&CheckMap[no][last[no]], &LineMap[0],Odin);	//����
			LineMap[0].Used = 0;
			CheckMap[no][last[no]].Used = 1;
			return 1;
		}
		return 0;
	}
	//Vip�˿� û�л����� ֱ�ӽ������ ������̫һ��
	else {
		EnVip(no);
	}
}

//Vip�˿� û�л����� ֱ�ӽ������ ������̫һ��
int EnVip(int no) {
	int last = MaxCustCheck;	//����Ǹ���

	//�жϻ᲻���ص�
	if (CheckMap[no][last].Used)
		return 0;

	putimage(CheckMap[no][last].x, CheckMap[no][last].y, &VRimg);
	CheckMap[no][last].Used = 1;
	return 1;
}

//��������������
int DeCheck(int no) {
	if (CheckMap[no][0].Used) {
		setcolor(WHITE);
		//fillellipse(CheckMap[no][0].x, CheckMap[no][0].y, CheckMap[no][0].x + RXlong, CheckMap[no][0].y + RYlong);	//����ɫ���
		putimage(CheckMap[no][0].x, CheckMap[no][0].y,  &BACKimg);
		CheckMap[no][0].Used = 0;
		return 1;
	}
	return 0;
}

//����ʱ���ӳ�
int BeginOK(int i) //��λ�������ʱ��
{
	if (CheckMap[i][1].Used == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//��ͼ״̬ת��^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//------------------------------------------------------------------------------------------------------����
struct Cache  EnCheckCache, DeCheckCache;
int EnLineCache;//������cache

void ResetCheckCache() {
	EnCheckCache.head %= CacheNum;
	EnCheckCache.tail %= CacheNum;
	DeCheckCache.head %= CacheNum;
	DeCheckCache.tail %= CacheNum;
}

void PreEnLine() {
	if(EnLineCache)
		if (EnLine())	//�ɹ����뻺����
			EnLineCache--;		
}

void PreEnCheck() {
	if (EnCheckCache.head != EnCheckCache.tail) {
		if (EnCheck(EnCheckCache.no[EnCheckCache.head]))	//�ɹ����밲���
			EnCheckCache.head++;		//����-1
	}
	ResetCheckCache();
}

void PreDeCheck() {
	if (DeCheckCache.head != DeCheckCache.tail) {
		if (DeCheck(DeCheckCache.no[DeCheckCache.head]))
			DeCheckCache.head++;
	}
	ResetCheckCache();
}
//����^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


void InitDraw() {
	initgraph(Xlong, Ylong);
	//loadimage(&Rimg, _T("�˿�.jpg"), RXlong, RYlong);
	//loadimage(&VRimg, _T("�˿�new.jpg"), RXlong, RYlong);
	setbkcolor(WHITE);
	cleardevice();
	//�����ͼƬ��ʼ��
	SetWin();
	//�����״̬��ʼ��
	InitState();
	//������ʼ��
	SetButton();
	loadimage(&Rimg, _T("�˿�.jpg"), RXlong, RYlong);
	loadimage(&VRimg, _T("�˿�new.jpg"), RXlong, RYlong);
	loadimage(&BACKimg, _T("����.jpg"), RXlong, RYlong);
	//��ͼ��ʼ��
	CreateLineMap();
	CreateCheckMap();

	//Cache��ʼ��
	EnLineCache = 0;
	EnCheckCache.head = EnCheckCache.tail = 0;
	DeCheckCache.head = DeCheckCache.tail = 0;

}

clock_t PreMoveTime;
clock_t NowMoveTime;
//�������ɣ�

void toy() {
	NowMoveTime = clock();
	//����˳���ܱ䣡���� ����ѧ�İ��أ�����
	if ((NowMoveTime - PreMoveTime) > FlashTime) {
		PreMoveTime = NowMoveTime;	//����ʱ��

		PreDeCheck();	//�������
		UpdateState();//����״̬����
		for (int i = 0; i < NumOfWin; i++) {
			Move(CheckMap[i], (MinStep + i),Odin);//��ͨ����ڶ�
		}
		for (int i = 0; i < NumOfVIPWin; i++) {
			Move(CheckMap[i+NumOfWin], (MaxCustCheck + 1) ,Vip);//vip����ڶ�
		}
		PreEnCheck();	//�������
		Move(LineMap, MaxCustSingleLine*MaxLines,Odin);//��������
		PreEnLine();	//��������
	}
}