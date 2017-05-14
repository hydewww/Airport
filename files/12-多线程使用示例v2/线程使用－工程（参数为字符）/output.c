 /*本模块用于负责接收输入请求*/ 

//声明该变量在其他文件中已经定义 
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
             fputc(*cPtr,cfPtr);  //写文件 
             //fputc(*cPtr,stdout); 
            //putchar(ch);
             fflush(cfPtr); 
        } 
    _endthreadex(0);
   
}
