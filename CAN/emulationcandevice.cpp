#include "emulationcandevice.h"

EmulationCanDevice::EmulationCanDevice(QObject *parent): CanDevice(parent)
{
}

void EmulationCanDevice::sendMessage(const CanMessage &msg)
{
    qDebug()<<"sending msg: "<< msg.toString();
}

void EmulationCanDevice::startInit()
{
    emit canDeviceModeChanged(CanDevice::CANDEVICE_MODE_WORK);
}

CanDevice *EmulationCanDevice::instance()
{
    if(!_self)
    {
        _self = new EmulationCanDevice();
    }
    return _self;
}
