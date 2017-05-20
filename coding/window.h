#ifndef _Window_
#define _Window_
typedef struct Window
{
	int WinState;/*工作状态：CloseWin窗口关闭  OpenWin空闲  OnSerWin正在服务
				 RestWin休息中  ReadyRestWin等待休息  ReadyClosWin等待关闭*/
	int SerNum;//服务的号码 		
	long SerTime;//本次服务结束时间		
	/*
	
	*/
	long RestTime;//本次休息结束时间
	long TotalSer;//总共服务人数
	long TotalTime;//总共服务时间
	int  WaitNum;//记录当前安检口排队乘客数量
	Passenger *NowPas;//指向被安检乘客指针
	Passenger *WinHead;//窗口队列头指针
	Passenger *WinTail;//窗口队列尾指针
}Window;//窗口结构

extern Window *Win;//安检口数组
#endif