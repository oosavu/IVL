#include "canunitpower.h"


CanUnitPower* CanUnitPower::_self = 0;

CanUnitPower::CanUnitPower(QObject *parent):
    CanUnit(parent)
{
    qRegisterMetaType<powerModes>("powerModes");
    setPowerMode(POWER_MODE_UNKNOWN);
    processFunctions[canId::power1::ID_OFF_PWR     ] = static_cast<typeProcessCanMessage>(&CanUnitPower::process_ID_OFF_POWER);
    processFunctions[canId::power2::ID_STATUS_PWR  ] = static_cast<typeProcessCanMessage>(&CanUnitPower::process_ID_STATUS_POWER);
    processFunctions[canId::power2::ID_VERSION_PWR ] = static_cast<typeProcessCanMessage>(&CanUnitPower::process_ID_VERSION_POWER);
}

CanUnitPower *CanUnitPower::instance()
{
    if (_self == 0)
        _self = new CanUnitPower();
    return _self;
}


void CanUnitPower::process_ID_STATUS_POWER(const CanMessage &msg)
{
    //qDebug()<<msg.lenght;
    setPowerMode(POWER_MODE_WAIT); //TODO странности с этим статусом.
    setInitialized(true);
    setIsCharging(!msg.getBit(2,0));
    setChargeLevel(msg.getUInt8(1));
    if(msg.lenght == 5) setCurrSoundState((soundStates)msg.getUInt8(4));
    else setCurrSoundState((soundStates)msg.getUInt8(3));

    EventManager::instance()->serviceEvent(EventIDs::AlarmDischarge     ,   getChargeLevel() < 10  );   /* Баттарея разряжена */
    EventManager::instance()->serviceEvent(EventIDs::AlarmPowerOut      ,   msg.getBit(2,0)        );   /* "Нет сетевого питания" */
    EventManager::instance()->serviceEvent(EventIDs::AlarmVentFail      ,   msg.getBit(2,1)        );
    EventManager::instance()->serviceEvent(EventIDs::AlarmTimeOut10min  ,   msg.getBit(2,2)        );
    EventManager::instance()->serviceEvent(EventIDs::AlarmTransFail     ,   msg.getBit(2,6)        );/* "  Неисправность ключа ЗУ      " */
    EventManager::instance()->serviceEvent(EventIDs::Alarm52            ,   msg.getBit(2,7)        );
    if(msg.lenght == 5) EventManager::instance()->serviceEvent(EventIDs::MsgExtPowerSource  ,   msg.getBit(3,0)        );
}

void CanUnitPower::process_ID_VERSION_POWER(const CanMessage &msg)
{
}


void CanUnitPower::process_ID_OFF_POWER(const CanMessage &msg)
{
}
