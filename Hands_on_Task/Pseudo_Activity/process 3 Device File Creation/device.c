#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

dev_t pdevid;

int ndevices = 1;

struct cdev cdev;

struct device *pdev;  // global
struct class *pclass; // global

static int __init psuedo_init(void) 
{

  int ret;
  int i = 0;

  ret = alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");

  //  cdev_init(&cdev, &fops);

  kobject_set_name(&cdev.kobj, "pdevice%d", 0);

  ret = cdev_add(&cdev, pdevid, 1);

  if (ret) {

    printk("Pseudo: Failed to register driver\n");

    return -EINVAL;
  }

  printk("Successfully registered,major=%d,minor=%d\n", MAJOR(pdevid),

         MINOR(pdevid));

  printk("Pseudo Driver Sample..welcome\n");
  pclass = class_create(THIS_MODULE, "pseudo_class");
  // alloc_chrdev_region, cdev_init, cdev_add
  pdev = device_create(pclass, NULL, pdevid, NULL, "psample%d", i);
  return 0;
  
}

static void __exit psuedo_exit(void) {

  unregister_chrdev_region(pdevid, ndevices);

  printk("Pseudo Driver Sample..Bye\n");

  cdev_del(&cdev);
  
  device_destroy(pclass, pdevid);
  
  class_destroy(pclass);
}

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pawan Kumar");
MODULE_DESCRIPTION("First Driver");
