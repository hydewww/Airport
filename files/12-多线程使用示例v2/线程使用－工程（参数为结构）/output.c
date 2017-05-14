 /*本模块用于负责接收输入请求*/ 

//声明该变量在其他文件中已经定义 
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
             fputs((*cPtr).name,cfPtr);  //写文件 
             fprintf(cfPtr,"%5d\n",(*cPtr).age); 
             fflush(cfPtr); 
        }   
    _endthreadex(0);
		 
}
