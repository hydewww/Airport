#include<stdio.h>
#include<windows.h>
#include <process.h> 

int tickets=100;

unsigned __stdcall Fun1Proc(void* pArguments)
{
	while(tickets>0)
	{
		printf("thread1 sell ticket : %d\n",tickets--);
	}
	
    _endthreadex(0);	
	return 0;
}

unsigned __stdcall Fun2Proc(void* pArguments)
{
	while(tickets>0)
	{
		printf("thread2 sell ticket : %d\n",tickets--);
	}
    _endthreadex(0);	
	return 0;
}

int main()
{
    HANDLE hThread1 =(HANDLE)_beginthreadex(NULL,0,Fun1Proc,NULL,0,NULL);
    HANDLE hThread2 =(HANDLE)_beginthreadex(NULL,0,Fun2Proc,NULL,0,NULL);
    
	//HANDLE hThread1=CreateThread(NULL,0,Fun1Proc,NULL ,0,NULL);
	//HANDLE hThread2=CreateThread(NULL,0,Fun2Proc,NULL ,0,NULL);
	
    WaitForSingleObject(hThread2,INFINITE);	
	CloseHandle(hThread2);
    WaitForSingleObject(hThread1,INFINITE);
	CloseHandle(hThread1);
	//Sleep(4000);
	system("pause");
	return 0;
}
