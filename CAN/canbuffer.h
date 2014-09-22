#ifndef CANBUFFER_H
#define CANBUFFER_H

#include <QObject>
#include "canmessage.h"

class CanBuffer : public QObject
{
Q_OBJECT
public:
    explicit CanBuffer(int _size = 100, QObject *parent=0);
    CanMessage pop();

    bool push(const CanMessage &pkg);
    QQueue<CanMessage> msgQueue;
private:
    QSemaphore popSem,pushSem;
    QMutex mutex;

};

#endif // CANBUFFER_H
