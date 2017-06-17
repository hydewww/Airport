#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "passenger.h"
#include "window.h" 
#include "queue.h"

#define VIP 1
#define ODIN 0
int PreClose = 0;//记录准备关闭安检口的数目
int OdinWatNum;

//进入缓冲区
void EnQueue(Queue* queue) {
	Passenger* p;
	if (!(p = (Passenger*)malloc(sizeof(Passenger)))) {
		puts("乘客进入缓冲区失败");
		exit(EXIT_FAILURE);
	}
	queue->SumNum++;
	queue->WaitNum++;

	p->State = thisEvent.check;//尚未分配安检口
	p->id = queue->SumNum;//分配id

	p->SerNum = 0;//0为未安检口
	p->TaskTime = MinSec + rand() % (MaxSec + 1);//设置安检的时间
	p->next = NULL;
	queue->QueueTail->next = p;//将乘客插入排队缓冲区的队尾
	queue->QueueTail = p;//队尾指针指向尾乘客

}
void DistriNum(entry *event)//为乘客分配号码并插入排队缓冲区
{
	int number = 0;//本次到达乘客数量计数器
	Passenger* p = NULL;//乘客指针

	if (event->type == 'G') {
		for (number = 0; number < event->mans; number++)
		{
			if (OdinQueue->WaitNum >= MaxCustSingleLine*MaxLines) //排队缓冲区已满
			{
				EventOutputFile('F', 0, 0);//事件输出
				break;
			}
			OdinWatNum++;//---------------
			EnQueue(OdinQueue);//-----------------入队
			//EnLineCache++;//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^进缓冲区Cahce
			if (event->check == 4)
				EnCache(&EnLineCache, 1);
			else if (event->check == 0)
				EnCache(&EnLineCache, 0);
				
			EventOutputFile('G', OdinQueue->SumNum, 0);//事件输出
		}
	}
	else if (event->type == 'V') {
		for (number = 0; number < event->mans; number++)
		{
			EnQueue(VipQueue);//-------------
			//----------不输出事件 装作没有缓冲区（手动滑稽
		}
	}
}
/*进入缓冲区*/

//缓冲区进安检口
int PreWinOK();

void PreWinRun(int IsVip) {
	Queue* queue = IsVip ? VipQueue : OdinQueue;
	int WinNum = IsVip ? NumOfVIPWin : NumOfWin;
	Window* win = IsVip ? VIPWin : Win;

	int NowWinNo = 0;//窗口数组编号
	int MinWaitNum = MaxCustCheck;//最少安检口排队乘客数量
	int MinWaitWinNo = 0;//最少乘客排队的安检口数组编号		
	if (queue == OdinQueue)
	{
		if (PreWinOK() == 0)
		{
			return;
		}
	}
	while (queue->WaitNum != 0  )//有人在排队缓冲区排队
	{
		MinWaitWinNo = 0;
		MinWaitNum = MaxCustCheck;

		//记录目前排队最少且处于正常工作的安检口	
		for (NowWinNo = 0; NowWinNo < WinNum; NowWinNo++) //数组编号小于安检口总数则执行循环
		{
			if ((MinWaitNum > win[NowWinNo].WaitNum) && (win[NowWinNo].WinState == OpenWin || win[NowWinNo].WinState == OnSerWin || (win[NowWinNo].WinState == ReadyClosWin&&AirportState == ShutDown))) 																																													
			{
				MinWaitNum = Win[NowWinNo].WaitNum; //记录当前最少排队人数
				MinWaitWinNo = NowWinNo; //改变当前最少安检口编号
			}
		}
		//入安检口
		if (MinWaitNum < MaxCustCheck) //存在排队未满的安检口
		{
			win[MinWaitWinNo].WinTail->next = queue->QueueHead->next;//将排队缓冲区队头插入该安检口的队尾
			win[MinWaitWinNo].WinTail = queue->QueueHead->next;//将安检口队尾改为其下一个
			queue->QueueHead->next = queue->QueueHead->next->next;//改变排队缓冲区的队头为其下一个
			win[MinWaitWinNo].WinTail->next = NULL;//将安检口队尾的下一个置为空
			win[MinWaitWinNo].WaitNum++;//此安检口排队乘客量加一
			queue->WaitNum--;//排队缓冲区乘客-1
			EnCache(&EnCheckCache, IsVip ? MinWaitWinNo + NumOfWin : MinWaitWinNo);
			//EnCheckCache.no[(EnCheckCache.tail++) % CacheNum] = IsVip ? MinWaitWinNo + NumOfWin: MinWaitWinNo;//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^进安检口Cache
			//ResetCheckCache();//^^^^^^^^^^^^^^^^
			if(IsVip)
				EventOutputFile('c', win[MinWaitWinNo].WinTail->id, MinWaitWinNo + 1);//事件输出
			else
				EventOutputFile('C', win[MinWaitWinNo].WinTail->id, MinWaitWinNo + 1);//事件输出
		}
		else //所有可用安检口队列已满
			break;
	}//while
	if (queue->WaitNum == 0)
	{
		queue->QueueTail = queue->QueueHead;
	}
}


