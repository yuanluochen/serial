/**
 * @file thread.c
 * @author yuanluochen
 * @brief 开辟串口收与发线程
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "thread.h"
#include "UartTask.h"

//串口任务ID
pthread_t UartTaskTid = 0;

static void TaskCreate(void);


/**
 * @brief 任务开始，并开始开辟串口收发线程
 * 
 */
void TaskStart(void)
{
    //创建任务
    TaskCreate();
}

//开辟程序任务
static void TaskCreate(void)
{
    
    //创建串口任务线程
    pthread_create(&UartTaskTid, NULL, UartTask, NULL);
}