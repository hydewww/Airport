#include<stdio.h>
#include<windows.h>
#include <process.h> 

unsigned __stdcall Fun1Proc(void* pArguments)
{
	printf("hThreadl is running\n");

     _endthreadex(0);
	return 0;
}

int main()
{
	HANDLE hThread1;
	
    hThread1 =(HANDLE)_beginthreadex(NULL,0,Fun1Proc,NULL,0,NULL);
	//hThreadl=CreateThread(NULL,0,Fun1Proc,NULL,0,NULL); 

	printf("main thread is running\n"); 

    WaitForSingleObject(hThread1,INFINITE);
	CloseHandle(hThread1);

	system("pause");
	return 0;
}
