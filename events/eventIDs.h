#ifndef EVENTIDS_H
#define EVENTIDS_H


#include <QObject>

class EventTypes: public QObject
{
    Q_OBJECT
    Q_ENUMS(ETypes)

    public:
        enum ETypes{
            /** инфо-сообщение только в окне тревог. Не
             * производится обновление полей времени добавления
             * или снятия такого события
             * Запись только в окно тревог
             */
            Info1,
            /** инфо-сообщение попадает в журнал тревог минуя
             * список тревог, окно тревог и журнал отложенных
             * тревог. Допускается только "добавление" такого
             * события. Для события обновляется только время
             * добавления, время снятия неприменимо
             * Запись в журнал тревог, время возникновения
             */
            Info2,
            /** инфо-сообщение попадает в журнал  тревог минуя
             * список тревог, окно тревог и журнал отложенных
             * тревог. Допускается "добавление" и "удаление"
             * такого события. Для события обновляется время
             * добавления, время удаления.
             * Запись в журнал тревог, интервал действия тревоги
             */
            Info3,
            /** Низкий приоритет
             * Попадает везде
             */
            Low,
            /** Средний приоритет.
             * попадает везде
             */
            Mid,
            /** Высокий приоритет.
             * Попадает везде
             */
            High
        };
};

/**
 * Класс, описывающий перечисления для тревог
 */
class EventIDs: public QObject
{
    Q_OBJECT
    Q_ENUMS(Ids)
public:

    /// Перечисление, описываюее возможные ID тревог.
    /// Нужно для возможности из QML выцепить из файла Dictionary.qml строку по индексу
    enum Ids{
        AlarmPAR =0                 ,/* Переход в ПАР */
        AlarmAR1                    ,/* Переход в АР1 */
        AlarmAR2                    ,/* Переход в АР2 */
        AlarmAR3                    ,/* Переход в АР3 */
        AlarmDischarge              ,/* Баттарея разряжена */
        AlarmAccOut                 ,/* " Аккумулятор отсутствует       " */
        AlarmCurrOver               ,/* "    Авария аккумулятора        " Авария аккумулятора (превышение тока зарядки аккумулятора или замыкание) */
        AlarmVoltOver               ,/* Превышение напряжения зарядки аккумулятора */
        AlarmTransFail              ,/* "  Неисправность ключа ЗУ      " */
        AlarmTimeOut10min           ,/* До полного разряда осталось < 10 мин */
        AlarmConnectError           ,/* Ошибка связи */
        AlarmCIVLOutCAN             ,/* Нет cвязи с КИВЛ-18 */
        AlarmPowerOutCAN            ,/* Нет cвязи с БП */
        AlarmVentFail               ,/* Неисправность вентилятора рабочего блока */
        AlarmRazg                   ,/* Разгерметизация */
        AlarmApnea                  ,/* Апноэ */
        AlarmHighPressure           ,/* Высокое давление */
        AlarmOcclusion              ,/* Окклюзия контура */
        AlarmHighEtCO2              ,/* Высокое СО2 */
        AlarmLowEtCO2               ,/* Низкое СО2 */
        AlarmHighVE                 ,/* Высокий минутный объем */
        AlarmLowVE                  ,/* Низкий минутный объем */
        AlarmHighVT                 ,/* Высокий объем вдоха */
        AlarmLowVT                  ,/* Низкий объем вдоха */
        AlarmHiPercentOxy           ,/* Высокая концентрация О2 */
        AlarmLoPercentOxy           ,/* Низкая концентрация О2 */
        AlarmOverPmax               ,/* Достигнуто Pmax */
        AlarmWeakPulseSignal        ,/* Слабый сигнал пульса */
        Alarm52                     ,/* Hеисправность канала формирования звука */
        AlarmTSPressed              ,/* Зажат тачскрин */
        AlarmLowLevelPressure       ,/* Низкое давление в контуре */
        AlarmTargetMVNotReachable   ,/* Целевая MV не достижима */
        AlarmVtminReached           ,/* Целевая MV не достижима */
        /***********************************************************************************/
        /*                     Тревоги в статусном пакете от КИВЛ                          */
        /***********************************************************************************/
        Alarm_CIVLStatFail_Can      ,/* ошибка передачи по CAN  */
        Alarm_CIVLStatFail_Ref      ,/* неисправен ИОН для AD7738  */
        Alarm_CIVLStatFailMix       ,/* Отсутствие связи с СГ */
        Alarm_CIVLStatFailP_Diff    ,/* Неисправность дифференицального датчика давления для датчика потока в электромагнитном клапане выдоха */
        Alarm_CIVLStatFailP_Exp     ,/* Неисправность датчика давления в магистрали выдоха */
        Alarm_CIVLStatFailP_Insp    ,/* Неисправность датчика давления в магистрали вдоха */
        Alarm_CIVLStatFailAD7738    ,/* Ошибка обмена с АЦП AD7738 */
        Alarm_CIVLStatFailFiO2      ,/* Неисправность датчика кислорода */
        Alarm_CIVLStatFailEMV       ,/* Неисправность клапана выдоха */
        Alarm_CIVLStatFailF_M       ,/* Неисправность VLV_F- */
        Alarm_CIVLStatFailF_P       ,/* Неисправность VLV_F+ */
        Alarm_CIVLStatFailZ_M       ,/* Неисправность VLV_Z- */
        Alarm_CIVLStatFailZ_P       ,/* Неисправность VLV_Z+ */
        Alarm_CIVLStatFailCompr     ,/* Неисправность компрессора продувки */
        Alarm_CIVLStatFailSafe      ,/* неисправность клапана безопасности */
        Alarm_CIVLStatFailFG        ,/* неисправен генератор потока */
        Alarm_CIVLStatFailEEPROM    ,/* неисправна EEPROM (хранящая время работы аппарата) */
        Alarm_CIVLStatFailC_FG      ,/* Ошибка констант генератора потока */
        Alarm_CIVLStatFailC_EMV     ,/* Клапан выдоха не откалиброван или ошибка в коэффициентах */
        Alarm_CIVLStatFailC_FP      ,/* Ошибка констант преобразователя "поток-давление" */
        Alarm_CIVLStatFailC_P       ,/* Ошибка констант датчиков давления */
        Alarm_CIVLStatFail12VA      ,/* ошибка напряжения 12VA */
        Alarm_CIVLStatFail2_5V      ,/* ошибка напряжения 2.5VA  */
        Alarm_CIVLStatFail5VA       ,/* ошибка напряжения 5VA */
        Alarm_CIVLStatFail12V_VLV   ,/* ошибка напряжения 12V_VLV */
        Alarm_CIVLStatFail15VA      ,/* ошибка напряжения 15VA */
        Alarm_CIVLStatFailV_EMV     ,/* ошибка напряжения V_EMV */
        /***********************************************************************************/
        /*                     Тревоги в статусном пакете от CГ                            */
        /***********************************************************************************/
        Alarm_MixStatFailPressOxy   ,/* При неисправном датчике давления для магистрали кислорода */
        Alarm_MixStatFailPressAbs   ,/* При неисправном датчике  абсолютного давления перед ГП */
        Alarm_MixStatFailPropOxy    ,/* При неисправном пропорциональном клапане О2 */
        Alarm_MixStatFailC_P_Abs    ,/* Не откалиброван датчик абсолютного давления перед ГП */

