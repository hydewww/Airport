 /*��ģ�����ڸ��������������*/ 

//�����ñ����������ļ����Ѿ����� 
#include<stdio.h>
#include "type.h"

void output(struct STUDENT * cPtr)
{
    long int i;
    FILE * cfPtr=NULL;
    
    if( (cfPtr=fopen("data.txt","w"))==NULL)
       printf("can't open file\n"); 
    else   
        while(1){
           for(i=1;i<=22222222;i++); 
             fputs((*cPtr).name,cfPtr);  //д�ļ� 
             fprintf(cfPtr,"%5d\n",(*cPtr).age); 
             fflush(cfPtr); 
        }   
    _endthreadex(0);
		 
}
