#include "canunitkivl.h"
#include "graphics/graphicmanager.h"
#include "ventmode/ventmodemanager.h"

CanUnitKIVL* CanUnitKIVL::_self = 0;

CanUnitKIVL::CanUnitKIVL(QObject *parent):
    CanUnit(parent)
{
    qRegisterMetaType<civlModes>("civlModes");

    vexpAvgIndex = 0;
    vexpAvg[0] = 0;
    vexpAvg[1] = 0;
    vexpAvg[2] = 0;
    vexpAvg[3] = 0;

    m_inspWasSpont = false;

    setCivlMode(CIVL_MODE_UNKNOWN);
    processFunctions[ canId::kivl::ID_INSP_CIVL       ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_INSP_CIVL       );
    processFunctions[ canId::kivl::ID_WAVE_CIVL       ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_WAVE_CIVL       );
    processFunctions[ canId::kivl::ID_STATUS_CIVL     ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_STATUS_CIVL     );
    processFunctions[ canId::kivl::ID_CLBR_ERR_CIVL   ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_CLBR_ERR_CIVL   );
    processFunctions[ canId::kivl::ID_VERSION_CIVL    ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_VERSION_CIVL    );
    processFunctions[ canId::kivl::ID_M_VINSP_CIVL    ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_VINSP_CIVL    );
    processFunctions[ canId::kivl::ID_M_VEXP_CIVL     ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_VEXP_CIVL     );
    processFunctions[ canId::kivl::ID_M_PEEP_CIVL	  ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_PEEP_CIVL	  );
    processFunctions[ canId::kivl::ID_M_RB_CIVL	      ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_RB_CIVL	      );
    processFunctions[ canId::kivl::ID_M_PIP_CIVL	  ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_PIP_CIVL	  );
    processFunctions[ canId::kivl::ID_M_MV_CIVL	      ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_MV_CIVL	      );
    processFunctions[ canId::kivl::ID_M_TEXP_CIVL	  ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_TEXP_CIVL	  );
    processFunctions[ canId::kivl::ID_M_TINSP_CIVL    ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_TINSP_CIVL    );
    processFunctions[ canId::kivl::ID_M_COMPL_CIVL    ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_COMPL_CIVL    );
    processFunctions[ canId::kivl::ID_M_LEAK_CIVL     ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_LEAK_CIVL     );
    processFunctions[ canId::kivl::ID_WORKTIME_CIVL   ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_WORKTIME_CIVL   );
    processFunctions[ canId::kivl::ID_OXYVOLTAGE_CIVL ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_OXYVOLTAGE_CIVL );
    processFunctions[ canId::kivl::ID_M_PPLATO_CIVL   ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_PPLATO_CIVL   );
    processFunctions[ canId::kivl::ID_M_FLOWPEAK_CIVL ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_FLOWPEAK_CIVL );
    processFunctions[ canId::kivl::ID_M_AIRWAY_CIVL   ] = static_cast<typeProcessCanMessage>(&CanUnitKIVL::process_ID_M_AIRWAY_CIVL   );

    currPIP        = new MeasureParameter( 0xFFFF, false); /* PIP [см вод.ст.] */
    currRB         = new MeasureParameter(      0, true ); /* Частота дыхания */
    currRBspont    = new MeasureParameter(      0, true ); /* Частота спонтанных дыханий */
    currPplato     = new MeasureParameter(      0, true ); /* давление плато [смН2О] */
    currTe         = new MeasureParameter(      0, true ); /* Время выдоха [мсек] */
    currTi         = new MeasureParameter(      0, true ); /* Время вдоха  [мсек] */
    currVE         = new MeasureParameter(      0, true );
    currVEa        = new MeasureParameter(      0, true );
    currMVspont    = new MeasureParameter(      0, true ); /* Минутный объём спонтанный */
    currC_stat     = new MeasureParameter( 0xFFFF, false); /* Комплайнс статический [0.1 мл/смН2О] */
    currR_stat     = new MeasureParameter( 0xFFFF, false); /* Резистанс статический [ммН2О * с/л] */
    currLSF_C      = new MeasureParameter( 0xFFFF, false); /* Комплайнс [0.1 мл/смН2О] */
    currLSF_R      = new MeasureParameter( 0xFFFF, false); /* Резистанс [ммН2О * с/л]  */
    currVolExp     = new MeasureParameter( 0xFFFF, false); /* объём выдоха [мл] */
    currVolInsp    = new MeasureParameter(      0, true ); /* объём вдоха [мл] */
    currLEAK       = new MeasureParameter(      0, true ); /* утечка [л/мин] */
    currFlowPeak   = new MeasureParameter(      0, true ); /* пиковое значение потока на вдохе */
    currPEEP       = new MeasureParameter( 0xFFFF, false); /* ПДКВ [cм вод.ст.] */
    currAutoPEEP   = new MeasureParameter( 0xFFFF, false); /* АутоПДКВ [мм Н2О] */
    currExpEndFlow = new MeasureParameter( 0xFFFF, false); /* EndExpFlow [0.1 л/мин] */
    currPmean      = new MeasureParameter( 0xFFFF, false); /* Pmean - среднее давление в магистрали вдоха [мм. вод. ст.] */
    currRCExp      = new MeasureParameter( 0xFFFF, false); /* RCExp - постоянная времени на выдохе [мс] */
    currLEAKPerc   = new MeasureParameter( 0xFFFF, false); /* утечка [%] */
    currSI         = new MeasureParameter( 0xFFFF, false); /* стресс индекс */
    currCDyn       = new MeasureParameter(      0, true ); /* динамический комплайнс [мл/см вод.ст.] */
    currWVent      = new MeasureParameter( 0xFFFF, false); /* Работа дыхания аппаратная [0.01 Дж/л] */
    currWSpont     = new MeasureParameter( 0xFFFF, false); /* Работа дыхания пациента   [0.01 Дж/л] */
    currO2         = new MeasureParameter( 0xFFFF, false); /* % содержание кислорода в дыхательной смеси */

    currRSBI       = new MeasureParameter(      0, true ); /* значение RSBI         */
    currPEEPtot    = new MeasureParameter(      0, true ); /* значение PEEP Total = PEEP + AutoPEEP                  */
    currRExp       = new MeasureParameter(      0, true ); /* резистанс дыхательного контура на выдохе [мм вод.ст./(мл/сек)] */
    currTi_Ttot    = new MeasureParameter(      0, true ); /* значение Tinsp/Ttotal */
    currI_E        = new MeasureParameter(      0, true ); /* Отношение вдоха к выдоху [0.01 ед.] */
    currRCInsp     = new MeasureParameter(      0, true ); /* постоянная времени на вдохе [мс] */
    currElastence  = new MeasureParameter( 0xFFFF, false); /* значение эластенса    */
    currMVsp_MV    = new MeasureParameter(      0, true ); /* значение MV_spont/MV  */
    currCCirc      = new MeasureParameter( 0xFFFF, false); /* комплайнс дыхательного контура [мл/см вод.ст.] */
    currRCirc      = new MeasureParameter( 0xFFFF, false); /* резистанс дыхательного контура [0.1 cмH2O * c / л] */

    elOnFiO2error = new TunningParameter(    1,    0,     1 ); //TODO уточнить про все границы
    elFiO2        = new TunningParameter(    5,    1,    50 );
    elPO2         = new TunningParameter(    1,    0,     3 );
    elP           = new TunningParameter(    0,    0,    20 );
    elMVmax       = new TunningParameter(12000, 1000, 50000 );
    elMVmin       = new TunningParameter(    0,    0,  1000 );
    elVExpMax     = new TunningParameter( 4004, 4001,  6000 );
    elVExpMin     = new TunningParameter(    0,    0,  4000 );
    elRBmax       = new TunningParameter(   20,   10,   120 );
    elRBmin       = new TunningParameter(    5,    1,    10 );


//    currFlow        = new MeasureParameter(   1000, true );
//    currFlow_L_min  = new MeasureParameter(    100, true );
//    currVol         = new MeasureParameter(  10000, true );
//    currPR          = new MeasureParameter( 0xFFFF, false); /* Pulse Rate */
//
//    currVO2         = new MeasureParameter(      0, true );
//    currMaxInspLEAK = new MeasureParameter(      0, true ); /* Максимальное значение утечки за время вдоха [л/мин] */
//    currEndExpLEAK  = new MeasureParameter(      0, true ); /* Значение утечки в конце выдоха [л/мин] */
//    currFilling     = new MeasureParameter(      0, true ); /* наполнение - отношение размаха волны к подставке [%] */
//    currLevelFill   = new MeasureParameter(      0, true );
//    currScaleIndFill= new MeasureParameter(      0, true );
//    currEtO2        = new MeasureParameter( 0xFFFF, false); /* концентрация О2 в конце выдоха */
//    currEtCO2_pr    = new MeasureParameter( 0xFFFF, false); /* СО2 на выдохе [0.1%] */
//    currEtCO2_mm    = new MeasureParameter( 0xFFFF, false); /* CO2 на выдохе [мм рт.ст.] */
//    currFiCO2_pr    = new MeasureParameter( 0xFFFF, false); /* СО2 на вдохе [0.1%] */
//    currFiCO2_mm    = new MeasureParameter( 0xFFFF, false); /* CO2 на вдохе [мм рт.ст.] */
//    currSPO2_pr     = new MeasureParameter(    101, true ); /* SPO2 в процентах */
//    currAtmPres     = new MeasureParameter(    760, true ); /* Атмосферное давление [мм рт. ст.] */
//    currP01         = new MeasureParameter(      0, true ); /* величина P0.1 [мм вод.ст.] */
//    currVCO2        = new MeasureParameter(      0, true ); /* элиминация CO2 за цикл [мл] */
//    currMValv       = new MeasureParameter(      0, true ); /* альвеолярная  вентиляция за минуту [0.1 л/мин] */
//    currValv        = new MeasureParameter(      0, true ); /* альвеолярная  вентиляция за цикл [мл] */
//    currVd          = new MeasureParameter(      0, true ); /* мертвое пространство за цикл [мл] */
//    currMVAdapt     = new MeasureParameter( 0xFFFF, false); /* процент MV адаптационный [%] */
//    currPaw1        = new MeasureParameter(      0, true ); /* Мгновенное значение давления после трубки [мм вод. ст.] */
//    currVd_Vt       = new MeasureParameter(      0, true ); /* Отношение объема мертвого пространства к дыхательному объему */

    connect(elRBmin  , SIGNAL(trueValueChanged(qint32)), SLOT(checkBoundsAndErrorsRB()));
    connect(elRBmax  , SIGNAL(trueValueChanged(qint32)), SLOT(checkBoundsAndErrorsRB()));

    connect(elMVmin  , SIGNAL(trueValueChanged(qint32)), SLOT(checkBoundsAndErrorsMV()));
    connect(elMVmax  , SIGNAL(trueValueChanged(qint32)), SLOT(checkBoundsAndErrorsMV()));

    connect(elVExpMin, SIGNAL(trueValueChanged(qint32)), SLOT(checkBoundsAndErrorsVolExp()));
    connect(elVExpMax, SIGNAL(trueValueChanged(qint32)), SLOT(checkBoundsAndErrorsVolExp()));

}

