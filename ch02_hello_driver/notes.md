##printk的日志级别
日志级别：KERN_EMERG, KERN_ALERT, KERN_CRIT, KERN_ERR, KERN_WARNING,
KERN_NOTICE, KERN_INFO, KERN_DE
默认情况下，只有KERN_WARNING及以上级别的消息会显示在控制台
可以使用dmesg查看所有级别的消息

```
// 不同级别的printk示例
printk(KERN_DEBUG "Debug message\n");
printk(KERN_INFO "Informational message\n");
printk(KERN_ERR "Error message\n");
```