//休息或下班事件
void RestOrClosWin(entry *event)//接收事件完成安检口下班及休息功能
{
	int i = 0;//设置循环变量
	switch (event->type)
	{
	case 'X'://安检口申请休息
		if ((Win[event->check - 1].WinState == OnSerWin) || (Win[event->check - 1].WinState == OpenWin))//只有处于正在安检或空闲的安检口可以准备休息
		{
			Win[event->check - 1].WinState = ReadyRestWin;//设置安检口状态为准备休息
			EventOutputFile('X', 0, event->check);//事件输出
		}
		break;
	case 'Q':
		AirportState = ShutDown;//---------------------------------------------------MD这个BUG好隐秘----------
		for (i = 0; i < NumOfWin; i++)//遍历安检口数组
		{
			if (Win[i].WinState != CloseWin)//安检口不在关闭状态
			{
				if (Win[i].WinState == RestWin)
				{
					WinNum++;
				}
				Win[i].WinState = ReadyClosWin;//改变安检口状态为准备关闭(正在休息或准备休息的安检口强制准备下班）
			}
		}
		for (i = 0; i < NumOfVIPWin; i++)
		{
			if (VIPWin[i].WinState != CloseWin)//安检口不在关闭状态
			{
				VIPWin[i].WinState = ReadyClosWin;//改变安检口状态为准备关闭(正在休息或准备休息的安检口强制准备下班）
			}
		}
		EventOutputFile('Q', 0, 0);//事件输出
		break;
	default:
		break;
	}
}


