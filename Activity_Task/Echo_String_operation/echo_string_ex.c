#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>

SYSCALL_DEFINE2(string_echo, const char*,input_string, char*,string_output)
{
   char buffer_in[50];
   int num,length;
   num=copy_from_user(buffer_in,input_string,40);
   if(num)
   {
      printk("\nCopy from user Error");
      return -EFAULT;
   }
   for(length=0;buffer_in[length]!='\0';length++);
   num=copy_to_user(string_output,buffer_in,length);
   if(num)
   {
      printk("\nCopy to user Error");
      return -EFAULT;
   }
   printk("\Result = %s", buffer_in);
   return 0;
}
