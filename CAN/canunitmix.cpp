#include "canunitmix.h"
#include "regimemanager.h"


CanUnitMix* CanUnitMix::_self = 0;


CanUnitMix::CanUnitMix(QObject *parent):
    CanUnit(parent)
{
    qRegisterMetaType<mixModes>("mixModes");
    setMixMode(MIX_MODE_UNKNOWN);

    currPOxy = new MeasureParameter( 0xFFFF, false);
    elPOxyLim = new TunningParameter(2,0,3);

    connect(elPOxyLim, SIGNAL(trueValueChanged(qint32)),SLOT(calcPOxyErrors()));

    processFunctions[canId::mix::ID_STATUS_MIX     ] = static_cast<typeProcessCanMessage>(&CanUnitMix::process_ID_STATUS_MIX);
    processFunctions[canId::mix::ID_VERSION_MIX    ] = static_cast<typeProcessCanMessage>(&CanUnitMix::process_ID_VERSION_MIX);
}

CanUnitMix *CanUnitMix::instance()
{
    if (_self == 0)
        _self = new CanUnitMix();
    return _self;
}

void CanUnitMix::bindContext(QQmlContext *ctx)
{
    ctx->setContextProperty("currPOxy"     , currPOxy    );
    ctx->setContextProperty("elPOxyLim"    , elPOxyLim   );
}

void CanUnitMix::calcPOxyErrors()
{
    if(currPOxy->getAvilability())
    {
        EventManager::instance()->serviceEvent(EventIDs::AlarmHighPressureOxy,currPOxy->getValue() <  elPOxyLim->getTrueValue()*5);
        EventManager::instance()->serviceEvent(EventIDs::AlarmLowPressureOxy,currPOxy->getValue() > 25);
    }
}

void CanUnitMix::process_ID_STATUS_MIX(const CanMessage &msg)
{
//    emit signalGetStatus();
    setMixMode(mixModes(msg.getUInt8(3)));
    setInitialized(true);
    currPOxy->setValue(msg.getUInt8(0));

    EventManager::instance()->serviceEvent(EventIDs::Alarm_MixStatFailPressOxy, msg.getBit(7,7)); // При неисправном датчике давления для магистрали кислорода
    EventManager::instance()->serviceEvent(EventIDs::Alarm_MixStatFailPressAbs, msg.getBit(7,6)); // При неисправном датчике  абсолютного давления перед ГП
    EventManager::instance()->serviceEvent(EventIDs::Alarm_MixStatFailPropOxy , msg.getBit(7,1)); // При неисправном пропорциональном клапане О2
    EventManager::instance()->serviceEvent(EventIDs::Alarm_MixStatFailC_P_Abs , msg.getBit(6,4)); // Не откалиброван датчик абсолютного давления перед ГП

    if (getMixMode() == MIX_MODE_WORK)
    {
        calcPOxyErrors();
    }
    else if (getMixMode() == MIX_MODE_AR1)
        RegimeManager::instance()->setRegimeManagerMode(RegimeManager::REGIMEMANAGER_MODE_AR1);
    else if (getMixMode() == MIX_MODE_AR2)
        RegimeManager::instance()->setRegimeManagerMode(RegimeManager::REGIMEMANAGER_MODE_AR2);
    else if (getMixMode() == MIX_MODE_AR3)
        RegimeManager::instance()->setRegimeManagerMode(RegimeManager::REGIMEMANAGER_MODE_AR3);
    else if (getMixMode() == MIX_MODE_PAR)
        RegimeManager::instance()->setRegimeManagerMode(RegimeManager::REGIMEMANAGER_MODE_PAR);
}

void CanUnitMix::process_ID_VERSION_MIX(const CanMessage &msg)
{
}
