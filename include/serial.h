#pragma once
/**
 * @file serial.h
 * @author yuanluochen
 * @brief 配置Linux串口收发，以及串口的初始化
 * @version 0.2
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>

#define UART_PATH "/dev/ttyUSB0"

//串口波特率
typedef enum
{
    SERIAL_SPEED_115200 = B115200,
    SERIAL_SPEED_19200 = B19200,
    SERIAL_SPEED_9600 = B9600,
    SERIAL_SPEED_4800 = B4800,
    SERIAL_SPEED_2400 = B2400,
    SERIAL_SPEED_1200 = B1200,
    SERIAL_SPEED_300 = B300,
} SerialSpeed;

//串口数据流控制配置
typedef enum
{
    NO_FLOW_CTRL = 0,       //不使用流控制
    HARDWARE_FLOW_CTRL = 1, //硬件流控制
    SOFTWARE_FLOW_CTRL = 2, //软件流控制
} SerialFlowCtrl;

//数据位的位数
typedef enum
{
    DATA_5BIT = CS5,
    DATA_6BIT = CS6,
    DATA_7BIT = CS7,
    DATA_8BIT = CS8,
} SerialDataBit;

//校验位
typedef enum
{
    NO_PARITY = 'N', //无奇偶校验
    ODD_CHECK = 'O', //奇校验
    EVENNESS = 'E',  //偶校验
    SPACE = 'S',     //空格
} SerialCheck;

//停止位
typedef enum
{
    NO_STOP_BIT = 0,
    STOP_BIT = 1
} SerialStopBit;

//失败
#define FALSE 0
//成功
#define TRUE 1

//串口地址
#define UART_PATH "/dev/ttyUSB0"

//串口初始化
void SerialInit(void);
//串口发送函数
int UartSend(int fd, uint8_t *SendBuf, int DataLen);
//串口打开函数
int UartOpen(char* port);
//串口关闭函数
void UartClose(int fd);



