#include<time.h>
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
#include"global.h"
//two pi
#define TWOPI 2*3.1415926

#define OX 1370
#define OY 130

#define asdf 4
#define qwer 1									

#define DialRadius 90
#define HourRadius 25
#define MinRadius 50
#define SecRadius 75

#define ClockRadius 100


struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};
#define MAXSTAR 200
STAR star[MAXSTAR];

//-------------------------------------------------------------------------------------------------------------------Kira
#define StarRadius ClockRadius

//����
void ResetStar(int i)
{

	int random = rand() % 180+180;
	star[i].x = StarRadius*cos(random *TWOPI / 360);
	star[i].y = StarRadius*sin(random * TWOPI / 360);
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬��ɫԽ��
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);

}

//�ƶ�
void MoveStar()
{
	setorigin(OX, OY);
	for (int i = 0; i < MAXSTAR; i++) {
		// ������λ��
		star[i].y += star[i].step;
		if (star[i].x*star[i].x + star[i].y*star[i].y > StarRadius*StarRadius)
			ResetStar(i);

		// ��������
		putpixel((int)star[i].x, star[i].y, star[i].color);
	}
	setorigin(0, 0);
}

//��ʼ��
void InitStar() {
	setorigin(OX, OY);
	srand((unsigned)time(NULL));	// �������
	for (int i = 0; i < MAXSTAR; i++)
	{
		ResetStar(i);
		star[i].y += rand() % (StarRadius * 2);
	}
	setorigin(0, 0);
}
//Kira^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//----------------------------------------------------------------------------------------------------------------tick tock
void DrawDial() {
	setorigin(OX, OY);
	setlinecolor(BLACK);
	setcolor(BLACK);
	setfillcolor(WHITE);//���ÿ̶���ɫ
	for (int Angle = 0; Angle < 360; Angle += 6)//ÿ��6�Ȼ�һ��Բ
	{
		if (Angle % 30 == 0)//ÿ��30�Ȼ�һ����Բ �뾶Ϊ15
			fillcircle(DialRadius * cos(Angle*TWOPI / 360), DialRadius * sin(Angle*TWOPI / 360), asdf);
		else
			fillcircle(DialRadius * cos(Angle*TWOPI / 360), DialRadius * sin(Angle*TWOPI / 360), qwer);
	}
	setorigin(0, 0);
	setcolor(WHITE);
}
void DrawHand() {
	setorigin(OX, OY);

	//��ȡ��ǰʱ��
	time_t Time;
	struct tm * t;
	time(&Time);
	t = localtime(&Time);

	setlinecolor(WHITE);//���ñ�����ɫ

	//��
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1);//�����������
	line(0, 0, (int)(SecRadius * cos((t->tm_sec - 16)*TWOPI / 60)), (int)(SecRadius * sin((t->tm_sec - 16)*TWOPI / 60)));
	//�� 
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 2);
	line(0, 0, (int)(MinRadius * cos((t->tm_min - 16)*TWOPI / 60)), (int)(MinRadius * sin((t->tm_min - 16)*TWOPI / 60)));
	//ʱ
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 4);
	int hour;
	if ((hour = t->tm_hour) > 12)
		hour -= 12;
	line(0, 0, (int)(HourRadius * cos(((hour - 3)*TWOPI / 12 + (TWOPI / 12)*(t->tm_min - 15) / 60))), (int)(HourRadius * sin(((hour - 3)*TWOPI / 12 + (TWOPI / 12)*(t->tm_min - 15) / 60))));

	//��ԭ
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1);
	setorigin(0, 0);
}

void DrawClock()
{
	DrawDial();//������
	DrawHand();//������
}
//tick tock^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void StarClock() {
	setorigin(OX, OY);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	setcolor(BLACK);
	fillcircle(0, 0, ClockRadius);
	MoveStar();
	DrawClock();
	setorigin(0, 0);
}




/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>final*/
//����WINDOWS_X,WINDOWS_Y
#define MAXStar 500
STAR Star[MAXStar];
void ResetFinalStar(int i)
{
	Star[i].x = rand() % WINDOWS_X;
	Star[i].y = 0;
	Star[i].step = (rand() % 5000) / 1000.0 + 1;
	Star[i].color = (int)(Star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬��ɫԽ��
	Star[i].color = RGB(Star[i].color, Star[i].color, Star[i].color);

}

//�ƶ�
void MoveFinalStar()
{
	for (int i = 0; i < MAXStar; i++) {
		putpixel((int)Star[i].x, Star[i].y, BLACK);
		// ������λ��
		Star[i].y += Star[i].step;
		if (Star[i].y > WINDOWS_Y)
			ResetFinalStar(i);
		
		// ��������
		putpixel((int)Star[i].x, Star[i].y, Star[i].color);
	}
}

//��ʼ��
void InitFinalStar() {
	srand((unsigned)time(NULL));	// �������
	for (int i = 0; i < MAXStar; i++)
	{
		ResetFinalStar(i);
		Star[i].y += rand() % WINDOWS_Y;
	}
}
