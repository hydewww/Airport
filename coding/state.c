#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"a.h"

int TotalOdinCus = 0; //��ǰ�ܳ˿�����
int OdinLineWaitNum = 0;//��ǰ�������˿͵ȴ�����
int OdinWatNum=0;//��ǰ�ܳ˿͵ȴ�����
int PreClose = 0;//��¼׼���رհ���ڵ���Ŀ
Passenger* Queuehead;//�ŶӶ���ͷָ�룬nextָ���һλ�˿�
Passenger* Queuetail;//�ŶӶ���βָ�룬ʼ��ָ�����һλ�˿�
//time_t TimeNow;//��ǰʱ��


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
	for (number = 0; number < event->mans; number++)
	/*
	����Ŷӻ������������ --------------���޸ģ��ڱ���������if�ж�
	׼���°�Ҳ���ܽ��� ---------------���޸ģ��������ܿ��ƺ�����
	*/
	{
		if (OdinLineWaitNum >= MaxCustSingleLine*MaxLines) //�Ŷӻ���������
		{
			EventOutputFile('F', 0, 0);//�����¼��������-----�Ŷӻ�������
			break;
		}
		TotalOdinCus++;//�ܳ˿�������һ
		OdinLineWaitNum++;//��ǰ�Ŷӻ������˿ͼ�һ
		OdinWatNum++;//��ǰ�ܵȴ��˿�����һ
		if ((p = (Passenger*)malloc(sizeof(Passenger))) == NULL)
		{
			printf("�����ڴ�ʧ�ܣ�");
		}
		else
		{
			p->State = 0;//��δ���䰲���
			p->id = TotalOdinCus;//����id

			EventOutputFile('G', p->id, 0);//�����¼����--------------����IdΪXX�˿͵��Ŷӻ�����

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
	//for (; ; MinWaitWinNum = 0, MinWaitNum = MaxCustCheck) //���ڿ��Բ���˿͵İ���ڶ���
	while(OdinLineWaitNum!=0)//�������Ŷӻ������Ŷ�
	/*
	��������ܸ�дһ�£����for��break�е���--------------�õģ��ĳ�While��0.0
	*/
	{
		MinWaitWinNum = 0;
		MinWaitNum = MaxCustCheck;

		for (NowWinNum = 0; (NowWinNum < NumOfWin); NowWinNum++) //������С�ڰ����������ִ��ѭ��
		{
			if ((MinWaitNum > Win[NowWinNum].WaitNum) && (Win[NowWinNum].WinState == OpenWin || Win[NowWinNum].WinState == OnSerWin ||( Win[NowWinNum].WinState == ReadyClosWin&&AirportState==ShutDown))) //��¼Ŀǰ�Ŷ������Ҵ������������İ����
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
}
void RestOrClosWin(entry event)//�����¼���ɰ�����°༰��Ϣ����
{
	int i = 0;//����ѭ������
	switch (event.type)
	{
		case 'X'://�����������Ϣ
			if ((Win[event.check - 1].WinState==OnSerWin)||(Win[event.check - 1].WinState==OpenWin))//ֻ�д������ڰ������еİ���ڿ���׼����Ϣ
			{
				Win[event.check - 1].WinState = ReadyRestWin;//���ð����״̬Ϊ׼����Ϣ
				EventOutputFile('X', 0, event.check);//�����¼����----------------------------------WinID�����������Ϣ
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
			for (i = 0; i < NumOfWin; i++)//�������������
			{
				if (Win[i].WinState != CloseWin)//����ڲ��ڹر�״̬
				{
					Win[i].WinState = ReadyClosWin;//�ı䰲���״̬Ϊ׼���ر�(������Ϣ��׼����Ϣ�İ����ǿ��׼���°ࣩ
				}
			}
			EventOutputFile('Q', 0, 0);//�����¼����-------------------���յ��°�ָ��
			break;
		default:
			break;
	}
}

void WinRun() //����ڴ����˿ͼ����㰲���״̬ת��
{
	int i = 0;//�����������
	int n = 0;//�˴�״̬����ѭ���������谲�������
	int NowState;//����ڵ�ǰ״̬
	if (((OdinLineWaitNum / WinNum) <= EasySeqLen)&&(WinNum>MinCheck)&&(PreClose==0)&&(AirportState==OnWork))//�Ŷӻ������٣��йر�һ������ڵ�����(��ǰ��������������ٰ������,����������ShutDown),��һ��ֻ����һ������ڴ��ڴ�״̬
	{
		for (i = NumOfWin-1; i >=0; i--)//�����ʼѰ��һ�����ʹرյİ����
		{
			if (Win[i].WinState == OnSerWin || Win[i].WinState == OpenWin)//�ҵ�һ�����л����ڰ���İ����
			{
				Win[i].WinState = ReadyClosWin;//���ð����״̬Ϊ׼���ر�
				PreClose++;//׼���رհ������Ŀ��һ
				break;//һ�����ر�һ��
			}
		}
	}
	for (i = 0; i < NumOfWin; i++)//������������飬���г˿ʹ����������״̬ת��
	{
		NowState = Win[i].WinState;//��ȡ�����״̬
		switch (NowState)
		{
			case CloseWin: //����ڴ��ڹر�״̬
				if ((((OdinWatNum +1-MaxCustCheck*n) / WinNum) >= MaxSeqLen)&&WinNum<NumOfWin)//�Ŷӻ������˿͹�������ʣ�ల�������Ҫ�����µİ����
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
					EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����----------------------PasId�˿���ɰ���
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
					time(&TimeNow);//��ȡ��ǰʱ��
					Win[i].WinState = RestWin;//�ı䰲���״̬Ϊ������Ϣ
					Win[i].RestTime = TimeNow + MinRestSec + rand() % (MaxRestSec + 1);//Ϊ�����������Ϣ����ʱ��
					EventOutputFile('K', 0, i + 1);//�����¼����-------------------------------------WinID����ڿ�ʼ��Ϣ
				}
				/*
				���nowpas=null winhead->next!=null ��Ҫ������һ���˿�------------���޸�
				*/
				else if((Win[i].NowPas==NULL)&&(Win[i].WinHead->next!=NULL))//û�����ڰ��쵫�������Ŷ�
				{
					Win[i].NowPas = Win[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
					Win[i].WinHead->next = Win[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
					Win[i].SerNum = Win[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
					time(&TimeNow);//��ȡ��ǰʱ��
					Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
					Win[i].TotalSer++;//����ĳ˿�������
					Win[i].TotalTime += Win[i].NowPas->TaskTime;//�������ʱ������					
				}
				else if (Win[i].NowPas != NULL)//�������ڰ���
				{
					time(&TimeNow);//��ȡ��ǰʱ��
					if (TimeNow >= Win[i].SerTime)//�������
					{					
						EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����------------------------------------PasId�˿���ɰ���
						Win[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
					}
				}
				break;
			case ReadyClosWin: //����ڴ���׼���ر�״̬
				if ((Win[i].NowPas == NULL) && (Win[i].WinHead->next == NULL))//����ر�����
				/*
				Winhead->next=null Լ�ڻ�����----------------------������޸ģ��ⶼ���㷢����

				*/
				{
					Win[i].WinState = CloseWin;//�ı䰲���״̬Ϊ�ر�
					WinNum--;//�����������һ
					EventOutputFile('S', 0, i + 1);//�����¼����--------------------------------------WinID����ڹر�

				}
				/*
				���nowpas=null winhead->next!=null ��Ҫ������һ���˿�-----------���޸�
				*/
				else if ((Win[i].NowPas == NULL)&&(Win[i].WinHead->next != NULL))//û�����ڰ��쵫�������Ŷ�
				{
					Win[i].NowPas = Win[i].WinHead->next; //Ϊ��ͷ�˿Ͱ���
					Win[i].WinHead->next = Win[i].WinHead->next->next;//�ı��ͷ�˿�Ϊ�����һ��
					Win[i].SerNum = Win[i].NowPas->id;//Ϊ�����÷������Ϊ�˿�ID
					time(&TimeNow);//��ȡ��ǰʱ��
					Win[i].SerTime = TimeNow + Win[i].NowPas->TaskTime;//���ô˴ΰ������ʱ��
					Win[i].TotalSer++;//����ĳ˿�������
					Win[i].TotalTime += Win[i].NowPas->TaskTime;//�������ʱ������					
				}
				else if (Win[i].NowPas != NULL)//�������ڰ���
				{
					time(&TimeNow);//��ȡ��ǰʱ��
					if (TimeNow >= Win[i].SerTime)//�������
					{
						EventOutputFile('L', Win[i].NowPas->id, 0);//�����¼����-------------------------------------PasId�˿���ɰ���
						Win[i].NowPas = NULL;//���ñ�����˿�ָ��Ϊ��
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
			/*
			EventOutputFile('G',int PasID,int WinID);------------------------���޸�
			*/
			break;
		default: //������¼�
			RestOrClosWin(*event);//�������״̬����Ϊ׼����Ϣ���°�
			/*
			EventOutputFile('X',int PasID,int WinID);------------------------���޸�
			*/
			break;
		}
	}//if
	PreWinRun(); //���Ŷӻ������ĳ˿Ͳ��뵽�����
	/*
	EventOutputFile('C',int PasID,int WinID);-------------------------���޸� 
	*/
	WinRun();////����ڴ����˿ͼ����㰲���״̬ת��
	if (event->type == 'Q') //�յ��°�ָ��
	{
		AirportState= CheckWin();//�жϰ�����ܷ�ر�
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