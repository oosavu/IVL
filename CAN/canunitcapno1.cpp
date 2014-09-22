#include "canunitcapno1.h"
#include "graphics/graphicmanager.h"

CanUnitCapno1* CanUnitCapno1::_self = 0;

CanUnitCapno1::CanUnitCapno1(QObject *parent):
    CanUnit(parent)
{
   // m_unitID = UnitID_CAPNO1;
    processFunctions[canId::capno1::ID_STATUS_CAPNO1      ] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_STATUS_CAPNO1      );
    processFunctions[canId::capno1::ID_VERSION_CAPNO1     ] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_VERSION_CAPNO1     );
    processFunctions[canId::capno1::ID_WAVE_CAPNO1        ] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_WAVE_CAPNO1        );
    processFunctions[canId::capno1::ID_CO2_DATA_CAPNO1    ] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_CO2_DATA_CAPNO1    );
    processFunctions[canId::capno1::ID_O2_DATA_CAPNO1     ] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_O2_DATA_CAPNO1     );
    processFunctions[canId::capno1::ID_CALOXY_DEBUG_CAPNO1] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_CALOXY_DEBUG_CAPNO1);
    processFunctions[canId::capno1::ID_CALIBR_MSG_CAPNO1  ] = static_cast<typeProcessCanMessage>(&CanUnitCapno1::process_ID_CALIBR_MSG_CAPNO1  );

    currEtO2        = new MeasureParameter( 0xFFFF, false); /* концентрация О2 в конце выдоха */
    currEtCO2_pr    = new MeasureParameter( 0xFFFF, false); /* СО2 на выдохе [0.1%] */
    currEtCO2_mm    = new MeasureParameter( 0xFFFF, false); /* CO2 на выдохе [мм рт.ст.] */
    currFiCO2_pr    = new MeasureParameter( 0xFFFF, false); /* СО2 на вдохе [0.1%] */
    currFiCO2_mm    = new MeasureParameter( 0xFFFF, false); /* CO2 на вдохе [мм рт.ст.] */
    currVO2         = new MeasureParameter(      0, true );

    elEtCO2prMin    = new TunningParameter(  20,   20,   60 );
    elEtCO2prMax    = new TunningParameter(  60,   20,  120 );
    elEtCO2mmMin    = new TunningParameter(  15,  15,  40 );
    elEtCO2mmMax    = new TunningParameter(  40,  15, 100 );

    connect(elEtCO2prMin, SIGNAL(trueValueChanged(qint32)),SLOT(checkBoundsAndErrorsEtCO2()));
    connect(elEtCO2prMax, SIGNAL(trueValueChanged(qint32)),SLOT(checkBoundsAndErrorsEtCO2()));
    connect(elEtCO2mmMin, SIGNAL(trueValueChanged(qint32)),SLOT(checkBoundsAndErrorsEtCO2()));
    connect(elEtCO2mmMax, SIGNAL(trueValueChanged(qint32)),SLOT(checkBoundsAndErrorsEtCO2()));

}

void CanUnitCapno1::process_ID_STATUS_CAPNO1(const CanMessage &msg)
{

    setInitialized(true);
    quint8 capno1Status = msg.getUInt8(0);
    //qDebug()<<"capno:" << capno1Status;
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg01 , capno1Status == 0x01);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg02 , capno1Status == 0x02);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg03 , capno1Status == 0x03);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg04 , capno1Status == 0x04);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg05 , capno1Status == 0x05);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg07 , capno1Status == 0x10);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg08 , capno1Status == 0x11);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg09 , capno1Status == 0x12);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg10 , capno1Status == 0x13);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg11 , capno1Status == 0x14);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg12 , capno1Status == 0x15);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg13 , capno1Status == 0x16);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg14 , capno1Status == 0x17);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg15 , capno1Status == 0x18);
    EventManager::instance()->serviceEvent( EventIDs::CapnoMsg16 , capno1Status == 0x19);
}

void CanUnitCapno1::process_ID_VERSION_CAPNO1(const CanMessage &msg)
{

}

void CanUnitCapno1::process_ID_WAVE_CAPNO1(const CanMessage &msg)
{
    //qDebug()<<msg.getInt16(0)<<" " <<msg.getInt16(2);
    GraphicManager::instance()->addCapnoData(msg.getInt16(0),msg.getInt16(2));
}

