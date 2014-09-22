#ifndef REGIMEMANAGER_H
#define REGIMEMANAGER_H

#include <QObject>
#include <QDebug>
#include "CAN/candevice.h"
#include "canmanager.h"


//#include "alarmmanager.h"
//#include "nebulaizermanager.h"

//class CanManager;
//class CanDevice;

/// Класс, представляющий режим БУ.
/// преоставляет методы установки и получения режима, а так же выполняет логику при изменении режима
class RegimeManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(regimeManagerModes)
    /// публикация свойства режима для QML
    Q_PROPERTY(regimeManagerModes regimeManagerMode READ getRegimeManagerMode WRITE setRegimeManagerMode NOTIFY regimeManagerModeChanged)
public:


    /// перечисление возможных режимов работы БУ
    enum  regimeManagerModes{
        REGIMEMANAGER_MODE_WAIT = 0,
        REGIMEMANAGER_MODE_COMMON_INIT = 1,   ///< горячий рестарт
        REGIMEMANAGER_MODE_FIRST_RUN = 2,
        REGIMEMANAGER_MODE_WORK = 3,
        REGIMEMANAGER_MODE_AR1 = 4,           ///< Фатальный отказ КИВЛ.
        REGIMEMANAGER_MODE_AR2 = 5,           ///< Частичный отказ КИВЛ – при потере функции управления потоком (отказ воздуходувки)
        REGIMEMANAGER_MODE_AR3 = 6,           ///< Фатальный отказ СГ
        REGIMEMANAGER_MODE_PAR = 7,           ///< Нарушение электропитания КИВЛ и СГ, а также при их одновременном фатальном отказе.
        REGIMEMANAGER_MODE_CALIBR = 8,
        REGIMEMANAGER_MODE_BLOCKWORK = 9,
        REGIMEMANAGER_MODE_TST = 10,           ///< тестовый режим работы
        REGIMEMANAGER_MODE_CHECK = 11,
        REGIMEMANAGER_MODE_STANDBY = 12
    };

    /// колличество возможных режимов
    static const quint32 modesCount = 13;

    /// получение текущего режима
    /// @returns текущий режим
//    RegimeManager::regimeManagerModes getMode();



    /// метод получения ссылки на объект.
    /// @returns указатель на объект
    static RegimeManager* instance();

    regimeManagerModes getRegimeManagerMode()
    {
        return m_regimeManagerMode;
    }

public slots:


    void slotCanDeviceMode(CanDevice::canDeviceModes arg);

    /// установка нового режима
    /// @param arg новый режим
    void setRegimeManagerMode(regimeManagerModes arg)
    {
        {
            if (m_regimeManagerMode != arg) {
                m_regimeManagerMode = arg;
                qDebug() << "NEW MODE:" << m_regimeManagerMode;
                CanMessage msgCapnoOpt(canId::capno1::ID_OPT_CAPNO1,8);
                msgCapnoOpt.setUInt8(0xFF,0);
                msgCapnoOpt.setUInt8(0x96,4);
                emit regimeManagerModeChanged(arg);
            }
        }
    }


private:

    /// указатель на объект
    static RegimeManager* _self;

    /// конструктор.
    RegimeManager(QObject *parent = 0);

    regimeManagerModes m_regimeManagerMode;

signals:
    void regimeManagerModeChanged(regimeManagerModes arg);
};


Q_DECLARE_METATYPE(RegimeManager::regimeManagerModes)

#endif // REGIMEMANAGER_H
