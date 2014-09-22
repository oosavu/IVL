#include "ventmodemanager.h"

//опеределение статических переменных
VentModeManager*     VentModeManager::_self = 0 ;
TunningParameter     VentModeManager::tpFiO2           ;
TunningParameter     VentModeManager::tpPMax           ;
TunningParameter     VentModeManager::tpPTrig          ;
TunningParameter     VentModeManager::tpFTrig          ;
TunningParameter     VentModeManager::tpRB             ;
TunningParameter     VentModeManager::tpPEEP           ;
TunningParameter     VentModeManager::tpVInsp          ;
TunningParameter     VentModeManager::tpTInsp          ;
TunningParameter     VentModeManager::tpPSupp          ;
TunningParameter     VentModeManager::tpPInsp          ;
TunningParameter     VentModeManager::tpPHigh          ;
TunningParameter     VentModeManager::tpPLow           ;
TunningParameter     VentModeManager::tpTHigh          ;
TunningParameter     VentModeManager::tpTLow           ;
TunningParameter     VentModeManager::tpPlato          ;
TunningParameter     VentModeManager::tpFSupp          ;
TunningParameter     VentModeManager::tpFormFlow       ;
TunningParameter     VentModeManager::tpTrigWnd        ;
TunningParameter     VentModeManager::tpPramp          ;
TunningParameter     VentModeManager::tpPercMV         ;
TunningParameter     VentModeManager::tpAdaptMV        ;
TunningParameter     VentModeManager::tpOpenValve      ;
TunningParameter     VentModeManager::tpETS            ;
TunningParameter     VentModeManager::tpETC            ;
TunningParameter     VentModeManager::tpApneaRegime    ;
TunningParameter     VentModeManager::tpApneaV         ;
TunningParameter     VentModeManager::tpApneaPi        ;
TunningParameter     VentModeManager::tpApneaRB        ;
TunningParameter     VentModeManager::tpApneaT         ;
TunningParameter     VentModeManager::tpISVVt          ;
TunningParameter     VentModeManager::tpISVVtMax       ;
TunningParameter     VentModeManager::tpISVrazgIRV     ;
TunningParameter     VentModeManager::tpTrigMode       ;
TunningParameter     VentModeManager::tpFACC           ;
TunningParameter     VentModeManager::tpComplPeriod    ;
TunningParameter     VentModeManager::tpFEnd           ;
TunningParameter     VentModeManager::tpSigh           ;
TunningParameter     VentModeManager::tpVInspTrig      ;
TunningParameter     VentModeManager::tpDisconSens     ;
TunningParameter     VentModeManager::tpLimPmax        ;
TunningParameter     VentModeManager::tpLimTinsp       ;
TunningParameter     VentModeManager::tpTRazgNIV       ;
TunningParameter     VentModeManager::tpFEndNIV        ;
TunningParameter     VentModeManager::tpTubeType       ;
TunningParameter     VentModeManager::tpTubeDiameter   ;
TunningParameter     VentModeManager::tpLeakComp       ;
TunningParameter     VentModeManager::tpDeltaPEEP      ;
TunningParameter     VentModeManager::tpPatientAge     ;
TunningParameter     VentModeManager::tpPatientGender  ;
TunningParameter     VentModeManager::tpPatientHeight  ;
AssociatedParameter  VentModeManager::apTiTc           ;
AssociatedParameter  VentModeManager::apFlow           ;
AssociatedParameter  VentModeManager::apFlowMax        ;
AssociatedParameter  VentModeManager::apTexp           ;
AssociatedParameter  VentModeManager::apMV             ;
AssociatedParameter  VentModeManager::apTramp          ;


VentModeManager::VentModeManager(QObject *parent) :
    QObject(parent)
{
    setParamRulesMap();
    m_ventMode = (ventmodes)(-1);
    setVentMode(CIVL_VENTMODE_CMV_VCV);
    m_trueVentMode = (ventmodes)(-1);
    setTrueVentMode(CIVL_VENTMODE_UNKNOWN);
    refreshAvilableChangeMode();
    setIsAPNEA(false);
    connect(&tpPatientAge,SIGNAL(currValueChanged(qint32)), this, SLOT(onPatientAgeChanged(qint32)));

    foreach (TunningParameter* tp, rulesScope.keys())
    {
        connect(tp,SIGNAL(currValueChanged(qint32)), this, SLOT(onAnyParameterChange()));
    }
    setInitValues();
    onAnyParameterChange();
//    foreach (NonEditableBoundedTunningParameter* dp, vdpRulesScope.keys())
//    {
//        connect(dp,SIGNAL(valueChanged(qint32)), this, SLOT(onAnyParameterChange()));
//    }
    printStateToConsole(0);
}

void VentModeManager::setTrueVentMode(VentModeManager::ventmodes arg)
{
    if (m_trueVentMode != arg) {
        m_trueVentMode = arg;
        emit trueVentModeChanged(arg);
    }
}

VentModeManager *VentModeManager::instance()
{
    if(!_self)
    {
        _self = new VentModeManager();
    }
    return _self;
}

void VentModeManager::setAvilableChangeMode(bool newAC)
{
    m_avilablityChangeMode = newAC;
    emit avilableChangeModeChanged();
}

void VentModeManager::acceptModeVent()
{
   // qDebug()<<"accept mode: " <<QThread::currentThreadId();
    refreshAvilableChangeMode(); //на всякий случай послелдняя проверка
    if(getAvilableChangeMode())
    {
        setTrueVentMode(getVentMode());
        foreach (TunningParameter* tp, rulesScope.keys()) {
            tp->acceptValue();
        }
        setStateToKIVL();
    }
}

void VentModeManager::cancelModeVent()
{
    if(getTrueVentMode() != CIVL_VENTMODE_UNKNOWN) setVentMode(getTrueVentMode());
    foreach (TunningParameter* tp, rulesScope.keys()) {
        tp->restoreValue();
    }
    refreshAvilableChangeMode();
}

void VentModeManager::stopVent()
{
    CanMessage kivlwait(canId::kivl::ID_MODE_CIVL,1);
    kivlwait.setUInt8(0,0);
    CanDevice::instance()->sendMessage(kivlwait);

    CanMessage mixwait(canId::mix::ID_MODE_MIX,1);
    mixwait.setUInt8(0,0);
    CanDevice::instance()->sendMessage(mixwait);


    CanMessage power(canId::power2::ID_MODE_PWR,1);
    power.setBit(0,0,0);
    CanDevice::instance()->sendMessage(power);
}

void VentModeManager::canselAPNEA()
{
    if(getIsAPNEA())
    {
        //TODO код отправки сообщения о включении режима.
    }
}

