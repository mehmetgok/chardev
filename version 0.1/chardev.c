/*
  - URL: http://tuxthink.blogspot.com/2010/11/writing-example-driver-from-scratch_13.html
  - URL: http://tuxthink.blogspot.com/p/kernel-related.html
  
  
  - Major number get then create char device with
  
  # mknod /dev/char_arr c 249 0
  # echo foo > /dev/char_arr
  # cat /dev/char_arr
  # rm /dev/char_arr
  
  
  - Modified by Mehmet GOK, 11.12.2013
 
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h> // required for various structures related to files liked fops. 
#include <asm/uaccess.h> // required for copy_from and copy_to user functions 
#include <linux/semaphore.h>
#include <linux/cdev.h> 

static int Major;
static int written,read;

struct device {
 char array[100];
 struct semaphore sem;
}char_arr;

int open(struct inode *inode, struct file *filp)
{
 
 printk(KERN_INFO "Inside open \n");
 if(down_interruptible(&char_arr.sem)) {
  printk(KERN_INFO " could not hold semaphore");
  return -1;
 }
 read = written;
 return 0;
}

int release(struct inode *inode, struct file *filp) {
 printk (KERN_INFO "Inside close \n");
 printk(KERN_INFO "Releasing semaphore");
 up(&char_arr.sem);
 return 0;
}

ssize_t read_char(struct file *filp, char *buff, size_t count, loff_t *offp) {
 unsigned long ret;
 printk("Inside read \n");
 if(count > read) 
 count = read;
 read = read -count;
 ret = copy_to_user(buff, char_arr.array, count);
 return count;
}

ssize_t write_char(struct file *filp, const char *buff, size_t count, loff_t *offp) { 
 unsigned long ret; 
 printk(KERN_INFO "Inside write \n");
 ret = copy_from_user(char_arr.array, buff, count); 
 written += count;
 return count;
}

struct file_operations fops = {
 
 owner:  THIS_MODULE,
 read:  read_char,
 write:  write_char,
 open:   open,
 release: release
};


struct cdev *kernel_cdev; 


int char_arr_init (void) {
 int ret;
 dev_t dev_no,dev;

 kernel_cdev = cdev_alloc(); 
  kernel_cdev->ops = &fops;
 kernel_cdev->owner = THIS_MODULE;
 printk (" Inside init module\n");
  ret = alloc_chrdev_region( &dev_no , 0, 1,"char_arr_dev");
  if (ret < 0) 
  {
      printk("Major number allocation is failed\n");
      return ret; 
  }
  
  Major = MAJOR(dev_no);
  printk (KERN_INFO" The major number for your device is %d\n", Major); 

  // not!! init_MUTEX(&char_arr.sem)
  // http://www.linuxquestions.org/questions/blog/frandalla-68463/patching-802-11-linux-sta-driver-for-kernel-2-6-37-3558/ 
  sema_init(&char_arr.sem, 1);

 ret = cdev_add( kernel_cdev,dev_no,1);
 if(ret < 0 ) 
 {
  printk(KERN_INFO "Unable to allocate cdev");
  return ret;
 }

 return 0;
}

void char_arr_cleanup(void) {
 printk(KERN_INFO " Inside cleanup_module\n");
 cdev_del(kernel_cdev);
 unregister_chrdev_region(Major, 1);
}

MODULE_LICENSE("GPL"); 
module_init(char_arr_init);
module_exit(char_arr_cleanup);
