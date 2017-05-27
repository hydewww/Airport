#ifndef _QUEUE_H_
#define _QUEUE_H_
#include"passenger.h"
typedef struct Queue {
	Passenger* QueueHead; 
	Passenger* QueueTail;
	int WaitNum;//当前等待人数
	int SumNum;//总共等待人数
}Queue;

#endif 
