/**
 * @file main.c
 * @author yuanluochen
 * @brief linux环境下串口收发，用于robotmaster超级对抗赛自定义控制器测试
 * @version 0.2
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "serial.h"
#include "thread.h"
#include <pthread.h>

int main()
{
    
    //初始化串口配置
    SerialInit();
    //开辟线程
    TaskStart();
    while(1)
    {
        sleep(1);
    }
    return 0;
}
