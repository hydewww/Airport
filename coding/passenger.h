#ifndef _Passenger_
#define _passenger_
typedef struct Passenger
{
	int State;//����״̬ 0δ���䣬1�ѷ��䴰�ڣ�2�ѿ�ʼ���죬3���뿪
	int SerNum;//����
	long TaskTime;//����ʱ��
	int id;
	Passenger *next;
} Passenger;

#endif


