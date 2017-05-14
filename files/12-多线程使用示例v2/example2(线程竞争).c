#include<stdio.h>
#include<windows.h>
#include <process.h> 

int index=0;
unsigned __stdcall Fun1Proc(void* pArguments)
{
	while(index++<500)
	{
		printf("hThreadl is running\n");
	}

    _endthreadex(0);	
	return 0;
}
int main()
{
    HANDLE hThread1;
    hThread1 =(HANDLE)_beginthreadex(NULL,0,Fun1Proc,NULL,0,NULL);
	//hThreadl=CreateThread(NULL,0,Fun1Proc,NULL,0,NULL); 

	while(index++<500)
	{
		printf("main thread is running\n");		
	}

    WaitForSingleObject(hThread1,INFINITE);
	CloseHandle(hThread1);

	system("pause");
	return 0;
}