void VentModeManager::acceptModeApnea()
{
    tpApneaRegime.acceptValue();
    tpApneaV.acceptValue();
    tpApneaPi.acceptValue();
    tpApneaRB.acceptValue();
    tpApneaT.acceptValue();

    CanMessage apnea(canId::kivl::ID_PARAPNEA_CIVL,6);
    apnea.setUInt8(tpApneaRB.getTrueValue(),0);     //Байт0: частота вентиляции апноэ [вд/мин]
    apnea.setUInt8(tpApneaT.getTrueValue(),1);      //Байт1: время детекции апноэ [с]
    apnea.setUInt16(tpApneaV.getTrueValue(),2);     //Байты2,3: дыхательный объём при возникновении апноэ [мл]
    apnea.setUInt8(tpApneaPi.getTrueValue(),4);     //Байт4: целевое давление апноэ на вдохе при апноэ PCV типа [см вод.ст.]
    apnea.setUInt8(tpApneaRegime.getTrueValue(),5); //Байт5: =0/1 типа апноэ VCV/PCV

    CanDevice::instance()->sendMessage(apnea);

}

void VentModeManager::cancelModeApnea()
{
    tpApneaRegime.restoreValue();
    tpApneaV.restoreValue();
    tpApneaPi.restoreValue();
    tpApneaRB.restoreValue();
    tpApneaT.restoreValue();
}

void VentModeManager::setIsAPNEA(bool arg)
{
    if (m_isAPNEA != arg) {
        m_isAPNEA = arg;
        EventManager::instance()->serviceEvent(EventIDs::AlarmApnea,m_isAPNEA);
        emit IsAPNEAChanged(arg);
    }
}

VentModeManager::ventmodes VentModeManager::getTrueVentMode() const
{
    return m_trueVentMode;
}

void VentModeManager::onAnyParameterChange()
{
    //qDebug()<<"oepc: 0: ";
    calcAllDependenceParams();
    //qDebug()<<"oepc: 1";
    calculateAllConflicts();
    //qDebug()<<"oepc: 2";
    refreshAvilableChangeMode();
    //qDebug()<<"oepc: 3";
}

void VentModeManager::setVentMode(VentModeManager::ventmodes arg)
{
    if (m_ventMode != arg) {
        m_ventMode = arg;
        refreshLimitsState();
        emit ventModeChanged();
    }
}

void VentModeManager::onPatientAgeChanged(qint32 age)
{
    refreshLimitsState();
}

