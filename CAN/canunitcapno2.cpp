#include "canunitcapno2.h"

CanUnitCapno2* CanUnitCapno2::_self = 0;

CanUnitCapno2::CanUnitCapno2(QObject *parent):
    CanUnit(parent)
{
    processFunctions[canId::capno2::ID_STATUS_CAPNO2   ] = static_cast<typeProcessCanMessage>(&CanUnitCapno2::process_ID_STATUS_CAPNO2);
    processFunctions[canId::capno2::ID_WAVE_CAPNO2     ] = static_cast<typeProcessCanMessage>(&CanUnitCapno2::process_ID_WAVE_CAPNO2);
    processFunctions[canId::capno2::ID_DATA_CAPNO2     ] = static_cast<typeProcessCanMessage>(&CanUnitCapno2::process_ID_DATA_CAPNO2);
    processFunctions[canId::capno2::ID_VERSION_CAPNO2  ] = static_cast<typeProcessCanMessage>(&CanUnitCapno2::process_ID_VERSION_CAPNO2);
}

CanUnitCapno2 *CanUnitCapno2::instance()
{
    if (_self == 0)
        _self = new CanUnitCapno2();
    return _self;
}



void CanUnitCapno2::process_ID_STATUS_CAPNO2(const CanMessage &msg)
{

}

void CanUnitCapno2::process_ID_WAVE_CAPNO2(const CanMessage &msg)
{

}

void CanUnitCapno2::process_ID_DATA_CAPNO2(const CanMessage &msg)
{

}

void CanUnitCapno2::process_ID_VERSION_CAPNO2(const CanMessage &msg)
{

}
