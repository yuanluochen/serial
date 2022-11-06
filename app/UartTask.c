/**
 * @file UartTask.c
 * @author yuanluochen
 * @brief 串口任务，接收自定义控制器数据，通过串口将数据发送出去
 * @version 0.1
 * @date 2022-11-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "UartTask.h"

static GetKeyBoardData(Uart_t* UartGetKeyBoardData);
static GetData(Uart_t* UartGetData);

//串口发送数据结构体
Uart_t UartTx;

void* UartTask(void* param)
{
    sleep(1);
    //初始化串口结构体
    while(1)
    {
        //获取要发送的数据

        sleep(1);
    }   
}

//获取数据
static GetData(Uart_t* UartGetData)
{
}
