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
static wait_queue_head_t w2;
static int buflen = 0;
static int a = 0;

static int thread_one(void *pargs) {
  int i;
  for (i = 1; i <= max; i++) {
    wait_event_interruptible(w1, (a > 0));
    val++;
    printk("Thread A--Consumer ");
    a--;
    if (a == 0)
      wake_up_interruptible(&w2);
  }
  return 0;
}

static int thread_two(void *pargs) {
  int i;
  for (i = 1; i <= max; i++) {
    wait_event_interruptible(w2, (a < 6));
    val--;
    printk("Thread B--Producer");
    a++;
    if (a >= 6)
      wake_up_interruptible(&w1);
  }

  return 0;
}

static int __init waitque2_init(void) {
  init_waitqueue_head(&w1);
  init_waitqueue_head(&w2);
  task1 = kthread_run(thread_one, NULL, "thread_A");
  task2 = kthread_run(thread_two, NULL, "thread_B");
  return 0;
}

static void __exit waitque2_exit(void) {
  printk("VAL:%d", val);
  printk("----EXIT----");
}

module_init(waitque2_init);
module_exit(waitque2_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("NITIN SHETTY");
MODULE_DESCRIPTION("Waitque2");
