#include "socketcanrt.h"


SocketCanRt::SocketCanRt(QObject *parent)
{
    socket = new Socket();
}

void SocketCanRt::run()
{
    //qDebug()<< "SocketCanRt: " << QThread::currentThreadId();
    for(;;)
    {
        socket->readMsg();
        emit gettingMessage();
    }
}
