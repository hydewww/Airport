/*�����ܣ����������̣߳�һ�����ڴӼ��̽��������ַ����浽ȫ�ֱ������ļ��
����һ����ȫ�ֱ������ļ����ݶ���������һ�������㣬�������һ�ļ���*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
 
void getInput(void); 
void modify(void); 

char ch='A';
int endsign=0;
    
int main()
{
   int i; 
   //�����߳�1�����ڴӼ��̽����ַ���д�뵽ȫ�ֱ���ch���ļ���    
   DWORD ThreadID1 = 1;
   HANDLE hRead1 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//��������������߳�
  
  //�����߳�2�����ڽ�ȫ�ֱ���ch���ļ��������޸ĺ�����������ȡ���ַ�д����һ�ļ� 
   DWORD ThreadID2 = 2;
   HANDLE hRead2 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)modify,NULL,0,&ThreadID2);//��������������߳� 
  
/*   while(endsign==0){
    //ѭ������ѭ������Ҫ�У�����main����һ�������������߳�Ҳ�ͽ����ˡ� 
   }
 */
   WaitForSingleObject(hRead1,INFINITE);
   WaitForSingleObject(hRead2,INFINITE);
   CloseHandle(hRead1);
   CloseHandle(hRead2);
    
   system("PAUSE");	
   return 0;
}

void getInput(void)
{   
    int i;
    FILE * cfPtr=NULL;
    
    if( (cfPtr=fopen("charin.txt","w"))==NULL)
       printf("can't open file for write\n"); 
    else   
       {
           while(ch!='#'){ 
           printf("input a char\n");      
           ch=getchar();
           fflush(stdin);
           fputc(ch,cfPtr);  //д�ļ� 
           fflush(cfPtr);
           }   
           fclose(cfPtr);
           endsign=1;
       }

    _endthreadex(0);

}

void modify(void)
{
     struct listNode
     { char data;
       struct listNode *nextPtr; 
     };
     typedef struct listNode LISTNODE;
     typedef LISTNODE * LISTNODEPTR;
     LISTNODEPTR newPtr;  
 
    char fch;
    FILE * rfPtr=NULL;
    FILE * wfPtr=NULL; //��Ϊ����ֻ̨��Ϊһ���߳�ռ�ã�����Ϊ�˸��ٶ�ȡ�����
                       //��Ҫ����ȡ������д����һ�ļ��� 

    if( (wfPtr=fopen("chartest.txt","w"))==NULL)
       printf("can't open file for test\n"); 
    else
    {
    if( (rfPtr=fopen("charin.txt","r"))==NULL)
       printf("can't open file for read\n"); 
    else   
        {
           while((fch=fgetc(rfPtr))!=EOF){ //���ļ� 
             	newPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
                if (newPtr!=NULL)
                { newPtr->data=fch;
                  newPtr->nextPtr=NULL; 
                }//end if  ���������� 
                
                fputc(fch,wfPtr);  //д����һ�ļ� 
           }//end while��   
           fclose(rfPtr);
           fclose(wfPtr);
        
        }// end else in.txt   
    }// end else test.txt

    _endthreadex(0);

}
