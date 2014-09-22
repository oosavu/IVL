#include "socketcanwt.h"

SocketCanWt::SocketCanWt(QObject *parent) :
    QThread(parent)
{
    buffer = new CanBuffer();
    socket = new Socket();
}

void SocketCanWt::run()
{
    //qDebug()<< "SocketCanWt: " << QThread::currentThreadId();
    for(;;)
    {
        socket->writeMsg(buffer->pop());
    }
}
