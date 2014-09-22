#ifndef SOCKETCANRT_H
#define SOCKETCANRT_H

#include <QThread>
#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <net/if.h>
//#include <sys/ioctl.h>
//#include <linux/can.h>
//#include <linux/can/raw.h>

#include "socket.h"

class SocketCanRt : public QThread
{
    Q_OBJECT
public:
    explicit SocketCanRt(QObject *parent = 0);
    void run();
    Socket* socket;
   // CanMessage& msg;
private:

signals:
    void gettingMessage(/*const CanMessage& msg*/);

public slots:

};

#endif // SOCKETCANRT_H
