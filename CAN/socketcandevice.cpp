#include "socketcandevice.h"

SocketCanDevice::SocketCanDevice(QObject *parent):
    CanDevice(parent)
{
    canRT = new SocketCanRt();
    canWT = new SocketCanWt();
    connect(canRT,SIGNAL(gettingMessage(/*const CanMessage&*/)),this,SLOT(catchMsg(/*const CanMessage& */)),Qt::DirectConnection);
}

CanDevice *SocketCanDevice::instance()
{
    if(!_self)
    {
        _self = new SocketCanDevice();
    }
    return _self;
}

void SocketCanDevice::sendMessage(const CanMessage &msg)
{
    canWT->buffer->push(msg);
}

void SocketCanDevice::startInit()
{
    emit canDeviceModeChanged(SocketCanDevice::CANDEVICE_MODE_WORK);
    canRT->start();
    canWT->start();
}

void SocketCanDevice::catchMsg(/*const CanMessage& msg*/)
{
   // qDebug()<<canRT->buffer->msgQueue.count();
    receiveMessage(canRT->socket->lastMsg);
}
