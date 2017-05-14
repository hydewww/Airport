#ifndef _Passenger_
#define _passenger_
typedef struct Passenger
{
	int State;//服务状态 0未分配，1已分配窗口，2已开始安检，3已离开
	int id;//乘客id
	int SerNum;//窗口
	long TaskTime;//安检时间
	 Passenger *next;
} Passenger;

Passenger* Queuehead;//排队队列头指针，next指向第一位乘客
Passenger* Queuetail;//排队队列尾指针，始终指向最后一位乘客

#endif


