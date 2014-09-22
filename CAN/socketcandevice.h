#ifndef SOCKETCANDEVICE_H
#define SOCKETCANDEVICE_H


#include "candevice.h"
#include "socketcanrt.h"
#include "socketcanwt.h"

class SocketCanDevice: public CanDevice
{
    Q_OBJECT
    SocketCanRt* canRT;
    SocketCanWt* canWT;
protected:
    SocketCanDevice(QObject *parent = 0);
public:
    /// определение метода получения ссылки на объект
    static CanDevice* instance();
    void sendMessage(const CanMessage& msg);
    void startInit();
public slots:
    void catchMsg();
};

#endif // SOCKETCANDEVICE_H
