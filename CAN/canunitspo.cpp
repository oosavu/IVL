#include "canunitspo.h"

CanUnitSPO* CanUnitSPO::_self = 0;

void CanUnitSPO::process1(const CanMessage &msg)
{
   // qDebug() << "SPO!"<< msg.toString();
}

CanUnitSPO::CanUnitSPO(QObject *parent):
    CanUnit(parent)
{
 //   m_unitID = UnitID_SPO;
    processFunctions[canId::spo::ID_STATUS_SPO  ] = static_cast<typeProcessCanMessage>(&CanUnitSPO::process1);
    processFunctions[canId::spo::ID_VERSION_SPO ] = static_cast<typeProcessCanMessage>(&CanUnitSPO::process1);
    processFunctions[canId::spo::ID_WAVE_SPO    ] = static_cast<typeProcessCanMessage>(&CanUnitSPO::process1);
}

CanUnitSPO *CanUnitSPO::instance()
{
    if (_self == 0)
        _self = new CanUnitSPO();
    return _self;
}
