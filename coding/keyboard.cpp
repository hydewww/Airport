//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//#include "global.h"
//#include "passenger.h"
//#include "window.h" 
//
//unsigned _stdcall KeyEvent(void * p)
//{
//	char c;
//	srand(time(NULL));
//	while (AirportState != OffWork&&AirportState != ShutDown)
//	{
//
//		if (kbhit())
//		{
//			c = _getch();
//			while (lock != 0)
//			{
//				;
//			}
//			lock = 1;
//			switch (c)
//			{
//			case 'g':
//				thisEvent.type = 'G';
//				thisEvent.mans = 1;
//				thisEvent.check = 0;
//				thisEvent.ev_valid = 0;
//				printf("һ���˿͵���\n");
//				EnLineCache++;
//				break;
//			case 'x':
//				thisEvent.type = 'X';
//				thisEvent.check = rand() % 10 + 1;
//				thisEvent.ev_valid = 0;
//				break;
//			case 'v':
//				thisEvent.type = 'V';
//				thisEvent.mans = 1;
//				thisEvent.check = 0;
//				thisEvent.ev_valid = 0;
//				printf("һ��VIP�˿͵���\n");
//				break;
//			case 'q':
//				thisEvent.type = 'Q';
//				thisEvent.ev_valid = 0;
//				printf("������Ҫ�°�\n");
//				_endthreadex(0);
//				return 0;
//				break;
//			case 'w':
//				thisEvent.type = 'G';
//				thisEvent.ev_valid = 0;
//				thisEvent.mans = 1;
//				thisEvent.check = 4;
//				printf("һ��Ǳ��Σ�ճ˿͵���\n");
//				break;
//			default:
//				printf("��Ч����\n");
//				break;
//			}
//		}
//	}
//	_endthreadex(0);
//	return 0;
//
//
//}