#ifndef CANUNITKIVL_H
#define CANUNITKIVL_H

#include "canunit.h"


class CanUnitKIVL : public CanUnit
{
    Q_OBJECT
    Q_ENUMS(civlModes)
    Q_PROPERTY(civlModes civlMode READ getCivlMode WRITE setCivlMode NOTIFY civlModeChanged)
public:
    enum civlModes  {
        CIVL_MODE_WAIT         = 0, /* режим ОЖИДАНИЕ */
        CIVL_MODE_WORK         = 1, /* режим РАБОТА */
        CIVL_MODE_SHORTTEST    = 2, /* "Короткий Внутренний Тест" */
//        CIVL_MODE_FULLTEST     = 3, /* "Полный Внутренний Тест" */
//        CIVL_MODE_CLBRPEEP     = 4, /* "калибровка клапана выдоха" */
//        CIVL_MODE_CLBROXY      = 5, /* "калибровка медленного датчика кислорода на вдохе" */
//        CIVL_MODE_CLBROXYCAPNO = 6, /* "калибровка быстрого датчика кислорода в капнографе" */
//        CIVL_MODE_CLBRPRESS    = 7, /* "калибровка датчиков давления" */
//        CIVL_MODE_CHKEMVE      = 8, /* "проверка ЭМКВ" */
//        CIVL_MODE_CLBRMIX      = 9, /* "калибровка датчика потока кислорода в СГ" */
//        CIVL_MODE_CLBRFG       =10, /* "калибровка генератора потока" */
//        CIVL_MODE_MAKEFLOW     =11, /* "генерация потока" */
//        CIVL_MODE_CHKLEAK      =12, /* "проверка утечки" */
//        CIVL_MODE_TSTCHILD     =13, /* "технологический детский режим" */
//        CIVL_MODE_CLBRFLOWSENS =14, /* "калибровка датчиков потока" */
//        CIVL_MODE_CLBRFEXP     =15, /* "калибровка преобразователя поток-давление" */
//        CIVL_MODE_AR1          =16, /* "АВАРИЙНЫЙ РЕЖИМ №1" */
//        CIVL_MODE_AR2          =17, /* "АВАРИЙНЫЙ РЕЖИМ №2" */
//        CIVL_MODE_AR3          =18, /* "АВАРИЙНЫЙ РЕЖИМ №3" */
//        CIVL_MODE_PAR          =19, /* "ПОЛНОСТЬЮ АВАРИЙНЫЙ РЕЖИМ" */
//        CIVL_MODE_CLBRCHNGOXY  =20, /* "замена датчика кислорода на вдохе" */
        CIVL_MODE_UNKNOWN      =21  /* режим кивла не известен */
    };
private:

    void process_ID_INSP_CIVL(const CanMessage &msg);
    void process_ID_WAVE_CIVL(const CanMessage &msg);
    void process_ID_STATUS_CIVL(const CanMessage &msg);
    void process_ID_CLBR_ERR_CIVL(const CanMessage &msg);
    void process_ID_VERSION_CIVL(const CanMessage &msg);
    void process_ID_M_VINSP_CIVL(const CanMessage &msg);
    void process_ID_M_VEXP_CIVL(const CanMessage &msg);
    void process_ID_M_PEEP_CIVL(const CanMessage &msg);
    void process_ID_M_RB_CIVL(const CanMessage &msg);
    void process_ID_M_PIP_CIVL(const CanMessage &msg);
    void process_ID_M_MV_CIVL(const CanMessage &msg);
    void process_ID_M_TEXP_CIVL(const CanMessage &msg);
    void process_ID_M_TINSP_CIVL(const CanMessage &msg);
    void process_ID_M_COMPL_CIVL(const CanMessage &msg);
    void process_ID_M_LEAK_CIVL(const CanMessage &msg);
    void process_ID_WORKTIME_CIVL(const CanMessage &msg);
    void process_ID_OXYVOLTAGE_CIVL(const CanMessage &msg);
    void process_ID_M_PPLATO_CIVL(const CanMessage &msg);
    void process_ID_M_FLOWPEAK_CIVL(const CanMessage &msg);
    void process_ID_M_AIRWAY_CIVL(const CanMessage &msg);


