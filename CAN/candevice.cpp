#include "candevice.h"

CanDevice* CanDevice::_self = 0;

CanDevice::CanDevice(QObject *parent) :
    QObject(parent)
{
    setCanDeviceMode(CANDEVICE_MODE_UNKNOWN);
}

bool CanDevice::registerCanUnit( CanUnit* unit)
{
    QSet<quint32> ids = unit->getMessageIDsSet();
    if (ids.count() == 0)
    {
        qDebug() << "Error: register empty CanUnit in CanDevice!";
        return false;
    }
    QSet<quint32> intersect = canUnitsMap.keys().toSet().intersect(ids);
    if(intersect.count() != 0)
    {
        qDebug() << "Error: found CAN ID conflict: " << intersect;
        return false;
    }
    foreach(quint32 id, ids)
        canUnitsMap[id] = unit;
    return true;
}

bool CanDevice::unRegisterCanUnit(CanUnit *unit)
{
    if(!canUnitsMap.values().contains(unit))
    {
        qDebug() << "Warning: This CanUnit already unregistered!";
        return false;
    }
    QMap<quint32,CanUnit*>::iterator it = canUnitsMap.begin();
    for( ; it != canUnitsMap.end(); ++it)
        if(it.value() == unit)
        {
            it = --canUnitsMap.erase(it);
        }
    return true;
}




CanDevice *CanDevice::instance()
{
    //qDebug() << "candevice instance. it is bad";

    return _self;
}


void CanDevice::receiveMessage(const CanMessage& msg)
{
        if(canUnitsMap.contains(msg.id)) // если оно есть в списке для обработки
        {
           // if(msg.id != 1190) qDebug()<<"read msg!: " + msg.toString();

            CanUnit* unit = canUnitsMap[msg.id];
            unit->canMessageProcessing(msg); // то вызываем отдаём на обработку CAN - устройству
        }
}
