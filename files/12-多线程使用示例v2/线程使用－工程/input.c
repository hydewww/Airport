 /*��ģ�����ڸ��������������*/ 

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


