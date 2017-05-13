#ifndef _Global_
#define _Global_
#include<time.h>
//����״̬
#define OffWork 0    //�°�
#define OnWork 1     //���ڹ���
#define ShutDown 2 
//����״̬
#define CloseWin 0   //���ڹر�
#define OpenWin 1    //���ڿ���
#define OnSerWin 2   //�������ڷ���
#define RestWin 3    //����������Ϣ
#define ReadyRestWin 4  //����׼����Ϣ
#define ReadyClosWin 5  //����׼���ر�

//ȫ�ֱ�������
extern int AirportState;//����״̬
extern int TotalOdinCus;//��ǰ�ܵĳ˿�����
extern int OdinWatNum;//��ǰ�˿͵ȴ�����

extern clock_t TimeStart;//��ʼʱ��
extern clock_t TimeFinish;//����ʱ�� 
extern clock_t TimeNow;	//���ڵ�ʱ��

extern int MaxCustSingleLine;//���������ȴ��˿���
extern int MaxLines;		// ���λ����������MaxLines��ֱ�����
extern int MaxSeqLen;		// �������ȴ�����
extern int EasySeqLen;		// ���ڵȴ�����

extern int NumOfWin;	//���������Ŀ
extern int WinNum;		//����ڹ�����Ŀ
extern int MinRestSec;	//����ڿ���С��Ϣʱ��
extern int MaxRestSec;	//����������Ϣʱ��
extern int MinCheck;	//���ٿ��Ű��������
extern int MaxCheck;	//��࿪�Ű��������
extern int MaxCustCheck;//����ڶ�����󳤶�
extern int MaxSec;		//�������󰲼�ʱ�� ��λ����
extern int MinSec;		//�������С����ʱ�� ��λ����
extern int PassengerArriveTask;//������ĳ˿Ͱ��Ŵ��ں���

struct entry {
	int no; //�¼����
	int sec;//�¼�����ʱ����
	char type;//�¼����ͣ�C-�˿͵��X-�����������ͣ��Q-�°ࣻ
	int mans; //�¼�����1-��������
	int check; //�¼�����2-������ͣ�İ���ڱ�� 
};

//��������
void MainInput();
void AirportOnServe();
void DistriNum(int);
void WinRun();
long SerTaskTime();
void MainPara();
void CusOutput();
void NowTime();
void RegularOutput();
void ResultOutput();

#endif