//乘客安检
void CheckBegin(Window* win) {

	win->NowPas = win->WinHead->next; //为队头乘客安检
	win->WinHead->next = win->WinHead->next->next;//改变队头乘客为其的下一个
	win->SerNum = win->NowPas->id;//为其设置服务号码为乘客ID
	time(&TimeNow);//获取当前时间
	win->SerTime = TimeNow + win->NowPas->TaskTime;//设置此次安检结束时间
	win->TotalSer++;//服务的乘客量增加
	win->WaitNum--;//排队的乘客数量减一
	win->TotalTime += win->NowPas->TaskTime;//服务的总时间增加
	if (win->WinHead->next == NULL)//WIn->Head==NULL,让尾指向头
	{
		win->WinTail = win->WinHead; //让尾和头和同指
	}
}
void CheckOver(Window* win,int no) {
	if (win->NowPas->State == 4)//安检失败
	{
		EventOutputFile('B', win->NowPas->id, 0);//事件输出
		mciSendString(TEXT("seek music to start"), NULL, 0, NULL);
		//mciSendString(TEXT("open 警报2.mp3 alias music"), NULL, 0, NULL);
		mciSendString(TEXT("play music"), NULL, 0, NULL);
	}
	else
		EventOutputFile('L', win->NowPas->id, 0);

	EnCache(&DeCheckCache,no);
	//DeCheckCache.no[(DeCheckCache.tail++)% CacheNum] = no;//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^出安检口Cache
	//ResetCheckCache();
	free(win->NowPas);//--------------------释放内存
	win->NowPas = NULL;//设置被安检乘客指针为空
}
void WinRun() //安检口处理乘客及计算安检口状态转换
{
	int i = 0;//安检口数组编号
	int n = 0;//此次状态处理循环中已增设安检口数量
	int NowState;//安检口当前状态
	
	//排队缓冲人少，有关闭一个安检口的需求(当前安检口数大于最少安检口数,机场不处于ShutDown),且一次只能有一个安检口处于此状态
	if ((AirportState == OnWork) &&((OdinQueue->WaitNum / WinNum) <= EasySeqLen) && (WinNum>MinCheck) && (PreClose == 0) )	{
		//for (i = NumOfWin-1; i >=0; i--)//从最后开始寻找一个合适关闭的安检口
		for (i = 0; i < NumOfWin; i++)//从前开始寻找一个适合关闭的安检口
		{
			if (Win[i].WinState == OnSerWin || Win[i].WinState == OpenWin)//找到一个空闲或正在安检的安检口
			{
				Win[i].WinState = ReadyClosWin;//设置安检口状态为准备关闭
				PreClose++;//准备关闭安检口数目加一
				break;//一次最多关闭一个
			}
		}
	}

	for (i = 0; i < NumOfWin; i++)//遍历安检口数组，进行乘客处理及安检口状态转换
	{
		NowState = Win[i].WinState;//获取安检口状态
		switch (NowState)
		{
		case CloseWin: //安检口处于关闭状态
			if ((AirportState != ShutDown) && (((OdinWatNum + 1 - MaxCustCheck*n) / WinNum) >= MaxSeqLen) && WinNum<NumOfWin)//排队缓冲区乘客过多且于剩余安检口则需要开放新的安检口
			{
				Win[i].WinState = OpenWin;//安检口状态设置为空闲
				WinNum++;//当前安检口数量增加
				n++;//已增设安检口加一
				EventOutputFile('O', 0, i + 1);//事件输出
			}
			break;
		case OpenWin: //安检口处于空闲状态
			if (Win[i].WinHead->next != NULL)//有人在此安检口排队
			{
				if (BeginOK(i)==0)
				{
					break;
				}
				Win[i].WinState = OnSerWin;//改变安检口状态为正在服务
				CheckBegin(&Win[i]);//-------------
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
				OdinWatNum--;//排队总人数减一

				CheckOver(&Win[i],i);//------------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
				WinNum++;
				EventOutputFile('J', 0, i + 1);//事件输出

			}
			else//休息未结束
			{
				;
			}
			break;
		case ReadyRestWin: //安检口处于申请休息状态
			if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//安检口无人排队且空闲														
			{
				Win[i].WinTail = Win[i].WinHead;//DEBUG-------尾和头同指
				time(&TimeNow);//获取当前时间
				Win[i].WinState = RestWin;//改变安检口状态为正在休息
				Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//为安检口设置休息结束时间
				EventOutputFile('K', 0, i + 1);//事件输出
				WinNum--;
			}
			else if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next != NULL))//没人正在安检但有人在排队
			{
				CheckBegin(&Win[i]);//---------
			}
			else if (Win[i].NowPas != NULL)//有人正在安检
			{
				time(&TimeNow);//获取当前时间
				if (TimeNow >= Win[i].SerTime)//安检完成

				{
					CheckOver(&Win[i],i);//-------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					OdinWatNum--;//排队总人数减一
				}
			}
			break;
		case ReadyClosWin: //安检口处于准备关闭状态
			if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//满足关闭条件
			{
				Win[i].WinTail = Win[i].WinHead;//DEBUG-------尾和头同指
				Win[i].WinState = CloseWin;//改变安检口状态为关闭
				WinNum--;//工作安检口数量减一
				EventOutputFile('S', 0, i + 1);//新增事件输出
				PreClose--; //待关闭安检口数量减一（机场不处于ShutDown状态）

			}
			else if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next != NULL))//没人正在安检但有人在排队
			{
				CheckBegin(&Win[i]);//------------------
			}
			else if (Win[i].NowPas != NULL)//有人正在安检
			{
				time(&TimeNow);//获取当前时间
				if (TimeNow >= Win[i].SerTime)//安检完成
				{
					CheckOver(&Win[i],i);//-------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					OdinWatNum--;//------------------------------------有人正在安检 这里没减0 0
				}
			}
			break;
		default:
			break;
		}//Switch
	}//for
}
void VIPWinRun() //安检口处理乘客及计算安检口状态转换
{
	int i = 0;//安检口数组编号
	int NowState;//安检口当前状态
	for (i = 0; i < NumOfVIPWin; i++)//遍历安检口数组，进行乘客处理及安检口状态转换
	{
		NowState = VIPWin[i].WinState;//获取安检口状态
		switch (NowState)
		{
		case OpenWin: //安检口处于空闲状态
			if (VIPWin[i].WinHead->next != NULL)//有人在此安检口排队
			{
				if (BeginOK(i+NumOfWin) == 0)
				{
					break;
				}
				
				VIPWin[i].WinState = OnSerWin;//改变安检口状态为正在服务
				CheckBegin(&VIPWin[i]);//--------------------------
			}
			else//无人排队
				;
			break;
		case OnSerWin: //安检口处于正在安检状态
			time(&TimeNow);//获取当前时间
			if (TimeNow >= VIPWin[i].SerTime)//安检完成
			{
				CheckOver(&VIPWin[i],i+NumOfWin);//---------------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
				VIPWin[i].WinState = OpenWin;//状态转换为空闲

			}
			else //安检未结束
				;
			break;

		case ReadyClosWin: //安检口处于准备关闭状态
			if ((VIPWin[i].NowPas == NULL) && (VIPWin[i].WinHead->next == NULL))//满足关闭条件
			{
				VIPWin[i].WinTail = VIPWin[i].WinHead;//DEBUG-------尾和头同指
				VIPWin[i].WinState = CloseWin;//改变安检口状态为关闭
				VipWinNum--; 
				EventOutputFile('S', 0, i + 1);//事件输出
				//PreClose--; //待关闭安检口数量减一（机场不处于ShutDown状态）

			}
			else if ((VIPWin[i].NowPas == NULL) && (VIPWin[i].WinHead->next != NULL))//没人正在安检但有人在排队
			{
				CheckBegin(&VIPWin[i]);//-----------------
			}
			else if (VIPWin[i].NowPas != NULL)//有人正在安检
			{
				time(&TimeNow);//获取当前时间
				if (TimeNow >= VIPWin[i].SerTime)//安检完成
				{
					CheckOver(&VIPWin[i],i + NumOfWin);//-----------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
				}

			}
			break;
		default:
			break;
		}//Switch
	}//for
}
/*乘客安检*/