void VentModeManager::setParamRulesMap()
{
    ParamRule* ruleFiO2           = new ParamRule( MIN_OXY_CHILD,  MIN_OXY_ADULT,  MAX_OXY_CHILD,  MAX_OXY_ADULT                   );
    ParamRule* rulePMax           = new ParamRule( MIN_PMAX_CHILD,  MIN_PMAX_ADULT,  MAX_PMAX_CHILD,  MAX_PMAX_ADULT               );
    ParamRule* rulePTrig          = new ParamRule( MIN_PSENSE_CHILD,   MIN_PSENSE_ADULT, MAX_PSENSE_CHILD, MAX_PSENSE_ADULT        );
    ParamRule* ruleFTrig          = new ParamRule( MIN_FSENSE_CHILD,   MIN_FSENSE_ADULT,  MAX_FSENSE_CHILD,  MAX_FSENSE_ADULT      );
    ParamRule* ruleRB             = new ParamRule( MIN_RB_CHILD_CMV,   MIN_RB_ADULT_CMV_PCV,  MAX_RB_CHILD_CMV,  MAX_RB_ADULT_CMV  );
    ParamRule* rulePEEP           = new ParamRule( MIN_PEEP_CHILD,   MIN_PEEP_ADULT,  MAX_PEEP_CHILD,  MAX_PEEP_ADULT              );
    ParamRule* ruleVInsp          = new ParamRule( MIN_VINSP_CHILD, MIN_VINSP_ADULT, MAX_VINSP_CHILD, MAX_VINSP_ADULT              );
    ParamRule* ruleTInsp          = new ParamRule( MIN_TINSP_CHILD, MIN_TINSP_ADULT,MAX_TINSP_CHILD,MAX_TINSP_ADULT                );
    ParamRule* rulePSupp          = new ParamRule( MIN_PSUPP_CHILD,   MIN_PSUPP_ADULT,  MAX_PSUPP_CHILD,  MAX_PSUPP_ADULT          );
    ParamRule* rulePInsp          = new ParamRule( MIN_PINSP_CHILD,   MIN_PINSP_ADULT,  MAX_PINSP_CHILD,  MAX_PINSP_ADULT          );
    ParamRule* rulePHigh          = new ParamRule( MIN_PHIGH_CHILD,    MIN_PHIGH_ADULT,  MAX_PHIGH_CHILD,  MAX_PHIGH_ADULT         );
    ParamRule* rulePLow           = new ParamRule( MIN_PLOW_CHILD,  MIN_PLOW_ADULT,  MAX_PLOW_CHILD,  MAX_PLOW_ADULT               );
    ParamRule* ruleTHigh          = new ParamRule( MIN_THIGH_CHILD,  MIN_THIGH_ADULT,  MAX_THIGH_CHILD,  MAX_THIGH_ADULT           );
    ParamRule* ruleTLow           = new ParamRule( MIN_TLOW_CHILD,  MIN_TLOW_ADULT,  MAX_TLOW_CHILD,  MAX_TLOW_ADULT               );
    ParamRule* rulePlato          = new ParamRule( MIN_PLATO_CHILD,  MIN_PLATO_ADULT,  MAX_PLATO_CHILD,  MAX_PLATO_ADULT           );
    ParamRule* ruleFSupp          = new ParamRule( MIN_FSUPP_CHILD,  MIN_FSUPP_ADULT,  MAX_FSUPP_CHILD,  MAX_FSUPP_ADULT           );
    ParamRule* ruleFormFlow       = new ParamRule( 0,0,1,1);
    ParamRule* ruleTrigWnd        = new ParamRule( MIN_TRIGWND_CHILD,  MIN_TRIGWND_ADULT,  MAX_TRIGWND_CHILD,  MAX_TRIGWND_ADULT    );
    ParamRule* rulePramp          = new ParamRule( MIN_PRESRAMP_CHILD,  MIN_PRESRAMP_ADULT,  MAX_PRESRAMP_CHILD,  MAX_PRESRAMP_ADULT);
    ParamRule* rulePercMV         = new ParamRule( MIN_PERCMV,MIN_PERCMV,MAX_PERCMV,MAX_PERCMV);
    ParamRule* ruleAdaptMV        = new ParamRule( 0,0,1,1);
    ParamRule* ruleOpenValve      = new ParamRule( 0,0,1,1 );
    ParamRule* ruleETS            = new ParamRule( MIN_FEND,MIN_FEND,MAX_FEND,MAX_FEND );
    ParamRule* ruleETC            = new ParamRule( MIN_ETC, MIN_ETC, MAX_ETC, MAX_ETC  );
    ParamRule* ruleApneaRegime    = new ParamRule( 0,0,1,1);
    ParamRule* ruleApneaV         = new ParamRule( MIN_VT[0]  ,MIN_VT[1]  ,MAX_VT[0]  ,MAX_VT[1]   );
    ParamRule* ruleApneaPi        = new ParamRule( MIN_PT[0]  ,MIN_PT[1]  ,MAX_PT[0]  ,MAX_PT[1]   );
    ParamRule* ruleApneaRB        = new ParamRule( MIN_RB[0]  ,MIN_RB[1]  ,MAX_RB[0]  ,MAX_RB[1]   );
    ParamRule* ruleApneaT         = new ParamRule( MIN_TAPN[0],MIN_TAPN[1],MAX_TAPN[0],MAX_TAPN[1] );
    ParamRule* ruleISVVt          = new ParamRule( 60,60,90,90);
    ParamRule* ruleISVVtMax       = new ParamRule( 10,10,22,22);
    ParamRule* ruleISVrazgIRV     = new ParamRule( 0,0,1,1 );
    ParamRule* ruleTrigMode       = new ParamRule( 0,0,1,1 );
    ParamRule* ruleFACC           = new ParamRule( 10,10,100,100);
    ParamRule* ruleComplPeriod    = new ParamRule( 0, 0, 10, 10 );
    ParamRule* ruleFEnd           = new ParamRule( 5,5,50,50 );
    ParamRule* ruleSigh           = new ParamRule( 0,0,1,1 );
    ParamRule* ruleVInspTrig      = new ParamRule( 0,0,1,1  );
    ParamRule* ruleDisconSens     = new ParamRule( 0,0,50,50);
    ParamRule* ruleLimPmax        = new ParamRule( 0,0,1,1  );
    ParamRule* ruleLimTinsp       = new ParamRule( 0,0,1,1 );
    ParamRule* ruleTRazgNIV       = new ParamRule( 0,0,60,60);
    ParamRule* ruleFEndNIV        = new ParamRule( 10,10,50,50);
    ParamRule* ruleTubeType       = new ParamRule( 0,0,1,1);
    ParamRule* ruleTubeDiameter   = new ParamRule( 45,45,60,60);
    ParamRule* ruleLeakComp       = new ParamRule( 0,0,1,1  );
    ParamRule* ruleDeltaPEEP      = new ParamRule( 3,3,25,25);
    ParamRule* rulePatientAge     = new ParamRule( 0,0,1,1  );
    ParamRule* rulePatientGender  = new ParamRule( 0,0,1,1  );
    ParamRule* rulePatientHeight  = new ParamRule( 30,100,150,250 );


    rulesScope[&tpFiO2           ] = ruleFiO2          ;
    rulesScope[&tpPMax           ] = rulePMax          ;
    rulesScope[&tpPTrig          ] = rulePTrig         ;
    rulesScope[&tpFTrig          ] = ruleFTrig         ;
    rulesScope[&tpRB             ] = ruleRB            ;
    rulesScope[&tpPEEP           ] = rulePEEP          ;
    rulesScope[&tpVInsp          ] = ruleVInsp         ;
    rulesScope[&tpTInsp          ] = ruleTInsp         ;
    rulesScope[&tpPSupp          ] = rulePSupp         ;
    rulesScope[&tpPInsp          ] = rulePInsp         ;
    rulesScope[&tpPHigh          ] = rulePHigh         ;
    rulesScope[&tpPLow           ] = rulePLow          ;
    rulesScope[&tpTHigh          ] = ruleTHigh         ;
    rulesScope[&tpTLow           ] = ruleTLow          ;
    rulesScope[&tpPlato          ] = rulePlato         ;
    rulesScope[&tpFSupp          ] = ruleFSupp         ;
    rulesScope[&tpFormFlow       ] = ruleFormFlow      ;
    rulesScope[&tpTrigWnd        ] = ruleTrigWnd       ;
    rulesScope[&tpPramp          ] = rulePramp         ;
    rulesScope[&tpPercMV         ] = rulePercMV        ;
    rulesScope[&tpAdaptMV        ] = ruleAdaptMV       ;
    rulesScope[&tpOpenValve      ] = ruleOpenValve     ;
    rulesScope[&tpETS            ] = ruleETS           ;
    rulesScope[&tpETC            ] = ruleETC           ;
    rulesScope[&tpApneaRegime    ] = ruleApneaRegime   ;
    rulesScope[&tpApneaV         ] = ruleApneaV        ;
    rulesScope[&tpApneaPi        ] = ruleApneaPi       ;
    rulesScope[&tpApneaRB        ] = ruleApneaRB       ;
    rulesScope[&tpApneaT         ] = ruleApneaT        ;
    rulesScope[&tpISVVt          ] = ruleISVVt         ;
    rulesScope[&tpISVVtMax       ] = ruleISVVtMax      ;
    rulesScope[&tpISVrazgIRV     ] = ruleISVrazgIRV    ;
    rulesScope[&tpTrigMode       ] = ruleTrigMode      ;
    rulesScope[&tpFACC           ] = ruleFACC          ;
    rulesScope[&tpComplPeriod    ] = ruleComplPeriod   ;
    rulesScope[&tpFEnd           ] = ruleFEnd          ;
    rulesScope[&tpSigh           ] = ruleSigh          ;
    rulesScope[&tpVInspTrig      ] = ruleVInspTrig     ;
    rulesScope[&tpDisconSens     ] = ruleDisconSens    ;
    rulesScope[&tpLimPmax        ] = ruleLimPmax       ;
    rulesScope[&tpLimTinsp       ] = ruleLimTinsp      ;
    rulesScope[&tpTRazgNIV       ] = ruleTRazgNIV      ;
    rulesScope[&tpFEndNIV        ] = ruleFEndNIV       ; //TODO почему  edp,  не просто dp
    rulesScope[&tpTubeType       ] = ruleTubeType      ;
    rulesScope[&tpTubeDiameter   ] = ruleTubeDiameter  ;
    rulesScope[&tpLeakComp       ] = ruleLeakComp      ;
    rulesScope[&tpDeltaPEEP      ] = ruleDeltaPEEP     ;
    rulesScope[&tpPatientAge     ] = rulePatientAge    ;
    rulesScope[&tpPatientGender  ] = rulePatientGender ;
    rulesScope[&tpPatientHeight  ] = rulePatientHeight ;


    ParamRule* ruleTiTc           = new ParamRule(MIN_TI_TC, MIN_TI_TC, MAX_TI_TC, MAX_TI_TC);
    ParamRule* ruleFlow           = new ParamRule(  30,  30,  400, 1000 );
    ParamRule* ruleFlowMax        = new ParamRule(  30,  30,  400, 1000 );
    ParamRule* ruleTexp           = new ParamRule( 200, 300, 5000, 7000 );
    ParamRule* ruleMV             = new ParamRule(   5,   5, 5000, 7000 );
    ParamRule* rulTramp           = new ParamRule(   5,   5, 5000, 7000 );

    vdpRulesScope[&apTiTc     ] = ruleTiTc    ;
    vdpRulesScope[&apFlow     ] = ruleFlow    ;
    vdpRulesScope[&apFlowMax  ] = ruleFlowMax ;
    vdpRulesScope[&apTexp     ] = ruleTexp    ;
    vdpRulesScope[&apMV       ] = ruleMV      ;
    vdpRulesScope[&apTramp    ] = rulTramp    ;

}

