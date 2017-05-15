#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"global.h"
#include"passenger.h"
#include"window.h"

int TotalOdinCus = 0; //��ǰ�ܳ˿�����

Passenger* Queuehead;//�ŶӶ���ͷָ�룬nextָ���һλ�˿�
Passenger* Queuetail;//�ŶӶ���βָ�룬ʼ��ָ�����һλ�˿�
time_t TimeNow;//��ǰʱ��


void QueueEstablish()//��������ͷָ�뺯��
{
	if ((Queuehead = (Passenger*)malloc(sizeof(Passenger))) == NULL)
	{
		printf("�����ڴ�ʧ��!\n");
	}
	Queuehead->next = NULL;//��ʼ�޳˿�
	Queuetail = Queuehead;//βָ���ͷָ��ָͬ

}

void DistriNum(entry *event)//Ϊ�˿ͷ�����벢�����Ŷӻ�����
{
	
	int number = 0;//���ε���˿�����������
	Passenger* p;//�˿�ָ��
	for (number = 0; (number < event->mans) && (AirportState != OffWork); number++)
	{
		TotalOdinCus++;//�˿�������һ
		OdinWatNum++;//��ǰ�ȴ��˿�����һ
		if ((p = (Passenger*)malloc(sizeof(Passenger))) == NULL)
		{
			printf("�����ڴ�ʧ�ܣ�");
		}
		else
		{
			p->State = 0;//��δ���䰲���
			p->id = TotalOdinCus;//����id
			p->SerNum = 0;//0Ϊδ�����
			p->TaskTime = MinSec + rand() % (MaxSec + 1);//���ð����ʱ��
			p->next = NULL;
			Queuetail->next = p;//���˿Ͳ����Ŷӻ������Ķ�β
			Queuetail = p;//��βָ��ָ��β�˿�
			p = p->next;
		}
	}

}

void PreWinRun() //���Ŷӻ������ĳ˿Ͳ��뵽�����
{
	int NowWinNum = 0;//����������
	int MinWaitNum = MaxCustCheck;//���ٰ�����Ŷӳ˿�����
	int MinWaitWinNum = 0;//���ٳ˿��Ŷӵİ����������
	for (; ; MinWaitWinNum = 0, MinWaitNum = MaxCustCheck) //���ڿ��Բ���˿͵İ���ڶ���
	{
		for (NowWinNum = 0; NowWinNum < NumOfWin; NowWinNum++) //������С�ڰ����������ִ��ѭ��
		{
			if ((MinWaitNum > Win[NowWinNum].WaitNum) && (Win[NowWinNum].WinState == OpenWin || Win[NowWinNum].WinState == OnSerWin || Win[NowWinNum].WinState == ReadyClosWin)) //��¼Ŀǰ�Ŷ������Ҵ������������İ����
			{
				MinWaitNum = Win[NowWinNum].WaitNum; //��¼��ǰ�����Ŷ�����
				MinWaitWinNum = NowWinNum; //�ı䵱ǰ���ٰ���ڱ��
			}
		}
		if (MinWaitWinNum < MaxCustCheck) //�����Ŷ�δ���İ����
		{
			Win[MinWaitWinNum].WinTail->next = Queuehead->next;//���Ŷӻ�������ͷ����ð���ڵĶ�β
			Win[MinWaitWinNum].WinTail = Queuehead->next;//������ڶ�β��Ϊ����һ��
			Queuehead->next = Queuehead->next->next;//�ı��Ŷӻ������Ķ�ͷΪ����һ��
			Win[MinWaitWinNum].WinTail->next = NULL;//������ڶ�β����һ����Ϊ��
			Win[MinWaitWinNum].WaitNum++;//�˰�����Ŷӳ˿�����һ
		}
		else //����ڶ�������
		{
			break;
		}
	}
}
void RestOrClosWin(entry event)//�����¼���ɰ�����°༰��Ϣ����
{
	switch (event.type)
	{
		case 'X'://�����������Ϣ
			Win[event.check - 1].WinState = ReadyRestWin;//���ð����״̬Ϊ׼����Ϣ
			break;
		case 'Q':
			int i = 0;//����ѭ������
			for (i = 0; i < NumOfWin; i++)//�������������
			{
				if (Win[i].WinState != CloseWin)//����ڲ��ڹر�״̬
				{
					Win[i].WinState = ReadyClosWin;//�ı䰲���״̬Ϊ׼���ر�(������Ϣ��׼����Ϣ�İ����ǿ��׼���°ࣩ
				}
			}
			break;
		default:
			break;
	}
}