    MeasureParameter*  currWSpont      ;  /* Работа дыхания пациента   [0.01 Дж/л] */
    MeasureParameter*  currWVent       ;  /* Работа дыхания аппаратная [0.01 Дж/л] */
    MeasureParameter*  currVolInsp     ;  /* объём вдоха [мл] */
    MeasureParameter*  currVolExp      ;  /* объём выдоха [мл] */
    MeasureParameter*  currPEEP        ;  /* ПДКВ [cм вод.ст.] */
    MeasureParameter*  currAutoPEEP    ;  /* АутоПДКВ [мм Н2О] */
    MeasureParameter*  currExpEndFlow  ;  /* EndExpFlow [0.1 л/мин] */
    MeasureParameter*  currRCExp       ;  /* RCExp - постоянная времени на выдохе [мс] */
    MeasureParameter*  currRB          ;  /* Частота дыхания */
    MeasureParameter*  currRBspont     ;  /* Частота спонтанных дыханий */
    MeasureParameter*  currPIP         ;  /* PIP [см вод.ст.] */
    MeasureParameter*  currSI          ;  /* стресс индекс */
    MeasureParameter*  currCDyn        ;  /* динамический комплайнс [мл/см вод.ст.] */
    MeasureParameter*  currVE          ;
    MeasureParameter*  currVEa         ;
    MeasureParameter*  currMVspont     ;  /* Минутный объём спонтанный */
    MeasureParameter*  currTe          ;  /* Время выдоха [мсек] */
    MeasureParameter*  currTi          ;  /* Время вдоха  [мсек] */
    MeasureParameter*  currC_stat      ;  /* Комплайнс статический [0.1 мл/смН2О] */
    MeasureParameter*  currR_stat      ;  /* Резистанс статический [ммН2О * с/л] */
    MeasureParameter*  currLSF_C       ;  /* Комплайнс [0.1 мл/смН2О] */
    MeasureParameter*  currLSF_R       ;  /* Резистанс [ммН2О * с/л]  */
    MeasureParameter*  currPmean       ;  /* Pmean - среднее давление в магистрали вдоха [мм. вод. ст.] */
    MeasureParameter*  currLEAKPerc    ;  /* утечка [%] */
    MeasureParameter*  currLEAK        ;  /* утечка [л/мин] */
    MeasureParameter*  currPplato      ;  /* давление плато [смН2О] */
    MeasureParameter*  currFlowPeak    ;  /* пиковое значение потока на вдохе */
    MeasureParameter*  currO2          ;  /* % содержание кислорода в дыхательной смеси */

    MeasureParameter*  currRSBI;          /* значение RSBI         */
    MeasureParameter*  currPEEPtot;       /* значение PEEP Total = PEEP + AutoPEEP                  */
    MeasureParameter*  currRExp;          /* резистанс дыхательного контура на выдохе [мм вод.ст./(мл/сек)] */
    MeasureParameter*  currTi_Ttot;       /* значение Tinsp/Ttotal */
    MeasureParameter*  currI_E;           /* Отношение вдоха к выдоху [0.01 ед.] */
    MeasureParameter*  currRCInsp;        /* постоянная времени на вдохе [мс] */
    MeasureParameter*  currElastence;     /* значение эластенса    */
    MeasureParameter*  currMVsp_MV;       /* значение MV_spont/MV  */
    MeasureParameter*  currCCirc;         /* комплайнс дыхательного контура [мл/см вод.ст.] */
    MeasureParameter*  currRCirc;         /* резистанс дыхательного контура [0.1 cмH2O * c / л] */

