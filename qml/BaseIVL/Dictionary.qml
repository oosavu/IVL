import QtQuick 2.0
import CppImport 1.0

QtObject{

    property var ventModesStrs:{
     0:    qsTr("NStr_Mode_CMV_VCV")    + tm.tS,
     1:    qsTr("NStr_Mode_CMV_PCV")    + tm.tS,
     2:    qsTr("NStr_Mode_SIMV_PCV")   + tm.tS,
     3:    qsTr("NStr_Mode_SIMV_VCV")   + tm.tS,
     4:    qsTr("NStr_Mode_CPAP")       + tm.tS,
     5:    qsTr("NStr_Mode_BISTEP")     + tm.tS,
     6:    qsTr("NStr_Mode_NIV")        + tm.tS,
     7:    qsTr("NStr_Mode_APRV")       + tm.tS,
     8:    qsTr("NStr_Mode_PCV_VG")     + tm.tS,
     9:    qsTr("NStr_Mode_SIMV_DC")    + tm.tS,
    10:    qsTr("NStr_Mode_ISV")        + tm.tS,
    11:    qsTr("NStr_Mode_UNKNOWN")    + tm.tS,
    }
    property var rulesVM:{
        0:{ // CMV/VCV
            0: { 0: dpFiO2      , 1: "FiO2", 2: "%"     },
            1: { 0: dpPMax      , 1: "Pmax", 2: "смH2O" },
            2: { 0: dpRB        , 1: "RB"  , 2: "1/мин."},
            3: { 0: dpPEEP      , 1: "PEEP", 2: "смH2O" },
            4: { 0: dpVInsp     , 1: "VInsp", 2: "мл"    },
            5: { 0: dpTInsp     , 1: "TInsp", 2: "сек"   },
            6: { 0: dpPTrig     , 1: "PTrig", 2: "смH2O" },
            7: { 0: dpTrigWnd   , 1: "TrigWnd", 2: "%"     },
            8: { 0: dpFormFlow  , 1: "dpFormFlow", 2: "%"     },
            9: { 0: dpPlato     , 1: "FiO2", 2: "%"     },
            10:{ 0: 0           , 1: "FiO2", 2: "%"     },
            11:{ 0: 0           , 1: "FiO2", 2: "%"     }
        },
        1:{ // CMV/PCV
            0: { 0: dpFiO2      , 1: "FiO2", 2: "%"     },
            1: { 0: dpPMax      , 1: "Pmax", 2: "Pa"    },
            2: { 0: dpRB        , 1: "RB"  , 2: "1/sec" },
            3: { 0: dpPEEP      , 1: "PEEP", 2: "Pa"    },
            4: { 0: dpPInsp     , 1: "FiO2", 2: "%"     },
            5: { 0: dpTInsp     , 1: "FiO2", 2: "%"     },
            6: { 0: dpPTrig     , 1: "FiO2", 2: "%"     },
            7: { 0: dpTrigWnd   , 1: "FiO2", 2: "%"     },
            8: { 0: 0           , 1: "FiO2", 2: "%"     },
            9: { 0: 0           , 1: "FiO2", 2: "%"     },
            10:{ 0: 0           , 1: "FiO2", 2: "%"     },
            11:{ 0: 0           , 1: "FiO2", 2: "%"     }
        },
        2:{ // SIMV/VC
            0: { 0: dpFiO2      , 1: "FiO2", 2: "%"     },
            1: { 0: dpPMax      , 1: "Pmax", 2: "Pa"    },
            2: { 0: dpRB        , 1: "RB"  , 2: "1/sec" },
            3: { 0: dpPEEP      , 1: "PEEP", 2: "Pa"    },
            4: { 0: dpPInsp     , 1: "FiO2", 2: "%"     },
            5: { 0: dpTInsp     , 1: "FiO2", 2: "%"     },
            6: { 0: dpPTrig     , 1: "FiO2", 2: "%"     },
            7: { 0: dpTrigWnd   , 1: "FiO2", 2: "%"     },
            8: { 0: 0           , 1: "FiO2", 2: "%"     },
            9: { 0: 0           , 1: "FiO2", 2: "%"     },
            10:{ 0: 0           , 1: "FiO2", 2: "%"     },
            11:{ 0: 0           , 1: "FiO2", 2: "%"     }
        },
        3:{ // SIMV/PC
            0: { 0: dpFiO2      , 1: "FiO2", 2: "%"     },
            1: { 0: dpPMax      , 1: "Pmax", 2: "Pa"    },
            2: { 0: dpRB        , 1: "RB"  , 2: "1/sec" },
            3: { 0: dpPEEP      , 1: "PEEP", 2: "Pa"    },
            4: { 0: dpPInsp     , 1: "FiO2", 2: "%"     },
            5: { 0: dpTInsp     , 1: "FiO2", 2: "%"     },
            6: { 0: dpPTrig     , 1: "FiO2", 2: "%"     },
            7: { 0: dpTrigWnd   , 1: "FiO2", 2: "%"     },
            8: { 0: 0           , 1: "FiO2", 2: "%"     },
            9: { 0: 0           , 1: "FiO2", 2: "%"     },
            10:{ 0: 0           , 1: "FiO2", 2: "%"     },
            11:{ 0: 0           , 1: "FiO2", 2: "%"     }
        }
    }

    property var languageStrs:{
     0:    qsTr("NStr_Lang_Rus")    + tm.tS,
     1:    qsTr("NStr_Lang_Eng")    + tm.tS,
     }
//    Component.onCompleted: {
//        console.log(typeof(AlarmId.AlarmLoPercentOxy))
//        var qwe = {45: "123"}
//    }
//    property var alarmSt123
//    Component.onCompleted:{
//        alarmSt123 = {
//        (AlarmId.AlarmAR1) : "234",
//        AlarmId.AlarmAR2 : "235"}
//    }

    property var alarmStrs:[

/************************************************************************************/
/* Тревоги высокого приоритета. Самые приоритетные высокие -- вверху.               */
/************************************************************************************/
        qsTr("AlarmPAR") + tm.tS,               /* Переход в ПАР */
        qsTr("AlarmAR1") + tm.tS,               /* Переход в АР1 */
        qsTr("AlarmAR2") + tm.tS,               /* Переход в АР2 */
        qsTr("AlarmAR3") + tm.tS,               /* Переход в АР3 */
        qsTr("AlarmDischarge") + tm.tS,         /* Баттарея разряжена */
        qsTr("AlarmAccOut") + tm.tS,            /* " Аккумулятор отсутствует       " */
        qsTr("AlarmCurrOver") + tm.tS,          /* "    Авария аккумулятора        " Авария аккумулятора (превышение тока зарядки аккумулятора или замыкание) */
        qsTr("AlarmVoltOver") + tm.tS,          /* Превышение напряжения зарядки аккумулятора */
        qsTr("AlarmTransFail") + tm.tS,         /* "  Неисправность ключа ЗУ      " */
        qsTr("AlarmTimeOut10min") + tm.tS,      /* До полного разряда осталось < 10 мин */
        qsTr("AlarmConnectError") + tm.tS,      /* Ошибка связи */
        qsTr("AlarmCIVLOutCAN") + tm.tS,        /* Нет cвязи с КИВЛ-18 */
        qsTr("AlarmPowerOutCAN") + tm.tS,       /* Нет cвязи с БП */
        qsTr("AlarmVentFail") + tm.tS,          /* Неисправность вентилятора рабочего блока */
        qsTr("AlarmRazg") + tm.tS,              /* Разгерметизация */
        qsTr("AlarmApnea") + tm.tS,             /* Апноэ */
        qsTr("AlarmHighPressure") + tm.tS,      /* Высокое давление */
        qsTr("AlarmOcclusion") + tm.tS,         /* Окклюзия контура */
        qsTr("AlarmHighEtCO2") + tm.tS,         /* Высокое СО2 */
        qsTr("AlarmLowEtCO2") + tm.tS,          /* Низкое СО2 */
        qsTr("AlarmHighVE" ) + tm.tS,           /* Высокий минутный объем */
        qsTr("AlarmLowVE") + tm.tS,             /* Низкий минутный объем */
        qsTr("AlarmHighVT") + tm.tS,            /* Высокий объем вдоха */
        qsTr("AlarmLowVT"  ) + tm.tS,           /* Низкий объем вдоха */
        qsTr("AlarmHiPercentOxy" ) + tm.tS,     /* Высокая концентрация О2 */
        qsTr("AlarmLoPercentOxy" ) + tm.tS,     /* Низкая концентрация О2 */
        qsTr("AlarmOverPmax" ) + tm.tS,         /* Достигнуто Pmax */
        qsTr("AlarmWeakPulseSignal" ) + tm.tS,  /* Слабый сигнал пульса */
        qsTr("Alarm52" ) + tm.tS,               /* Hеисправность канала формирования звука */
        qsTr("AlarmTSPressed") + tm.tS,         /* Зажат тачскрин */
        qsTr("AlarmLowLevelPressure") + tm.tS,  /* Низкое давление в контуре */
/***********************************************************************************/
/*                     Тревоги в статусном пакете от КИВЛ                          */
/***********************************************************************************/
        qsTr("Alarm_CIVLStatFail_Can") + tm.tS,     /* ошибка передачи по CAN  */
        qsTr("Alarm_CIVLStatFail_Ref") + tm.tS,     /* неисправен ИОН для AD7738  */
        qsTr("Alarm_CIVLStatFailMix") + tm.tS,      /* Отсутствие связи с СГ */
        qsTr("Alarm_CIVLStatFailP_Diff") + tm.tS,   /* Неисправность дифференицального датчика давления для датчика потока в электромагнитном клапане выдоха */
        qsTr("Alarm_CIVLStatFailP_Exp") + tm.tS,    /* Неисправность датчика давления в магистрали выдоха */
        qsTr("Alarm_CIVLStatFailP_Insp") + tm.tS,   /* Неисправность датчика давления в магистрали вдоха */
        qsTr("Alarm_CIVLStatFailAD7738") + tm.tS,   /* Ошибка обмена с АЦП AD7738 */
        qsTr("Alarm_CIVLStatFailFiO2") + tm.tS,     /* Неисправность датчика кислорода */
        qsTr("Alarm_CIVLStatFailEMV") + tm.tS,      /* Неисправность клапана выдоха */
        qsTr("Alarm_CIVLStatFailF_M") + tm.tS,      /* Неисправность VLV_F- */
        qsTr("Alarm_CIVLStatFailF_P") + tm.tS,      /* Неисправность VLV_F+ */
        qsTr("Alarm_CIVLStatFailZ_M") + tm.tS,      /* Неисправность VLV_Z- */
        qsTr("Alarm_CIVLStatFailZ_P") + tm.tS,      /* Неисправность VLV_Z+ */
        qsTr("Alarm_CIVLStatFailCompr") + tm.tS,    /* Неисправность компрессора продувки */
        qsTr("Alarm_CIVLStatFailSafe") + tm.tS,     /* неисправность клапана безопасности */
        qsTr("Alarm_CIVLStatFailFG") + tm.tS,       /* неисправен генератор потока */
        qsTr("Alarm_CIVLStatFailEEPROM") + tm.tS,   /* неисправна EEPROM (хранящая время работы аппарата) */
        qsTr("Alarm_CIVLStatFailC_FG") + tm.tS,     /* Ошибка констант генератора потока */
        qsTr("Alarm_CIVLStatFailC_EMV") + tm.tS,    /* Клапан выдоха не откалиброван или ошибка в коэффициентах */
        qsTr("Alarm_CIVLStatFailC_FP") + tm.tS,     /* Ошибка констант преобраз ,ователя "поток-давление" */
        qsTr("Alarm_CIVLStatFailC_P") + tm.tS,      /* Ошибка констант датчиков давления */
        qsTr("Alarm_CIVLStatFail12VA") + tm.tS,     /* ошибка напряжения 12VA */
        qsTr("Alarm_CIVLStatFail2_5V") + tm.tS,     /* ошибка напряжения 2.5VA  */
        qsTr("Alarm_CIVLStatFail5VA") + tm.tS,      /* ошибка напряжения 5VA */
        qsTr("Alarm_CIVLStatFail12V_VLV") + tm.tS,  /* ошибка напряжения 12V_VLV */
        qsTr("Alarm_CIVLStatFail15VA") + tm.tS,     /* ошибка напряжения 15VA */
        qsTr("Alarm_CIVLStatFailV_EMV") + tm.tS,    /* ошибка напряжения V_EMV */
/***********************************************************************************/
/*                     Тревоги в статусном пакете от CГ                            */
/***********************************************************************************/
        qsTr("Alarm_MixStatFailPressOxy") + tm.tS,  /* При неисправном датчике давления для магистрали кислорода */
        qsTr("Alarm_MixStatFailPressAbs") + tm.tS,  /* При неисправном датчике  абсолютного давления перед ГП */
        qsTr("Alarm_MixStatFailPropOxy") + tm.tS,   /* При неисправном пропорциональном клапане О2 */
        qsTr("Alarm_MixStatFailC_P_Abs") + tm.tS,   /* Не откалиброван датчик абсолютного давления перед ГП */
/***********************************************************************************/
/*     Тревоги среднего приоритета. Самые приоритетные средние -- вверху.          */
/***********************************************************************************/
        qsTr("AlarmPowerOut") + tm.tS,              /* Нет сетевого питания */
        qsTr("AlarmHighFreqBreath") + tm.tS,        /* Высокая частота */
        qsTr("AlarmLowFreqBreath") + tm.tS,         /* Низкая частота */
        qsTr("AlarmHighPressureOxy") + tm.tS,       /* Высокое давление кислорода */
        qsTr("AlarmLowPressureOxy") + tm.tS,        /* Низкое давление кислорода */
        qsTr("AlarmHighSpO2") + tm.tS,              /* Гипероксия */
        qsTr("AlarmLowSpO2") + tm.tS,               /* Гипоксия */
        qsTr("AlarmHighPR") + tm.tS,                /* Тахикардия */
        qsTr("AlarmLowPR") + tm.tS,                 /* Брадикардия */
        qsTr("AlarmSPOModFail") + tm.tS,            /* Модуль ФПГ не ,исправен */
        qsTr("AlarmSPOSensTakeoff") + tm.tS,        /* Датчик модуля ФПГ сброшен */
        qsTr("AlarmCheckCapnoAdapter") + tm.tS,     /* "Проверьте адаптер капно и проведите калибровку" */
        qsTr("MsgCalibrFiO2") + tm.tS,              /* Калибровка датчика FiO2 */
        qsTr("MsgCalibrChangeFiO2") + tm.tS,        /* Замена датчика FiO2 */
        qsTr("MsgTSNotCalibrated") + tm.tS,         /* Сенсорная панель не откалибрована */
        qsTr("MsgChangeFiO2") + tm.tS,              /* Замените датчик FiO2 */
        qsTr("MsgCompleteCalibrFiO2") + tm.tS,      /* Выполните калибровку датчика FiO2 */
/***********************************************************************************/
/*     Тревоги низкого приоритета (информационные) , попадающие в журналы тревог   */
/***********************************************************************************/
        qsTr("AlarmNebulSwitchOn") + tm.tS,         /* "Небулайзер включён" */
        qsTr("AlarmNoCapno") + tm.tS,               /* Капнограф отключен */
        qsTr("AlarmPPFail") + tm.tS,                /* ПП неисправен */
        qsTr("AlarmCapnoFail") + tm.tS,             /* Капнометр неисправен */
        qsTr("CapnoMsg03") + tm.tS,                 /* "Закупорка капнографа          " */
        qsTr("CapnoMsg09") + tm.tS,                 /* "Неисправен излучатель (капно) " */
        qsTr("CapnoMsg10") + tm.tS,                 /* "Неисправен приемник   (капно) " */
        qsTr("CapnoMsg11") + tm.tS,                 /* "Неисправен компрессор (капно) " */
        qsTr("CapnoMsg12") + tm.tS,                 /* "Неиспр.Д.Давл." */
        qsTr("CapnoMsg13") + tm.tS,                 /*"Перегрев (капно)              "*/
        qsTr("CapnoMsg15") + tm.tS,                 /* "Залита камера (капно) " */
        qsTr("AlarmNoSPOModule") + tm.tS,           /* "Модуль ФПГ отсутствует" */
        qsTr("AlarmNoSPOSens") + tm.tS,             /* "Датчик модуля ФПГ отключен" */
        qsTr("AlarmSPOSensFail") + tm.tS,           /* "Датчик модуля ФПГ неисправен" */
        qsTr("AlarmSPOSensDegr") + tm.tS,           /* "Деградация датчика модуля ФПГ" */
/***********************************************************************************/
/*     Информационные сообщения. Переход в режим вентиляции.                       */
/***********************************************************************************/
        qsTr("AlarmZerroCalibr") + tm.tS,           /* сообщение "Калибровка нуля!!!" */
        qsTr("AlarmCapnoMessages") + tm.tS,         /* сообщения от капнометра */
        qsTr("ModeVent_CMV_VCV") + tm.tS,           /* "CMV/VCV" */
        qsTr("ModeVent_CMV_PCV") + tm.tS,,          /* "CMV/PCV" */
        qsTr("ModeVent_SIMV_PCV") + tm.tS,          /* "SIMV/PC" */
        qsTr("ModeVent_SIMV_VCV") + tm.tS,          /* "SIMV/VC" */
        qsTr("ModeVent_CPAP") + tm.tS,              /* "CPAP+PS" */
        qsTr("ModeVent_Adult") + tm.tS,             /* " ADULT " */
        qsTr("ModeVent_Pediatr") + tm.tS,           /* " CHILD " */
        qsTr("ModeVent_Apnea") + tm.tS,             /* " APNEA " */
        qsTr("ModeVent_BISTEP") + tm.tS,            /* "BiSTEP " */
        qsTr("MsgCalibrSuccess") + tm.tS,           /* Калибровка завершена */
        qsTr("MsgCalibrCancel") + tm.tS,            /* Калибровка отменена */
        qsTr("MsgCalibrFail") + tm.tS,              /* Ошибка калибровки */
        qsTr("MsgCalibrFSensEMVE") + tm.tS,         /* "Калибр. датч. потока на выдохе" */
        qsTr("MsgCalibrFastOxy") + tm.tS,           /* "Калибр. датч. #O@" */        /* "Калибр. датчика кислорода #O@ " */
        qsTr("MsgCalibrEMVE") + tm.tS,              /* "Калибр. ЭМКВ  " */        /* "        Калибровка ЭМКВ       " */
        qsTr("MsgCalibrSST") + tm.tS,               /* "   Короткий внутренний тест   " */ /* "КВТ              " */
/***********************************************************************************/
/*    Информационные сообщения. Самые приоритетные никакие -- вверху.              */
/*    Не попадают в журналы тревог                                                 */
/***********************************************************************************/
        qsTr("NebulNotSwitch") + tm.tS,             /* "Небулайзер не вкл." */
        qsTr("CapnoMsg01") + tm.tS,                 /* "Калибр. капно." */
        qsTr("CapnoMsg02") + tm.tS,                 /* "Прогрев капно." */
        qsTr("CapnoMsg04") + tm.tS,                 /* "Просушка капн." */
        qsTr("CapnoMsg07") + tm.tS,                 /*"Капно отключен пользователем  " */
        qsTr("CapnoMsg08") + tm.tS,                 /*"Капнограф отключен закупорка  " */
        qsTr("CapnoMsg14") + tm.tS,                 /*"  Капнограф не используется   " */
        qsTr("CapnoMsg16") + tm.tS,                 /*"  Продувка неудачна (капно)   " */
        qsTr("AlarmStorageList") + tm.tS,           /* сообщение "См.Отлож.тревоги!" */
        qsTr("CapnoMsg00") + tm.tS,                 /* "              " , - 0x00 */
        qsTr("CapnoMsg05") + tm.tS,                 /* "Демонстрация  " , - 0x05 */
        qsTr("CapnoMsg06") + tm.tS,                 /* "  Не подключена линия капно   " , - 0x06 */
        qsTr("MsgExtPowerSource") + tm.tS,          /* "Работа от внешнего ист.питания" */ /* "Внеш. ист.пит." */
        qsTr("AlarmStartDevice") + tm.tS,           /* сообщение "Включение аппарата!!!" */
        qsTr("AlarmStopDevice") + tm.tS,            /* сообщение "Выключение аппарата" */
        qsTr("AlarmSetNewTime") + tm.tS,            /* сообщение "Установлено новое время" */
        qsTr("MsgSanat") + tm.tS,                   /* "Санация" */
        qsTr("MsgOxygen") + tm.tS,                  /* "Оксигенация" */
        qsTr("MsgAlvRecrMan") + tm.tS,              /* Маневр раскрытия альвеол */
        qsTr("MsgStandby") + tm.tS,                 /* Режим ожидания */
        qsTr("MsgForcedInsp") + tm.tS,              /* Принудительный вдох */
        qsTr("AlarmBatteryFail") + tm.tS            /* " Аккумулятор отсутствует       " */
    ]
}
