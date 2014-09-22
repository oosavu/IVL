#include "regimemanager.h"

RegimeManager* RegimeManager::_self = 0;

RegimeManager::RegimeManager(QObject *parent) :
    QObject(parent)
{
   // qDebug() << "RegimeManager constructor";
    qRegisterMetaType<regimeManagerModes>("regimeManagerModes");
    setRegimeManagerMode(REGIMEMANAGER_MODE_WAIT);
}

RegimeManager *RegimeManager::instance()
{
    //qDebug() << "RegimeManager instance";
    if(!_self)
    {
        _self = new RegimeManager();
    }
    return _self;
}

void RegimeManager::slotCanDeviceMode(CanDevice::canDeviceModes arg) //todo
{
    if(arg == CanDevice::CANDEVICE_MODE_WORK)
    {
        setRegimeManagerMode(REGIMEMANAGER_MODE_COMMON_INIT);
        CanManager::instance()->startInitCanUnits();
    }
}
