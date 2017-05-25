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

int PreClose = 0;//��¼׼���رհ���ڵ���Ŀ

Queue* OdinQueue;
Queue* VipQueue;

void QueueEstablish(Queue* queue)//��������ͷָ�뺯��
{
	if (!(queue = (Queue*)malloc(sizeof(Queue))) || !(queue->QueueHead = (Passenger*)malloc(sizeof(Queue)))) {
		puts("���뻺�����ڴ�ʧ��!");
		exit(1);
	}
	queue->QueueHead->next = NULL;//��ʼ�޳˿�
	queue->QueueTail = queue->QueueHead;//βָ���ͷָ��ָͬ
	queue->SumNum = 0;
	queue->WaitNum = 0;
}

void EnQueue(Queue* queue) {
	Passenger* p;
	if (!(p = (Passenger*)malloc(sizeof(Passenger)))) {
		puts("�˿ͽ��뻺����ʧ��");
		exit(1);
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
			if (OdinLineWaitNum >= MaxCustSingleLine*MaxLines) //�Ŷӻ���������
			{
				EventOutputFile('F', 0, 0);//�¼����
				break;
			}

			/*OdinWatNum++;*/
			EnQueue(OdinQueue);//���
			EventOutputFile('G', OdinQueue->SumNum, 0);//�¼����
		}
	}
	else if (event->type == 'V') {
		for (number = 0; number < event->mans; number++)
		{
			EnQueue(VipQueue);
			//----------������¼� װ��û�л��������ֶ�����
		}
	}
}

void PreVIPWinRun() //���Ŷӻ������ĳ˿Ͳ��뵽�����
{
	int NowWinNum = 0;//����������
	int MinWaitNum = MaxCustCheck;//���ٰ�����Ŷӳ˿�����
	int MinWaitWinNum = 0;//���ٳ˿��Ŷӵİ����������
						  //for (; ; MinWaitWinNum = 0, MinWaitNum = MaxCustCheck) //���ڿ��Բ���˿͵İ���ڶ���
	while (VIPWatNum != 0)//�������Ŷӻ������Ŷ�
								/*
								��������ܸ�дһ�£����for��break�е���--------------�õģ��ĳ�While��0.0
								*/
	{
		MinWaitWinNum = 0;
		MinWaitNum = MaxCustCheck;

		for (NowWinNum = 0; (NowWinNum < NumOfVIPWin); NowWinNum++) //������С�ڰ����������ִ��ѭ��
		{
			if ((MinWaitNum > VIPWin[NowWinNum].WaitNum) && (VIPWin[NowWinNum].WinState == OpenWin || VIPWin[NowWinNum].WinState == OnSerWin || (VIPWin[NowWinNum].WinState == ReadyClosWin&&AirportState == ShutDown))) //��¼Ŀǰ�Ŷ������Ҵ������������İ����
																																																			 /*
																																																			 ���ڹرյĴ��ڲ�Ҫ����˿ͱȽϺã� -------���޸�---�����жϻ����Ƿ���׼���ر�״̬���������ڣ��򲻲������ڹرյİ���ڣ������0.0
																																																			 */
			{
				MinWaitNum = VIPWin[NowWinNum].WaitNum; //��¼��ǰ�����Ŷ�����
				MinWaitWinNum = NowWinNum; //�ı䵱ǰ���ٰ���ڱ��
			}
		}
		if (MinWaitNum < MaxCustCheck) //�����Ŷ�δ���İ����
									   /*
									   <=  -----------�Ҹо�=�Ļ��Ѿ�������0.0
									   */
		{

			VIPWin[MinWaitWinNum].WinTail->next = VIPQueuehead->next;//���Ŷӻ�������ͷ����ð���ڵĶ�β
			VIPWin[MinWaitWinNum].WinTail = VIPQueuehead->next;//������ڶ�β��Ϊ����һ��
			VIPQueuehead->next = VIPQueuehead->next->next;//�ı��Ŷӻ������Ķ�ͷΪ����һ��
			VIPWin[MinWaitWinNum].WinTail->next = NULL;//������ڶ�β����һ����Ϊ��
			VIPWin[MinWaitWinNum].WaitNum++;//�˰�����Ŷӳ˿�����һ
			VIPWatNum--;//�Ŷӻ������˿�-1
			EventOutputFile('C', VIPWin[MinWaitWinNum].WinTail->id, MinWaitWinNum + 1);//�����¼����----------------PasId�˿͵�WinId�����
		}
		else //���п��ð���ڶ�������
		{
			break;
		}
	}
	if (VIPWatNum == 0)
	{
		VIPQueuetail = VIPQueuehead;
	}
}
	
