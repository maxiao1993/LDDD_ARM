#include<linux/module.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define		SECOND_MAJOR	248

static int second_major = SECOND_MAJOR;
module_param(second_major, int, S_IRUGO);

struct second_dev {
	struct cdev cdev;
	atomic_t counter;
	struct timer_list s_timer;
};

static struct second_dev *second_devp;
static void second_timer_handler(unsigned long arg)
{
	mod_timer(&second_devp->s_timer, jiffies + HZ);	//触发下一次定时
	atomic_inc(&second_devp->counter);		//增加秒技术

	printk(KERN_INFO "current jiffies is %ld\n", jiffies);
}

static int second_open(struct inode *inode, struct file *filp)
{
	init_timer(&second_devp->s_timer);
	second_devp->s_timer.function = &second_timer_handler;
	second_devp->s_timer.expires = jiffies + HZ;

	add_timer(&second_devp->s_timer);

	atomic_set(&second_devp->counter, 0);		//初始化秒计数为0

	return 0;
}
