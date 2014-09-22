#include "canbuffer.h"

CanBuffer::CanBuffer(int _size, QObject *parent):QObject(parent)
{
    pushSem.release(_size);
}

CanMessage CanBuffer::pop()
{
    popSem.acquire();
    mutex.lock();
    CanMessage canPkg = msgQueue.dequeue();
    mutex.unlock();
    pushSem.release();
    return canPkg;
}


bool CanBuffer::push(const CanMessage &pkg)
{
    bool rc=false;

    if(pushSem.available() > 0)
    {
        pushSem.acquire();
        mutex.lock();
        msgQueue.enqueue(pkg);
        mutex.unlock();
        popSem.release();
        rc=true;
    }
    else{
        qDebug()<<"buffer is full!";
    }
    return(rc);
}
