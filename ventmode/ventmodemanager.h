#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include <QObject>
#include <QQmlContext>
#include "limitdefines.h"
#include "../types/tunningparameter.h"
#include "../types/associatedparameter.h"
//#include "../alarms/alarmmanager.h"
#include "../CAN/candevice.h"

struct TPCurrLimitsScope;
struct ParamRule;

/**
 * класс отвечающий за смену режимов вентиляции.
 * Для QML расшаривает текущий режим, настраевые параметры,
 * редко измеряемые параметры режимов.
 * TODO продумать общение данного класса с С++. формирование пакетов для кивл в нем ли делать?
 */
class VentModeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ventmodes trueVentMode READ getTrueVentMode NOTIFY trueVentModeChanged)
    Q_PROPERTY(ventmodes ventMode READ getVentMode WRITE setVentMode NOTIFY ventModeChanged)
    Q_PROPERTY(bool avilableChangeMode READ getAvilableChangeMode NOTIFY avilableChangeModeChanged)
    Q_PROPERTY(bool isAPNEA READ getIsAPNEA NOTIFY IsAPNEAChanged)
public:
    Q_ENUMS(ventmodes)
    enum  ventmodes{
        CIVL_VENTMODE_CMV_VCV = 0, /* CMV/VCV */
        CIVL_VENTMODE_CMV_PCV,     /* CMV/PCV */
        CIVL_VENTMODE_SIMV_PC,     /* SIMV/PCV+PS+apnea */
        CIVL_VENTMODE_SIMV_VC,     /* SIMV/VCV+PS+apnea */
        CIVL_VENTMODE_CPAP,        /* CPAP+PS+apnea */
        CIVL_VENTMODE_BISTEP,      /* BiSTEP+PS+apnea */
        CIVL_VENTMODE_NIV,         /* NIV */
        CIVL_VENTMODE_APRV,        /* APRV */
        CIVL_VENTMODE_PCV_VG,      /* PCV-VG */
        CIVL_VENTMODE_SIMV_DC,     /* SIMV/DC */
        CIVL_VENTMODE_ISV,         /* ISV */
        CIVL_VENTMODE_UNKNOWN,     /* Неизвестный режим вентиляции */
    };
    static VentModeManager* instance();
    void bindContext(QQmlContext* ctx);
    ventmodes getVentMode(){return m_ventMode;}
    bool getAvilableChangeMode(){return m_avilablityChangeMode;}
    void setAvilableChangeMode(bool newAC);
    Q_INVOKABLE void acceptModeVent();
    Q_INVOKABLE void cancelModeVent();
    Q_INVOKABLE void stopVent();
    Q_INVOKABLE void canselAPNEA();
    Q_INVOKABLE void acceptModeApnea();
    Q_INVOKABLE void cancelModeApnea();
//    Q_INVOKABLE void restorePatient();
//    Q_INVOKABLE void acceptPatient();
    bool getIsAPNEA() const {return m_isAPNEA;}
    void setIsAPNEA(bool arg);
    ventmodes getTrueVentMode() const;
