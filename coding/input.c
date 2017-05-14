#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 5 //时间的最大发生间隔（以秒为单位）
#define	OneOutOfTen 1 + rand() % 100 > 90	//10%为安检口申请休息的概率
#define MaxCrown 10 //一次性最大人数 

void MainInput();
void AirportOnServe();
double random();

double random()  //正态分布生成函数
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
			event[i].sec = (int)(random() * MaxGapTime + 1); //用正态分布产生从1到MaxGapTime的时间间隔

			if (OneOutOfTen) {		//10%的概率为关闭安检口
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
		printf("文件打开失败，请重启程序");
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
