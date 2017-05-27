#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 5 //事件的最大发生间隔（以秒为单位）
#define	OneOutOfTen (1 + rand() % 100) > 90	//10%为安检口申请休息的概率
#define MaxCrown 20 //一次性最大人数 
#define MaxVIPCrown 3//一次VIP事件最大人数
#define pi 3.1415926
#define e 2.71828
#define PROBABILITY_OF_VIP 0.7

entry thisEvent;
int MaxCheck;
int entryno = 0;

void MainInput();
void AirportOnServe();
double random(int,int);

double random(int now,int total)     //用Box_Muller算法产生高斯分布的随机数
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

int InputInt(int* num) {
	if (scanf("%d", num)) {
		while (getchar() != '\n');//清空缓冲区
		return 0;
	}
	printf("【请输入正确的数字！】\n\n");
	while (getchar() != '\n');
	return 1;
}

void MainInput() {

	int x = 100;
	for (int i = 0; i < x; i++) {
		printf("%f\n", random(i, x));
	}
	int EventNum;
	do {
		printf("输入事件个数：");
	} while (InputInt(&EventNum));
	FILE *finput = fopen("input.dat", "wb+");
	
	entry* event = (entry*)malloc(EventNum * sizeof(entry));
	if (finput) {
		srand(time(NULL));
		for (int i = 0; i < EventNum-1; i++) {

			event[i].no = i;
			event[i].sec = ((int)(random(i,EventNum) * MaxGapTime + 1) % MaxGapTime)+1; //用正态分布产生从1到MaxGapTime的时间间隔

			if (OneOutOfTen) {		//10%的概率为休息安检口
				event[i].type = 'X';
				event[i].check = 1 + rand() % NumOfWin;
				event[i].mans = 0;
			}
			else {  
				if (random(i,EventNum) > PROBABILITY_OF_VIP) {
					event[i].type = 'V';
					event[i].mans = ((int)(random(i,EventNum) * MaxVIPCrown + 1) % MaxVIPCrown);
					event[i].check = 0;
				}
				else  if (random(i,EventNum)>0.60) //危险乘客
				{
					event[i].type = 'G';
					event[i].mans = 1;
					event[i].check = 4; //扣留标志
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
		printf("文件打开失败，请重启程序");
		exit(1);
	}
	fclose(finput);
}

void AirportOnServe()
{
	//static int entryno = 0;
	static time_t TimeLastEvent;

	FILE *finput = fopen("input.dat", "rb");
	if (finput == NULL)
	{
		printf("读取事件文件失败");
		exit(1);
	}
	
	if (entryno == 0 || time(&TimeNow) >= TimeLastEvent)
	{
		fseek(finput, entryno * sizeof(entry), SEEK_SET);
		fread(&thisEvent, sizeof(entry), 1, finput);
		TimeLastEvent = time(&TimeNow) + thisEvent.sec;
		entryno++;
	}
	fclose(finput);
}
