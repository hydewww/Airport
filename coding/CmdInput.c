#include<stdio.h>
#include<stdlib.h>
#include"global.h"
unsigned __stdcall CmdInput(void* pArguments){
	if (new_sign) {
		new_sign = 0;
		char ch;
		struct entry event1;
		fflush(stdin);
		ch = getchar();
		if (ch == 'G') {
			event1.type = 'G';
			event1.mans = 1;
		}
		else if (ch == 'Q') {
			event1.type = 'Q';
		}
		else if (ch >= '1'&&ch <= MaxCheck + '0') {
			event1.type = 'X';
			event1.check = ch - '0';
		}
		else {
			event1.type = NULL;
		}
	}
	_endthreadex(0);
	return 0;
}