CanUnitKIVL *CanUnitKIVL::instance()
{
    if (_self == 0)
        _self = new CanUnitKIVL();
    return _self;
}

void CanUnitKIVL::process_ID_INSP_CIVL(const CanMessage &msg)
{
    quint8 inspFlag = msg.getUInt8(0);

    if(inspFlag == 0xFE || inspFlag == 0xFC)
    {
        emit signalInspiration();
        GraphicManager::instance()->isNeededRefreshLoops = true;
        m_inspWasSpont = true;
        //TODO LEAK
    }
    else if(inspFlag == 0xF8 ||inspFlag == 0xFF)
    {
        GraphicManager::instance()->isNeededRefreshLoops = true;
        m_inspWasSpont = false;
        //TODO LEAK
    }
    else if(inspFlag == 0xFA ||inspFlag == 0xF9 ||inspFlag == 0xFB)
    {
        //TODO LEAK
    }

    if (msg.lenght == 2)
    {
        //TODO P01
    }
}
void CanUnitKIVL::process_ID_WAVE_CIVL(const CanMessage &msg)
{
    GraphicManager::instance()->addPVFData(msg.getInt16(4),msg.getInt16(2),msg.getInt16(0));

}
void CanUnitKIVL::process_ID_STATUS_CIVL(const CanMessage &msg)
{
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailFiO2  ,msg.getBit(3,1));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailF_M   ,msg.getBit(2,4));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailF_P   ,msg.getBit(2,5));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailZ_P   ,msg.getBit(2,6));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailZ_M   ,msg.getBit(2,7));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailCompr ,msg.getBit(2,3));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailEEPROM,msg.getBit(2,0));

    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailC_FG  ,msg.getBit(1,7));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailC_P   ,msg.getBit(1,4));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailC_EMV ,msg.getBit(1,6));
    EventManager::instance()->serviceEvent(EventIDs::Alarm_CIVLStatFailC_FP  ,msg.getBit(1,5));

    EventManager::instance()->serviceEvent(EventIDs::MsgChangeFiO2           ,msg.getBit(4,4));
    EventManager::instance()->serviceEvent(EventIDs::MsgCompleteCalibrFiO2   ,msg.getBit(4,3));

    setCivlMode((CanUnitKIVL::civlModes)msg.getUInt8(0));
    setInitialized(true);

    if( getCivlMode() ==  CIVL_MODE_WORK)
    {
        currO2->setValue(msg.getUInt8(7));
        EventManager::instance()->serviceEvent(EventIDs::AlarmOverPmax       ,msg.getBit(0,3));
        EventManager::instance()->serviceEvent(EventIDs::AlarmOcclusion      ,msg.getBit(0,2));
        VentModeManager::instance()->setIsAPNEA(msg.getBit(0,5));
    }
}
void CanUnitKIVL::process_ID_CLBR_ERR_CIVL(const CanMessage &msg)
{

}
void CanUnitKIVL::process_ID_VERSION_CIVL(const CanMessage &msg)
{
    qDebug()<<"kivl VERSION: " + msg.toString();

}
void CanUnitKIVL::process_ID_M_VINSP_CIVL(const CanMessage &msg)
{
    currVolInsp->setValue(msg.getUInt16(0));
    if (m_inspWasSpont)
    {
        currWSpont->setValue(msg.getUInt16(2));
        currWVent->setValue(0);
    }
    else
    {
        currWSpont->setValue(0);
        currWVent->setValue(msg.getUInt16(2));
    }
}
void CanUnitKIVL::process_ID_M_VEXP_CIVL(const CanMessage &msg)
{
    currVolExp->setAvilability(true);
    currVolExp->setValue(msg.getUInt16(0)); //todo тревога VdVt

    checkBoundsAndErrorsVolExp();

    vexpAvg[vexpAvgIndex] = msg.getUInt16(0);
    vexpAvgIndex = (++vexpAvgIndex)%4;
    calcRSBI();
}
void CanUnitKIVL::process_ID_M_PEEP_CIVL(const CanMessage &msg)
{
    currPEEP->setAvilability(msg.getUInt16(0) != 0xFFFF);
    currPEEP->setValue(msg.getUInt16(0));
    currAutoPEEP->setAvilability(msg.getUInt16(2) != 0xFFFF);
    currAutoPEEP->setValue(msg.getUInt16(2));

    if(currPEEP->getAvilability() && currAutoPEEP->getAvilability())
    {
        currPEEPtot->setAvilability(true);
        currPEEPtot->setValue(currPEEP->getValue() + currAutoPEEP->getValue());
    }
    else currPEEPtot->setAvilability(false);

    currExpEndFlow->setAvilability(msg.getUInt16(4) != 0xFFFF);
    currExpEndFlow->setValue(msg.getInt16(4));
    currRCExp->setAvilability(msg.getUInt16(6) != 0xFFFF);
    currRCExp->setValue(msg.getUInt16(6));
    calcRExp();
}
void CanUnitKIVL::process_ID_M_RB_CIVL(const CanMessage &msg)
{
    //qDebug()<<"getRB: "<<msg.getUInt8(0);
    currRB->setValue(msg.getUInt8(0));
    checkBoundsAndErrorsRB();
    currRBspont->setValue(msg.getUInt8(1));
    calcRSBI();
}
void CanUnitKIVL::process_ID_M_PIP_CIVL(const CanMessage &msg)
{
    currPIP->setAvilability(msg.getUInt8(0) != 0xFF);
    currPIP->setValue(msg.getUInt8(0));

    EventManager::instance()->serviceEvent(EventIDs::AlarmLowLevelPressure, currPIP->getValue() < elP->getTrueValue());

    currCDyn->setAvilability(msg.getUInt16(1) != 0xFFFF);
    currCDyn->setValue(msg.getUInt16(1));
    currSI->setAvilability(msg.getUInt16(3) != 0xFFFF);
    currSI->setValue(msg.getUInt16(3));
}
void CanUnitKIVL::process_ID_M_MV_CIVL(const CanMessage &msg)
{

    currVE->setValue(msg.getUInt16(0)); //VE это как MV только VE =D
    currVEa->setValue(msg.getUInt16(2)); //VE это как MV только VE =D

    checkBoundsAndErrorsMV();

    if(msg.getUInt16(0) - msg.getUInt16(2) > 0) currMVspont->setValue(msg.getUInt16(2));
    else currMVspont->setValue(0);
    if(currVE->getValue() != 0) currMVsp_MV->setValue(100* currMVspont->getValue()/currVE->getValue());
}
void CanUnitKIVL::process_ID_M_TEXP_CIVL(const CanMessage &msg)
{
    currTe->setValue(msg.getUInt16(0));
    calcTiTtot();
    calcIE();
}
void CanUnitKIVL::process_ID_M_TINSP_CIVL(const CanMessage &msg)
{
    currTi->setValue(msg.getUInt16(0));
    calcTiTtot();
}
void CanUnitKIVL::process_ID_M_COMPL_CIVL(const CanMessage &msg)
{
    currC_stat->setValue(msg.getUInt16(0));
    currR_stat->setValue(msg.getUInt16(2));
    currC_stat->setAvilability(msg.getUInt16(0) != 0xFFFF);
    currR_stat->setAvilability(msg.getUInt16(2) != 0xFFFF);
    calcRExp();

    if(currC_stat->getAvilability() && currC_stat->getValue() != 0)
    {
        currElastence->setAvilability(currC_stat->getAvilability());
        currElastence->setValue(((10000 / currC_stat->getValue()) + 5) / 10);
    }
    else currElastence->setAvilability(false);

    if(currC_stat->getAvilability() && currR_stat->getAvilability())
    {
        currRCInsp->setAvilability(true);
        currRCInsp->setValue(currR_stat->getValue() * currC_stat->getValue() / 100);
    }
    else currRCInsp->setAvilability(false);

}
void CanUnitKIVL::process_ID_M_LEAK_CIVL(const CanMessage &msg)
{
    currPmean->setAvilability(msg.getUInt16(0) != 0xFFFF);
    currPmean->setValue(msg.getUInt16(0));

    currLEAK->setAvilability(msg.getUInt16(4)!= 0xFFFF);
    currLEAK->setValue(msg.getUInt16(4));

    currLEAKPerc->setAvilability(msg.getUInt16(6)!= 0xFFFF);
    currLEAKPerc->setValue(msg.getUInt16(6));
}
void CanUnitKIVL::process_ID_WORKTIME_CIVL(const CanMessage &msg)
{

}
void CanUnitKIVL::process_ID_OXYVOLTAGE_CIVL(const CanMessage &msg)
{

}
void CanUnitKIVL::process_ID_M_PPLATO_CIVL(const CanMessage &msg)
{
    currPplato->setValue(msg.getUInt8(0));
}
void CanUnitKIVL::process_ID_M_FLOWPEAK_CIVL(const CanMessage &msg)
{
    currFlowPeak->setValue(msg.getUInt8(0));
}
void CanUnitKIVL::process_ID_M_AIRWAY_CIVL(const CanMessage &msg)
{
    currRCirc->setAvilability(msg.getUInt16(0) != 0xFFFF);
    currRCirc->setValue(msg.getUInt16(0));

    currCCirc->setAvilability(msg.getUInt16(2)!= 0xFFFF);
    currCCirc->setValue(msg.getUInt16(2));
}

