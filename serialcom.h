#ifndef SERIALCOM_H
#define SERIALCOM_H
//===========================================

#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>
#include     <sys/stat.h>
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*POSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/
#include     <strings.h>

//=============================================
//串口名字
#define     TTYUSB0  "/dev/ttyUSB0"
#define     TTYMX3   "/dev/ttymxc3"
#define     TTYMX2   "/dev/ttymxc2"
#define     TTYMX1   "/dev/ttymxc1"
#define     TTYMX0   "/dev/ttymxc0"


//串口
#define     TTYS0   1
#define     TTYS1   2
#define     TTYS2   3
//波特率
#define     BAUD_2400       2400
#define     BAUD_4800       4800
#define     BAUD_9600       9600
#define     BAUD_115200     115200
#define     BAUD_19200      19200
#define     BAUD_460800     460800
//奇偶校验位
#define     PARITY_ODD    'O' //奇数
#define     PARITY_EVEN   'E' //偶数
#define     PARITY_NONE   'N' //无奇偶校验位
//停止位
#define     STOP_BIT_1     1
#define     STOP_BIT_2     2
//数据位
#define     DATA_BIT_7     7
#define     DATA_BIT_8     8
//========================================
class SerialCom
{
public:
    SerialCom();
    //串口API

    /*打开串口函数*/
    int open_port(int fd,int comport);
    //串口配置的函数
    int set_opt(int fd,int nSpeed, int nBits,
                char nEvent, int nStop);
    //从串口中读取数据
    int read_datas_tty(int fd,char *rcv_buf,int TimeOut,int Len);
    //向串口传数据
    int send_data_tty(int fd, char *send_buf,int Len);

    void close_fd(int fd);
};

#endif // SERIALCOM_H
