#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>


SYSCALL_DEFINE2(mysyscall3, const char __user *,ch,char __user *,gett)
{
   char buffer[100],reve[100];
   int n;
   int i;
   int j;
   int length=0;
   n=copy_from_user(buffer,ch,50);
   if(n)
   {
      printk("copy");
      return -EFAULT;
   }
   while(buffer[length] != '\0')
   	length=length+1;
    j=length-1;
   
   for(i=0;i<length;i++)
   {
     reve[i] = buf[j];
    j--;
   }
   reve[length]='\0';
   n=copy_to_user(gett,reve,50);
   if(n)
   {
    return -EFAULT;
   }
   printk("%s",reve);
   return 0;
}
