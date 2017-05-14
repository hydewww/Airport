/*程序功能：创建两个线程，一个用于从键盘接收输入字符保存到全局变量里，
，另一个将全局变量里的字符输出到文件*/

#include <stdio.h>
#include <stdlib.h>

//使用线程编程时，下面这两个头文件必须包含 
#include <winsock.h>
#include <winbase.h>

//void getInput(void); 
void getInput(char *); 
void output(void); 


int main()
{
   int i; 
   char ch='A';
       
   //DWORD ThreadID1 = 1;
   //HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//创建接收输入的线程
   DWORD ThreadID1 = 1;
   HANDLE hRead1 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)getInput,(LPVOID)&ch,0,&ThreadID1);//创建接收输入的线程
   
   DWORD ThreadID2 = 2;
   //HANDLE hRead2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output,NULL,0,&ThreadID2);//创建接收输入的线程
   HANDLE hRead2 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)output,(LPVOID)(&ch),0,&ThreadID2);//创建接收输入的线程
  
   WaitForSingleObject(hRead1,INFINITE);
   WaitForSingleObject(hRead2,INFINITE);
   CloseHandle(hRead1);
   CloseHandle(hRead2);
     
   system("PAUSE");	
   return 0;
}
