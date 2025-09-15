/*************************************************************************
	> File Name: virtual_led.c
	> Author: leey.lee
	> 
	> Motto: Let the Bug come harder~
 ************************************************************************/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEVICE_NAME "vled"
static int vled_open(struct inode *inode, struct file *filp)
{
    pr_info("vled device opened\n");
    return 0;
}
static int vled_release(struct inode *inode, struct file *filp)
{
    pr_info("vled device closed\n");
    return 0;
}
static ssize_t vled_read(struct file *filp, char __user *buf,
size_t count, loff_t *f_pos)
{
    char status = '1'; // 模拟读取LED状态
    if (copy_to_user(buf, &status, 1))
    return -EFAULT;
    return 1;
}
static ssize_t vled_write(struct file *filp, const char __user *buf,
size_t count, loff_t *f_pos)
{
    char val;
    if (copy_from_user(&val, buf, 1))
    return -EFAULT;
    pr_info("LED set to %c\n", val);
    return 1;
}
static struct file_operations vled_fops = {
    .owner = THIS_MODULE,
    .open = vled_open,
    .release = vled_release,
    .read = vled_read,
    .write = vled_write,
};

static int major = 0;
static struct cdev vled_cdev;

static int __init vled_init(void)
{
    dev_t devno;
    int ret;

    // 动态分配主设备号
    ret = alloc_chrdev_region(&devno, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("Failed to allocate char device region\n");
        return ret;
        major = MAJOR(devno);

        // 初始化字符设备
        cdev_init(&vled_cdev, &vled_fops);
        vled_cdev.owner = THIS_MODULE;

        // 添加字符设备到系统
        ret = cdev_add(&vled_cdev, devno, 1);
        if (ret) {
            pr_err("Failed to add cdev\n");
            unregister_chrdev_region(devno, 1);
            return ret;
        }
        pr_info("vled driver loaded with major %d\n", major);
        return 0;
    }
}

static void __exit vled_exit(void)
{
    dev_t devno = MKDEV(major, 0);
    cdev_del(&vled_cdev);
    unregister_chrdev_region(devno, 1);
    pr_info("vled driver unloaded\n");
}

module_init(vled_init);
module_exit(vled_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Virtual LED Driver");
