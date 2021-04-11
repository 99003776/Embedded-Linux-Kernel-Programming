#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#define __CR_testcall 401
int main() 
{
   printf("HELLO INDIA");
   int ret;
   char ch[200];
   ret=syscall(__CR_testcall,"shettynitin",ch);
   printf("\n echo string is %s\n", ch);
   if(ret<0)
     perror("testcall");
   return 0;
}