//检查能否下班
int CheckWin() //检查安检口是否能下班
{
	if (WinNum == 0&&VipWinNum==0) //所有工作已结束
	{
		return OffWork; //返回下班
	}
	else
	{
		return ShutDown; //返回准备下班
	}
}


void StateTrans(entry *event) // 总控制函数
{
	if (event->ev_valid == 0) //该事件未发生过,执行事件
	{
		event->ev_valid = 1;//设置该事件为已发生
		switch (event->type)
		{
		case 'G':	//乘客到达事件
			if (AirportState != ShutDown) //机场不处于准备下班状态
			{
				DistriNum(event);//将乘客分配到缓冲区
			}
			break;
		case 'V':
			if (AirportState != ShutDown) //机场不处于准备下班状态
			{
				DistriNum(event);//将VIP乘客直接分配到VIP窗口
			}
			break;
		case 'X': //安检口事件
			RestOrClosWin(event);//将安检口状态设置为准备休息或下班
			break;
		case 'Q': //安检口事件
			RestOrClosWin(event);//将安检口状态设置为准备休息或下班
			break;
		}
	}//if
	PreWinRun(VIP); //将排队缓冲区的乘客插入到安检口
	PreWinRun(ODIN);
	WinRun();////安检口处理乘客及计算安检口状态转换
	VIPWinRun();

	if (event->type == 'Q') //收到下班指令
	{
		AirportState = CheckWin();//判断安检口能否关闭
	}
}
