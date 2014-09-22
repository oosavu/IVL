#ifndef CANUNITCAPNO1_H
#define CANUNITCAPNO1_H

#include "canunit.h"

/// класс, представляющий капнограф БО.
/// является классом одиночкой,
/// занимается обработкой пакетов CAN от данного устройства
class CanUnitCapno1 : public CanUnit
{
    Q_OBJECT
private:
    void process_ID_STATUS_CAPNO1      (const CanMessage &msg);
    void process_ID_VERSION_CAPNO1     (const CanMessage &msg);
    void process_ID_WAVE_CAPNO1        (const CanMessage &msg);
    void process_ID_CO2_DATA_CAPNO1    (const CanMessage &msg);
    void process_ID_O2_DATA_CAPNO1     (const CanMessage &msg);
    void process_ID_CALOXY_DEBUG_CAPNO1(const CanMessage &msg);
    void process_ID_CALIBR_MSG_CAPNO1  (const CanMessage &msg);

    MeasureParameter*  currEtO2;        /* концентрация О2 в конце выдоха */
    MeasureParameter*  currEtCO2_pr;    /* СО2 на выдохе [0.1%] */
    MeasureParameter*  currEtCO2_mm;    /* CO2 на выдохе [мм рт.ст.] */
    MeasureParameter*  currFiCO2_pr;    /* СО2 на вдохе [0.1%] */
    MeasureParameter*  currFiCO2_mm;    /* CO2 на вдохе [мм рт.ст.] */
    MeasureParameter*  currVO2;

    TunningParameter*  elEtCO2prMin      ;
    TunningParameter*  elEtCO2prMax      ;
    TunningParameter*  elEtCO2mmMin      ;
    TunningParameter*  elEtCO2mmMax      ;

    /// указатель на объект
    static CanUnitCapno1* _self;
protected:
    /// конструктор
    CanUnitCapno1( QObject* parent = 0);
public:
    static CanUnitCapno1* instance();
    void bindContext(QQmlContext *ctx);

private slots:
    void checkBoundsAndErrorsEtCO2();


};

#endif // CANUNITCAPNO1_H
