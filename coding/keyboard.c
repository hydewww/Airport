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
	while (1)
	{
		if (lock == 0 && thisEvent.ev_valid == 1)
		{
			lock = 1;
			c = _getch();
			{
				switch (c)
				{
				case 'g':
					thisEvent.type = 'G';
					thisEvent.mans = 1;
					thisEvent.check = 0;
					thisEvent.ev_valid = 0;
					printf("һ���˿͵���\n");
					break;
				case 'x':
					thisEvent.type = 'X';
					thisEvent.check = rand() % 10 + 1;
					thisEvent.ev_valid = 0;
					printf("%d�Ű����������Ϣ\n", thisEvent.check);
					break;
				default:
					printf("ɶҲû����\n");
					break;
				}
			}
			lock = 0;
		}
	}
	_endthreadex(0);
	return 0;


}