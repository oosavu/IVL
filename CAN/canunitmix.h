#ifndef CANUNITMIX_H
#define CANUNITMIX_H

#include "canunit.h"

class CanUnitMix : public CanUnit
{
    Q_OBJECT
    Q_ENUMS(mixModes)
    Q_PROPERTY(mixModes mixMode READ getMixMode WRITE setMixMode NOTIFY mixModeChanged)
public:
    enum mixModes  {
        MIX_MODE_WAIT =0,           //  "ОЖИДАНИЕ"
        MIX_MODE_WORK =1,           //"РАБОТА". Поддержание заданной концентрации %О2. Переход в данный режим осуществляется, если имеется возможность работать в этом режиме (нет неисправностей, блокирующих нормальную работу аппарата). Неисправности можно узнать из статусного слова в ответе на изменение режима работы. СГ должен формировать пакеты с ID_FLOW_MIX и принимать пакеты ID_TASKOXY_MIX от КИВЛ. При отсутствии пакетов от КИВЛ заданная концентрация содержания кислорода поддерживаться не будет.
        MIX_MODE_KVT =2,            //  "Короткий Внутренний Тест" (КВТ)
        MIX_MODE_FVT =3,            //"Полный Внутренний Тест" (ПВТ)
        MIX_MODE_KALIB_DP =4,       //  (сервис) "КАЛИБРОВКА ДП". Переход в режим калибровки датчиков потока. Переход в данный режим осуществляется, если имеется возможность работать в этом режиме (нет неисправностей, блокирующих нормальную работу аппарата). Неисправности можно узнать из статусного слова в ответе на изменение режима работы. Разрешается приём пакетов с ID_COXY_MIX и ID_CAIR_MIX. Расширенная информация для режима калибровки содержится в пакете ID_OPT_MIX.
        MIX_MODE_KALIB_ATM_P =5,    //  (сервис) "КАЛИБРОВКА АТМ ДАВЛЕНИЯ". Текущее давление передаётся в пакете ID_PRESS_MIX, СГ отвечает ID_CLBR_ERR_MIX.
        MIX_MODE_KALIB_O2_P =6,     //  (сервис) "КАЛИБРОВКА ДАВЛЕНИЯ КИСЛОРОДА". Текущее давление передаётся в пакете ID_PRESS_MIX, СГ отвечает ID_CLBR_ERR_MIX.
        MIX_MODE_GEN_O2 =7,         // (сервис) "ГЕНЕРАЦИЯ КИСЛОРОДА". Требуемый поток кислорода устанавливается пакетом ID_TASKOXY_MIX. Режим предназначен для калибровки датчиков кислорода в верхней точке (в частности, датчика кислорода в капнографе бокового отведения).
        MIX_MODE_AR1 =8,            //  (сервис/анализ_рисков) "АВАРИЙНЫЙ РЕЖИМ №1" (АР-1). Аварийный режим №1. Необходимо подать 20 л/мин чистого кислорода. Игнорируется обработка пакета с требованием перейти в АР-1, т.к. это делает сам СГ.
        MIX_MODE_AR2 =9,            //  (сервис/анализ_рисков) "АВАРИЙНЫЙ РЕЖИМ №2" (АР-2). Игнорируется обработка пакета с требованием перейти в АР-2, т.к. это делает сам СГ.
        MIX_MODE_AR3 =10,           // (сервис/анализ_рисков) "АВАРИЙНЫЙ РЕЖИМ №3" (АР-3). Игнорируется обработка пакета с требованием перейти в АР-3, т.к. это делает сам СГ.
        MIX_MODE_PAR =11,           // (сервис/анализ_рисков) "ПОЛНОСТЬЮ АВАРИЙНЫЙ РЕЖИМ" (ПАР). Игнорируется обработка пакета с требованием перейти в ПАР, т.к. это делает сам СГ.
        MIX_MODE_UNKNOWN=12            // неизвестный режим
    };

private:
    /// указатель на объект
    static CanUnitMix* _self;
    mixModes m_civlMode;

    void process_ID_STATUS_MIX(const CanMessage &msg);
    void process_ID_VERSION_MIX(const CanMessage &msg);

    MeasureParameter*  currPOxy      ; //давление кислорода
    TunningParameter*     elPOxyLim     ;

protected:
    CanUnitMix( QObject* parent = 0);
public:
    static CanUnitMix* instance();


    mixModes getMixMode() const
    {
        return m_civlMode;
    }

    void bindContext(QQmlContext *ctx);

public slots:
    void setMixMode(mixModes arg)
    {
        //qDebug()<<"new mix mode: "<<arg;
        if (m_civlMode != arg) {
            m_civlMode = arg;

            emit mixModeChanged(arg);
        }
    }

    void calcPOxyErrors();
signals:
    void mixModeChanged(mixModes arg);
};


#endif // CANUNITMIX_H
