# pi-3b-c

本项目存放一些C语言相关代码，编译运行环境为树莓派3b

```
cai@raspberrypi: $ uname -a
Linux raspberrypi 6.12.47+rpt-rpi-v8 #1 SMP PREEMPT Debian 1:6.12.47-1+rpt1 (2025-09-16) aarch64 GNU/Linux

cai@raspberrypi: $ uname -r
6.12.47+rpt-rpi-v8

cai@raspberrypi: $ gcc -v
gcc version 14.2.0 (Debian 14.2.0-19)

cai@raspberrypi: $ cmake --version
cmake version 3.31.6
```

编译方式

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

编译完毕后，在`build`目录下即有可执行文件产物

## 项目结构

```
.
├── app
│   └── include
├── CMakeLists.txt
├── docs
├── main.c                      // 项目main函数
├── platform
│   ├── alloc
│   │   └── plat_alloc.c        // 平台内存分配，提供内存池和内存记录
│   ├── ds
│   │   ├── hash_table
│   │   ├── heap
│   │   ├── list
│   │   ├── queue
│   │   └── stack
│   ├── include                 // 存放platform目录下的所有头文件
│   │   └── ...
│   ├── thread_pool
│   └── timer
│       └── plat_timer.c
└── readme.md

15 directories, 8 files
```