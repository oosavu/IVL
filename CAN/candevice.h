#ifndef CANDEVICE_H
#define CANDEVICE_H

#include <QObject>
#include <QDebug>

#include "canunit.h"
#include "canbuffer.h"


/**
 * Абстрактный класс, определяющий CAN-интерфейс
 * Определяет интерфейс взаимодействия с CAN-устройством. Является "классом-одиночкой" (singleton).
 * Для использования необходимо унаследовать его и переопределить чисто виртуаьные методы.
 * Реализован кольцевой буфер как задел на будующее (если обработка сообщения должна быть отложена)
 */

class CanDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(canDeviceModes canDeviceMode READ getCanDeviceMode WRITE setCanDeviceMode NOTIFY canDeviceModeChanged)
    Q_ENUMS(canDeviceModes)
public:
    enum canDeviceModes{
        CANDEVICE_MODE_UNKNOWN  = 0, /*неизвестный режим*/
        CANDEVICE_MODE_WORK     = 1, /*рабочий режим*/
        CANDEVICE_MODE_ERROR    = 2  /*режим ошибки*/
    };




    /// Функция начала инициализации. олжна быть переопределена в потомках.
    virtual void startInit() = 0;


    /// метод отправки CAN-сообщения. должен быть определён в потомке
    /// @param msg - отправляемое сообщение.
    /// @returns true в случае удачной отправки, false иначе
    virtual void sendMessage(const CanMessage& msg) = 0;

    /// метод регистрации устройства CAN.
    /// анализирует словарь принимаемых сообщений устройства и добавляет в свой словарь.
    /// @param unit CAN-устройство для регистрации.
    /// @returns true в случае успешного добавления,
    /// @returns false в случае конфликта идентификаторов или пустого списка в unit
    bool registerCanUnit(CanUnit* unit);

    /// метод отмены регистрации устройства CAN.
    /// анализирует, есть ли данный CanUnit в списке. в случае если есть - удаляет его
    /// @returns true в случае успешного удаления,
    /// @returns false - если CanUnit не обнаружен в списке.
    bool unRegisterCanUnit(CanUnit* unit);

    /// метод получения текущего списка подключенных CAN - устройств
    /// @returns список указателей на обрабатываемые CAN - устройства.
    QList<CanUnit*> getCanUnitList() {return canUnitsMap.values().toSet().toList();}

    /// метод получения ссылки на объект.
    /// @returns указатель на объект
    static CanDevice* instance();

    canDeviceModes getCanDeviceMode() const
    {
        return m_canDeviceMode;
    }
protected:

    /// указатель на себя.
    /// необходимо для реализации паттерна singelton
    static CanDevice* _self;

    /// конструктор. объявлен как protected для возможности вызова из наследника
    CanDevice(QObject *parent = 0);


    /// последнее принятое сообщение (копируется из буфера входящих и отсюда обрабатывается)
    CanMessage lastMsg;
private:

    /// словарь, для определения по индексу сообщения класса приёмника.
    QMap<quint32,CanUnit*> canUnitsMap;

    canDeviceModes m_canDeviceMode;



public slots:
    void setCanDeviceMode(canDeviceModes arg)
    {
        if (m_canDeviceMode != arg) {
            m_canDeviceMode = arg;
            emit canDeviceModeChanged(arg);
        }
    }

protected slots:

    /// слот обработки пришедшего сообщения.
    /// сигнал, на который необходимо подписать данный слот, зависит от реализации.
    /// инициализирует элемент в messageBuffer,
    /// определяет объект, которому предназначен данный пакет и вызывает у него функцию обработки сообщения.
    void receiveMessage(const CanMessage& msg);

signals:
    void getError();
    void canDeviceModeChanged(CanDevice::canDeviceModes arg);
};



#endif // CANDEVICE_H
