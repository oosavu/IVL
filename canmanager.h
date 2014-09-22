#ifndef CANMANAGER_H
#define CANMANAGER_H

#include <QDateTime>

#include "regimemanager.h"


#include "CAN/canunitmix.h"
#include "CAN/canunitkivl.h"
#include "CAN/canunitpower.h"
#include "CAN/canunitspo.h"
#include "CAN/canunitcapno1.h"
#include "CAN/canunitcapno2.h"
#include "CAN/candevice.h"

//class TimerThread: public QTimer
//{

//};

class CanManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime systemDateTime READ systemDateTime WRITE setSystemDateTime NOTIFY systemDateTimeChanged)



public:
    static CanManager* instance();


    QDateTime systemDateTime() const
    {
        return m_systemDateTime;
    }

private:
    static CanManager* _self;
    explicit CanManager(QObject *parent = 0);

    QTimer* timer50Hz;
    QTime timeLeft;
    int ticks;

    QDateTime m_systemDateTime;

    QThread canManagerThread;

signals:

void systemDateTimeChanged(QDateTime arg);

public slots:
    void startInitCanUnits();
    
    void setSystemDateTime(QDateTime arg)
    {
        if (m_systemDateTime != arg) {
            m_systemDateTime = arg;
            emit systemDateTimeChanged(arg);
        }
    }

private slots:
    void slot50Hz();
    void slot1hz();

    
};

#endif // CANMANAGER_H
