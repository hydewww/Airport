#include <stdio.h>
#include <stdlib.h>
//#include<time.h>
#include <windows.h>
#include <process.h> 
//这个例子用来解决多线程间存在数据依赖的问题，如何顺序启动，在满足依赖关系后启动。 

int data=0; //线程间共享数据 
unsigned __stdcall input(void* pArguments);
unsigned __stdcall output(void* pArguments);

main()
{
  long int i=0;
  unsigned ThreadID1,ThreadID2;
  HANDLE hRead1,hOut1;
  
  ThreadID1=1;
  hRead1 =(HANDLE)_beginthreadex(NULL,0,input,NULL,0,&ThreadID1);

  while (data==0)
  {
      i++;  
  }
  printf("i=%d\n",i);
  if (data==1)
  {
     ThreadID2=2;
     hOut1 =(HANDLE)_beginthreadex(NULL,0,output,NULL,0,&ThreadID2);
  }  
  WaitForSingleObject(hOut1,INFINITE);
  printf("output thread passed! data=%d\n",data);
  CloseHandle(hRead1);
  CloseHandle(hOut1);
  system("PAUSE");	
  return 0;
} 

unsigned __stdcall input(void* pArguments)
{
     Sleep(1000);
     data=1;
     Sleep(5000);
     
     _endthreadex(0);

     return 0;
} 

unsigned __stdcall output(void* pArguments)
{
     data++;
     Sleep(2000);     

     _endthreadex(0);
     return 0;
}
