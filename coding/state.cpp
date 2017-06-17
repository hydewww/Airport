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
int PreClose = 0;//��¼׼���رհ���ڵ���Ŀ
int OdinWatNum;

//���뻺����
void EnQueue(Queue* queue) {
	Passenger* p;
	if (!(p = (Passenger*)malloc(sizeof(Passenger)))) {
		puts("�˿ͽ��뻺����ʧ��");
		exit(EXIT_FAILURE);
	}
	queue->SumNum++;
	queue->WaitNum++;

	p->State = thisEvent.check;//��δ���䰲���
	p->id = queue->SumNum;//����id

	p->SerNum = 0;//0Ϊδ�����
	p->TaskTime = MinSec + rand() % (MaxSec + 1);//���ð����ʱ��
	p->next = NULL;
	queue->QueueTail->next = p;//���˿Ͳ����Ŷӻ������Ķ�β
	queue->QueueTail = p;//��βָ��ָ��β�˿�

}
void DistriNum(entry *event)//Ϊ�˿ͷ�����벢�����Ŷӻ�����
{
	int number = 0;//���ε���˿�����������
	Passenger* p = NULL;//�˿�ָ��

	if (event->type == 'G') {
		for (number = 0; number < event->mans; number++)
		{
			if (OdinQueue->WaitNum >= MaxCustSingleLine*MaxLines) //�Ŷӻ���������
			{
				EventOutputFile('F', 0, 0);//�¼����
				break;
			}
			OdinWatNum++;//---------------
			EnQueue(OdinQueue);//-----------------���
			//EnLineCache++;//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^��������Cahce
			if (event->check == 4)
				EnCache(&EnLineCache, 1);
			else if (event->check == 0)
				EnCache(&EnLineCache, 0);
				
			EventOutputFile('G', OdinQueue->SumNum, 0);//�¼����
		}
	}
	else if (event->type == 'V') {
		for (number = 0; number < event->mans; number++)
		{
			EnQueue(VipQueue);//-------------
			//----------������¼� װ��û�л��������ֶ�����
		}
	}
}
/*���뻺����*/

//�������������
int PreWinOK();

void PreWinRun(int IsVip) {
	Queue* queue = IsVip ? VipQueue : OdinQueue;
	int WinNum = IsVip ? NumOfVIPWin : NumOfWin;
	Window* win = IsVip ? VIPWin : Win;

	int NowWinNo = 0;//����������
	int MinWaitNum = MaxCustCheck;//���ٰ�����Ŷӳ˿�����
	int MinWaitWinNo = 0;//���ٳ˿��Ŷӵİ����������		
	if (queue == OdinQueue)
	{
		if (PreWinOK() == 0)
		{
			return;
		}
	}
	while (queue->WaitNum != 0  )//�������Ŷӻ������Ŷ�
	{
		MinWaitWinNo = 0;
		MinWaitNum = MaxCustCheck;

		//��¼Ŀǰ�Ŷ������Ҵ������������İ����	
		for (NowWinNo = 0; NowWinNo < WinNum; NowWinNo++) //������С�ڰ����������ִ��ѭ��
		{
			if ((MinWaitNum > win[NowWinNo].WaitNum) && (win[NowWinNo].WinState == OpenWin || win[NowWinNo].WinState == OnSerWin || (win[NowWinNo].WinState == ReadyClosWin&&AirportState == ShutDown))) 																																													
			{
				MinWaitNum = Win[NowWinNo].WaitNum; //��¼��ǰ�����Ŷ�����
				MinWaitWinNo = NowWinNo; //�ı䵱ǰ���ٰ���ڱ��
			}
		}
		//�밲���
		if (MinWaitNum < MaxCustCheck) //�����Ŷ�δ���İ����
		{
			win[MinWaitWinNo].WinTail->next = queue->QueueHead->next;//���Ŷӻ�������ͷ����ð���ڵĶ�β
			win[MinWaitWinNo].WinTail = queue->QueueHead->next;//������ڶ�β��Ϊ����һ��
			queue->QueueHead->next = queue->QueueHead->next->next;//�ı��Ŷӻ������Ķ�ͷΪ����һ��
			win[MinWaitWinNo].WinTail->next = NULL;//������ڶ�β����һ����Ϊ��
			win[MinWaitWinNo].WaitNum++;//�˰�����Ŷӳ˿�����һ
			queue->WaitNum--;//�Ŷӻ������˿�-1
			EnCache(&EnCheckCache, IsVip ? MinWaitWinNo + NumOfWin : MinWaitWinNo);
			//EnCheckCache.no[(EnCheckCache.tail++) % CacheNum] = IsVip ? MinWaitWinNo + NumOfWin: MinWaitWinNo;//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^�������Cache
			//ResetCheckCache();//^^^^^^^^^^^^^^^^
			if(IsVip)
				EventOutputFile('c', win[MinWaitWinNo].WinTail->id, MinWaitWinNo + 1);//�¼����
			else
				EventOutputFile('C', win[MinWaitWinNo].WinTail->id, MinWaitWinNo + 1);//�¼����
		}
		else //���п��ð���ڶ�������
			break;
	}//while
	if (queue->WaitNum == 0)
	{
		queue->QueueTail = queue->QueueHead;
	}
}


