#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "global.h"
#include "passenger.h"
#include "window.h" 

unsigned _stdcall KeyEvent(void * p)
{
	char c;
	srand(time(NULL));
	while (AirportState != OffWork&&AirportState != ShutDown)
	{

		c = _getch();
		while (lock !=0)
		{
			;
		}
		lock = 1;
		switch (c)
		{
		case 'g':
			thisEvent.type = 'G';
			thisEvent.mans = 1;
			thisEvent.check = 0;
			thisEvent.ev_valid = 0;
			printf("一名乘客到达\n");
			break;
		case 'x':
			thisEvent.type = 'X';
			thisEvent.check = rand() % 10 + 1;
			thisEvent.ev_valid = 0;
			printf("%d号安检口申请休息\n", thisEvent.check);
			break;
		case 'v':
			thisEvent.type = 'V';
			thisEvent.mans = 1;
			thisEvent.check = 0;
			thisEvent.ev_valid = 0;
			printf("一名VIP乘客到达\n");
			break;
		case 'q':
			_endthreadex(0);
			return 0;
			break;

		default:
			printf("无效输入\n");
			break;
		}
	}
	_endthreadex(0);
	return 0;


}