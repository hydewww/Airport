#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

int TotalOdinCus = 0; //当前总乘客数量

Passenger* Queuehead;//排队队列头指针，next指向第一位乘客
Passenger* Queuetail;//排队队列尾指针，始终指向最后一位乘客
time_t TimeNow;//当前时间


void QueueEstablish()//创建队列头指针函数
{
	if ((Queuehead = (Passenger*)malloc(sizeof(Passenger))) == NULL)
	{
		printf("申请内存失败!\n");
	}
	Queuehead->next = NULL;//开始无乘客
	Queuetail = Queuehead;//尾指针和头指针同指

}

void DistriNum(entry event)//为乘客分配号码并插入排队缓冲区
{
	int number=0;//本次到达乘客数量计数器
	Passenger* p;//乘客指针
	for(number = 0; (number < event.mans)&&(AirportState!=OffWork);number++)
	{
		TotalOdinCus++;//乘客数量加一
		OdinWatNum++;//当前等待乘客数加一
		if ((p = (Passenger*)malloc(sizeof(Passenger))) == NULL)
		{
			printf("申请内存失败！");
		}
		else
		{
			p->State = 0;//尚未分配安检口
			p->id = TotalOdinCus;//分配id
			p->SerNum = 0;//0为未安检口
			p->TaskTime = MinSec + rand() % (MaxSec + 1);//设置安检的时间
			p->next = NULL;
			Queuetail->next = p;//将乘客插入排队缓冲区的队尾
			Queuetail = p;//队尾指针指向尾乘客
			p = p->next;
		}	
	}
}

void PreWinRun() //将排队缓冲区的乘客插入到安检口
{
	int NowWinNum = 0;//窗口数组编号
	int MinWaitNum = MaxCustCheck;//最少安检口排队乘客数量
	int MinWaitWinNum = 0;//最少乘客排队的安检口数组编号
	for (; ; MinWaitWinNum = 0, MinWaitNum = MaxCustCheck) //存在可以插入乘客的安检口队列
	{
		for (NowWinNum = 0; NowWinNum < NumOfWin; NowWinNum++) //数组编号小于安检口总数则执行循环
		{
			if ((MinWaitNum > Win[NowWinNum].WaitNum) && (Win[NowWinNum].WinState == OpenWin || Win[NowWinNum].WinState == OnSerWin || Win[NowWinNum].WinState == ReadyClosWin)) //记录目前排队最少且处于正常工作的安检口
			{
				MinWaitNum = Win[NowWinNum].WaitNum; //记录当前最少排队人数
				MinWaitWinNum = NowWinNum; //改变当前最少安检口编号
			}
		}
		if (MinWaitWinNum < MaxCustCheck) //存在排队未满的安检口
		{
			Win[MinWaitWinNum].WinTail->next = Queuehead->next;//将排队缓冲区队头插入该安检口的队尾
			Win[MinWaitWinNum].WinTail = Queuehead->next;//将安检口队尾改为其下一个
			Queuehead->next = Queuehead->next->next;//改变排队缓冲区的队头为其下一个
			Win[MinWaitWinNum].WinTail->next = NULL;//将安检口队尾的下一个置为空
			Win[MinWaitWinNum].WaitNum++;//此安检口排队乘客量加一
		}
		else //安检口队列已满
		{
			break;
		}
	}
}

void WinRun(entry event) //安检口处理乘客及安检口状态转换
{
	int i = 0;//安检口数组编号
	int n = 0;//此次状态处理循环中已增设安检口数量
	int NowState;//安检口当前状态
	if (event.type == 'X') //有安检口申请休息
	{
		Win[event.check - 1].WinState = ReadyRestWin;//改变窗口状态为申请休息
	}
	else if (event.type == 'Q')//发生下班事件
	{
		for (i = 0; i <= NumOfWin; i++) //更改所有安检口状态位准备关闭
		{
			Win[i].WinState = ReadyClosWin;
		}
	}
	for (i = 0; i < NumOfWin; i++)//遍历安检口数组，进行乘客处理及安检口状态转换
	{
		NowState = Win[i].WinState;//获取安检口状态
		switch (NowState)
		{
			case CloseWin: //安检口处于关闭状态
				if (((OdinWatNum +1-MaxCustCheck*n) / WinNum) >= MaxSeqLen)//排队缓冲区乘客过多需要开开放新的安检口
				{
					Win[i].WinState = OpenWin;//安检口状态设置为空闲
					WinNum++;//当前安检口数量增加
				}
				break;
			case OpenWin: //安检口处于空闲状态
				if (Win[i].WinHead->next != NULL)//有人在此安检口排队
				{
					Win[i].WinState = OnSerWin;//改变安检口状态为正在服务
					Win[i].NowPas = Win[i].WinHead->next; //为队头乘客安检
					Win[i].WinHead->next = Win[i].WinHead->next->next;//改变队头乘客为其的下一个
					Win[i].SerNum = Win[i].NowPas->id;//为其设置服务号码为乘客ID
					time(&TimeNow);//获取当前时间
					Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//设置此次安检结束时间
					Win[i].TotalSer++;//服务的乘客量增加
					Win[i].TotalTime += Win[i].NowPas->TaskTime;//服务的总时间增加
				}
				else//无人排队
				{
					;
				}
				break;
			case OnSerWin: //安检口处于正在安检状态
				time(&TimeNow);//获取当前时间
				if (TimeNow >= Win[i].SerTime)//安检完成
				{
					Win[i].WinState = OpenWin;//状态转换为空闲
					Win[i].NowPas = NULL;//设置被安检乘客指针为空

				}
				else //安检未结束
				{
					;
				}
				break;
			case RestWin: //安检口处于正在休息状态
				time(&TimeNow);
				if (TimeNow >= Win[i].RestTime)//休息结束
				{
					Win[i].WinState = OpenWin;//状态改变为空闲

				}
				else//休息未结束
				{
					;
				}
				break;
			case ReadyRestWin: //安检口处于申请休息状态
				if ((Win[i].NowPas == NULL) && (Win[i].WinHead == NULL))//安检口无人排队且空闲
				{
					time(&TimeNow);//获取当前时间
					Win[i].WinState = RestWin;//改变安检口状态为正在休息
					Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//为安检口设置休息结束时间
				}
				else//不能休息
				{
					;
				}
				break;
			case ReadyClosWin: //安检口处于准备关闭状态
				if (((Win[i].NowPas == NULL) && (Win[i].WinHead == NULL)) && ((OdinWatNum + 1 - MaxCustCheck*n) / WinNum) <= EasySeqLen)//满足关闭条件(安检口空闲且炮队缓冲区人少)
				{
					Win[i].WinState = CloseWin;//改变安检口状态为关闭

				}
				else //不能关闭
				{
					;
				}
				break;
			default:
				break;
		}//Switch
	}//for
}

int StateTrans(entry event) // 总控制函数
{
	switch (event.type)
	{
		case 'c':			//乘客到达事件



	}
}