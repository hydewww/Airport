/*程序功能：创建两个线程，一个用于从键盘接收输入字符保存到全局变量里，
，另一个将全局变量里的字符输出到文件*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h> 

unsigned __stdcall getInput(void* pArguments); 
unsigned __stdcall output(void* pArguments); 

char ch='A';
    
int main()
{
   //创建线程1：用于从键盘接收字符，写入到全局变量ch中    
   unsigned ThreadID1 = 1;
   HANDLE hRead1 =(HANDLE)_beginthreadex(NULL,0,getInput,NULL,0,&ThreadID1);  
//   HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//创建接收输入的线程
  
  //创建线程2：用于将全局变量ch写入文件 
   unsigned ThreadID2 = 2;
   HANDLE hRead2 =(HANDLE)_beginthreadex(NULL,0,output,NULL,0,&ThreadID2);  
//   HANDLE hRead2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output,NULL,0,&ThreadID2);//创建接收输入的线程 

   WaitForSingleObject(hRead1,INFINITE);	
   CloseHandle(hRead1);
   WaitForSingleObject(hRead2,INFINITE);	
   CloseHandle(hRead2);

   system("PAUSE");	
   return 0;
}

unsigned __stdcall getInput(void* pArguments)
{  
   //int i=0; 
   while(ch!='q'){ 
      printf("input a char\n");      
      ch=getchar();
      getchar();//吃掉\n 
      //fflush(stdin);
   }   
    _endthreadex(0);	
    return 0;    
}

unsigned __stdcall output(void* pArguments)
{
    int i=0;
    FILE * cfPtr=NULL;
    
    if( (cfPtr=fopen("data.txt","w"))==NULL)
       printf("can't open file\n"); 
    else{   
            while(ch!='q'){            
               Sleep(500); //延迟 ,注意Sleep()函数第一个字母大写，如果是小写，在此版本下会导致线程无法唤醒。 
               fputc(ch,cfPtr);  //写文件 
           }//end while i
           fclose(cfPtr);
    }//end else    
    _endthreadex(0);	
    return 0;    
}