void VentModeManager::refreshAvilableChangeMode()
{

    foreach (TunningParameter* tp, rulesScope.keys()) {
        if(tp->getErrorLevel() == TunningParameter::TPError2)
        {
            setAvilableChangeMode(false);
            return;
        }
    }
    foreach (AssociatedParameter* ap, vdpRulesScope.keys()) {
        if(ap->getErrorLevel() == AssociatedParameter::APError2)
        {
            setAvilableChangeMode(false);
            return;
        }
    }
    setAvilableChangeMode(true);
}

void VentModeManager::setInitValues()
{
    tpFiO2.attemptSetCurrValue(          O2_ADULT_INI       );
    tpPMax.attemptSetCurrValue(          PMAX_ADULT_INI     );
    tpPTrig.attemptSetCurrValue(         PTRIG_ADULT_INI    );
    tpFTrig.attemptSetCurrValue(         FTRIG_ADULT_INI    );
    tpRB.attemptSetCurrValue(            RB_ADULT_INI       );
    tpPEEP.attemptSetCurrValue(          PEEP_ADULT_INI     );
    tpVInsp.attemptSetCurrValue(         VINSP_ADULT_INI    );
    tpTInsp.attemptSetCurrValue(         TINSP_ADULT_INI    );
    tpPSupp.attemptSetCurrValue(         PSUP_ADULT_INI     );
    tpPInsp.attemptSetCurrValue(         PT_ADULT_INI       );
    tpPHigh.attemptSetCurrValue(         P_HIGH_ADULT_INI   );
    tpPLow.attemptSetCurrValue(          P_LOW_ADULT_INI    );
    tpTHigh.attemptSetCurrValue(         T_HIGH_ADULT_INI   );
    tpTLow.attemptSetCurrValue(          T_LOW_ADULT_INI    );
    tpPlato.attemptSetCurrValue(         _HZ                );
    tpFSupp.attemptSetCurrValue(         FSUP_ADULT_INI     );
    tpFormFlow.attemptSetCurrValue(      1                  );
    tpTrigWnd.attemptSetCurrValue(       TRIGWND_ADULT_INI  );
    tpPramp.attemptSetCurrValue(         PRAMP_ADULT_INI    );
    tpPercMV.attemptSetCurrValue(        100                );
    tpAdaptMV.attemptSetCurrValue(       0                  );
    tpOpenValve.attemptSetCurrValue(     0                  );
    tpETS.attemptSetCurrValue(           _HZ                );
    tpETC.attemptSetCurrValue(           0                  );
    tpApneaRegime.attemptSetCurrValue(   0                  );
    tpApneaV.attemptSetCurrValue(        VT_APNEA_ADULT_INI );
    tpApneaPi.attemptSetCurrValue(       PT_APNEA_ADULT_INI );
    tpApneaRB.attemptSetCurrValue(       RB_APNEA_ADULT_INI );
    tpApneaT.attemptSetCurrValue(        TAPN_ADULT_INI     );
    tpISVVt.attemptSetCurrValue(        _HZ                 );
    tpISVVtMax.attemptSetCurrValue(     _HZ                 );
    tpISVrazgIRV.attemptSetCurrValue(   _HZ                 );
    tpTrigMode.attemptSetCurrValue(     1                   );
    tpFACC.attemptSetCurrValue(         FACC_ADULT_INI      );
    tpComplPeriod.attemptSetCurrValue(  _HZ                 );
    tpFEnd.attemptSetCurrValue(         FEND_ADULT_INI_NIV  );
    tpSigh.attemptSetCurrValue(         1                   );
    tpVInspTrig.attemptSetCurrValue(    _HZ                 );
    tpDisconSens.attemptSetCurrValue(   DISCON_SENSE_INI    );
    tpLimPmax.attemptSetCurrValue(      _HZ                 );
    tpLimTinsp.attemptSetCurrValue(     _HZ                 );
    tpTRazgNIV.attemptSetCurrValue(     _HZ                 );
    tpFEndNIV.attemptSetCurrValue(      _HZ                 );
    tpTubeType.attemptSetCurrValue(     _HZ                 );
    tpTubeDiameter.attemptSetCurrValue( _HZ                 );
    tpLeakComp.attemptSetCurrValue(     0                   );
    tpDeltaPEEP.attemptSetCurrValue(    DELTA_PEEP_INI      );
    tpPatientAge.attemptSetCurrValue(    0                  );
    tpPatientGender.attemptSetCurrValue( 1                  );
    tpPatientHeight.attemptSetCurrValue( 174                );

    foreach (TunningParameter* tp, rulesScope.keys()) {
        tp->acceptValue();
    }
}

void VentModeManager::printStateToConsole(int level)
{
    qDebug()<<"************VENTMODESTATE********************";
    qDebug()<<"trueVentMode: "<<getTrueVentMode();
    qDebug()<<"ventMode:     "<<getVentMode();

}