void CanUnitKIVL::checkBoundsAndErrorsRB()
{
    //qDebug()<<QThread::currentThreadId()<<": "<<"checkBoundsAndErrorsRB in";
    checkBoundsAndErrors(currRB,elRBmin,elRBmax,EventIDs::AlarmLowFreqBreath,EventIDs::AlarmHighFreqBreath);
    //qDebug()<<QThread::currentThreadId()<<": "<<"checkBoundsAndErrorsRB out";
}

void CanUnitKIVL::checkBoundsAndErrorsMV()
{
    checkBoundsAndErrors(currVE,elMVmin,elMVmax,EventIDs::AlarmLowVE,EventIDs::AlarmHighVE);
}

void CanUnitKIVL::checkBoundsAndErrorsVolExp()
{
    checkBoundsAndErrors(currVolExp,elVExpMin,elVExpMax,EventIDs::AlarmLowVT, EventIDs::AlarmHighVT);
}

void CanUnitKIVL::calcRSBI()
{
    if(vexpAvg[0] != 0 || vexpAvg[1] != 0 || vexpAvg[2] != 0 || vexpAvg[3] != 0)
        currRSBI->setValue(4000 * currRBspont->getValue() / (vexpAvg[0] + vexpAvg[1] + vexpAvg[2] + vexpAvg[3]));
    else currRSBI->setValue(0);
}

