#include "canunit.h"

CanUnit::CanUnit(QObject *parent) :
    QObject(parent)
{
    //qDebug() << "CanUnit constructor";
}

void CanUnit::checkBoundsAndErrors(MeasureParameter *param, TunningParameter *paramMin,
                                   TunningParameter *paramMax, EventIDs::Ids evMin, EventIDs::Ids evMax)
{
    paramMax->setMinValue(paramMin->getCurrValue());
    paramMin->setMaxValue(paramMax->getCurrValue());
    EventManager::instance()->serviceEvent(evMin, (param->getValue() < paramMin->getTrueValue()) && param->getAvilability());
    EventManager::instance()->serviceEvent(evMax, (param->getValue() > paramMax->getTrueValue()) && param->getAvilability());
}

void CanUnit::canMessageProcessing(const CanMessage &msg)
{
    if(processFunctions.contains(msg.id))
    {
       // guiMutex.lock();
        //QMutexLocker(&guiMutex);
        (this->*processFunctions[msg.id])(msg); //TODO это временно
        //guiMutex.unlock();
    }
}

QSet<quint32> CanUnit::getMessageIDsSet() const
{
    return processFunctions.keys().toSet();
}
