#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"passenger.h"
typedef struct Queue {
	Passenger* QueueHead; 
	Passenger* QueueTail;
	int WaitNum;//��ǰ�ȴ�����
	int SumNum;//�ܹ��ȴ�����
}Queue;

#endif 
