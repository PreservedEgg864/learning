/*************************************************************************
	> File Name: hello_world.c
	> Author: leey.lee
	> 
	> Motto: Let the Bug come harder~
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void){
    printk(KERN_ALERT "Hello world\n");
    return 0;
}

static void hello_exit(void){
    printk(KERN_ALERT "Goodye ,cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("leey.lee");
MODULE_DESCRIPTION("Hello kernel world module!");
