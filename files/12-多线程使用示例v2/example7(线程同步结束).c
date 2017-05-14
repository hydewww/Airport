//这个例子用来解释,如何让子线程和主线程按照约定的条件,同时结束. 
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <windows.h>
#include <process.h> 

unsigned __stdcall control(void* pArguments); 

int exsign=0; //退出标记 

main()
{
   long int i;
   unsigned ThreadID1 = 1;
   HANDLE hRead1 =(HANDLE)_beginthreadex(NULL,0,control,NULL,0,&ThreadID1);  
//  DWORD ThreadID1 = 1;
//  HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)control,NULL,0,&ThreadID1);

   WaitForSingleObject(hRead1,INFINITE);	
   CloseHandle(hRead1);

//  while (exsign==0) i++;
   system("PAUSE");	
   return 0;
} 

unsigned __stdcall control(void* pArguments)
{
         int T=1,t=0;
         int num=0;
         while (num<=20)
         {
               sleep(998);
               t++;
               printf("t=%d\n",t);
               if(t == 6){
                    T =1;
                    t = 0;
               }
               T++;
               printf("T=%d\n",T);
	           if(T == 6){
                    T = 0;
                    t = 1;
               }
               num++;
         }
         exsign=1;

    _endthreadex(0);	
    return 0;        
} 