//��Ϣ���°��¼�
void RestOrClosWin(entry *event)//�����¼���ɰ�����°༰��Ϣ����
{
	int i = 0;//����ѭ������
	switch (event->type)
	{
	case 'X'://�����������Ϣ
		if ((Win[event->check - 1].WinState == OnSerWin) || (Win[event->check - 1].WinState == OpenWin))//ֻ�д������ڰ������еİ���ڿ���׼����Ϣ
		{
			Win[event->check - 1].WinState = ReadyRestWin;//���ð����״̬Ϊ׼����Ϣ
			EventOutputFile('X', 0, event->check);//�¼����
		}
		break;
	case 'Q':
		AirportState = ShutDown;//---------------------------------------------------MD���BUG������----------
		for (i = 0; i < NumOfWin; i++)//�������������
		{
			if (Win[i].WinState != CloseWin)//����ڲ��ڹر�״̬
			{
				if (Win[i].WinState == RestWin)
				{
					WinNum++;
				}
				Win[i].WinState = ReadyClosWin;//�ı䰲���״̬Ϊ׼���ر�(������Ϣ��׼����Ϣ�İ����ǿ��׼���°ࣩ
			}
		}
		for (i = 0; i < NumOfVIPWin; i++)
		{
			if (VIPWin[i].WinState != CloseWin)//����ڲ��ڹر�״̬
			{
				VIPWin[i].WinState = ReadyClosWin;//�ı䰲���״̬Ϊ׼���ر�(������Ϣ��׼����Ϣ�İ����ǿ��׼���°ࣩ
			}
		}
		EventOutputFile('Q', 0, 0);//�¼����
		break;
	default:
		break;
	}
}