void CanUnitCapno1::process_ID_CO2_DATA_CAPNO1(const CanMessage &msg)
{
    currEtCO2_pr->setAvilability(msg.getUInt8(0) != 0xFF);
    currFiCO2_pr->setAvilability(msg.getUInt8(1) != 0xFF);
    currEtCO2_mm->setAvilability(msg.getUInt8(2) != 0xFF);
    currFiCO2_mm->setAvilability(msg.getUInt8(3) != 0xFF);
    currEtCO2_pr->setValue(msg.getUInt8(0));
    currFiCO2_pr->setValue(msg.getUInt8(1));
    currEtCO2_mm->setValue(msg.getUInt8(2));
    currFiCO2_mm->setValue(msg.getUInt8(3));

   // qDebug()<<"currEtCO2_pr: "<< msg.getUInt8(0) <<"currEtCO2_mm: "<< msg.getUInt8(2);
    checkBoundsAndErrorsEtCO2();
            //TODO как быть с тем что у нас еще тревоги по процентам?
}

void CanUnitCapno1::process_ID_O2_DATA_CAPNO1(const CanMessage &msg)
{
    currEtO2->setAvilability(msg.getUInt16(0) < 1000);
    currEtO2->setValue(msg.getUInt16(0));

    currVO2->setAvilability(msg.getUInt16(0) < 1000 && msg.getUInt16(2) < 1000);
    currVO2->setValue(qAbs(msg.getUInt16(2) - msg.getUInt16(0) + 5));
}

void CanUnitCapno1::process_ID_CALOXY_DEBUG_CAPNO1(const CanMessage &msg)
{

}

void CanUnitCapno1::process_ID_CALIBR_MSG_CAPNO1(const CanMessage &msg)
{

}

CanUnitCapno1 *CanUnitCapno1::instance()
{
    if (_self == 0)
        _self = new CanUnitCapno1();
    return _self;
}

void CanUnitCapno1::bindContext(QQmlContext *ctx)
{
    ctx->setContextProperty("currVO2"         , currVO2          );
    ctx->setContextProperty("currEtO2"        , currEtO2         );
    ctx->setContextProperty("currEtCO2_pr"    , currEtCO2_pr     );
    ctx->setContextProperty("currEtCO2_mm"    , currEtCO2_mm     );
    ctx->setContextProperty("currFiCO2_pr"    , currFiCO2_pr     );
    ctx->setContextProperty("currFiCO2_mm"    , currFiCO2_mm     );
    ctx->setContextProperty("elEtCO2prMin"    , elEtCO2prMin     );
    ctx->setContextProperty("elEtCO2prMax"    , elEtCO2prMax     );
    ctx->setContextProperty("elEtCO2mmMin"    , elEtCO2mmMin     );
    ctx->setContextProperty("elEtCO2mmMax"    , elEtCO2mmMax     );
}

void CanUnitCapno1::checkBoundsAndErrorsEtCO2()
{
    elEtCO2mmMax->setMinValue(elEtCO2mmMin->getCurrValue());
    elEtCO2mmMin->setMaxValue(elEtCO2mmMax->getCurrValue());
    elEtCO2prMax->setMinValue(elEtCO2prMin->getCurrValue());
    elEtCO2prMin->setMaxValue(elEtCO2prMax->getCurrValue());

    bool isMinError = (currEtCO2_mm->getValue() < elEtCO2mmMin->getTrueValue() && currEtCO2_mm->getAvilability())
    ||(currEtCO2_pr->getValue() < elEtCO2prMin->getTrueValue() && currEtCO2_pr->getAvilability());
    EventManager::instance()->serviceEvent(EventIDs::AlarmLowEtCO2,isMinError);

    bool isMaxError = (currEtCO2_mm->getValue() > elEtCO2mmMax->getTrueValue() && currEtCO2_mm->getAvilability()) ||
            (currEtCO2_pr->getValue() > elEtCO2prMax->getTrueValue() && currEtCO2_pr->getAvilability());
    EventManager::instance()->serviceEvent(EventIDs::AlarmHighEtCO2,isMaxError);

   // currEtCO2_mm->setErrorLevel();

}
