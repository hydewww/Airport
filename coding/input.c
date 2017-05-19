#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "passenger.h"
#include "window.h"
#include<math.h>

#define MaxGapTime 5 //时间的最大发生间隔（以秒为单位）
#define	OneOutOfTen 1 + rand() % 100 > 90	//10%为安检口申请休息的概率
#define MaxCrown 10 //一次性最大人数 
#define EventNum 10
#define pi 3.1415926
#define e 2.718
entry thisEvent;
int MaxCheck;

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
	return (x / 6);
}

void MainInput() {
		
	FILE *finput = fopen("input.dat", "wb+");
	
	entry event[EventNum];
	if (finput) {
		for (int i = 0; i < EventNum; i++) {

			event[i].no = i;
			event[i].sec = (int)(random() * MaxGapTime + 1); //用正态分布产生从1到MaxGapTime的时间间隔

			if (OneOutOfTen) {		//10%的概率为关闭安检口
				event[i].type = 'X';
				event[i].check = 1 + rand() % NumOfWin;
				event[i].mans = 0;
			}
			else {
				event[i].type = 'G';
				event[i].mans = (int)(random() * MaxCrown + 1);
				event[i].check = 0;
			}
			event[i].ev_valid = 0;
		}
		event[EventNum-1].type = 'Q';
		fwrite(&event, sizeof(entry), EventNum, finput);
	}
	else {
		printf("文件打开失败，请重启程序");
		exit(EXIT_FAILURE);//---------------------------------------------------------出错
	}
	fclose(finput);
}

void AirportOnServe() {
	static int i = 0;
	time_t time_pre_ev = TimeStart;
	time_t temtime;
	FILE *finput = fopen("input.dat", "rb");
	fseek(finput, i++ * sizeof(entry), SEEK_SET);
	if (finput == NULL) {
		printf("ERROR");
		exit(1);
	}
	fread(&thisEvent, sizeof(entry), 1, finput);
	time_t test = time(&temtime);
	
	if (test> thisEvent.sec + time_pre_ev) {
		time(&time_pre_ev) ;
		fread(&thisEvent, sizeof(entry), 1, finput);
	}
	fclose(finput);
}
