#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 10 //事件的最大发生间隔（以秒为单位）
#define MaxCrown 20 //一次性最大人数 
#define MaxVIPCrown 5//一次VIP事件最大人数
#define pi 3.1415926
#define e 2.71828
#define	PROBABILITY_OF_REST  10	//10%为安检口申请休息的概率
#define PROBABILITY_OF_VIP 20	//vip乘客生成概率为20%
#define PROBABILITY_OF_DANGEROURS 10 //危险乘客生成概率10%

entry thisEvent;
int   MaxCheck;
int   entryno = 0;

void   MainInput();
void   AirportOnServe();
double random(int,int);

double random(int now,int total)     //按事件号分布的正态函数
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

int InputInt(int* num) {		//正确输入数字的函数
	if (scanf("%d", num)) {
		while (getchar() != '\n');//清空缓冲区
		return 0;
	}
	printf("【请输入正确的数字！】\n\n");
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
			event[i].sec = ((int)(random(i,EventNum) * MaxGapTime + 1) % MaxGapTime)+1; //用正态分布产生从1到MaxGapTime的时间间隔

			if ((1 + rand() % 100) < PROBABILITY_OF_REST) {		//10%的概率为休息安检口
				event[i].type = 'X';
				event[i].check = 1 + rand() % NumOfWin;
				event[i].mans = 0;
			}
			else {  
				if ((1 + rand() % 100) < PROBABILITY_OF_VIP) {  //VIP乘客生成
					event[i].type = 'V';
					event[i].mans = ((int)(random(i,EventNum) * MaxVIPCrown + 1) % MaxVIPCrown);
					event[i].check = 0;
				}
				else  if ((1 + rand() % 100) < PROBABILITY_OF_DANGEROURS) //危险乘客
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
		exit(EXIT_FAILURE);
	}
	fclose(finput);
}

void AirportOnServe()  //机场在运行状态是按照时间间隔读入时间
{
	static time_t TimeLastEvent;

	FILE *finput = fopen("input.dat", "rb");
	if (finput == NULL)
	{
		printf("读取事件文件失败");
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
