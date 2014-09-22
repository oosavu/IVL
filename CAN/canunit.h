#ifndef CANUNIT_H
#define CANUNIT_H

#include <QTimer>
#include <QQmlContext>
#include "canmessage.h"
#include "can_id.h"

#include "../types/parametersTypes.h"
#include "../events/eventmanager.h"

//extern QMutex guiMutex;

class RegimeManager;

/// класс, представляющий абстрактное устройство CAN.
/// является классом - одиночкой
/// предоставляемый функционал - функция обработки сообщения CAN от данного модуля
/// в зависимости от текущего режима КИНД, лгика работы может изменяться (вызываются разные функции)
/// содержит свойство режима работы данного CAN - устройства и свойство ID устройства.
/// при изменении режима работы высылает сигнал conditionChanged().
class CanUnit : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool initialised READ getInitialized NOTIFY initializedChanged)

    bool m_initialised;

protected:

    /// определение ссфлки на функцию обработки CAN - сообщения.
    typedef void (CanUnit::*typeProcessCanMessage)(const CanMessage& msg);

    /// конструктор. объявлен как protected для возможности вызова из наследника
    CanUnit(QObject *parent = 0);

    /// массив словарей функций для данного модуля. должен быть заполнен в конструкторе предков
    QMap<quint32, typeProcessCanMessage> processFunctions;

    void checkBoundsAndErrors(MeasureParameter *param, TunningParameter *paramMin,
                              TunningParameter *paramMax, EventIDs::Ids evMin, EventIDs::Ids evMax);

public:

    /// Основной метод, вызывает соответствующую функцию обработки CAN-сообщения.
    /// проверяет текущий режим и ID сообщения. по ним вызывает соответствующую функцию из processFunctions
    /// @param msg ссылка на объект сообщения.
    void canMessageProcessing(const CanMessage& msg);

    /// метод получения множества принимаемых CAN-пакетов для каждого режима
    /// @returns множество идентификаторов
    QSet<quint32> getMessageIDsSet() const;

    bool getInitialized() const
    {
        return m_initialised;
    }

public slots:

    void setInitialized(bool arg)
    {
        if (m_initialised != arg) {
            m_initialised = arg;
            emit initializedChanged(arg);
        }
    }

signals:

//    void signalGetStatus();

    void initializedChanged(bool arg);
};


#endif // CANUNIT_H
