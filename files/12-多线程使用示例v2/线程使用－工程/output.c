 /*��ģ�����ڸ��������������*/ 

//�����ñ����������ļ����Ѿ����� 
#include<stdio.h>
extern char ch;

void output(void)
{
    long int i;
    FILE * cfPtr=NULL;
    
    if( (cfPtr=fopen("data.txt","w"))==NULL)
       printf("can't open file\n"); 
    else   
        while(1){
           for(i=1;i<=22222222;i++); 
             fputc(ch,cfPtr);  //д�ļ� 
            //putchar(ch);
             fflush(cfPtr); 
        }    
    _endthreadex(0);
}