        /*
        * Тревоги среднего приоритета. Самые приоритетные средние -- вверху.
        */
        AlarmPowerOut               ,/* Нет сетевого питания */
        AlarmHighFreqBreath         ,/* Высокая частота */
        AlarmLowFreqBreath          ,/* Низкая частота */
        AlarmHighPressureOxy        ,/* Высокое давление кислорода */
        AlarmLowPressureOxy         ,/* Низкое давление кислорода */
        AlarmHighSpO2               ,/* Гипероксия */
        AlarmLowSpO2                ,/* Гипоксия */
        AlarmHighPR                 ,/* Тахикардия */
        AlarmLowPR                  ,/* Брадикардия */
        AlarmSPOModFail             ,/* Модуль ФПГ неисправен */
        AlarmSPOSensTakeoff         ,/* Датчик модуля ФПГ сброшен */
        AlarmCheckCapnoAdapter      ,/* "Проверьте адаптер капно и проведите калибровку" */
        MsgCalibrFiO2               ,/* Калибровка датчика FiO2 */
        MsgCalibrChangeFiO2         ,/* Замена датчика FiO2 */
        MsgTSNotCalibrated          ,/* Сенсорная панель не откалибрована */
        MsgChangeFiO2               ,/* Замените датчик FiO2 */
        MsgCompleteCalibrFiO2       ,/* Выполните калибровку датчика FiO2 */

