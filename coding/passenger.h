#ifndef _PASSENGER_H_
#define _PASSENGER_H_
typedef struct Passenger
{
	int State;//����״̬ 0δ���䣬1�ѷ��䴰�ڣ�2�ѿ�ʼ���죬3���뿪
	int id;//�˿�id
	int SerNum;//����
	long TaskTime;//����ʱ��
	char type;//�˿����ͣ�V-VIP�˿ͣ�O-��ͨ�˿�,D-Σ�ճ˿�
	struct Passenger *next;
} Passenger;

#endif


