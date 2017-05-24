#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "global.h"
#include "passenger.h"
#include "window.h"

#define MaxGapTime 5 //事件的最大发生间隔（以秒为单位）
#define	OneOutOfTen (1 + rand() % 100) > 90	//10%为安检口申请休息的概率
#define MaxCrown 10 //一次性最大人数 
#define MaxVIPCrown 3//一次VIP事件最大人数
#define pi 3.1415926
#define e 2.71828
#define PROBABILITY_OF_VIP 0.70
//#define EventNum 10

entry thisEvent;
int MaxCheck;
int entryno = 0;

void MainInput();
void AirportOnServe();
double random();

double random()     //用Box_Muller算法产生高斯分布的随机数
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
		while (getchar() != '\n');//清空缓冲区
		return 0;
	}
	printf("【请输入正确的数字！】\n\n");
	while (getchar() != '\n');
	return 1;
}

void MainInput() {

	int EventNum;
	do {
		printf("输入事件个数：");
	} while (InputInt(&EventNum));
	FILE *finput = fopen("input.dat", "wb+");
	
	//entry event[EventNum];
	entry* event = (entry*)malloc(EventNum * sizeof(entry));
	if (finput) {
		srand(time(NULL));
		for (int i = 0; i < EventNum-1; i++) {

			event[i].no = i;
			event[i].sec = ((int)(random() * MaxGapTime + 1) % MaxGapTime)+1; //用正态分布产生从1到MaxGapTime的时间间隔

			if (OneOutOfTen) {		//10%的概率为关闭安检口
				event[i].type = 'X';
				event[i].check = 1 + rand() % NumOfWin;
				event[i].mans = 0;
			}
			else {
				if (random() > PROBABILITY_OF_VIP) {
					event[i].type = 'V';
					event[i].mans = ((int)(random() * MaxVIPCrown + 1) % MaxVIPCrown);
				}
				else
				{
					event[i].type = 'G';
					event[i].mans = ((int)(random() * MaxCrown + 1) % MaxCrown);
				}
				event[i].check = 0;
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
	//time_t time_pre_ev = TimeStart;
	//time_t temtime;

	FILE *finput = fopen("input.dat", "rb");
	if (finput == NULL)
	{
		printf("finput空了少年！");
		exit(1);
	}
	
	if (entryno == 0 || time(&TimeNow) >= TimeLastEvent)
	{
		fseek(finput, entryno * sizeof(entry), SEEK_SET);
		fread(&thisEvent, sizeof(entry), 1, finput);
		TimeLastEvent = time(&TimeNow) + thisEvent.sec;
		entryno++;
	}
	//printf("现在正在发生第%d个事件\n",entryno);
	fclose(finput);
}
