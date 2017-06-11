#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 10 //�¼�����������������Ϊ��λ��
#define MaxCrown 20 //һ����������� 
#define MaxVIPCrown 5//һ��VIP�¼��������
#define pi 3.1415926
#define e 2.71828
#define	PROBABILITY_OF_REST  10	//10%Ϊ�����������Ϣ�ĸ���
#define PROBABILITY_OF_VIP 20	//vip�˿����ɸ���Ϊ20%
#define PROBABILITY_OF_DANGEROURS 10 //Σ�ճ˿����ɸ���10%

entry thisEvent;
int   MaxCheck;
int   entryno = 0;

void   MainInput();
void   AirportOnServe();
double random(int,int);

double random(int now,int total)     //���¼��ŷֲ�����̬����
{
	double N;
	double sigama = 1;
	double x = (double)(now) / total * 6*sigama;
	double mu = 3;
	double z;

	z = -pow(x - mu, 2) /( 2 * pow(sigama, 2));
	N = (1 / ((sqrt(2 * pi))*sigama)) * pow(e,z);

	return 2*N;
}

int InputInt(int* num) {		//��ȷ�������ֵĺ���
	if (scanf("%d", num)) {
		while (getchar() != '\n');//��ջ�����
		return 0;
	}
	printf("����������ȷ�����֣���\n\n");
	while (getchar() != '\n');
	return 1;
}

void MainInput() {

	FILE *finput = fopen("input.dat", "wb+");
	
	entry* event = (entry*)malloc(EventNum * sizeof(entry));
	if (finput) {
		srand(time(NULL));
		for (int i = 0; i < EventNum-1; i++) {

			event[i].no = i;
			event[i].sec = ((int)(random(i,EventNum) * MaxGapTime + 1) % MaxGapTime)+1; //����̬�ֲ�������1��MaxGapTime��ʱ����

			if ((1 + rand() % 100) < PROBABILITY_OF_REST) {		//10%�ĸ���Ϊ��Ϣ�����
				event[i].type = 'X';
				event[i].check = 1 + rand() % NumOfWin;
				event[i].mans = 0;
			}
			else {  
				if ((1 + rand() % 100) < PROBABILITY_OF_VIP) {  //VIP�˿�����
					event[i].type = 'V';
					event[i].mans = ((int)(random(i,EventNum) * MaxVIPCrown + 1) % MaxVIPCrown);
					event[i].check = 0;
				}
				else  if ((1 + rand() % 100) < PROBABILITY_OF_DANGEROURS) //Σ�ճ˿�
				{
					event[i].type = 'G';
					event[i].mans = 1;
					event[i].check = 4; //������־
				}
				else
				{
					event[i].type = 'G';
					event[i].mans = ((int)(random(i,EventNum) * MaxCrown + 1) % MaxCrown);
					event[i].check = 0;
				}
			}
			event[i].ev_valid = 0;
		}
		event[EventNum-1].type = 'Q';
		event[EventNum - 1].ev_valid = 0;
		event[EventNum - 1].sec = 100000;
		fwrite(event, sizeof(entry), EventNum, finput);
	}
	else {
		printf("�ļ���ʧ�ܣ�����������");
		exit(EXIT_FAILURE);
	}
	fclose(finput);
}

void AirportOnServe()  //����������״̬�ǰ���ʱ��������ʱ��
{
	static time_t TimeLastEvent;

	FILE *finput = fopen("input.dat", "rb");
	if (finput == NULL)
	{
		printf("��ȡ�¼��ļ�ʧ��");
		exit(EXIT_FAILURE);
	}
	if (lock == 0)
	{
		if((AirportState != ShutDown)&& (entryno == 0 || time(&TimeNow) >= TimeLastEvent))
		{
			fseek(finput, entryno * sizeof(entry), SEEK_SET);
			fread(&thisEvent, sizeof(entry), 1, finput);
			TimeLastEvent = time(&TimeNow) + thisEvent.sec;
			entryno++;
		}
		lock = 1;
	}
	else
	{
		Sleep(100);
	}
	fclose(finput);
}
