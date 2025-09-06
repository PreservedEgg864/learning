#include <linux/module.h>
#include <linux/init.h>

// 模块初始化函数
static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, Linux kernel world!\n");
    return 0;
}

// 模块退出函数
static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, Linux kernel world!\n");
}

// 指定模块的初始化和退出函数
module_init(hello_init);
module_exit(hello_exit);

// 模块信息
MODULE_LICENSE("GPL");
MODULE_AUTHOR("leey.lee");
MODULE_DESCRIPTION("A simple Hello World Linux kernel module");
