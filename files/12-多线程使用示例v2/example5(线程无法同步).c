/*�����ܣ����������̣߳�һ�����ڴӼ��̽��������ַ����浽ȫ�ֱ����
����һ����ȫ�ֱ�������ַ�������ļ�*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h> 

unsigned __stdcall getInput(void* pArguments); 
unsigned __stdcall output(void* pArguments); 

char ch='A';
    
int main()
{
   //�����߳�1�����ڴӼ��̽����ַ���д�뵽ȫ�ֱ���ch��    
   unsigned ThreadID1 = 1;
   HANDLE hRead1 =(HANDLE)_beginthreadex(NULL,0,getInput,NULL,0,&ThreadID1);  
//   HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//��������������߳�
  
  //�����߳�2�����ڽ�ȫ�ֱ���chд���ļ� 
   unsigned ThreadID2 = 2;
   HANDLE hRead2 =(HANDLE)_beginthreadex(NULL,0,output,NULL,0,&ThreadID2);  
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
   //int i=0; 
   while(ch!='q'){ 
      printf("input a char\n");      
      ch=getchar();
      getchar();//�Ե�\n 
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
               Sleep(500); //�ӳ� ,ע��Sleep()������һ����ĸ��д�������Сд���ڴ˰汾�»ᵼ���߳��޷����ѡ� 
               fputc(ch,cfPtr);  //д�ļ� 
           }//end while i
           fclose(cfPtr);
    }//end else    
    _endthreadex(0);	
    return 0;    
}