void VentModeManager::refreshLimitsState()
{
    foreach (TunningParameter* tp, rulesScope.keys()) {
        if(rulesScope[tp]->specialLS.contains(getVentMode()))
        {
            if(tpPatientAge.getCurrValue() == false)
            {
                tp->setMinValue(rulesScope[tp]->specialLS[getVentMode()]->mA);
                tp->setMaxValue(rulesScope[tp]->specialLS[getVentMode()]->MA);
            }
            else
            {
                tp->setMinValue(rulesScope[tp]->specialLS[getVentMode()]->mC);
                tp->setMaxValue(rulesScope[tp]->specialLS[getVentMode()]->MC);
            }
        }
        else
        {
            if(tpPatientAge.getCurrValue() == false)
            {
                tp->setMinValue(rulesScope[tp]->defaultLS.mA);
                tp->setMaxValue(rulesScope[tp]->defaultLS.MA);
            }
            else
            {
                tp->setMinValue(rulesScope[tp]->defaultLS.mC);
                tp->setMaxValue(rulesScope[tp]->defaultLS.MC);
            }
        }
    }
    foreach (AssociatedParameter* ap, vdpRulesScope.keys()) {
        if(vdpRulesScope[ap]->specialLS.contains(getVentMode()))
        {
            if(tpPatientAge.getCurrValue() == false)
            {
                ap->setMinValue(vdpRulesScope[ap]->specialLS[getVentMode()]->mA);
                ap->setMaxValue(vdpRulesScope[ap]->specialLS[getVentMode()]->MA);
            }
            else
            {
                ap->setMinValue(vdpRulesScope[ap]->specialLS[getVentMode()]->mC);
                ap->setMaxValue(vdpRulesScope[ap]->specialLS[getVentMode()]->MC);
            }
        }
        else
        {
            if(tpPatientAge.getCurrValue() == false)
            {
                ap->setMinValue(vdpRulesScope[ap]->defaultLS.mA);
                ap->setMaxValue(vdpRulesScope[ap]->defaultLS.MA);
            }
            else
            {
                ap->setMinValue(vdpRulesScope[ap]->defaultLS.mC);
                ap->setMaxValue(vdpRulesScope[ap]->defaultLS.MC);
            }
        }
    }
}

void VentModeManager::onLimPMaxChanged()
{
    if(tpLimPmax.getCurrValue() == 0)
        rulesScope[&tpPMax]->defaultLS.MA = 87;
    else rulesScope[&tpPMax]->defaultLS.MA = 105;
    refreshLimitsState();
}

void VentModeManager::onLimTInspChanged()
{
    if(tpLimTinsp.getCurrValue() == 0)
        rulesScope[&tpTInsp]->defaultLS.MA = 3000;
    else rulesScope[&tpTInsp]->defaultLS.MA = 10000;
    refreshLimitsState();
}

void VentModeManager::calcAllDependenceParams()
{
    apTiTc.setValue( tpRB.getCurrValue()* tpTInsp.getCurrValue()/600);

    if(tpTInsp.getCurrValue() - tpPlato.getCurrValue() != 0)
    {
        //qDebug()<<"cadpVAL:"<<dpTInsp.getValue() - dpPlato.getValue();
        apFlow.setValue(600* tpVInsp.getCurrValue()/( tpTInsp.getCurrValue() - tpPlato.getCurrValue()));
    }
    else apFlow.setValue(600* tpVInsp.getCurrValue()/(1));
    //vdpFlow.setValue(600* dpVInsp.getValue()/( dpTInsp.getValue()));

    if(tpTInsp.getCurrValue() - tpPlato.getCurrValue() != 0)
        apFlowMax.setValue(1200* tpVInsp.getCurrValue()/( tpTInsp.getCurrValue() - tpPlato.getCurrValue()) - 30);
    else
        apFlowMax.setValue(1200* tpVInsp.getCurrValue()/(1) - 30);
    //vdpFlowMax.setValue(1200* dpVInsp.getValue()/( dpTInsp.getValue()) - 30);

    apTexp.setValue(60000/tpRB.getCurrValue() -  tpTInsp.getCurrValue());

    apMV.setValue( tpRB.getCurrValue()* tpVInsp.getCurrValue()/100);

    apTramp.setValue( ((1000*tpPInsp.getCurrValue()/( tpPramp.getCurrValue()))*1000)/tpTInsp.getCurrValue());
}

void VentModeManager::bindContext(QQmlContext *ctx)
{
    ctx->setContextProperty("tpFiO2"          , &tpFiO2             );
    ctx->setContextProperty("tpPMax"          , &tpPMax             );
    ctx->setContextProperty("tpPTrig"         , &tpPTrig            );
    ctx->setContextProperty("tpFTrig"         , &tpFTrig            );
    ctx->setContextProperty("tpRB"            , &tpRB               );
    ctx->setContextProperty("tpPEEP"          , &tpPEEP             );
    ctx->setContextProperty("tpVInsp"         , &tpVInsp            );
    ctx->setContextProperty("tpTInsp"         , &tpTInsp            );
    ctx->setContextProperty("tpPSupp"         , &tpPSupp            );
    ctx->setContextProperty("tpPInsp"         , &tpPInsp            );
    ctx->setContextProperty("tpPHigh"         , &tpPHigh            );
    ctx->setContextProperty("tpPLow"          , &tpPLow             );
    ctx->setContextProperty("tpTHigh"         , &tpTHigh            );
    ctx->setContextProperty("tpTLow"          , &tpTLow             );
    ctx->setContextProperty("tpPlato"         , &tpPlato            );
    ctx->setContextProperty("tpFSupp"         , &tpFSupp            );
    ctx->setContextProperty("tpFormFlow"      , &tpFormFlow         );
    ctx->setContextProperty("tpTrigWnd"       , &tpTrigWnd          );
    ctx->setContextProperty("tpPramp"         , &tpPramp            );
    ctx->setContextProperty("tpPercMV"        , &tpPercMV           );
    ctx->setContextProperty("tpAdaptMV"       , &tpAdaptMV          );
    ctx->setContextProperty("tpOpenValve"     , &tpOpenValve        );
    ctx->setContextProperty("tpETS"           , &tpETS              );
    ctx->setContextProperty("tpETC"           , &tpETC              );
    ctx->setContextProperty("tpApneaRegime"   , &tpApneaRegime      );
    ctx->setContextProperty("tpApneaV"        , &tpApneaV           );
    ctx->setContextProperty("tpApneaPi"       , &tpApneaPi          );
    ctx->setContextProperty("tpApneaRB"       , &tpApneaRB          );
    ctx->setContextProperty("tpApneaT"        , &tpApneaT           );
    ctx->setContextProperty("tpISVVt"         , &tpISVVt            );
    ctx->setContextProperty("tpISVVtMax"      , &tpISVVtMax         );
    ctx->setContextProperty("tpISVrazgIRV"    , &tpISVrazgIRV       );
    ctx->setContextProperty("tpTrigMode"      , &tpTrigMode         );
    ctx->setContextProperty("tpFACC"          , &tpFACC             );
    ctx->setContextProperty("tpComplPeriod"   , &tpComplPeriod      );
    ctx->setContextProperty("tpFEnd"          , &tpFEnd             );
    ctx->setContextProperty("tpSigh"          , &tpSigh             );
    ctx->setContextProperty("tpVInspTrig"     , &tpVInspTrig        );
    ctx->setContextProperty("tpDisconSens"    , &tpDisconSens       );
    ctx->setContextProperty("tpLimPmax"       , &tpLimPmax          );
    ctx->setContextProperty("tpLimTinsp"      , &tpLimTinsp         );
    ctx->setContextProperty("tpTRazgNIV"      , &tpTRazgNIV         );
    ctx->setContextProperty("tpFEndNIV"       , &tpFEndNIV          );
    ctx->setContextProperty("tpTubeType"      , &tpTubeType         );
    ctx->setContextProperty("tpTubeDiameter"  , &tpTubeDiameter     );
    ctx->setContextProperty("tpLeakComp"      , &tpLeakComp         );
    ctx->setContextProperty("tpDeltaPEEP"     , &tpDeltaPEEP        );
    ctx->setContextProperty("tpPatientAge"    , &tpPatientAge       );
    ctx->setContextProperty("tpPatientGender" , &tpPatientGender    );
    ctx->setContextProperty("tpPatientHeight" , &tpPatientHeight    );
    ctx->setContextProperty("apTiTc"          , &apTiTc             );
    ctx->setContextProperty("apFlow"          , &apFlow             );
    ctx->setContextProperty("apFlowMax"       , &apFlowMax          );
    ctx->setContextProperty("apTexp"          , &apTexp             );
    ctx->setContextProperty("apMV"            , &apMV               );
    ctx->setContextProperty("apTramp"         , &apTramp            );
}

