#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 5 //ʱ�����������������Ϊ��λ��
#define	OneOutOfTen 1 + rand() % 100 > 90	//10%Ϊ�����������Ϣ�ĸ���
#define MaxCrown 10 //һ����������� 

void MainInput();
void AirportOnServe();
double random();

double random()  //��̬�ֲ����ɺ���
{
	double U1, U2, W, mult;
	static double X1, X2;
	static int call = 0;
	int mu = 0;
	int sigma = 1;

	srand(time(NULL));

	if (call == 1)
	{
		call = !call;
		return (mu + sigma * (double)X2);
	}

	do
	{
		U1 = -1 + ((double)rand() / RAND_MAX) * 2;
		U2 = -1 + ((double)rand() / RAND_MAX) * 2;
		W = pow(U1, 2) + pow(U2, 2);
	} while (W >= 1 || W == 0);

	mult = sqrt((-2 * log(W)) / W);
	X1 = U1 * mult;
	X2 = U2 * mult;

	call = !call;

	return fabs((mu + sigma * (double)X1) / 3);
}

void MainInput() {
		
	FILE *finput = fopen("input.dat", "wb+");
	
	struct entry event[100];
	if (finput) {
		for (int i = 0; i < 99; i++) {

			event[i].no = i;
			event[i].sec = (int)(random() * MaxGapTime + 1); //����̬�ֲ�������1��MaxGapTime��ʱ����

			if (OneOutOfTen) {		//10%�ĸ���Ϊ�رհ����
				event[i].type = 'X';
				event[i].check = 1 + rand() % MaxCheck;
				event[i].mans = 0;
			}
			else {
				event[i].type = 'G';
				event[i].mans = (int)(random() * MaxCrown + 1);
				event[i].check = 0;
			}
			event[i].ev_valid = 0;
		}
		event[99].type = 'Q';
		fwrite(&event, sizeof(struct entry), 100, finput);
	}
	else {
		printf("�ļ���ʧ�ܣ�����������");
		exie(EXIT_FAILURE);
	}
	fclose(finput);
}

void AirportOnServe() {
		
	time_t time_pre_ev = TimeStart;
	time_t temtime;
	FILE *finput = fopen("input.dat", "rb+");

	extern struct entry thisEvent;

	fread(&thisEvent, sizeof(struct entry), 1, "finput");
	if (time(&temtime)> thisEvent.sec + time_pre_ev) {
		time_pre_ev = clock();
		fread(&thisEvent, sizeof(struct entry), 1, "finput");
	}
}
