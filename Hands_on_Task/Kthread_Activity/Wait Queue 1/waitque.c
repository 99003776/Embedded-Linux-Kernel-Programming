#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/syscalls.h>

static struct task_struct *task1;
static struct task_struct *task2;
int val = 100;

const int max = 30;

static wait_queue_head_t w1;
static int buflen = 0;

static int thread_one(void *pargs) {
  int i;
  wait_event_interruptible(w1, (buflen > 0));
  printk("---> Thread A Welcome<--- Consumer");
  for (i = 1; i <= max; i++) {
    val++;
    printk("Thread A");
    if (kthread_should_stop())
      break;
  }
  return 0;
}

static int thread_two(void *pargs) {
  int i;
  printk("---> Thread B Welcome<---Producer");
  for (i = 1; i <= max; i++) {
    val--;
    printk("Thread B");
    if (kthread_should_stop())
      break;
  }
  buflen++;
  wake_up_interruptible(&w1);
  return 0;
}

static int __init waitque_init(void) {
  init_waitqueue_head(&w1);
  task1 = kthread_run(thread_one, NULL, "thread_A");
  task2 = kthread_run(thread_two, NULL, "thread_B");
  return 0;
}

static void __exit waitque_exit(void) {
  printk("VAL:%d", val);
  printk("----EXIT----");
}

module_init(waitque_init);
module_exit(waitque_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pawan Kumar");
MODULE_DESCRIPTION("Waitque");