void CanUnitKIVL::calcRExp()
{
    if(currC_stat->getAvilability() && currRCExp->getAvilability() && currC_stat->getValue() != 0)
    {
        currRExp->setAvilability(true);
        currRExp->setValue(10* currRCExp->getValue() / currC_stat->getValue());
    }
}

void CanUnitKIVL::calcTiTtot()
{
    if(currTi->getValue() != 0 || currTe->getValue() != 0)
    {
        currTi_Ttot->setAvilability(true);
        currTi_Ttot->setValue(100*currTi->getValue() / (currTi->getValue() + currTe->getValue()));
    }
    else currTi_Ttot->setAvilability(false);
}

void CanUnitKIVL::calcIE()
{
    if(currTe->getValue() == 0)
    {
        currI_E->setAvilability(false);
    }
    else{
        currI_E->setValue(currTi->getValue() * 100/ currTe->getValue());
        currI_E->setAvilability(true);
    }
}

void CanUnitKIVL::bindContext(QQmlContext *ctx)
{
    //qDebug()<< "bind context: " << QThread::currentThreadId();
    ctx->setContextProperty("elOnFiO2error"    , elOnFiO2error   );
    ctx->setContextProperty("elFiO2"           , elFiO2          );
    ctx->setContextProperty("elPO2"            , elPO2           );
    ctx->setContextProperty("elP"              , elP             );
    ctx->setContextProperty("elMVmax"          , elMVmax         );
    ctx->setContextProperty("elMVmin"          , elMVmin         );
    ctx->setContextProperty("elVExpMax"        , elVExpMax       );
    ctx->setContextProperty("elVExpMin"        , elVExpMin       );
    ctx->setContextProperty("elRBmax"          , elRBmax         );
    ctx->setContextProperty("elRBmin"          , elRBmin         );

    ctx->setContextProperty("currPIP"         , currPIP          );
    ctx->setContextProperty("currRB"          , currRB           );
    ctx->setContextProperty("currRBspont"     , currRBspont      );
    ctx->setContextProperty("currPplato"      , currPplato       );
    ctx->setContextProperty("currTe"          , currTe           );
    ctx->setContextProperty("currTi"          , currTi           );
    ctx->setContextProperty("currVE"          , currVE           );
    ctx->setContextProperty("currVEa"         , currVEa          );
    ctx->setContextProperty("currMVspont"     , currMVspont      );
    ctx->setContextProperty("currC_stat"      , currC_stat       );
    ctx->setContextProperty("currR_stat"      , currR_stat       );
    ctx->setContextProperty("currLSF_C"       , currLSF_C        );
    ctx->setContextProperty("currLSF_R"       , currLSF_R        );
    ctx->setContextProperty("currVolExp"      , currVolExp       );
    ctx->setContextProperty("currVolInsp"     , currVolInsp      );
    ctx->setContextProperty("currLEAK"        , currLEAK         );
    ctx->setContextProperty("currFlowPeak"    , currFlowPeak     );
    ctx->setContextProperty("currPEEP"        , currPEEP         );
    ctx->setContextProperty("currAutoPEEP"    , currAutoPEEP     );
    ctx->setContextProperty("currExpEndFlow"  , currExpEndFlow   );
    ctx->setContextProperty("currPmean"       , currPmean        );
    ctx->setContextProperty("currRCExp"       , currRCExp        );
    ctx->setContextProperty("currLEAKPerc"    , currLEAKPerc     );
    ctx->setContextProperty("currSI"          , currSI           );
    ctx->setContextProperty("currCDyn"        , currCDyn         );
    ctx->setContextProperty("currWVent"       , currWVent        );
    ctx->setContextProperty("currWSpont"      , currWSpont       );
    ctx->setContextProperty("currO2"          , currO2           );
    ctx->setContextProperty("currRSBI"        , currRSBI         );
    ctx->setContextProperty("currPEEPtot"     , currPEEPtot      );
    ctx->setContextProperty("currRExp"        , currRExp         );
    ctx->setContextProperty("currTi_Ttot"     , currTi_Ttot      );
    ctx->setContextProperty("currI_E"         , currI_E          );
    ctx->setContextProperty("currRCInsp"      , currRCInsp       );
    ctx->setContextProperty("currElastence"   , currElastence    );
    ctx->setContextProperty("currMVsp_MV"     , currMVsp_MV      );
    ctx->setContextProperty("currCCirc"       , currCCirc        );
    ctx->setContextProperty("currRCirc"       , currRCirc        );

//    ctx->setContextProperty("currFlow"        , currFlow         );
//    ctx->setContextProperty("currFlow_L_min"  , currFlow_L_min   );
//    ctx->setContextProperty("currVol"         , currVol          );
//    ctx->setContextProperty("currPR"          , currPR           );
//    ctx->setContextProperty("currVO2"         , currVO2          );
//    ctx->setContextProperty("currMaxInspLEAK" , currMaxInspLEAK  );
//    ctx->setContextProperty("currEndExpLEAK"  , currEndExpLEAK   );
//    ctx->setContextProperty("currFilling"     , currFilling      );
//    ctx->setContextProperty("currLevelFill"   , currLevelFill    );
//    ctx->setContextProperty("currScaleIndFill", currScaleIndFill );
//    ctx->setContextProperty("currEtO2"        , currEtO2         );
//    ctx->setContextProperty("currEtCO2_pr"    , currEtCO2_pr     );
//    ctx->setContextProperty("currEtCO2_mm"    , currEtCO2_mm     );
//    ctx->setContextProperty("currFiCO2_pr"    , currFiCO2_pr     );
//    ctx->setContextProperty("currFiCO2_mm"    , currFiCO2_mm     );
//    ctx->setContextProperty("currSPO2_pr"     , currSPO2_pr      );
//    ctx->setContextProperty("currAtmPres"     , currAtmPres      );
//    ctx->setContextProperty("currP01"         , currP01          );
//    ctx->setContextProperty("currVCO2"        , currVCO2         );
//    ctx->setContextProperty("currMValv"       , currMValv        );
//    ctx->setContextProperty("currValv"        , currValv         );
//    ctx->setContextProperty("currVd"          , currVd           );
//    ctx->setContextProperty("currMVAdapt"     , currMVAdapt      );
//    ctx->setContextProperty("currPaw1"        , currPaw1         );
//    ctx->setContextProperty("currVd_Vt"       , currVd_Vt        );

}
