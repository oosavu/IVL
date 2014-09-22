#ifndef SOCKETCANWT_H
#define SOCKETCANWT_H

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

class SocketCanWt : public QThread
{
    Q_OBJECT
public:
    explicit SocketCanWt(QObject *parent = 0);
    void run();
    CanBuffer* buffer;
    Socket* socket;
private:


signals:

public slots:

};

#endif // SOCKETCANWT_H
