 /*��ģ�����ڸ��������������*/ 

//�����ñ����������ļ����Ѿ����� 
#include<stdio.h>
//extern char ch;

void output(char * cPtr)
{
    long int i;
    FILE * cfPtr=NULL;
    
    if( (cfPtr=fopen("data.txt","w"))==NULL)
       printf("can't open file\n"); 
    else   
        while(1){
           for(i=1;i<=22222222;i++); 
             fputc(*cPtr,cfPtr);  //д�ļ� 
             //fputc(*cPtr,stdout); 
            //putchar(ch);
             fflush(cfPtr); 
        } 
    _endthreadex(0);
   
}