    TunningParameter*  elOnFiO2error      ;
    TunningParameter*  elFiO2             ;
    TunningParameter*  elPO2              ;
    TunningParameter*  elP                ;
    TunningParameter*  elMVmax            ;
    TunningParameter*  elMVmin            ;
    TunningParameter*  elVExpMin          ;
    TunningParameter*  elVExpMax          ;
    TunningParameter*  elRBmin            ;
    TunningParameter*  elRBmax            ;

//    /// @name параметры для отображения в прямоугольниках измеряемых параметров.
//    /// @{
//    MeasureParameter*  currFlow;
//    MeasureParameter*  currFlow_L_min;
//    MeasureParameter*  currVol;
//    MeasureParameter*  currPR;          /* Pulse Rate */
//
//
//    MeasureParameter*  currMaxInspLEAK; /* Максимальное значение утечки за время вдоха [л/мин] */
//    MeasureParameter*  currEndExpLEAK;  /* Значение утечки в конце выдоха [л/мин] */
//    MeasureParameter*  currLevelFill;   /* уровень наполнения для шкального индикатора - текущий верхний предел динамики сигнала, значения от 0 до 10 */
//    MeasureParameter*  currScaleIndFill;/* динамика сигнала наполнения в шкальном индикаторе значения от 0 до 10 */
//    MeasureParameter*  currFilling;     /* наполнение - отношение размаха волны к подставке [%] */
//
//    MeasureParameter*  currEtCO2_pr;    /* СО2 на выдохе [0.1%] */
//    MeasureParameter*  currEtCO2_mm;    /* CO2 на выдохе [мм рт.ст.] */
//    MeasureParameter*  currFiCO2_pr;    /* СО2 на вдохе [0.1%] */
//    MeasureParameter*  currFiCO2_mm;    /* CO2 на вдохе [мм рт.ст.] */
//    MeasureParameter*  currSPO2_pr;     /* SPO2 в процентах */
//    MeasureParameter*  currAtmPres;     /* Атмосферное давление [мм рт. ст.] */
//    MeasureParameter*  currP01;         /* величина P0.1 [мм вод.ст.] */
//    MeasureParameter*  currVCO2;        /* элиминация CO2 за цикл [мл] */
//    MeasureParameter*  currMValv;       /* альвеолярная  вентиляция за минуту [0.1 л/мин] */
//    MeasureParameter*  currValv;        /* альвеолярная  вентиляция за цикл [мл] */
//    MeasureParameter*  currVd;          /* мертвое пространство за цикл [мл] */
//    MeasureParameter*  currMVAdapt;     /* процент MV адаптационный [%] */
//    MeasureParameter*  currPaw1;        /* Мгновенное значение давления после трубки [мм вод. ст.] */
//    MeasureParameter*  currVd_Vt;       /* Отношение объема мертвого пространства к дыхательному объему */
//
//    /// @}



    void calcRSBI();
    void calcRExp();
    void calcTiTtot();
    void calcIE();
    quint16 vexpAvg[4];
    quint8 vexpAvgIndex;

    /// указатель на объект
    static CanUnitKIVL* _self;

    civlModes m_civlMode;

    bool m_inspWasSpont;

protected:
    CanUnitKIVL( QObject* parent = 0);
public:
    static CanUnitKIVL* instance();
    void processInspiration(const CanMessage &msg);

    civlModes getCivlMode() const
    {
        return m_civlMode;
    }

    void bindContext(QQmlContext *ctx);

public slots:
    void setCivlMode(civlModes arg)
    {
       // qDebug()<<"new kivl mode: "<<arg;
        if (m_civlMode != arg) {
            m_civlMode = arg;
            emit civlModeChanged(arg);
        }
    }

private slots:
    void checkBoundsAndErrorsRB();
    void checkBoundsAndErrorsMV();
    void checkBoundsAndErrorsVolExp();

signals:

    void signalInspiration();


    void civlModeChanged(civlModes arg);
};

#endif // CANUNITKIVL_H
