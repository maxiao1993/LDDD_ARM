/*
 *	a simple char device driver: globalmem without mutex
 *
 *	
 *
 */

#include<linux/module.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define GLOBALMEM_SIZE	0x1000
#define MEM_CLEAR	0x1
#define GLOBALMEM_MAJOR	230

static int globalmem_major = GLOBALMEM_major;
module_param(globalmem_major, int, S_IRUGO);

struct globalmem_dev {
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
};

struct globalmem_dev *globalmem_devp;

static int globalmem_open(struct inode *inode, struct file *filp)
{
	filp->private_data = globalmem_devp;
	return 0;
}

static int globalmem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
struct globalmem_dev *dev = filp->private_data;

switch (cmd) {
case MEM_CLEAR:
	memset(dev->mem, 0, GLOBALMEM_SIZE);
	printk(KERN_INFO "globalmem is set to zero\n");
	break;
default:
	return -EINVAL;
}
return 0;
}


