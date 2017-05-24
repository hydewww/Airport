#ifndef _PASSENGER_H_
#define _PASSENGER_H_
typedef struct Passenger
{
	int State;//服务状态 0未分配，1已分配窗口，2已开始安检，3已离开
	int id;//乘客id
	int SerNum;//窗口
	long TaskTime;//安检时间
	char type;//乘客类型：V-VIP乘客，O-普通乘客,D-危险乘客
	struct Passenger *next;
} Passenger;

struct Passenger* Queuehead;//排队队列头指针，next指向第一位乘客
struct Passenger* Queuetail;//排队队列尾指针，始终指向最后一位乘客
#endif