void VentModeManager::setStateToKIVL()
{
    CanMessage par1(canId::kivl::ID_PAR1_CIVL,8);
    par1.setEnum(getVentMode(),4,0,0);              //биты3..0: режим ИВЛ
    par1.setBit(tpTrigMode.getCurrValue(),0,4);        //бит4: =0 активен триггер по давлению, =1 активен триггер по потоку
    par1.setBit(tpFormFlow.getCurrValue(),0,5);         //бит5: =0 поток прямоугольный, =1 поток убывающий
    par1.setBit(tpSigh.getCurrValue(),0,6 );           //бит6: =0 нет режима "вздох", =1 режим "вздох" (через 50 циклов)
    par1.setBit(tpPatientAge.getCurrValue(),0,7);       //бит7: =1/0 детский/взрослый режим

    if(getVentMode() == CIVL_VENTMODE_APRV || getVentMode() == CIVL_VENTMODE_BISTEP)
        par1.setUInt8(tpPLow.getCurrValue(),1);         //Байт1: В режиме BiSTEP  APRV это есть Plow.
    else par1.setUInt8(tpPEEP.getCurrValue(),1);        //Байт1: величина ПДКВ [см вод.ст.].
    if(tpTrigMode.getCurrValue())                      //ежели по потоку
    {
        par1.setUInt8(0,2);                         //Байт2: чувствительность триггера по давлению равна нолю
        par1.setUInt8(tpFTrig.getCurrValue(),3);        //Байт3: чувствительность триггера по потоку [0.1 л/мин]
    }
    else                                            //ежелит по давлению
    {
        par1.setUInt8(tpPTrig.getCurrValue(),2);        //Байт2: чувствительность триггера по давлению
        par1.setUInt8(0,3);                         //Байт3: чувствительность триггера по потоку равна нолю
    }
    if(getVentMode() == CIVL_VENTMODE_NIV)              //ежели NIV
        par1.setUInt16(3000,4);                         //Байты4,5: время вдоха [мс].
    else if(getVentMode() == CIVL_VENTMODE_APRV || getVentMode() == CIVL_VENTMODE_BISTEP)
        par1.setUInt16(tpTHigh.getCurrValue(),4);       //Байты4,5: время вдоха [мс].
    else
        par1.setUInt16(tpTInsp.getCurrValue(),4);       //Байты4,5: время вдоха [мс]

    if(getVentMode() == CIVL_VENTMODE_APRV || getVentMode() == CIVL_VENTMODE_BISTEP)
        par1.setUInt16(tpTLow.getCurrValue(),6);        //Байты6,7: время выдоха [мс]
    else
        par1.setUInt16(apTexp.getValue(),6);           //Байты6,7: время выдоха [мс]

    CanMessage par2(canId::kivl::ID_PAR2_CIVL,8);
    par2.setUInt16(tpVInsp.getCurrValue(),0);           //Байты0,1: объём вдоха [мл] (200..2000)
    par2.setUInt8(100*tpPlato.getCurrValue()/tpTInsp.getCurrValue(),2);    //Байт2: длительность плато [%] (0..40)
    par2.setUInt8(tpPSupp.getCurrValue(),3);            //Байт3: величина PS над уровнем ПДКВ [см вод.ст.] Используется в режимах SIMV/VC, SIMV/PC, CPAP, BiSTEP
    par2.setUInt8(tpPMax.getCurrValue(),4);             //Байт4: значение Pmax [см вод.ст.] (20..80)
    if(getVentMode() == CIVL_VENTMODE_APRV || getVentMode() == CIVL_VENTMODE_BISTEP)
        par2.setUInt8(tpPHigh.getCurrValue(),5);        //Байт5: значение Pt [см вод.ст.] (Pressure Tidal, целевое давление вдоха) (5..80) Используется в режимах CMV/PCV, SIMV/PC, BiSTEP. В режиме BiSTEP это есть Phigh.
    else par2.setUInt8(tpPInsp.getCurrValue() + tpPEEP.getCurrValue(),5); //Байт5: значение Pt [см вод.ст.] (Pressure Tidal, целевое давление вдоха) (5..80) Используется в режимах CMV/PCV, SIMV/PC, BiSTEP.

    par2.setUInt8(tpTrigWnd.getCurrValue()/(apTexp.getValue() - 200),6);    //Байт6: триггерное окно (0..100%)
    if(getVentMode() == CIVL_VENTMODE_NIV)
        par2.setUInt8(tpFEndNIV.getCurrValue(),7);     //Байт7: триггер окончания вдоха [% от Finsp_max]
    else
        par2.setUInt8(tpFEnd.getCurrValue(),7);        //Байт7: триггер окончания вдоха [% от Finsp_max]

    CanMessage par3(canId::kivl::ID_PAR3_CIVL,7);
    if(getVentMode() == CIVL_VENTMODE_NIV)
        par3.setUInt16(tpFACC.getCurrValue(),0);       // Байты0,1: для режима НИВ - ускорение потока 10..100 [%].
    else
        par3.setUInt16(tpPramp.getCurrValue(),0);       // Байты0,1: для режимов, отличных от НИВ - скорость нарастания давления 50..2000 [ммH2O/с]
    par3.setUInt8(2,2);                             // TODO хз что куда        // Байт2: число, отвечающее за частоту выдачи пакета ID_WAVE_CIVL для отрисовки графиков. Частота выдачи равна 500/Байт, но не менее 15 Гц. Байт = 1..33, другие значения считаются равны 33 (15 Гц)
    par3.setUInt8(tpFSupp.getCurrValue(),3);            // Байт3: поток поддержки [л/мин]
    par3.setUInt8(tpDisconSens.getCurrValue(),4);      // Байт4: чувствительность к дисконнекции [%]. Если в 3 подряд дыхательных циклах объём выдоха будет более чем на указанное число % меньше объёма вдоха, то будет продетектирована разгерметизация. 0% означает что объём выдоха может быть любым, без выработки тревоги "разгерметизация" по этому критерию. 100% означает, что отличие даже на 1 мл приведёт к тревоге. От 0 до 100%, остальные значения ограничиваются до 100%
    par3.setUInt8(tpDeltaPEEP.getCurrValue(),5);                             // TODO ока не делал этот параметр  // Байт5: приращение deltaPEEP для манёвра раскрытия альвеол
    par3.setBit(tpLeakComp.getCurrValue(),6,0);        // Байт6: бит0: =1/0 -- вкл/выкл компенсацию утечки, только в CMV/VCV
    par3.setBit(tpOpenValve.getCurrValue(),6,1);        // Байт6. бит 0; открыитый  контур

//        CanMessage parISV1(canId::kivl::ID_ISV_PAR1_CIVL,8);
//        par2.setUInt8(dpPatientHeight.getTrueValue(),0);        //рост пациента [см] */
//        par2.setUInt8(dpPercMV.getTrueValue(),getTrueValue(),2);//коэффициент для вычисления абсолютного значения Vtmax (K на кг IBW) [10 - 22] */
//        par2.setUInt16(dpPSupp.getTrueValue(),3);               //идеальный вес пациента IBW [0.1 кг] */
//        par2.setUInt16(dpPMax.getTrueValue(),4);                //процент минутной вентиляции %MV [%] */
//        par2.setUInt16(dpPMax.getTrueValue(),4);                //целевой MV [мл/мин] */

//        CanMessage parISV2(canId::kivl::ID_ISV_PAR2_CIVL,2);
//        par2.setUInt16(dpVInsp.getTrueValue(),0);           //разрешить IRV в ISV [0 - запретить, 1 - разрешить] */
//        par2.setUInt8(1.getTrueValue(),2);                  //адаптация МОД [0 - выкл, 1 - вкл] */


    CanMessage apnea(canId::kivl::ID_PARAPNEA_CIVL,6);
    apnea.setUInt8(tpApneaRB.getTrueValue(),0);    //Байт0: частота вентиляции апноэ [вд/мин]
    apnea.setUInt8(tpApneaT.getTrueValue(),1);    //Байт1: время детекции апноэ [с]
    apnea.setUInt16(tpApneaV.getTrueValue(),2); //Байты2,3: дыхательный объём при возникновении апноэ [мл]
    apnea.setUInt8(tpApneaPi.getTrueValue(),4);    //Байт4: целевое давление апноэ на вдохе при апноэ PCV типа [см вод.ст.]
    apnea.setUInt8(tpApneaRegime.getTrueValue(),5);     //Байт5: =0/1 типа апноэ VCV/PCV

    CanMessage opt(canId::kivl::ID_OPT_CIVL,8);
    opt.setBit(1,3,3);
    opt.setBit(1,7,3);

    CanMessage kivlwork(canId::kivl::ID_MODE_CIVL,1);
    kivlwork.setUInt8(1,0);

    CanMessage mixwork(canId::mix::ID_MODE_MIX,1);
    mixwork.setUInt8(1,0);

    CanMessage fio2(canId::bu::ID_OXY,1);
    fio2.setUInt8(22,0);

    CanMessage power(canId::power2::ID_MODE_PWR,1);
    power.setBit(1,0,0);

    CanMessage msg_CAPNO1_WAIT(canId::capno1::ID_MODE_CAPNO1,1);
    msg_CAPNO1_WAIT.setUInt8(1,0);

    CanDevice::instance()->sendMessage(msg_CAPNO1_WAIT);
    CanDevice::instance()->sendMessage(power);
    CanDevice::instance()->sendMessage(mixwork);
    CanDevice::instance()->sendMessage(fio2);
    CanDevice::instance()->sendMessage(apnea);
    CanDevice::instance()->sendMessage(opt);
    CanDevice::instance()->sendMessage(par1);
    CanDevice::instance()->sendMessage(par2);
    CanDevice::instance()->sendMessage(par3);
    CanDevice::instance()->sendMessage(kivlwork);
}

