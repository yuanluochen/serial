/**
 * @file serial.c
 * @author yuanluochen
 * @brief 配置Linux环境下的串口收发，以及串口的初始化
 * @version 0.2
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "serial.h"

//函数声明
static int UartConfig(int fd, SerialSpeed speed, 
                              SerialFlowCtrl flow_ctrl, 
                              SerialDataBit databit, 
                              SerialCheck parity, 
                              SerialStopBit stopbits);

int fd = 0;//串口文件标识符
/**
 * @brief 打开串口，并初始化串口参数
 * 
 */
void SerialInit(void)
{
    //打开串口
    fd = UartOpen(UART_PATH);
    //配置串口参数
    UartConfig(fd, SERIAL_SPEED_115200, NO_FLOW_CTRL, DATA_8BIT, NO_PARITY, NO_STOP_BIT);
}

/**
 * @brief 串口开启函数
 *
 * @param fd 文件描述符
 * @param port 串口号 文件绝对路径
 * @return 错误返回 FALSE 成功返回文件描述符
 */
int UartOpen(char* port)
{
    //打开串口文件
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    //验证是否打开
    if (fd < 0)
    {
        perror("Can't Open Serial Port");
        return FALSE;
    }
    //恢复串口为阻塞状态
    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        printf("fcntl failed!\n");
        return FALSE;
    }
    else
    {
        printf("fcntl=%d\n", fcntl(fd, F_SETFL, 0));
    }
    //测试是否为终端设备
    if (0 == isatty(STDIN_FILENO))
    {
        printf("standard input is not a terminal device\n");
        return FALSE;
    }
    else
    {
        printf("isatty success!\n");
    }
    printf("fd->open=%d\n", fd);
    return fd;
}

/**
 * @brief 串口配置函数
 *
 * @param fd 文件标识符
 * @param speed 串口波特率配置 115200 19200 9600 4800 2400 1200 300
 * @param flow_ctrl 配置数据流控制 0 不使用流控制 1 使用硬件流控制 2 使用软件流控制
 * @param datebit 配置数据位 5 5bit 6 6bit 7 7bit 8 8bit
 * @param parity 设置校验位 ‘N’ 无奇偶校验位 ‘O’ 奇校验 ‘E’ 偶校验 'S' 空格
 * @return 串口配置成功 TRUE 失败 FALSE
 */
static int UartConfig(int fd, SerialSpeed speed, 
                              SerialFlowCtrl flow_ctrl, 
                              SerialDataBit databit, 
                              SerialCheck parity, 
                              SerialStopBit stopbits)
{
    //串口配置结构体
    struct termios SerialOptions;
    //判断调用串口是否成功
    if (tcgetattr(fd, &SerialOptions) != 0)
    {
        //调用失败
        perror("Setup Serial 1");
        return FALSE;
    }

    //设置串口波特率
    cfsetispeed(&SerialOptions, speed);
    cfsetospeed(&SerialOptions, speed);

    //修改控制模式，保证程序不会占用串口
    SerialOptions.c_cflag |= CLOCAL;
    //修改控制模式，使得能够从串口中读取数据
    SerialOptions.c_cflag |= CREAD;

    //设置数据流控制
    switch (flow_ctrl)
    {
    case NO_FLOW_CTRL: //不使用流控制
        SerialOptions.c_cflag &= ~CRTSCTS;
        break;
    case HARDWARE_FLOW_CTRL: //使用硬件流控制
        SerialOptions.c_cflag |= CRTSCTS;
        break;
    case SOFTWARE_FLOW_CTRL: //使用软件流控制
        SerialOptions.c_cflag |= IXON | IXOFF | IXANY;
        break;
    }

    //屏蔽其他标志位
    SerialOptions.c_cflag &= ~CSIZE;
    //设置数据位
    SerialOptions.c_cflag |= databit;

    //设置校验位
    switch (parity)
    {
    case NO_PARITY: //无奇偶校验
        SerialOptions.c_cflag &= ~PARENB;
        SerialOptions.c_iflag &= ~INPCK;
        break;
    case ODD_CHECK: //奇校验
        SerialOptions.c_cflag |= (PARODD | PARENB);
        SerialOptions.c_iflag |= INPCK;
        break;
    case EVENNESS: //偶校验
        SerialOptions.c_cflag |= PARENB;
        SerialOptions.c_cflag &= ~PARODD;
        SerialOptions.c_iflag |= INPCK;
        break;
    case SPACE: //空格
        SerialOptions.c_cflag &= ~PARENB;
        SerialOptions.c_cflag &= ~CSTOPB;
        break;
    }

    //设置停止位
    switch (stopbits)
    {
    case NO_STOP_BIT: //无停止位
        SerialOptions.c_cflag &= ~CSTOPB;
        break;
    case STOP_BIT: //设置停止位
        SerialOptions.c_cflag &= CSTOPB;
        break;
    }

    //修改输出模式，原始数据输出
    SerialOptions.c_oflag &= ~OPOST;

    SerialOptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    //设置等待时间和最小接收字节
    SerialOptions.c_cc[VTIME] = 1; // 读取一个字节等待 1*(1 / 10)s
    SerialOptions.c_cc[VMIN] = 1;  //读取字符最小个数为1

    //如果发生数据溢出，接收数据，但是不再读取，刷新收到数据但是不读
    tcflush(fd, TCIFLUSH);

    //激活配置
    if (tcsetattr(fd, TCSANOW, &SerialOptions) != 0)
    {
        perror("com set error!\n");
        return FALSE;
    }

    return TRUE;
}
/**
 * @brief 串口发送函数
 *
 * @param fd 文件描述符
 * @param SendBuf 存放发送数据的数据位
 * @param DataLen 发送数据长度
 * @return 如果发送成功则为 TRUE 失败为 FALSE
 */
int UartSend(int fd, uint8_t *SendBuf, int DataLen)
{
    int len = 0;

    //读取数据存放在缓存区
    len = write(fd, SendBuf, DataLen);
    if (DataLen == len)
    {
        printf("send message successful\n");
        printf("send message is : %s\n", SendBuf);
    }
}
/**
 * @brief 串口关闭函数 
 * 
 * @param fd 文件描述符
 */
void UartClose(int fd)
{
    //关闭串口
    close(fd);
}