        /*
        * Тревоги низкого приоритета (информационные), попадающие в журналы тревог
        */
        AlarmNebulSwitchOn          ,/* "Небулайзер включён" */
        AlarmNoCapno                ,/* Капнограф отключен */
        AlarmPPFail                 ,/* ПП неисправен */
        AlarmCapnoFail              ,/* Капнометр неисправен */
        CapnoMsg03                  ,/* "Закупорка капнографа          " */
        CapnoMsg09                  ,/* "Неисправен излучатель (капно) " */
        CapnoMsg10                  ,/* "Неисправен приемник   (капно) " */
        CapnoMsg11                  ,/* "Неисправен компрессор (капно) " */
        CapnoMsg12                  ,/* "Неиспр.Д.Давл." */
        CapnoMsg13                  ,/*"Перегрев (капно)              "*/
        CapnoMsg15                  ,/* "Залита камера (капно) " */
        AlarmNoSPOModule            ,/* "Модуль ФПГ отсутствует" */
        AlarmNoSPOSens              ,/* "Датчик модуля ФПГ отключен" */
        AlarmSPOSensFail            ,/* "Датчик модуля ФПГ неисправен" */
        AlarmSPOSensDegr            ,/* "Деградация датчика модуля ФПГ" */
        /*
        * Информационные сообщения. Переход в режим вентиляции.
        */
        AlarmZerroCalibr            ,/* сообщение "Калибровка нуля!!!" */
        AlarmCapnoMessages          ,/* сообщения от капнометра */
        ModeVent_CMV_VCV            ,/* "CMV/VCV" */
        ModeVent_CMV_PCV            ,/* "CMV/PCV" */
        ModeVent_SIMV_PCV           ,/* "SIMV/PC" */
        ModeVent_SIMV_VCV           ,/* "SIMV/VC" */
        ModeVent_CPAP               ,/* "CPAP+PS" */
        ModeVent_Adult              ,/* " ADULT " */
        ModeVent_Pediatr            ,/* " CHILD " */
        ModeVent_Apnea              ,/* " APNEA " */
        ModeVent_BISTEP             ,/* "BiSTEP " */
        MsgCalibrSuccess            ,/* Калибровка завершена */
        MsgCalibrCancel             ,/* Калибровка отменена */
        MsgCalibrFail               ,/* Ошибка калибровки */
        MsgCalibrFSensEMVE          ,/* "Калибр. датч. потока на выдохе" */
        MsgCalibrFastOxy            ,/* "Калибр. датч. #O@" *//* "Калибр. датчика кислорода #O@ " */
        MsgCalibrEMVE               ,/* "Калибр. ЭМКВ  " *//* "        Калибровка ЭМКВ       " */
        MsgCalibrSST                ,/* "   Короткий внутренний тест   " */ /* "КВТ              " */
        MsgUSBOutOfSpace            ,/* "USB: Носитель данных заполнен" */ /* "USB: Нет места" */
        AlarmSCMModFail             ,/* Модуль СЦМ неисправен */
        AlarmPlimit                 ,/* Достигнут Plimit - проверьте Pmax */
        /*
        * Информационные сообщения. Самые приоритетные никакие -- вверху.
        * Не попадают в журналы тревог
        */
        /*Info1*/
        NebulNotSwitch              ,/* "Небулайзер не вкл." */
        CapnoMsg01                  ,/* "Калибр. капно." */
        CapnoMsg02                  ,/* "Прогрев капно." */
        CapnoMsg04                  ,/* "Просушка капн." */
        CapnoMsg07                  ,/*"Капно отключен пользователем  " */
        CapnoMsg08                  ,/*"Капнограф отключен закупорка  " */
        CapnoMsg14                  ,/*"  Капнограф не используется   " */
        CapnoMsg16                  ,/*"  Продувка неудачна (капно)   " */
        AlarmStorageList            ,/* сообщение "См.Отлож.тревоги!" */
        CapnoMsg00                  ,/* "              ", - 0x00 */
        CapnoMsg05                  ,/* "Демонстрация  ", - 0x05 */
        CapnoMsg06                  ,/* "  Не подключена линия капно   ", - 0x06 */
        MsgExtPowerSource           ,/* "Работа от внешнего ист.питания" *//* "Внеш. ист.пит." */

        /*Info2*/
        AlarmStartDevice            ,/* сообщение "Включение аппарата!!!" */
        AlarmStopDevice             ,/* сообщение "Выключение аппарата" */
        AlarmSetNewTime             ,/* сообщение "Установлено новое время" */

        /*Info3*/
        MsgSanat                    ,/* "Санация" */
        MsgOxygen                   ,/* "Оксигенация" */
        MsgAlvRecrMan               ,/* Маневр раскрытия альвеол */
        MsgStandby                  ,/* Режим ожидания */
        MsgForcedInsp               ,/* Принудительный вдох */
        AlarmBatteryFail             /* " Аккумулятор отсутствует       " */
    };
    static EventTypes::ETypes getEventType(EventIDs::Ids id)
    {
        if(id <= EventIDs::Alarm_MixStatFailC_P_Abs) return EventTypes::High;
        else if(id <= EventIDs::MsgCompleteCalibrFiO2)  return EventTypes::Mid;
        else if(id <= EventIDs::AlarmPlimit)  return EventTypes::Low;
        else if(id <= EventIDs::MsgExtPowerSource)  return EventTypes::Info1;
        else if(id <= EventIDs::AlarmSetNewTime)  return EventTypes::Info2;
        else if(id <= EventIDs::AlarmBatteryFail)  return EventTypes::Info3;
    }
};



#endif // EVENTIDS_H
