#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define __NR_testcall 402
int main(int arg,char *argv[])
{
  int ret;
  char *string_output;
  int i=1;
  while(i < arg)
  {
    string_output =malloc(sizeof(char)*50);
    ret=syscall(__NR_testcall,argv[i],string_output);
    if(ret<0)
    {
  	perror("testcall");
    }
    printf("\n\n%s", string_output);
    free(string_output);
    i++;
  }
  return 0;
}