void VentModeManager::calculateAllConflicts()
{
    TunningParameter::tunningErrorLevels elVInsp    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPlato    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elRB       =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elTInsp    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPTrig    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elFTrig    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elFSupp    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPEEP     =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elTrigWnd  =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elFormFlow =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPInsp    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPSupp    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPHigh    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elPLow     =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elTHigh    =  TunningParameter::TPErrorNo;
    TunningParameter::tunningErrorLevels elTLow     =  TunningParameter::TPErrorNo;


/************** VInsp  FormFlow ******************/
    if(getVentMode() == CIVL_VENTMODE_CMV_VCV || getVentMode() == CIVL_VENTMODE_SIMV_DC || getVentMode() == CIVL_VENTMODE_SIMV_VC)
    {
        if(apFlow.getErrorLevel() == AssociatedParameter::APError2)
        {
            elVInsp = TunningParameter::TPError2;
            elFormFlow = TunningParameter::TPError2;
        }
        else if(tpFormFlow.getCurrValue() == 1 && apFlowMax.getErrorLevel() == AssociatedParameter::APError2)
        {
            elVInsp = TunningParameter::TPError1;
            elFormFlow = TunningParameter::TPError1;
        }
    }

/************** Plato ******************/
    if(getVentMode() == CIVL_VENTMODE_CMV_VCV && apFlow.getErrorLevel() == AssociatedParameter::APError2 && tpPlato.getCurrValue() > 0)
        elPlato = TunningParameter::TPError2;
    if(tpPlato.getCurrValue()>7*tpTInsp.getCurrValue()/10)
        elPlato = TunningParameter::TPError2;

/**************  RB, TInsp  ******************/
    if(getVentMode() == CIVL_VENTMODE_CMV_VCV ||
       getVentMode() == CIVL_VENTMODE_CMV_PCV ||
       getVentMode() == CIVL_VENTMODE_SIMV_PC ||
       getVentMode() == CIVL_VENTMODE_SIMV_DC ||
       getVentMode() == CIVL_VENTMODE_SIMV_VC)
    {
        if (60000/tpRB.getCurrValue() - tpTInsp.getCurrValue() < (tpPatientAge.getCurrValue()? 200 : 300))
        {
            elRB = TunningParameter::TPError2;
            elTInsp = TunningParameter::TPError2;
        }
    }
    if(tpPlato.getCurrValue()>7*tpTInsp.getCurrValue()/10)
        elTInsp = TunningParameter::TPError2;

/**************  PTrig  ******************/
    if((getVentMode() == CIVL_VENTMODE_CMV_VCV ||
       getVentMode() == CIVL_VENTMODE_CMV_PCV ||
       getVentMode() == CIVL_VENTMODE_SIMV_PC ||
       getVentMode() == CIVL_VENTMODE_SIMV_VC ||
       getVentMode() == CIVL_VENTMODE_CPAP    ||
       getVentMode() == CIVL_VENTMODE_NIV     ||
       getVentMode() == CIVL_VENTMODE_PCV_VG  ||
       getVentMode() == CIVL_VENTMODE_SIMV_DC) &&
       tpTrigMode.getCurrValue() == 0 && tpPTrig.getCurrValue() > tpPEEP.getCurrValue()*10)
       elPTrig = TunningParameter::TPError1;

/**************  FTrig FSupp  ******************/
    if(tpFTrig.getCurrValue() > tpFSupp.getCurrValue())
    {
        elFTrig = TunningParameter::TPError2;
        elFSupp = TunningParameter::TPError2;
    }
/***********  PEEP  ******************/
    if(getVentMode() == CIVL_VENTMODE_CMV_VCV)
    {
        if(tpPEEP.getCurrValue() + 10 > tpPMax.getCurrValue())
            elPEEP = TunningParameter::TPError2;
    }
    else if(getVentMode() == CIVL_VENTMODE_CMV_PCV)
    {
        if(tpPEEP.getCurrValue() + 5 > tpPMax.getCurrValue())
            elPEEP = TunningParameter::TPError2;
    }
    else if(getVentMode() == CIVL_VENTMODE_SIMV_VC ||
            getVentMode() == CIVL_VENTMODE_SIMV_PC ||
            getVentMode() == CIVL_VENTMODE_SIMV_DC ||
            getVentMode() == CIVL_VENTMODE_CPAP)
    {
        if(tpPEEP.getCurrValue() + tpPSupp.getCurrValue() + 5 > tpPMax.getCurrValue())
            elPEEP = TunningParameter::TPError2;
    }
    else if(getVentMode() == CIVL_VENTMODE_PCV_VG)
    {
        if(tpPEEP.getCurrValue() + 15 > tpPMax.getCurrValue())
            elPEEP = TunningParameter::TPError2;
    }

/**************  TrigWnd  ******************/
    if((getVentMode() == CIVL_VENTMODE_CMV_VCV ||
       getVentMode() == CIVL_VENTMODE_CMV_PCV ||
       getVentMode() == CIVL_VENTMODE_SIMV_PC ||
       getVentMode() == CIVL_VENTMODE_PCV_VG ) &&
       tpTrigWnd.getCurrValue() < 0) //TODO if (!MainTrigWndDimIsPercent && dep->Tsense > 100) col = RED;
    {
        elTrigWnd = TunningParameter::TPError2;
    }

/**************  PInsp  ******************/
    if((getVentMode() == CIVL_VENTMODE_CMV_PCV ||
        getVentMode() == CIVL_VENTMODE_SIMV_PC ) &&
        tpPMax.getCurrValue() < tpPEEP.getCurrValue()+ tpPInsp.getCurrValue() + 5)
    {
        elPInsp = TunningParameter::TPError2;
    }

/**************  PSupp  ******************/
    if((getVentMode() == CIVL_VENTMODE_SIMV_PC ||
        getVentMode() == CIVL_VENTMODE_SIMV_VC ||
        getVentMode() == CIVL_VENTMODE_CPAP    ||
        getVentMode() == CIVL_VENTMODE_SIMV_DC ) &&
        tpPEEP.getCurrValue() + tpPSupp.getCurrValue() + 5 > tpPMax.getCurrValue())
    {
        elPSupp = TunningParameter::TPError2;
    }
    else if( getVentMode() == CIVL_VENTMODE_APRV   ||
             getVentMode() == CIVL_VENTMODE_BISTEP )
    {
        if(tpPatientAge.getCurrValue()?  tpPMax.getCurrValue() >60: tpPMax.getCurrValue()> 80)
        {
            elPSupp = TunningParameter::TPError2;
            elPLow  = TunningParameter::TPError2;
        }
    }

/**************  PHigh  ******************/
    if((getVentMode() == CIVL_VENTMODE_BISTEP ||
        getVentMode() == CIVL_VENTMODE_APRV ) &&
        tpPHigh.getCurrValue() < tpPLow.getCurrValue())
    {
        elPHigh = TunningParameter::TPError2;
    }

/**************  Plow  ******************/
    if(( getVentMode() == CIVL_VENTMODE_APRV ) &&
        !(tpPHigh.getCurrValue() < tpPLow.getCurrValue()) &&
          tpPLow.getCurrValue() + tpPSupp.getCurrValue() > 75 )
    {
        elPLow = TunningParameter::TPError2;
    }

/************** THigh TLow ******************/
    if((getVentMode() == CIVL_VENTMODE_APRV ) &&
        tpTHigh.getCurrValue() < tpTLow.getCurrValue())
    {
        elTHigh = TunningParameter::TPError2;
        elTLow  = TunningParameter::TPError2;
    }

    tpVInsp.setErrorLevel(    elVInsp    );
    tpPlato.setErrorLevel(    elPlato    );
    tpRB.setErrorLevel(       elRB       );
    tpTInsp.setErrorLevel(    elTInsp    );
    tpPTrig.setErrorLevel(    elPTrig    );
    tpFTrig.setErrorLevel(    elFTrig    );
    tpFSupp.setErrorLevel(    elFSupp    );
    tpPEEP.setErrorLevel(     elPEEP     );
    tpTrigWnd.setErrorLevel(  elTrigWnd  );
    tpFormFlow.setErrorLevel( elFormFlow );
    tpPInsp.setErrorLevel(    elPInsp    );
    tpPSupp.setErrorLevel(    elPSupp    );
    tpPHigh.setErrorLevel(    elPHigh    );
    tpPLow.setErrorLevel(     elPLow     );
    tpTHigh.setErrorLevel(    elTHigh    );
    tpTLow.setErrorLevel(     elTLow     );
}
