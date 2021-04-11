#include<linux/kernel.h>
#include<linux/syscalls.h>

SYSCALL_DEFINE4(mysyscall,int,p,int,q,int,r,int,s)
{
	printk("This is Test call p=%d q=%d" ,p,q,r,s);
	return p+q+r+s;
}
