#pragma once
/**
 * @file UartTask.h
 * @author yuanluochen
 * @brief 串口任务文件，接收自定义控制器数据，通过串口将数据发送出去
 * @version 0.1
 * @date 2022-11-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "serial.h"

//串口数据类型
typedef uint8_t UartDataType_t;

//串口数数据结构体
typedef struct 
{
    //起始段长度
    int BeginLen;
    //数据段长度
    int DataLen;
    //结束段长度
    int EndLen;
    //数据段总体长度
    int sumLen;
    //串口数据
    UartDataType_t Data[];
    
}UartData_t;

//要发送的数据
typedef struct 
{
    //数据长度
    int len;
    //串口要发送的数据
    UartDataType_t TxData[];
}TxData_t;

//串口结构体
typedef struct 
{
    //串口发送要发送的数据，从自定义控制器接收的数据
    TxData_t TxData;
    //发送总体数据
    UartData_t UartTxData;
    
}Uart_t;




//串口任务函数
void* UartTask(void* param);