//�˿Ͱ���
void CheckBegin(Window* win) {

	win->NowPas = win->WinHead->next; //Ϊ��ͷ�˿Ͱ���
	win->WinHead->next = win->WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
	win->SerNum = win->NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
	time(&TimeNow);//��ȡ��ǰʱ��
	win->SerTime = TimeNow + win->NowPas->TaskTime;//���ô˴ΰ������ʱ��
	win->TotalSer++;//����ĳ˿�������
	win->WaitNum--;//�Ŷӵĳ˿�������һ
	win->TotalTime += win->NowPas->TaskTime;//�������ʱ������
	if (win->WinHead->next == NULL)//WIn->Head==NULL,��βָ��ͷ
	{
		win->WinTail = win->WinHead; //��β��ͷ��ָͬ
	}
}
void CheckOver(Window* win,int no) {
	if (win->NowPas->State == 4)//����ʧ��
	{
		EventOutputFile('B', win->NowPas->id, 0);//�¼����
		mciSendString(TEXT("seek music to start"), NULL, 0, NULL);
		//mciSendString(TEXT("open ����2.mp3 alias music"), NULL, 0, NULL);
		mciSendString(TEXT("play music"), NULL, 0, NULL);
	}
	else
		EventOutputFile('L', win->NowPas->id, 0);

	EnCache(&DeCheckCache,no);
	//DeCheckCache.no[(DeCheckCache.tail++)% CacheNum] = no;//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^�������Cache
	//ResetCheckCache();
	free(win->NowPas);//--------------------�ͷ��ڴ�
	win->NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
}
void WinRun() //����ڴ���˿ͼ����㰲���״̬ת��
{
	int i = 0;//�����������
	int n = 0;//�˴�״̬����ѭ���������谲�������
	int NowState;//����ڵ�ǰ״̬
	
	//�Ŷӻ������٣��йر�һ������ڵ�����(��ǰ��������������ٰ������,����������ShutDown),��һ��ֻ����һ������ڴ��ڴ�״̬
	if ((AirportState == OnWork) &&((OdinQueue->WaitNum / WinNum) <= EasySeqLen) && (WinNum>MinCheck) && (PreClose == 0) )	{
		//for (i = NumOfWin-1; i >=0; i--)//�����ʼѰ��һ�����ʹرյİ����
		for (i = 0; i < NumOfWin; i++)//��ǰ��ʼѰ��һ���ʺϹرյİ����
		{
			if (Win[i].WinState == OnSerWin || Win[i].WinState == OpenWin)//�ҵ�һ�����л����ڰ���İ����
			{
				Win[i].WinState = ReadyClosWin;//���ð����״̬Ϊ׼���ر�
				PreClose++;//׼���رհ������Ŀ��һ
				break;//һ�����ر�һ��
			}
		}
	}

	for (i = 0; i < NumOfWin; i++)//������������飬���г˿ʹ��������״̬ת��
	{
		NowState = Win[i].WinState;//��ȡ�����״̬
		switch (NowState)
		{
		case CloseWin: //����ڴ��ڹر�״̬
			if ((AirportState != ShutDown) && (((OdinWatNum + 1 - MaxCustCheck*n) / WinNum) >= MaxSeqLen) && WinNum<NumOfWin)//�Ŷӻ������˿͹�������ʣ�ల�������Ҫ�����µİ����
			{
				Win[i].WinState = OpenWin;//�����״̬����Ϊ����
				WinNum++;//��ǰ�������������
				n++;//�����谲��ڼ�һ
				EventOutputFile('O', 0, i + 1);//�¼����
			}
			break;
		case OpenWin: //����ڴ��ڿ���״̬
			if (Win[i].WinHead->next != NULL)//�����ڴ˰�����Ŷ�
			{
				if (BeginOK(i)==0)
				{
					break;
				}
				Win[i].WinState = OnSerWin;//�ı䰲���״̬Ϊ���ڷ���
				CheckBegin(&Win[i]);//-------------
			}
			else//�����Ŷ�
			{
				;
			}
			break;
		case OnSerWin: //����ڴ������ڰ���״̬
			time(&TimeNow);//��ȡ��ǰʱ��
			if (TimeNow >= Win[i].SerTime)//�������
			{
				Win[i].WinState = OpenWin;//״̬ת��Ϊ����
				OdinWatNum--;//�Ŷ���������һ

				CheckOver(&Win[i],i);//------------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

			}
			else //����δ����
			{
				;
			}
			break;
		case RestWin: //����ڴ���������Ϣ״̬
			time(&TimeNow);
			if (TimeNow >= Win[i].RestTime)//��Ϣ����
			{
				Win[i].WinState = OpenWin;//״̬�ı�Ϊ����
				WinNum++;
				EventOutputFile('J', 0, i + 1);//�¼����

			}
			else//��Ϣδ����
			{
				;
			}
			break;
		case ReadyRestWin: //����ڴ���������Ϣ״̬
			if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//����������Ŷ��ҿ���														
			{
				Win[i].WinTail = Win[i].WinHead;//DEBUG-------β��ͷָͬ
				time(&TimeNow);//��ȡ��ǰʱ��
				Win[i].WinState = RestWin;//�ı䰲���״̬Ϊ������Ϣ
				Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//Ϊ�����������Ϣ����ʱ��
				EventOutputFile('K', 0, i + 1);//�¼����
				WinNum--;
			}
			else if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
			{
				CheckBegin(&Win[i]);//---------
			}
			else if (Win[i].NowPas != NULL)//�������ڰ���
			{
				time(&TimeNow);//��ȡ��ǰʱ��
				if (TimeNow >= Win[i].SerTime)//�������

				{
					CheckOver(&Win[i],i);//-------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					OdinWatNum--;//�Ŷ���������һ
				}
			}
			break;
		case ReadyClosWin: //����ڴ���׼���ر�״̬
			if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//����ر�����
			{
				Win[i].WinTail = Win[i].WinHead;//DEBUG-------β��ͷָͬ
				Win[i].WinState = CloseWin;//�ı䰲���״̬Ϊ�ر�
				WinNum--;//���������������һ
				EventOutputFile('S', 0, i + 1);//�����¼����
				PreClose--; //���رհ����������һ������������ShutDown״̬��

			}
			else if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
			{
				CheckBegin(&Win[i]);//------------------
			}
			else if (Win[i].NowPas != NULL)//�������ڰ���
			{
				time(&TimeNow);//��ȡ��ǰʱ��
				if (TimeNow >= Win[i].SerTime)//�������
				{
					CheckOver(&Win[i],i);//-------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
					OdinWatNum--;//------------------------------------�������ڰ��� ����û��0 0
				}
			}
			break;
		default:
			break;
		}//Switch
	}//for
}
void VIPWinRun() //����ڴ���˿ͼ����㰲���״̬ת��
{
	int i = 0;//�����������
	int NowState;//����ڵ�ǰ״̬
	for (i = 0; i < NumOfVIPWin; i++)//������������飬���г˿ʹ��������״̬ת��
	{
		NowState = VIPWin[i].WinState;//��ȡ�����״̬
		switch (NowState)
		{
		case OpenWin: //����ڴ��ڿ���״̬
			if (VIPWin[i].WinHead->next != NULL)//�����ڴ˰�����Ŷ�
			{
				if (BeginOK(i+NumOfWin) == 0)
				{
					break;
				}
				
				VIPWin[i].WinState = OnSerWin;//�ı䰲���״̬Ϊ���ڷ���
				CheckBegin(&VIPWin[i]);//--------------------------
			}
			else//�����Ŷ�
				;
			break;
		case OnSerWin: //����ڴ������ڰ���״̬
			time(&TimeNow);//��ȡ��ǰʱ��
			if (TimeNow >= VIPWin[i].SerTime)//�������
			{
				CheckOver(&VIPWin[i],i+NumOfWin);//---------------------^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
				VIPWin[i].WinState = OpenWin;//״̬ת��Ϊ����

			}
			else //����δ����
				;
			break;

		case ReadyClosWin: //����ڴ���׼���ر�״̬
			if ((VIPWin[i].NowPas == NULL) && (VIPWin[i].WinHead->next == NULL))//����ر�����
			{
				VIPWin[i].WinTail = VIPWin[i].WinHead;//DEBUG-------β��ͷָͬ
				VIPWin[i].WinState = CloseWin;//�ı䰲���״̬Ϊ�ر�
				VipWinNum--; 
				EventOutputFile('S', 0, i + 1);//�¼����
				//PreClose--; //���رհ����������һ������������ShutDown״̬��

			}
			else if ((VIPWin[i].NowPas == NULL) && (VIPWin[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
			{
				CheckBegin(&VIPWin[i]);//-----------------
			}
			else if (VIPWin[i].NowPas != NULL)//�������ڰ���
			{
				time(&TimeNow);//��ȡ��ǰʱ��
				if (TimeNow >= VIPWin[i].SerTime)//�������
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
/*�˿Ͱ���*/


//����ܷ��°�
int CheckWin() //��鰲����Ƿ����°�
{
	if (WinNum == 0&&VipWinNum==0) //���й����ѽ���
	{
		return OffWork; //�����°�
	}
	else
	{
		return ShutDown; //����׼���°�
	}
}


void StateTrans(entry *event) // �ܿ��ƺ���
{
	if (event->ev_valid == 0) //���¼�δ������,ִ���¼�
	{
		event->ev_valid = 1;//���ø��¼�Ϊ�ѷ���
		switch (event->type)
		{
		case 'G':	//�˿͵����¼�
			if (AirportState != ShutDown) //����������׼���°�״̬
			{
				DistriNum(event);//���˿ͷ��䵽������
			}
			break;
		case 'V':
			if (AirportState != ShutDown) //����������׼���°�״̬
			{
				DistriNum(event);//��VIP�˿�ֱ�ӷ��䵽VIP����
			}
			break;
		case 'X': //������¼�
			RestOrClosWin(event);//�������״̬����Ϊ׼����Ϣ���°�
			break;
		case 'Q': //������¼�
			RestOrClosWin(event);//�������״̬����Ϊ׼����Ϣ���°�
			break;
		}
	}//if
	PreWinRun(VIP); //���Ŷӻ������ĳ˿Ͳ��뵽�����
	PreWinRun(ODIN);
	WinRun();////����ڴ���˿ͼ����㰲���״̬ת��
	VIPWinRun();

	if (event->type == 'Q') //�յ��°�ָ��
	{
		AirportState = CheckWin();//�жϰ�����ܷ�ر�
	}
}
