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

//串口任务函数
void* UartTask(void* param);