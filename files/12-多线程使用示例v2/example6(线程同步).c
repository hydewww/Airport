/*�����ܣ����������̣߳�һ�����ڴӼ��̽��������ַ����浽ȫ�ֱ����
����һ����ȫ�ֱ�������ַ�������ļ�*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h> 

unsigned __stdcall getInput(void* pArguments); 
unsigned __stdcall output(void* pArguments); 

char ch='A';
int new_sign=0;
int exit_sign=0;
    
int main()
{
   //�����߳�1�����ڴӼ��̽����ַ���д�뵽ȫ�ֱ���ch��    
   unsigned ThreadID1 = 1;
   HANDLE hRead1 =(HANDLE)_beginthreadex(NULL,0,getInput,NULL,0,&ThreadID1);  
//   DWORD ThreadID1 = 1;
//   HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//��������������߳�
  
  //�����߳�2�����ڽ�ȫ�ֱ���chд���ļ� 
   unsigned ThreadID2 = 2;
   HANDLE hRead2 =(HANDLE)_beginthreadex(NULL,0,output,NULL,0,&ThreadID2);  
//   DWORD ThreadID2 = 2;
//   HANDLE hRead2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)output,NULL,0,&ThreadID2);//��������������߳� 

    WaitForSingleObject(hRead1,INFINITE);	
	CloseHandle(hRead1);
    WaitForSingleObject(hRead2,INFINITE);	
	CloseHandle(hRead2);

  system("PAUSE");	
  return 0;
}

unsigned __stdcall getInput(void* pArguments)
{  
   while(!exit_sign){ 
      if (new_sign==0)
      {
         printf("input a char\n");      
         ch=getchar();
         new_sign=1;
         getchar();//�Ե�\n
         if (ch=='#') exit_sign=1;
      }
   }   
    _endthreadex(0);	
    return 0;        
}

unsigned __stdcall output(void* pArguments)
{
    FILE * cfPtr=NULL;
    
    if( (cfPtr=fopen("data.txt","w"))==NULL)
       printf("can't open file\n"); 
    else{   
         while(!exit_sign){
           if (new_sign)
           {
              fputc(ch,cfPtr);  //д�ļ� 
              new_sign=0;
           }//end if
         }//end while
         fclose(cfPtr);
    }//end else    
    _endthreadex(0);	
    return 0;    
}
