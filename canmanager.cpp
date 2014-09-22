#include "canmanager.h"

CanManager* CanManager::_self = 0;

CanManager::CanManager(QObject *parent) :
    QObject(parent)
{
    //qDebug()<< "CanManager: " << canManagerThread;
    canManagerThread.setObjectName("canManager");
    timer50Hz = new QTimer(0);
    timer50Hz->moveToThread(&canManagerThread);
    timer50Hz->setInterval(20);
    ticks = 50;
    connect(timer50Hz, SIGNAL(timeout()),SLOT(slot50Hz()), Qt::DirectConnection);
    canManagerThread.start();

}

void CanManager::slot50Hz()
{
    ticks++;
    if(ticks >= 50)
    {
        ticks = 0;
        slot1hz();
    }
}

void CanManager::slot1hz()
{

    CanMessage msgSynchro(canId::bu::ID_SYNHRO,6);
    setSystemDateTime(QDateTime::currentDateTime());
    msgSynchro.setUInt8(systemDateTime().date().year() - 2000,   0);
    msgSynchro.setUInt8(systemDateTime().date().month(),         1);
    msgSynchro.setUInt8(systemDateTime().date().day(),           2);
    msgSynchro.setUInt8(systemDateTime().time().hour(),          3);
    msgSynchro.setUInt8(systemDateTime().time().minute(),        4);
    msgSynchro.setUInt8(systemDateTime().time().second(),        5);
    //QDateTime ddt = QDateTime::currentDateTime();
//    msgSynchro.setUInt8(ddt.date().year() - 2000,   0);
//    msgSynchro.setUInt8(ddt.date().month(),         1);
//    msgSynchro.setUInt8(ddt.date().day(),           2);
//    msgSynchro.setUInt8(ddt.time().hour(),          3);
//    msgSynchro.setUInt8(ddt.time().minute(),        4);
//    msgSynchro.setUInt8(ddt.time().second(),        5);
    CanDevice::instance()->sendMessage(msgSynchro);


    if(RegimeManager::instance()->getRegimeManagerMode() == RegimeManager::REGIMEMANAGER_MODE_COMMON_INIT)
    {


        if(!CanUnitKIVL::instance()->getInitialized())
        {

            CanMessage msg_KIVL_WAIT(canId::kivl::ID_MODE_CIVL,1);
            msg_KIVL_WAIT.setUInt8(0,0);
            CanDevice::instance()->sendMessage(msg_KIVL_WAIT);
        }
        if(!CanUnitPower::instance()->getInitialized())
        {
            CanMessage msg_POWER_WAIT(canId::power2::ID_MODE_PWR,1);
            msg_POWER_WAIT.setBit(0,0,0);
            CanDevice::instance()->sendMessage(msg_POWER_WAIT);
        }
        if(!CanUnitMix::instance()->getInitialized())
        {
            CanMessage msg_MIX_WAIT(canId::mix::ID_MODE_MIX,1);
            msg_MIX_WAIT.setUInt8(0,0);
            CanDevice::instance()->sendMessage(msg_MIX_WAIT);
        }

        if(!CanUnitCapno1::instance()->getInitialized())
        {
            CanMessage msg_CAPNO1_WAIT(canId::capno1::ID_MODE_CAPNO1,1);
            msg_CAPNO1_WAIT.setUInt8(0,0);
            CanDevice::instance()->sendMessage(msg_CAPNO1_WAIT);
        }


        if(timeLeft.elapsed()>7000)
        {
            qDebug() << "INITIALIZATION FAILED! GOTO BLOCKWORK";
            RegimeManager::instance()->setRegimeManagerMode(RegimeManager::REGIMEMANAGER_MODE_BLOCKWORK);
        }
        else if(CanUnitPower::instance()->getInitialized() &&
           CanUnitMix::instance()->getInitialized() &&
           CanUnitKIVL::instance()->getInitialized())
        {
            qDebug() << "INITIALIZATION OK!";
           // qDebug()<< "slot1hz: " << QThread::currentThreadId();
            RegimeManager::instance()->setRegimeManagerMode(RegimeManager::REGIMEMANAGER_MODE_WORK);
        }
    }

}

CanManager *CanManager::instance()
{
    if(_self == 0) _self = new CanManager();
    return _self;
}

void CanManager::startInitCanUnits()
{
    CanUnitMix::instance()->setInitialized(false);
    CanUnitPower::instance()->setInitialized(false);
    CanUnitKIVL::instance()->setInitialized(false);
    timeLeft.start();
//timer50Hz->start();
    QMetaObject::invokeMethod(timer50Hz, "start", Qt::QueuedConnection);
}


