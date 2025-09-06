# Linux Device Drivers Study

## About
本仓库记录了我学习 **《Linux设备驱动程序》** 过程中的实验与作业代码。  
内容涵盖：
- 字符设备、块设备、网络设备驱动
- I2C / SPI / GPIO / USB 等总线驱动
- 设备树(Device Tree)与内核模块开发
- 调试与分析技巧（`dmesg`、`strace`、逻辑分析仪等）

目标：  
通过**动手实践 + 硬件调试**，理论结合实践，逐步掌握的 Linux 驱动开发能力。

## 一级目录结构
```
├── ch01_prepare           # 测试的demo。
├── ch02_hello_driver      # 第1章：Hello World 内核模块
├── ch03_char_device       # 第2章：字符设备驱动
├── ch04_block_device      # 第3章：块设备驱动
├── ch05_usb_driver        # 第4章：USB 驱动
├── ch06_i2c_spi_driver    # 第5章：I2C/SPI 驱动
├── ...
└── docs                   # 学习笔记与调试记录
```


### 备注
- 部分代码基于《Linux设备驱动程序》书中示例，并结合个人实验进行修改。

