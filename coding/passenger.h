#ifndef _PASSENGER_H_
#define _PASSENGER_H_
typedef struct Passenger
{
	int State;//����״̬ 0δ���䣬1�ѷ��䴰�ڣ�2�ѿ�ʼ���죬3���뿪
	int id;//�˿�id
	int SerNum;//����
	long TaskTime;//����ʱ��
	char type;//�˿����ͣ�V-VIP�˿ͣ�O-��ͨ�˿�
	struct Passenger *next;
} Passenger;

struct Passenger* Queuehead;//�ŶӶ���ͷָ�룬nextָ���һλ�˿�
struct Passenger* Queuetail;//�ŶӶ���βָ�룬ʼ��ָ�����һλ�˿�
#endif


