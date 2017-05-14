/*程序功能：创建两个线程，一个用于从键盘接收输入字符保存到全局变量和文件里，
，另一个将全局变量和文件内容读出，创建一个链表结点，输出到另一文件中*/

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
   //创建线程1：用于从键盘接收字符，写入到全局变量ch和文件中    
   DWORD ThreadID1 = 1;
   HANDLE hRead1 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);//创建接收输入的线程
  
  //创建线程2：用于将全局变量ch和文件读出，修改呼叫链表，将读取的字符写入另一文件 
   DWORD ThreadID2 = 2;
   HANDLE hRead2 = (HANDLE)_beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)modify,NULL,0,&ThreadID2);//创建接收输入的线程 
  
/*   while(endsign==0){
    //循环。本循环必须要有，否则main函数一结束，另两个线程也就结束了。 
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
           fputc(ch,cfPtr);  //写文件 
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
    FILE * wfPtr=NULL; //因为控制台只能为一个线程占用，所以为了跟踪读取情况，
                       //需要将读取的内容写入另一文件。 

    if( (wfPtr=fopen("chartest.txt","w"))==NULL)
       printf("can't open file for test\n"); 
    else
    {
    if( (rfPtr=fopen("charin.txt","r"))==NULL)
       printf("can't open file for read\n"); 
    else   
        {
           while((fch=fgetc(rfPtr))!=EOF){ //读文件 
             	newPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
                if (newPtr!=NULL)
                { newPtr->data=fch;
                  newPtr->nextPtr=NULL; 
                }//end if  创建链表结点 
                
                fputc(fch,wfPtr);  //写入另一文件 
           }//end while读   
           fclose(rfPtr);
           fclose(wfPtr);
        
        }// end else in.txt   
    }// end else test.txt

    _endthreadex(0);

}
