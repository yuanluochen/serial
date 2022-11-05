# Linux环境下的串口

## 编写环境

fedora linux

编译器:  gcc
调试器:  gdb
编辑器:  vscode

## 简介

### 工程简介

该工程用于Robotmaster超级对抗赛自定义控制器测试所用。

该工程任务为，接收自定义控制器数值，通过该工程，将自定义控制器数据转化为串口数据发送到串口发送端。发送给机器人。

### 工程文件简介

#### 文件结构

├── app
│   ├── makefile
│   └── thread.c
├── hardware
│   ├── makefile
│   └── serial.c
├── include
│   ├── serial.h
│   └── thread.h
├── main
│   ├── main.c
│   └── makefile
├── makefile
├── obj
│   └── makefile
└── README.md

#### 各文件夹作用

1. app:       存放线程开辟，以及各线程程序的文件夹
2. hardware:  硬件驱动驱动文件夹，现存放串口初始化，串口收发函数文件
3. include：  工程所有文件的头文件
4. main:      存放工程主函数文件
5. obj:       存放编译工程时的临时文件

## 日志