void PreWinRun() //���Ŷӻ������ĳ˿Ͳ��뵽�����
{
	int NowWinNum = 0;//����������
	int MinWaitNum = MaxCustCheck;//���ٰ�����Ŷӳ˿�����
	int MinWaitWinNum = 0;//���ٳ˿��Ŷӵİ����������
						  //for (; ; MinWaitWinNum = 0, MinWaitNum = MaxCustCheck) //���ڿ��Բ���˿͵İ���ڶ���
	while (OdinLineWaitNum != 0)//�������Ŷӻ������Ŷ�
								/*
								��������ܸ�дһ�£����for��break�е���--------------�õģ��ĳ�While��0.0
								*/
	{
		MinWaitWinNum = 0;
		MinWaitNum = MaxCustCheck;

		for (NowWinNum = 0; (NowWinNum < NumOfWin); NowWinNum++) //������С�ڰ����������ִ��ѭ��
		{
			if ((MinWaitNum > Win[NowWinNum].WaitNum) && (Win[NowWinNum].WinState == OpenWin || Win[NowWinNum].WinState == OnSerWin || (Win[NowWinNum].WinState == ReadyClosWin&&AirportState == ShutDown))) //��¼Ŀǰ�Ŷ������Ҵ������������İ����
																																																			 /*
																																																			 ���ڹرյĴ��ڲ�Ҫ����˿ͱȽϺã� -------���޸�---�����жϻ����Ƿ���׼���ر�״̬���������ڣ��򲻲������ڹرյİ���ڣ������0.0
																																																			 */
			{
				MinWaitNum = Win[NowWinNum].WaitNum; //��¼��ǰ�����Ŷ�����
				MinWaitWinNum = NowWinNum; //�ı䵱ǰ���ٰ���ڱ��
			}
		}
		if (MinWaitNum < MaxCustCheck) //�����Ŷ�δ���İ����
									   /*
									   <=  -----------�Ҹо�=�Ļ��Ѿ�������0.0
									   */
		{
			Win[MinWaitWinNum].WinTail->next = Queuehead->next;//���Ŷӻ�������ͷ����ð���ڵĶ�β
			Win[MinWaitWinNum].WinTail = Queuehead->next;//������ڶ�β��Ϊ����һ��
			Queuehead->next = Queuehead->next->next;//�ı��Ŷӻ������Ķ�ͷΪ����һ��
			Win[MinWaitWinNum].WinTail->next = NULL;//������ڶ�β����һ����Ϊ��
			Win[MinWaitWinNum].WaitNum++;//�˰�����Ŷӳ˿�����һ
			OdinLineWaitNum--;//�Ŷӻ������˿�-1
			EventOutputFile('C', Win[MinWaitWinNum].WinTail->id, MinWaitWinNum + 1);//�����¼����----------------PasId�˿͵�WinId�����
		}
		else //���п��ð���ڶ�������
		{
			break;
		}
	}
	if (OdinLineWaitNum == 0)
	{
		Queuetail = Queuehead;
	}
}

