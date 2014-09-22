#ifndef SOCKET_H
#define SOCKET_H

#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <net/if.h>
//#include <sys/ioctl.h>
//#include <linux/can.h>
//#include <linux/can/raw.h>

#include "canbuffer.h"

class Socket
{
public:
    Socket();
    void writeMsg(const CanMessage& msg);
    CanMessage lastMsg;
    void readMsg();

private:
    //struct can_frame frame;
    int sock;
};

#endif // SOCKET_H
