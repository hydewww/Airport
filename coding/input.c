#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 5 //�¼�����������������Ϊ��λ��
#define	OneOutOfTen (1 + rand() % 100) > 90	//10%Ϊ�����������Ϣ�ĸ���
#define MaxCrown 11 //һ����������� 
#define MaxVIPCrown 3//һ��VIP�¼��������
#define pi 3.1415926
#define e 2.71828
#define PROBABILITY_OF_VIP 0.7
//#define EventNum 10

entry thisEvent;
int MaxCheck;
int entryno = 0;

void MainInput();
void AirportOnServe();
double random();

double random()     //��Box_Muller�㷨������˹�ֲ��������
{
	double u = 3, N = 1;
	double r, t, z, x;
	double s1, s2;
	s1 = (1.0 + rand()) / (RAND_MAX + 1.0);
	s2 = (1.0 + rand()) / (RAND_MAX + 1.0);
	r = sqrt(-2 * log(s2) / log(e));
	t = 2 * pi*s1;
	z = r*cos(t);
	x = u + z*N;
	x /= 6;
	if (x > 1) {
		x -= 1;
	}
	else if(x < 0) {
		x += 1;
	}
	return x;
}

int InputInt(int* num) {
	if (scanf("%d", num)) {
		while (getchar() != '\n');//��ջ�����
		return 0;
	}
	printf("����������ȷ�����֣���\n\n");
	while (getchar() != '\n');
	return 1;
}

void MainInput() {

	int EventNum;
	do {
		printf("�����¼�������");
	} while (InputInt(&EventNum));
	FILE *finput = fopen("input.dat", "wb+");
	
	//entry event[EventNum];
	entry* event = (entry*)malloc(EventNum * sizeof(entry));
	if (finput) {
		srand(time(NULL));
		for (int i = 0; i < EventNum-1; i++) {

			event[i].no = i;
			event[i].sec = ((int)(random() * MaxGapTime + 1) % MaxGapTime)+1; //����̬�ֲ�������1��MaxGapTime��ʱ����

			if (OneOutOfTen) {		//10%�ĸ���Ϊ��Ϣ�����
				event[i].type = 'X';
				event[i].check = 1 + rand() % NumOfWin;
				event[i].mans = 0;
			}
			else {  
				if (random() > PROBABILITY_OF_VIP) {
					event[i].type = 'V';
					event[i].mans = ((int)(random() * MaxVIPCrown + 1) % MaxVIPCrown);
					event[i].check = 0;
				}
				else  if (random()>0.60) //Σ�ճ˿�
				{
					event[i].type = 'G';
					event[i].mans = 1;
					event[i].check = 4; //������־
				}
				else
				{
					event[i].type = 'G';
					event[i].mans = ((int)(random() * MaxCrown + 1) % MaxCrown);
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
		exit(1);
	}
	fclose(finput);
}

void AirportOnServe()
{
	//static int entryno = 0;
	static time_t TimeLastEvent;
	//time_t time_pre_ev = TimeStart;
	//time_t temtime;

	FILE *finput = fopen("input.dat", "rb");
	if (finput == NULL)
	{
		printf("finput�������꣡");
		exit(1);
	}
	
	if (entryno == 0 || time(&TimeNow) >= TimeLastEvent)
	{
		fseek(finput, entryno * sizeof(entry), SEEK_SET);
		fread(&thisEvent, sizeof(entry), 1, finput);
		TimeLastEvent = time(&TimeNow) + thisEvent.sec;
		entryno++;
	}
	//printf("�������ڷ�����%d���¼�\n",entryno);
	fclose(finput);
}
