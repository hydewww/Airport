 /*本模块用于负责接收输入请求*/ 

#include<stdio.h> 
#include "type.h"

void getInput(struct STUDENT * cPtr)
{   
    int i;
    
   while(1){ 
      printf("input student's name \n");      
      gets((*cPtr).name);
      printf("input student's age \n"); 
      scanf("%d",&(*cPtr).age);     
      fflush(stdin);
   }   
    _endthreadex(0);
    
}


