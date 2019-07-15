#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <termios.h>
enum BaudRateTabl:int
{
    Baud57600   = B57600   ,
    Baud115200  = B115200  ,
    Baud230400  = B230400  ,
    Baud460800  = B460800  ,
    Baud500000  = B500000  ,
    Baud576000  = B576000  ,
    Baud921600  = B921600  ,
    Baud1000000 = B1000000 ,
    Baud1152000 = B1152000 ,
    Baud1500000 = B1500000 ,
    Baud2000000 = B2000000 ,
    Baud2500000 = B2500000 ,
    Baud3000000 = B3000000 ,
    Baud3500000 = B3500000 ,
    Baud4000000 = B4000000 ,
};

class serialport
{
public:
    serialport();
    static int init(const char *device_name, BaudRateTabl baud);
    static int free(int fd);
private:
    static int set_interface_attribs (int fd, int speed, int parity);
    static void set_blocking (int fd, int should_block);
};

#endif // SERIALPORT_H
