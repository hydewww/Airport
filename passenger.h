#ifndef _Passenger_
#define _passenger_
typedef struct Passenger
{
	int State;//服务状态 0未分配，1已分配窗口，2已开始安检，3已离开
	int SerNum;//窗口
	long TaskTime;//安检时间
} Passenger;
Passenger Pas[1000];//乘客数组
#define MaxPass 1000  //定义最大乘客数量
#endif


