#ifndef _Passenger_
#define _passenger_
typedef struct Passenger
{
	int State;//服务状态 0未分配，1已分配窗口，2已开始安检，3已离开
	int SerNum;//窗口
	long TaskTime;//安检时间
	int id;
	Passenger *next;
} Passenger;

#endif


