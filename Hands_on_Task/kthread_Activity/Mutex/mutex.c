#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>
#include <linux/syscalls.h>
static struct task_struct *task1;
static struct task_struct *task2;
int val = 100;
const int max = 10;
static DEFINE_MUTEX(s1);
static int thread_one(void *pargs) {
  int i;
  printk("---> Thread A Welcome<---");
  mutex_lock(&s1);
  for (i = 1; i <= max; i++) {
    val++;
    printk("Thread A");
    if (kthread_should_stop())
      break;
  }
  mutex_unlock(&s1);
  do_exit(0);
  return 0;
}

static int thread_two(void *pargs) {
  int i;
  printk("---> Thread B Welcome<---");
  mutex_lock(&s1);
  for (i = 1; i <= max; i++) {
    val--;
    printk("Thread B");
    if (kthread_should_stop())
      break;
  }
  mutex_unlock(&s1);
  do_exit(0);
  return 0;
}

static int __init thread_init(void) {
  mutex_init(&s1);
  task1 = kthread_run(thread_one, NULL, "thread_A");
  // kthread_create + wake_up_process
  task2 = kthread_run(thread_two, NULL, "thread_B");
  return 0;
}

static void __exit thread_exit(void) {
  printk("VAL:%d", val);
  printk("----EXIT----");
}

module_init(thread_init);
module_exit(thread_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("NITIN SHETTY");
MODULE_DESCRIPTION("Mutual Exclusion");
