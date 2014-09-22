#ifndef EVENT_H
#define EVENT_H
#include <QDateTime>
#include <QDebug>
#include "eventIDs.h"
class Event: public QObject
{
    Q_OBJECT
    Q_PROPERTY(EventIDs::Ids id         READ getId       WRITE setId       NOTIFY idChanged)
    Q_PROPERTY(EventTypes::ETypes type  READ getType     WRITE setType     NOTIFY typeChanged)
    Q_PROPERTY(QDateTime startDT        READ getStartDT  WRITE setStartDT  NOTIFY startDTChanged)
    Q_PROPERTY(QDateTime endDT          READ getEndDT    WRITE setEndDT    NOTIFY endDTChanged)
    Q_PROPERTY(bool isOpened            READ getIsOpened WRITE setIsOpened NOTIFY isOpenedChanged)

public:
    Event(EventIDs::Ids _id, QObject *parent = 0): QObject(parent)
    {
        m_startDT = QDateTime::currentDateTime();
        m_id = _id;
        m_type = EventIDs::getEventType(m_id);
        m_endDT = QDateTime::currentDateTime();
        m_isOpened = true;
    }

    Event(const Event &other){}

    ~Event(){}

    void close()
    {
        m_endDT = QDateTime::currentDateTime();
        setIsOpened(false);
    }

    EventIDs::Ids getId() const
    {
        return m_id;
    }

    EventTypes::ETypes getType() const
    {
        return m_type;
    }

    QDateTime getStartDT() const
    {
        return m_startDT;
    }

    QDateTime getEndDT() const
    {
        return m_endDT;
    }

    bool getIsOpened() const
    {
        return m_isOpened;
    }

public slots:

    void setId(EventIDs::Ids arg)
    {
        if (m_id != arg) {
            m_id = arg;
            emit idChanged(arg);
        }
    }

    void setType(EventTypes::ETypes arg)
    {
        if (m_type != arg) {
            m_type = arg;
            emit typeChanged(arg);
        }
    }

    void setStartDT(QDateTime arg)
    {
        if (m_startDT != arg) {
            m_startDT = arg;
            emit startDTChanged(arg);
        }
    }

    void setEndDT(QDateTime arg)
    {
        if (m_endDT != arg) {
            m_endDT = arg;
            emit endDTChanged(arg);
        }
    }
    void setIsOpened(bool arg)
    {
        if (m_isOpened != arg) {
            m_isOpened = arg;
            emit isOpenedChanged(arg);
        }
    }

signals:


    void idChanged(EventIDs::Ids arg);

    void startDTChanged(QDateTime arg);

    void endDTChanged(QDateTime arg);

    void typeChanged(EventTypes::ETypes arg);

    void isOpenedChanged(bool arg);

private:

    EventIDs::Ids m_id;
    QDateTime m_startDT;
    QDateTime m_endDT;
    bool m_isOpened;
    EventTypes::ETypes m_type;
};

//Q_DECLARE_METATYPE(Event)

#endif // EVENT_H
