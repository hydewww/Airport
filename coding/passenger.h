#ifndef _Passenger_
#define _passenger_
typedef struct Passenger
{
	int State;//����״̬ 0δ���䣬1�ѷ��䴰�ڣ�2�ѿ�ʼ���죬3���뿪
	int id;//�˿�id
	int SerNum;//����
	long TaskTime;//����ʱ��
	 Passenger *next;
} Passenger;

Passenger* Queuehead;//�ŶӶ���ͷָ�룬nextָ���һλ�˿�
Passenger* Queuetail;//�ŶӶ���βָ�룬ʼ��ָ�����һλ�˿�

#endif