private:

    static TunningParameter     tpFiO2            ;
    static TunningParameter     tpPMax            ;
    static TunningParameter     tpPTrig           ;
    static TunningParameter     tpFTrig           ;
    static TunningParameter     tpRB              ;
    static TunningParameter     tpPEEP            ;
    static TunningParameter     tpVInsp           ;
    static TunningParameter     tpTInsp           ;
    static TunningParameter     tpPSupp           ;
    static TunningParameter     tpPInsp           ;
    static TunningParameter     tpPHigh           ;
    static TunningParameter     tpPLow            ;
    static TunningParameter     tpTHigh           ;
    static TunningParameter     tpTLow            ;
    static TunningParameter     tpPlato           ;
    static TunningParameter     tpFSupp           ;
    static TunningParameter     tpFormFlow        ;
    static TunningParameter     tpTrigWnd         ;
    static TunningParameter     tpPramp           ;
    static TunningParameter     tpPercMV          ;
    static TunningParameter     tpAdaptMV         ;
    static TunningParameter     tpOpenValve       ;
    static TunningParameter     tpETS             ;
    static TunningParameter     tpETC             ;
    static TunningParameter     tpApneaRegime     ;
    static TunningParameter     tpApneaV          ;
    static TunningParameter     tpApneaPi         ;
    static TunningParameter     tpApneaRB         ;
    static TunningParameter     tpApneaT          ;
    static TunningParameter     tpISVVt           ;
    static TunningParameter     tpISVVtMax        ;
    static TunningParameter     tpISVrazgIRV      ;
    static TunningParameter     tpTrigMode        ;
    static TunningParameter     tpFACC            ;
    static TunningParameter     tpComplPeriod     ;
    static TunningParameter     tpFEnd            ;
    static TunningParameter     tpSigh            ;
    static TunningParameter     tpVInspTrig       ;
    static TunningParameter     tpDisconSens      ;
    static TunningParameter     tpLimPmax         ;
    static TunningParameter     tpLimTinsp        ;
    static TunningParameter     tpTRazgNIV        ;
    static TunningParameter     tpFEndNIV         ;
    static TunningParameter     tpTubeType        ;
    static TunningParameter     tpTubeDiameter    ;
    static TunningParameter     tpLeakComp        ;
    static TunningParameter     tpDeltaPEEP       ;
    static TunningParameter     tpPatientAge      ;
    static TunningParameter     tpPatientGender   ;
    static TunningParameter     tpPatientHeight   ;
    static AssociatedParameter  apTiTc            ;
    static AssociatedParameter  apFlow            ;
    static AssociatedParameter  apFlowMax         ;
    static AssociatedParameter  apTexp            ;
    static AssociatedParameter  apMV              ;
    static AssociatedParameter  apTramp           ;

    void setParamRulesMap();
    void refreshLimitsState();
    void setStateToKIVL();
    void refreshAvilableChangeMode();
    void setInitValues();
    void printStateToConsole(int level);


    VentModeManager(QObject *parent = 0);
    static VentModeManager* _self;


    bool m_avilablityChangeMode;
    bool m_isAPNEA;
    ventmodes m_trueVentMode;
    ventmodes m_ventMode;
    QMap<TunningParameter*, ParamRule*> rulesScope;
    QMap<AssociatedParameter*, ParamRule*> vdpRulesScope;

private slots:
    void onAnyParameterChange();
    void onPatientAgeChanged(qint32 age);
    void calculateAllConflicts();

    void onLimPMaxChanged();
    void onLimTInspChanged();
    void calcAllDependenceParams();

public slots:
    void setTrueVentMode(ventmodes arg);
    void setVentMode(ventmodes arg);


signals:
    void avilableChangeModeChanged();
    void IsAPNEAChanged(bool arg);
    void trueVentModeChanged(ventmodes arg);
    void ventModeChanged();
};

struct TPCurrLimitsScope{
    qint32 mC;
    qint32 mA;
    qint32 MC;
    qint32 MA;

    void reset(qint32 _mC = 23, qint32 _mA = 43, qint32 _MC = 34, qint32 _MA = 56)
    {
        mC = _mC;
        mA = _mA;
        MC = _MC;
        MA = _MA;
    }
    TPCurrLimitsScope(qint32 _mC = 23, qint32 _mA = 43, qint32 _MC = 34, qint32 _MA = 56)
    {
        reset(_mC,_mA,_MC,_MA);
    }
};

struct ParamRule{
    TPCurrLimitsScope defaultLS;
    QMap<VentModeManager::ventmodes,TPCurrLimitsScope*> specialLS;
    ParamRule(qint32 _mC, qint32 _mA, qint32 _MC, qint32 _MA)
    {
        defaultLS.reset(_mC,_mA,_MC,_MA);
    }
    void setSpecialLS(VentModeManager::ventmodes vm, qint32 _mC, qint32 _mA, qint32 _MC, qint32 _MA)
    {
        specialLS[vm] = new TPCurrLimitsScope(_mC,_mA,_MC,_MA);
    }
};




#endif // MODEMANAGER_H
