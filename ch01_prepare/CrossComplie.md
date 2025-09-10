#交叉编译树莓派

官方文档：
https://www.raspberrypi.com/documentation/computers/linux_kernel.html

### 1. 安装工具
```bash
sudo apt update
sudo apt install bc bison flex libssl-dev make libc6-dev libncurses5-dev
```

安装交叉编译工具链（树莓派 5 是 ARM64 架构）：
```bash
sudo apt install crossbuild-essential-arm64
```

### 2. 拉取仓库
```bash
git clone --depth=1 https://github.com/raspberrypi/linux
```

 [让树莓派 5 跑上“香草”主线内核：精简裁剪、交叉编译与部署全流程](https://blog.bktus.com/archives/2760/)，详细讲解了如何裁剪驱动、配置 DTS 文件、同步主线代码。

### 3. 修改配置
树莓派 5 默认配置：
```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2712_defconfig
```
也可以通过 `menuconfig` 定制功能：
```bash
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
```

### 4. 编译
```bash
make -j$(nproc) ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- Image modules dtbs
```

### 5. 安装
```bash

make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc) INSTALL_MOD_PATH=../modules modules_install

```

### 6. 查看生成文件路径
```bash
ls arch/arm64/boot/Image         # 内核镜像
ls arch/arm64/boot/dts/broadcom/*.dtb  # 设备树文件
ls modules.builtin              # 模块列表
```

### 7. scp中转到树莓派
```bash
# 记得创建tmp.broadcom,overlays
# kernel镜像
scp leeyan@124.70.164.255:~/linux/arch/arm64/boot/Image jiali@192.168.110.45:~/tmp/
# 设备树
scp -r leeyan@124.70.164.255:~/linux/arch/arm64/boot/dts/broadcom/*.dtb jiali@192.168.110.45:~/tmp/dts/broadcom/
scp -r leeyan@124.70.164.255:~/linux/arch/arm64/boot/dts/overlays/*.dtb* jiali@192.168.110.45:~/tmp/dts/overlays/
scp -r leeyan@124.70.164.255:~/linux/arch/arm64/boot/dts/overlays/README jiali@192.168.110.45:~/tmp/dts/overlays/
# 模块
cd ..
tar jcvf modules.tar.bz2 modules/
scp leeyan@124.70.164.255:~/modules.tar.bz2 jiali@192.168.110.45:~/tmp/
```

### 8. 部署
```bash
# 备份
cd /boot/fireware/
sudo cp kernel8.img kernel88.img
# 替换
sudo cp ~/tmp/Image /boot/firmware/kernel8.img
sudo cp ~/tmp/dts/broadcom/*.dtb /boot/firmware/
sudo cp ~/tmp/dts/overlays/*.dtb* /boot/firmware/overlays/
sudo cp ~/tmp/dts/overlays/README /boot/firmware/overlays/
tar jxf ~/tmp/modules.tar.bz2
sudo cp -r ~/tmp/modules/lib/modules/* /lib/modules/
sudo cp -r ~/tmp/modules/lib/firmware/* /lib/firmware/
# /boot/firware/config.txt
# 内核在/lib/modules/config看
kernel=kernel8.img
```
