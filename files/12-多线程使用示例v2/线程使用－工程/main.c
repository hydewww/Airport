/*�����ܣ����������̣߳�һ�����ڴӼ��̽��������ַ����浽ȫ�ֱ����
����һ����ȫ�ֱ�������ַ�������ļ�*/

#include <stdio.h>
#include <stdlib.h>

//ʹ���̱߳��ʱ������������ͷ�ļ�������� 
#include <winsock.h>
#include <winbase.h>

void getInput(void); 
void output(void); 

char ch='A';
    
int main()
{
   int i; 
       
   DWORD ThreadID1 = 1;
   HANDLE hRead1 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//��������������߳�
  
   DWORD ThreadID2 = 2;
   HANDLE hRead2 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)output,NULL,0,&ThreadID2);//��������������߳�
  
   WaitForSingleObject(hRead1,INFINITE);
   WaitForSingleObject(hRead2,INFINITE);
   CloseHandle(hRead1);
   CloseHandle(hRead2);
   
   system("PAUSE");	
   return 0;
}
