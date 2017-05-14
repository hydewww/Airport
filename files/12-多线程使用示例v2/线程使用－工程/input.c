 /*本模块用于负责接收输入请求*/ 

#include<stdio.h> 
extern char ch;
 
void getInput(void)
{   
    int i;
    
   while(1){ 
      printf("input a char\n");      
      ch=getchar();
      fflush(stdin);
   }   
    _endthreadex(0);    
}