void RestOrClosWin(entry *event)//�����¼���ɰ�����°༰��Ϣ����
{
	int i = 0;//����ѭ������
	switch (event->type)
	{
	case 'X'://�����������Ϣ
		if ((Win[event->check - 1].WinState == OnSerWin) || (Win[event->check - 1].WinState == OpenWin))//ֻ�д������ڰ������еİ���ڿ���׼����Ϣ
		{
			Win[event->check - 1].WinState = ReadyRestWin;//���ð����״̬Ϊ׼����Ϣ
			EventOutputFile('X', 0, event->check);//�����¼����----------------------------------WinID�����������Ϣ
		}
		break;
		/*
		��鰲����Ƿ��� ------------------���޸�
		*/
	case 'Q':
		//int i = 0;//����ѭ������
		/*
		������int������ a declartion cannot have a label --------------��Ҳ������0.0------���޸�
		*/
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
		EventOutputFile('Q', 0, 0);//�����¼����-------------------���յ��°�ָ��
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
	if (((OdinWatNum / WinNum) <= EasySeqLen) && (WinNum>MinCheck) && (PreClose == 0) && (AirportState == OnWork))//�Ŷӻ������٣��йر�һ������ڵ�����(��ǰ��������������ٰ������,����������ShutDown),��һ��ֻ����һ������ڴ��ڴ�״̬
	{
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
				EventOutputFile('O', 0, i + 1);//�����¼����----------------------------------WinID����ڿ���
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
				Win[i].WaitNum--;//------------------------------------�Ŷӵĳ˿�������һ
				Win[i].TotalTime += Win[i].NowPas->TaskTime;//�������ʱ������
				if (Win[i].WinHead->next == NULL)//---------------------------------------DEBUG----WIn->Head==NULL,��βָ��ͷ
				{
					Win[i].WinTail = Win[i].WinHead; //��β��ͷ��ָͬ
				}
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
				if (Win[i].NowPas->State == 4)//--------------------------------------------------------------����ʧ��
				{
					//EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����----------------------PasId�˿Ͱ���ʧ��
					mciSendString(TEXT("seek music to start"), NULL, 0, NULL);
					//mciSendString(TEXT("open ����2.mp3 alias music"), NULL, 0, NULL);
					mciSendString(TEXT("play music"), NULL, 0, NULL);
				}
				
				Win[i].WinState = OpenWin;//״̬ת��Ϊ����
				Win[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
				OdinWatNum--;//�Ŷ���������һ

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
				EventOutputFile('J', 0, i + 1);//�����¼����------------------------------WinId����ڽ�����Ϣ

			}
			else//��Ϣδ����
			{
				;
			}
			break;
		case ReadyRestWin: //����ڴ���������Ϣ״̬
			if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//����������Ŷ��ҿ���
																		  /*
																		  Winhead->next=null------------------���޸�
																		  */
			{
				Win[i].WinTail = Win[i].WinHead;//-------------------------------------------DEBUG-------β��ͷָͬ
				time(&TimeNow);//��ȡ��ǰʱ��
				Win[i].WinState = RestWin;//�ı䰲���״̬Ϊ������Ϣ
				Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//Ϊ�����������Ϣ����ʱ��
				EventOutputFile('K', 0, i + 1);//�����¼����-------------------------------------WinID����ڿ�ʼ��Ϣ
				WinNum--;
			}
			/*
			���nowpas=null winhead->next!=null ��Ҫ������һ���˿�------------���޸�
			*/
			else if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
			{
				Win[i].NowPas = Win[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
				Win[i].WinHead->next = Win[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
				if (Win[i].WinHead->next == NULL)//---------------------------------------------------------DEBUG--------��βָͬ
				{
					Win[i].WinTail = Win[i].WinHead;
				}
				Win[i].SerNum = Win[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
				time(&TimeNow);//��ȡ��ǰʱ��
				Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
				Win[i].TotalSer++;//����ĳ˿�������
				Win[i].WaitNum--;//-------------------------------------------�Ŷӵĳ˿ͼ�һ
				Win[i].TotalTime += Win[i].NowPas->TaskTime;//�������ʱ������					
			}
			else if (Win[i].NowPas != NULL)//�������ڰ���
			{
				time(&TimeNow);//��ȡ��ǰʱ��
				if (TimeNow >= Win[i].SerTime)//�������

				{
					if (Win[i].NowPas->State == 4)//--------------------------------------------------------------����ʧ��
					{
						//EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����----------------------PasId�˿Ͱ���ʧ��
						//mciSendString(TEXT("open ����2.mp3 alias music"), NULL, 0, NULL);
						mciSendString(TEXT("seek music to start"), NULL, 0, NULL);
						mciSendString(TEXT("play music"), NULL, 0, NULL);
					}
					EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����------------------------------------PasId�˿���ɰ���
					Win[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
					OdinWatNum--;//�Ŷ���������һ
				}
				if (Win[i].WinHead->next == NULL)//---------------------------------------------------------DEBUG--------��βָͬ
				{
					Win[i].WinTail = Win[i].WinHead;
				}
			}
			break;
		case ReadyClosWin: //����ڴ���׼���ر�״̬
			if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//����ر�����
																		  /*
																		  Winhead->next=null Լ�ڻ�����----------------------������޸ģ��ⶼ���㷢����
																		  */
			{
				Win[i].WinTail = Win[i].WinHead;//-------------------------------------------DEBUG-------β��ͷָͬ
				Win[i].WinState = CloseWin;//�ı䰲���״̬Ϊ�ر�
				WinNum--;//���������������һ
				EventOutputFile('S', 0, i + 1);//�����¼����--------------------------------------WinID����ڹر�
				PreClose--; //���رհ����������һ������������ShutDown״̬��

			}
			/*
			���nowpas=null winhead->next!=null ��Ҫ������һ���˿�-----------���޸�
			*/
			else if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
			{
				Win[i].NowPas = Win[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
				Win[i].WinHead->next = Win[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
				Win[i].SerNum = Win[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
				time(&TimeNow);//��ȡ��ǰʱ��
				Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
				Win[i].TotalSer++;//����ĳ˿�������
				Win[i].WaitNum--;//-----------------------------------------�Ŷӵĳ˿���-1
				Win[i].TotalTime += Win[i].NowPas->TaskTime;//�������ʱ������	
				if (Win[i].WinHead->next == NULL)//---------------------------------------------------------DEBUG--------��βָͬ
				{
					Win[i].WinTail = Win[i].WinHead;
				}
			}
			else if (Win[i].NowPas != NULL)//�������ڰ���
			{
				time(&TimeNow);//��ȡ��ǰʱ��
				if (TimeNow >= Win[i].SerTime)//�������
				{
					if (Win[i].NowPas->State == 4)//--------------------------------------------------------------����ʧ��
					{
						//EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����----------------------PasId�˿Ͱ���ʧ��
						//mciSendString(TEXT("open ����2.mp3 alias music"), NULL, 0, NULL);
						mciSendString(TEXT("seek music to start"), NULL, 0, NULL);
						mciSendString(TEXT("play music"), NULL, 0, NULL);
					}
					EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����-------------------------------------PasId�˿���ɰ���
					Win[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
					OdinWatNum--;//�Ŷ���������һ
				}
				if (Win[i].WinHead->next == NULL)//---------------------------------------------------------DEBUG--------��βָͬ
				{
					Win[i].WinTail = Win[i].WinHead;
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
	int n = 0;//�˴�״̬����ѭ���������谲�������
	int NowState;//����ڵ�ǰ״̬
	for (i = 0; i < NumOfVIPWin; i++)//������������飬���г˿ʹ��������״̬ת��
	{
		NowState = VIPWin[i].WinState;//��ȡ�����״̬
		switch (NowState)
		{
		case OpenWin: //����ڴ��ڿ���״̬
			if (VIPWin[i].WinHead->next != NULL)//�����ڴ˰�����Ŷ�
			{
				VIPWin[i].WinState = OnSerWin;//�ı䰲���״̬Ϊ���ڷ���
				VIPWin[i].NowPas = VIPWin[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
				VIPWin[i].WinHead->next = VIPWin[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
				VIPWin[i].SerNum = VIPWin[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
				time(&TimeNow);//��ȡ��ǰʱ��
				VIPWin[i].SerTime = TimeNow + VIPWin[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
				VIPWin[i].TotalSer++;//����ĳ˿�������
				VIPWin[i].WaitNum--;//------------------------------------�Ŷӵĳ˿�������һ
				VIPWin[i].TotalTime += VIPWin[i].NowPas->TaskTime;//�������ʱ������
				if (VIPWin[i].WinHead->next == NULL)//---------------------------------------DEBUG----WIn->Head==NULL,��βָ��ͷ
				{
					VIPWin[i].WinTail = VIPWin[i].WinHead; //��β��ͷ��ָͬ
				}
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
				VIPWin[i].WinState = OpenWin;//״̬ת��Ϊ����
				VIPWin[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
				OdinWatNum--;//�Ŷ���������һ
			}
			else //����δ����
			{
				;
			}
			break;

		case ReadyClosWin: //����ڴ���׼���ر�״̬
			if ((VIPWin[i].NowPas == NULL) && (VIPWin[i].WinHead->next == NULL))//����ر�����
																		  /*
																		  Winhead->next=null Լ�ڻ�����----------------------������޸ģ��ⶼ���㷢����
																		  */
			{
				VIPWin[i].WinTail = VIPWin[i].WinHead;//-------------------------------------------DEBUG-------β��ͷָͬ
				VIPWin[i].WinState = CloseWin;//�ı䰲���״̬Ϊ�ر�
				EventOutputFile('S', 0, i + 1);//�����¼����--------------------------------------WinID����ڹر�
				//PreClose--; //���رհ����������һ������������ShutDown״̬��

			}
			/*
			���nowpas=null winhead->next!=null ��Ҫ������һ���˿�-----------���޸�
			*/
			else if ((VIPWin[i].NowPas == NULL) && (VIPWin[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
			{
				VIPWin[i].NowPas = VIPWin[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
				VIPWin[i].WinHead->next = VIPWin[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
				VIPWin[i].SerNum = VIPWin[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
				time(&TimeNow);//��ȡ��ǰʱ��
				VIPWin[i].SerTime = TimeNow + VIPWin[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
				VIPWin[i].TotalSer++;//����ĳ˿�������
				VIPWin[i].WaitNum--;//-----------------------------------------�Ŷӵĳ˿���-1
				VIPWin[i].TotalTime += VIPWin[i].NowPas->TaskTime;//�������ʱ������	
				if (VIPWin[i].WinHead->next == NULL)//---------------------------------------------------------DEBUG--------��βָͬ
				{
					VIPWin[i].WinTail = VIPWin[i].WinHead;
				}
			}
			else if (VIPWin[i].NowPas != NULL)//�������ڰ���
			{
				time(&TimeNow);//��ȡ��ǰʱ��
				if (TimeNow >= VIPWin[i].SerTime)//�������
				{
					EventOutputFile('L', VIPWin[i].NowPas->id, 0);//�����¼����-------------------------------------PasId�˿���ɰ���
					VIPWin[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
					VIPWatNum--;//�Ŷ���������һ
				}
				if (VIPWin[i].WinHead->next == NULL)//---------------------------------------------------------DEBUG--------��βָͬ
				{
					VIPWin[i].WinTail = VIPWin[i].WinHead;
				}

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
	PreWinRun(); //���Ŷӻ������ĳ˿Ͳ��뵽�����
				 /*
				 EventOutputFile('C',int PasID,int WinID);-------------------------���޸�
				 */
	PreVIPWinRun();

	WinRun();////����ڴ���˿ͼ����㰲���״̬ת��
	VIPWinRun();
	if (event->type == 'Q') //�յ��°�ָ��
	{
		AirportState = CheckWin();//�жϰ�����ܷ�ر�
	}
}
/*
��Ҫһ���������
case 'G':fprintf(fp, "%d�ų˿ͽ����Ŷӻ�����\n", PasID); break; /
case 'F':fprintf(fp, "�Ŷӻ���������\n"); break; /
case 'C':fprintf(fp, "%d�ų˿ͽ���%d�Ű����\n", PasID, WinID); break;/
case 'L':fprintf(fp, "%d�ų˿���ɰ����뿪\n", PasID); break;/
case 'O':fprintf(fp, "%d�Ű���ڿ���", WinID); break; /
case 'S':fprintf(fp, "%d�Ű���ڹر�", WinID); break;
case 'X':fprintf(fp, "%d�Ű����������Ϣ", WinID); break;/
case 'K':fprintf(fp, "%d�Ű���ڿ�ʼ��Ϣ", WinID); break;/
case 'J':fprintf(fp, "%d�Ű���ڽ�����Ϣ", WinID); break;/
case 'Q':fprintf(fp, "���յ��°�ָ��\n"); break; /
*/