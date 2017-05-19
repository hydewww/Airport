#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"a.h"

int TotalOdinCus = 0; //当前总乘客数量
int OdinLineWaitNum = 0;//当前缓冲区乘客等待人数
int OdinWatNum=0;//当前总乘客等待人数
int PreClose = 0;//记录准备关闭安检口的数目
Passenger* Queuehead;//排队队列头指针，next指向第一位乘客
Passenger* Queuetail;//排队队列尾指针，始终指向最后一位乘客
//time_t TimeNow;//当前时间


void QueueEstablish()//创建队列头指针函数
{
	if ((Queuehead = (Passenger*)malloc(sizeof(Passenger))) == NULL)
	{
		printf("申请内存失败!\n");
	}
	Queuehead->next = NULL;//开始无乘客
	Queuetail = Queuehead;//尾指针和头指针同指

}

void DistriNum(entry *event)//为乘客分配号码并插入排队缓冲区
{
	
	int number = 0;//本次到达乘客数量计数器
	Passenger* p;//乘客指针
	for (number = 0; number < event->mans; number++)
	/*
	检查排队缓冲区最大人数 --------------已修改，在本函数添了if判断
	准备下班也不能进人 ---------------已修改，添加在总控制函数里
	*/
	{
		if (OdinLineWaitNum >= MaxCustSingleLine*MaxLines) //排队缓冲区已满
		{
			EventOutputFile('F', 0, 0);//新增事件输出函数-----排队缓冲区满
			break;
		}
		TotalOdinCus++;//总乘客数量加一
		OdinLineWaitNum++;//当前排队缓冲区乘客加一
		OdinWatNum++;//当前总等待乘客数加一
		if ((p = (Passenger*)malloc(sizeof(Passenger))) == NULL)
		{
			printf("申请内存失败！");
		}
		else
		{
			p->State = 0;//尚未分配安检口
			p->id = TotalOdinCus;//分配id

			EventOutputFile('G', p->id, 0);//新增事件输出--------------安排Id为XX乘客到排队缓冲区

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
	//for (; ; MinWaitWinNum = 0, MinWaitNum = MaxCustCheck) //存在可以插入乘客的安检口队列
	while(OdinLineWaitNum!=0)//有人在排队缓冲区排队
	/*
	这里好像能改写一下，这个for和break有点迷--------------好的，改成While了0.0
	*/
	{
		MinWaitWinNum = 0;
		MinWaitNum = MaxCustCheck;

		for (NowWinNum = 0; (NowWinNum < NumOfWin); NowWinNum++) //数组编号小于安检口总数则执行循环
		{
			if ((MinWaitNum > Win[NowWinNum].WaitNum) && (Win[NowWinNum].WinState == OpenWin || Win[NowWinNum].WinState == OnSerWin ||( Win[NowWinNum].WinState == ReadyClosWin&&AirportState==ShutDown))) //记录目前排队最少且处于正常工作的安检口
			/*
			正在关闭的窗口不要插入乘客比较好？ -------已修改---增加判断机场是否处于准备关闭状态，若不处于，则不插入正在关闭的安检口，否则插0.0
			*/
			{
				MinWaitNum = Win[NowWinNum].WaitNum; //记录当前最少排队人数
				MinWaitWinNum = NowWinNum; //改变当前最少安检口编号
			}
		}
		if (MinWaitNum < MaxCustCheck) //存在排队未满的安检口
		/*
		<=  -----------我感觉=的话已经满人了0.0
		*/
		{
			Win[MinWaitWinNum].WinTail->next = Queuehead->next;//将排队缓冲区队头插入该安检口的队尾
			Win[MinWaitWinNum].WinTail = Queuehead->next;//将安检口队尾改为其下一个
			Queuehead->next = Queuehead->next->next;//改变排队缓冲区的队头为其下一个
			Win[MinWaitWinNum].WinTail->next = NULL;//将安检口队尾的下一个置为空
			Win[MinWaitWinNum].WaitNum++;//此安检口排队乘客量加一
			OdinLineWaitNum--;//排队缓冲区乘客-1
			EventOutputFile('C', Win[MinWaitWinNum].WinTail->id, MinWaitWinNum + 1);//新增事件输出----------------PasId乘客到WinId安检口
		}
		else //所有可用安检口队列已满
		{
			break;
		}
	}
	if (OdinLineWaitNum == 0)
	{
		Queuetail = Queuehead;
	}
}
void RestOrClosWin(entry event)//接收事件完成安检口下班及休息功能
{
	int i = 0;//设置循环变量
	switch (event.type)
	{
		case 'X'://安检口申请休息
			if ((Win[event.check - 1].WinState==OnSerWin)||(Win[event.check - 1].WinState==OpenWin))//只有处于正在安检或空闲的安检口可以准备休息
			{
				Win[event.check - 1].WinState = ReadyRestWin;//设置安检口状态为准备休息
				EventOutputFile('X', 0, event.check);//新增事件输出----------------------------------WinID安检口申请休息
			}
			break;
			/*
			检查安检口是否开启 ------------------已修改
			*/
		case 'Q':
			//int i = 0;//设置循环变量
			/*
			我这里int报错了 a declartion cannot have a label --------------我也报错了0.0------已修改
			*/
			for (i = 0; i < NumOfWin; i++)//遍历安检口数组
			{
				if (Win[i].WinState != CloseWin)//安检口不在关闭状态
				{
					Win[i].WinState = ReadyClosWin;//改变安检口状态为准备关闭(正在休息或准备休息的安检口强制准备下班）
				}
			}
			EventOutputFile('Q', 0, 0);//新增事件输出-------------------接收到下班指令
			break;
		default:
			break;
	}
}

void WinRun() //安检口处理乘客及计算安检口状态转换
{
	int i = 0;//安检口数组编号
	int n = 0;//此次状态处理循环中已增设安检口数量
	int NowState;//安检口当前状态
	if (((OdinLineWaitNum / WinNum) <= EasySeqLen)&&(WinNum>MinCheck)&&(PreClose==0)&&(AirportState==OnWork))//排队缓冲人少，有关闭一个安检口的需求(当前安检口数大于最少安检口数,机场不处于ShutDown),且一次只能有一个安检口处于此状态
	{
		for (i = NumOfWin-1; i >=0; i--)//从最后开始寻找一个合适关闭的安检口
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
				if ((((OdinWatNum +1-MaxCustCheck*n) / WinNum) >= MaxSeqLen)&&WinNum<NumOfWin)//排队缓冲区乘客过多且于剩余安检口则需要开放新的安检口
				{
					Win[i].WinState = OpenWin;//安检口状态设置为空闲
					WinNum++;//当前安检口数量增加
					n++;//已增设安检口加一
					EventOutputFile('O', 0, i + 1);//新增事件输出----------------------------------WinID安检口开启
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
					if (Win[i].WinHead->next == NULL)//---------------------------------------DEBUG----WIn->Head==NULL,让尾指向头
					{
						Win[i].WinTail = Win[i].WinHead; //让尾和头和同指
					}
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
					EventOutputFile('L', Win[i].NowPas->id, 0);//新增事件输出----------------------PasId乘客完成安检
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
					EventOutputFile('J', 0, i + 1);//新增事件输出------------------------------WinId安检口结束休息

				}
				else//休息未结束
				{
					;
				}
				break;
			case ReadyRestWin: //安检口处于申请休息状态
				if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//安检口无人排队且空闲
				/*
				Winhead->next=null------------------已修改
				*/
				{
					Win[i].WinTail = Win[i].WinHead;//-------------------------------------------DEBUG-------尾和头同指
					time(&TimeNow);//获取当前时间
					Win[i].WinState = RestWin;//改变安检口状态为正在休息
					Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//为安检口设置休息结束时间
					EventOutputFile('K', 0, i + 1);//新增事件输出-------------------------------------WinID安检口开始休息
				}
				/*
				如果nowpas=null winhead->next!=null 需要处理下一个乘客------------已修改
				*/
				else if((Win[i].NowPas==NULL)&&(Win[i].WinHead->next!=NULL))//没人正在安检但有人在排队
				{
					Win[i].NowPas = Win[i].WinHead->next; //为队头乘客安检
					Win[i].WinHead->next = Win[i].WinHead->next->next;//改变队头乘客为其的下一个
					Win[i].SerNum = Win[i].NowPas->id;//为其设置服务号码为乘客ID
					time(&TimeNow);//获取当前时间
					Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//设置此次安检结束时间
					Win[i].TotalSer++;//服务的乘客量增加
					Win[i].TotalTime += Win[i].NowPas->TaskTime;//服务的总时间增加					
				}
				else if (Win[i].NowPas != NULL)//有人正在安检
				{
					time(&TimeNow);//获取当前时间
					if (TimeNow >= Win[i].SerTime)//安检完成
					{					
						EventOutputFile('L', Win[i].NowPas->id, 0);//新增事件输出------------------------------------PasId乘客完成安检
						Win[i].NowPas = NULL;//设置被安检乘客指针为空
					}


				}
				break;
			case ReadyClosWin: //安检口处于准备关闭状态
				if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//满足关闭条件
				/*
				Winhead->next=null 约炮缓冲区----------------------吼的已修改，这都被你发现了

				*/
				{
					Win[i].WinTail = Win[i].WinHead;//-------------------------------------------DEBUG-------尾和头同指
					Win[i].WinState = CloseWin;//改变安检口状态为关闭
					WinNum--;//安检口数量减一
					EventOutputFile('S', 0, i + 1);//新增事件输出--------------------------------------WinID安检口关闭

				}
				/*
				如果nowpas=null winhead->next!=null 需要处理下一个乘客-----------已修改
				*/
				else if ((Win[i].NowPas == NULL)&&(Win[i].WinHead->next != NULL))//没人正在安检但有人在排队
				{
					Win[i].NowPas = Win[i].WinHead->next; //为队头乘客安检
					Win[i].WinHead->next = Win[i].WinHead->next->next;//改变队头乘客为其的下一个
					Win[i].SerNum = Win[i].NowPas->id;//为其设置服务号码为乘客ID
					time(&TimeNow);//获取当前时间
					Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//设置此次安检结束时间
					Win[i].TotalSer++;//服务的乘客量增加
					Win[i].TotalTime += Win[i].NowPas->TaskTime;//服务的总时间增加					
				}
				else if (Win[i].NowPas != NULL)//有人正在安检
				{
					time(&TimeNow);//获取当前时间
					if (TimeNow >= Win[i].SerTime)//安检完成
					{
						EventOutputFile('L', Win[i].NowPas->id, 0);//新增事件输出-------------------------------------PasId乘客完成安检
						Win[i].NowPas = NULL;//设置被安检乘客指针为空
					}
				}
				break;
			default:
				break;
		}//Switch
	}//for
}
int CheckWin() //检查安检口是否能下班
{
	if (WinNum == 0) //所有工作已结束
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
			/*
			EventOutputFile('G',int PasID,int WinID);------------------------已修改
			*/
			break;
		default: //安检口事件
			RestOrClosWin(*event);//将安检口状态设置为准备休息或下班
			/*
			EventOutputFile('X',int PasID,int WinID);------------------------已修改
			*/
			break;
		}
	}//if
	PreWinRun(); //将排队缓冲区的乘客插入到安检口
	/*
	EventOutputFile('C',int PasID,int WinID);-------------------------已修改 
	*/
	WinRun();////安检口处理乘客及计算安检口状态转换
	if (event->type == 'Q') //收到下班指令
	{
		AirportState= CheckWin();//判断安检口能否关闭
	}
}
/*
需要一波输出函数
case 'G':fprintf(fp, "%d号乘客进入排队缓冲区\n", PasID); break; /
case 'F':fprintf(fp, "排队缓冲区已满\n"); break; /
case 'C':fprintf(fp, "%d号乘客进入%d号安检口\n", PasID, WinID); break;/
case 'L':fprintf(fp, "%d号乘客完成安检离开\n", PasID); break;/
case 'O':fprintf(fp, "%d号安检口开启", WinID); break; /
case 'S':fprintf(fp, "%d号安检口关闭", WinID); break;
case 'X':fprintf(fp, "%d号安检口申请休息", WinID); break;/
case 'K':fprintf(fp, "%d号安检口开始休息", WinID); break;/
case 'J':fprintf(fp, "%d号安检口结束休息", WinID); break;/
case 'Q':fprintf(fp, "接收到下班指令\n"); break; /
*/