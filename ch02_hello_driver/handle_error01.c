/*************************************************************************
	> File Name: handle_error.c
	> Author: leey.lee
	> 
	> Motto: Let the Bug come harder~
 ************************************************************************/

#include <linux/init.h>
#include <linux/module.h>

int __init my_init(void){
    int err = 0;
    // 使用指针和名称注册函数
    err = register_this(ptr1, "skull");
    if(err){ goto fail_this;}
    err = register_that(ptr1, "skull");
    if(err){ goto fail_that;}
    err = register_those(ptr1, "skull");
    if(err){ goto fail_those;}
    // 成功
    return 0;
    // 返回错误
    fail_those: unregister_those(ptr2,"skull");
    fail_that: unregister_this(ptr1,"skull");
    fail_this: return err;
}

module_init(my_init);

MODULE_DESCRIPTION("error handle test module");
