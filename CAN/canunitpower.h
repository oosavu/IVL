#ifndef CANUNITPOWER_H
#define CANUNITPOWER_H

#include "canunit.h"

class CanUnitPower : public CanUnit
{
    Q_OBJECT
    Q_ENUMS(powerModes)
    Q_ENUMS(soundStates)
    Q_PROPERTY(powerModes powerMode READ getPowerMode  NOTIFY powerModeChanged)
    Q_PROPERTY(bool isCharging READ getIsCharging  NOTIFY isChargingChanged)
    Q_PROPERTY(quint8 chargeLevel READ getChargeLevel  NOTIFY chargeLevelChanged)
    Q_PROPERTY(soundStates currSoundState READ getCurrSoundState WRITE setCurrSoundState NOTIFY currSoundStateChanged)

public:
    enum powerModes  {
        POWER_MODE_WAIT         = 0, /* режим ОЖИДАНИЕ */
        POWER_MODE_WORK         = 1, /* режим РАБОТА */
        POWER_MODE_UNKNOWN      = 2  /* режим кивла не известен */
    };
    enum soundStates  {
        POWER_SOUND_NONE       = 0, /* не играть звук */
        POWER_SOUND_HIGH       = 1, /* звук тревоги высокого приоритета */
        POWER_SOUND_MID        = 2  /* звук тревоги среднего приоритета */
    };

private:

    void process_ID_OFF_POWER(const CanMessage &msg);
    void process_ID_STATUS_POWER(const CanMessage &msg);
    void process_ID_VERSION_POWER(const CanMessage &msg);

    /// указатель на объект
    static CanUnitPower* _self;
    powerModes m_powerMode;

    bool m_isCharging;

    quint8 m_chargeLevel;

    soundStates m_currSoundState;

protected:
    CanUnitPower( QObject* parent = 0);
public:
    static CanUnitPower* instance();
    powerModes getPowerMode() const
    {
        return m_powerMode;
    }
    bool getIsCharging() const
    {
        return m_isCharging;
    }

    quint8 getChargeLevel() const
    {
        return m_chargeLevel;
    }

    soundStates getCurrSoundState() const
    {
        return m_currSoundState;
    }

public slots:
    void setPowerMode(powerModes arg)
    {
        if (m_powerMode != arg) {
            m_powerMode = arg;
            emit powerModeChanged(arg);
        }
    }
    void setIsCharging(bool arg)
    {
        if (m_isCharging != arg) {
            m_isCharging = arg;
            emit isChargingChanged(arg);
        }
    }

    void setChargeLevel(quint8 arg)
    {
        if (m_chargeLevel != arg) {
            m_chargeLevel = arg;
            emit chargeLevelChanged(arg);
        }
    }

    void setCurrSoundState(soundStates arg)
    {
        if (m_currSoundState != arg) {
            m_currSoundState = arg;
            emit currSoundStateChanged(arg);
        }
    }

signals:
    void powerModeChanged(powerModes arg);
    void isChargingChanged(bool arg);
    void chargeLevelChanged(quint8 arg);
    void currSoundStateChanged(soundStates arg);
};

#endif // CANUNITPOWER_H
