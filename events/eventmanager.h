#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QList>
#include <QMutexLocker>
#include <QVariant>
#include <QThread>
#include <QDebug>

#include "event.h"


extern QMutex guiMutex;

class EventManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant eventListAll        READ getEventListAll       NOTIFY eventListAllChanged       )
    Q_PROPERTY(QVariant eventListUnwatched  READ getEventListUnwatched NOTIFY eventListUnwatchedChanged )
    Q_PROPERTY(QVariant eventListCurrent    READ getEventListCurrent   NOTIFY eventListCurrentChanged   )

public:
    static EventManager* instance();

    QVariant getEventListAll() //const
    {
        QMutexLocker locker(&guiMutex);
        return QVariant::fromValue(m_eventListAll);
    }

    QVariant getEventListUnwatched() //const
    {
        QMutexLocker locker(&guiMutex);
        return QVariant::fromValue(m_eventListUnwatched);
    }

    QVariant getEventListCurrent() //const
    {
        QMutexLocker locker(&guiMutex);
        return QVariant::fromValue(m_eventListCurrent);
    }

signals:

    void eventListAllChanged(QVariant arg);

    void eventListUnwatchedChanged(QVariant arg);

    void eventListCurrentChanged(QVariant arg);

public:
    Q_INVOKABLE void openEvent(/*EventIDs::Ids _id*/int ___id);
    Q_INVOKABLE void closeEvent(EventIDs::Ids _id);
    Q_INVOKABLE void serviceEvent(EventIDs::Ids _id, bool openFlag);
    Q_INVOKABLE void watchAllAlarms();

private:
    QList<QObject*> m_eventListAll         ;
    QList<QObject*> m_eventListUnwatched   ;
    QList<QObject*> m_eventListCurrent     ;
    void insertEventToCurrent(QObject* _ev);
    QObject *findEvent(EventIDs::Ids _id, QList<QObject *> list);

    static EventManager* _self;
    explicit EventManager(QObject *parent = 0);




};

#endif // EVENTMANAGER_H