void WinRun() //����ڴ���˿ͼ����㰲���״̬ת��
{
	int i = 0;//�����������
	int n = 0;//�˴�״̬����ѭ���������谲�������
	int NowState;//����ڵ�ǰ״̬
	
	for (i = 0; i < NumOfWin; i++)//������������飬���г˿ʹ��������״̬ת��
	{
		NowState = Win[i].WinState;//��ȡ�����״̬
		switch (NowState)
		{
			case CloseWin: //����ڴ��ڹر�״̬
				if (((OdinWatNum +1-MaxCustCheck*n) / WinNum) >= MaxSeqLen)//�Ŷӻ������˿͹�����Ҫ�������µİ����
				{
					Win[i].WinState = OpenWin;//�����״̬����Ϊ����
					WinNum++;//��ǰ�������������
				}
				break;
			case OpenWin: //����ڴ��ڿ���״̬
				if (Win[i].WinHead->next != NULL)//�����ڴ˰�����Ŷ�
				{
					Win[i].WinState = OnSerWin;//�ı䰲���״̬Ϊ���ڷ���
					Win[i].NowPas = Win[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
					Win[i].WinHead->next = Win[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
					Win[i].SerNum = Win[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
					time(&TimeNow);//��ȡ��ǰʱ��
					Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
					Win[i].TotalSer++;//����ĳ˿�������
					Win[i].TotalTime += Win[i].NowPas->TaskTime;//�������ʱ������
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
					Win[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��

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

				}
				else//��Ϣδ����
				{
					;
				}
				break;
			case ReadyRestWin: //����ڴ���������Ϣ״̬
				if ((Win[i].NowPas == NULL) && (Win[i].WinHead == NULL))//����������Ŷ��ҿ���
				{
					time(&TimeNow);//��ȡ��ǰʱ��
					Win[i].WinState = RestWin;//�ı䰲���״̬Ϊ������Ϣ
					Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//Ϊ�����������Ϣ����ʱ��
				}
				else//������Ϣ
				{
					;
				}
				break;
			case ReadyClosWin: //����ڴ���׼���ر�״̬
				if (((Win[i].NowPas == NULL) && (Win[i].WinHead == NULL)) && ((OdinWatNum + 1 - MaxCustCheck) / WinNum) <= EasySeqLen)//����ر�����(����ڿ������ڶӻ���������)
				{
					Win[i].WinState = CloseWin;//�ı䰲���״̬Ϊ�ر�
					WinNum--;//�����������һ

				}
				else //���ܹر�
				{
					;
				}
				break;
			default:
				break;
		}//Switch
	}//for
}
int CheckWin() //��鰲����Ƿ����°�
{
	if (WinNum == 0) //���й����ѽ���
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
		case 'G':			//�˿͵����¼�
			DistriNum(event);//���˿ͷ��䵽������
			break;
		default: //������¼�
			RestOrClosWin(*event);//�������״̬����Ϊ׼����Ϣ���°�
			break;
		}
	}//if
	PreWinRun(); //���Ŷӻ������ĳ˿Ͳ��뵽�����
	WinRun();////����ڴ���˿ͼ����㰲���״̬ת��
	if (event->type == 'Q') //�յ��°�ָ��
	{
		AirportState= CheckWin();//�жϰ�����ܷ�ر�
	}
}