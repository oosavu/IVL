#include "eventmanager.h"
#include "QGuiApplication"

EventManager* EventManager::_self = 0;

EventManager::EventManager(QObject *parent) :
    QObject(parent)
{
    //m_eventListAll.append(new Event(EventIDs::AlarmAR1));

    //m_eventList.append(new Event());
    //m_eventList.append(new Event());
}

EventManager *EventManager::instance()
{
    if(_self == 0)
        _self = new EventManager();
    return _self;
}

void EventManager::openEvent(/*EventIDs::Ids _id*/int ___id)
{
    guiMutex.lock();
    EventIDs::Ids _id = (EventIDs::Ids)___id;
    if (EventIDs::getEventType(_id) == EventTypes::Info1)       //запись только в текущие тревоги
    {
        Event* ev = new Event(_id);
        ev->moveToThread(QGuiApplication::instance()->thread());
        insertEventToCurrent(ev);
    }
    else if (EventIDs::getEventType(_id) == EventTypes::Info2)  //просто записали разовое событие в журнал тервог (не закрывая его).
    {
        Event* ev = new Event(_id);
        ev->moveToThread(QGuiApplication::instance()->thread());
        m_eventListAll.append(ev);
    }
    else if(EventIDs::getEventType(_id) == EventTypes::Info3)   //Открыли тервогу в журнале тревог. TODO добавить проверку того, что тревога уже есть открытая.
    {
        Event* ev = new Event(_id);
        ev->moveToThread(QGuiApplication::instance()->thread());
        m_eventListAll.append(ev);
    }
    else{                                                       //полноценная тревога
        if(findEvent(_id,m_eventListCurrent)) return;           //если уже открыта, то выход
        Event* newEvent = new Event(_id);
        newEvent->moveToThread(QGuiApplication::instance()->thread());
        insertEventToCurrent(newEvent);
        m_eventListAll.append(newEvent); //????
        m_eventListUnwatched.append(newEvent);
    }

    guiMutex.unlock();

    emit eventListAllChanged(       QVariant::fromValue(m_eventListAll      ));
    emit eventListUnwatchedChanged( QVariant::fromValue(m_eventListUnwatched));
    emit eventListCurrentChanged(   QVariant::fromValue(m_eventListCurrent  ));
}

void EventManager::closeEvent(EventIDs::Ids _id)
{
    guiMutex.lock();
    Event* delEvent;
    if(EventIDs::getEventType(_id) == EventTypes::Info1)        // только лишь удалить из списка текущих
    {
        delEvent = static_cast<Event*>(findEvent(_id,m_eventListCurrent));
        m_eventListCurrent.removeOne(delEvent);

    }
    else if(EventIDs::getEventType(_id) == EventTypes::Info2)   //ничего не делаем
    {

    }
    else if(EventIDs::getEventType(_id) == EventTypes::Info3)   //закрыть в журнале.
    {
        delEvent = static_cast<Event*>(findEvent(_id,m_eventListAll));
        delEvent->close();
    }
    else                                                        //закрыть, удалить из просмотренных.
    {
       delEvent = static_cast<Event*>(findEvent(_id,m_eventListCurrent));
        if(delEvent == 0)
        {
            qDebug()<<"error: close not created event: " + QString::number(_id);
            return;
        }
        delEvent->close();
        m_eventListCurrent.removeOne(delEvent);
        m_eventListUnwatched.removeOne(delEvent);
    }

    guiMutex.unlock();

    emit eventListAllChanged(       QVariant::fromValue(m_eventListAll      ));
    emit eventListUnwatchedChanged( QVariant::fromValue(m_eventListUnwatched));
    emit eventListCurrentChanged(   QVariant::fromValue(m_eventListCurrent  ));
    //delete delEvent;
}

QObject *EventManager::findEvent(EventIDs::Ids _id, QList<QObject*> list)
{
    foreach (QObject* _ev, list)
    {
        if(static_cast<Event*>(_ev)->getId() == _id) return _ev;
    }
    return 0;
}

void EventManager::serviceEvent(EventIDs::Ids _id, bool openFlag)
{
    if(findEvent(_id,m_eventListCurrent) != 0)  // если тревога открыта
    {                                           // и надо закрыть
        if(!openFlag) closeEvent(_id);
    }
    else                                        // если закрыта
    {                                           // и надо открыть
        if(openFlag) openEvent(_id);
    }
}

void EventManager::watchAllAlarms()
{

}

void EventManager::insertEventToCurrent(QObject *_ev)
{
    Event* __ev = static_cast<Event*>(_ev);
    if(m_eventListCurrent.size() == 0) m_eventListCurrent.append(_ev);
    else
    {
        if(__ev->getId() > static_cast<Event*>(m_eventListCurrent.last())->getId())
            m_eventListCurrent.append(_ev);
        else
        {
            for(int i = 0; i < m_eventListCurrent.size(); i++)
            {
                if(static_cast<Event*>(m_eventListCurrent[i])->getId() > __ev->getId())
                {
                    m_eventListCurrent.insert(i,_ev);
                    return;
                }
            }
        }
    }
}

