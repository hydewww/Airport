#include<time.h>
#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>

//2pi
#define TWOPI 2*3.1415926

#define OX 512
#define OY 300

#define asdf 4
#define qwer 1										
		
#define DialRadius 180
#define HourRadius 50
#define MinRadius 100	
#define SecRadius 150

#define ClockRadius 200


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
#define PI 3.1415926
#define StarRadius ClockRadius

//重置
void ResetStar(int i)
{
	int random = rand() % 180 +90;
	star[i].x = StarRadius*cos(random*2*PI / 360);
	star[i].y = StarRadius*sin(random*2*PI / 360);
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

//移动
void MoveStar()
{
	for (int i = 0; i < MAXSTAR; i++) {
		// 计算新位置
		star[i].x += star[i].step;
		if (star[i].x*star[i].x + star[i].y*star[i].y > StarRadius*StarRadius)
			ResetStar(i);

		// 画新星星
		putpixel((int)star[i].x, star[i].y, star[i].color);
	}
}

//初始化
void InitStar() {
	srand((unsigned)time(NULL));	// 随机种子
	for (int i = 0; i < MAXSTAR; i++)
	{
		ResetStar(i);
	}
}
//Kira^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//----------------------------------------------------------------------------------------------------------------tick tock
void DrawDial() {
	setfillcolor(WHITE);//设置刻度颜色
	for (int Angle = 0; Angle < 360; Angle += 6)//每隔6度画一个圆
	{
		if (Angle % 30 == 0)//每隔30度画一个大圆 半径为15
			fillcircle(DialRadius * cos(Angle*TWOPI / 360), DialRadius * sin(Angle*TWOPI / 360), asdf);
		else
			fillcircle(DialRadius * cos(Angle*TWOPI / 360), DialRadius * sin(Angle*TWOPI / 360), qwer);
	}
}
void DrawHand() {
	//获取当前时间
	time_t Time;
	struct tm * t;
	time(&Time);
	t = localtime(&Time);

	setlinecolor(WHITE);//设置表针颜色

	//秒
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 3);//设置线条风格
	line(0, 0, (int)(SecRadius * cos((t->tm_sec - 16)*TWOPI / 60)), (int)(SecRadius * sin((t->tm_sec - 16)*TWOPI / 60)));
	//分 
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 10);
	line(0, 0, (int)(MinRadius * cos((t->tm_min - 16)*TWOPI / 60)), (int)(MinRadius * sin((t->tm_min - 16)*TWOPI / 60)));
	//时
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 15);
	int hour;
	if ((hour = t->tm_hour) > 12)
		hour -= 12;
	line(0, 0, (int)(HourRadius * cos(((hour - 3)*TWOPI / 12 + (TWOPI / 12)*(t->tm_min - 15) / 60))), (int)(HourRadius * sin(((hour - 3)*TWOPI / 12 + (TWOPI / 12)*(t->tm_min - 15) / 60))));

	//还原
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 1);
}

void DrawClock()
{
	DrawDial();//画表盘
	DrawHand();//画表针
}
//tick tock^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int main() {
	initgraph(1500, 800);
	setbkcolor(WHITE);
	cleardevice();

	setorigin(OX, OY);
	InitStar();
	while (1) {
		setfillcolor(BLACK);
		fillcircle(0, 0, ClockRadius);
		MoveStar();
		DrawClock();
		Sleep(50);
	}
	//DrawStar();
	//DrawClock();
	getch();
}