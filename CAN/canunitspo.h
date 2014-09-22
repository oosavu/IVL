#ifndef CANUNITSPO_H
#define CANUNITSPO_H

#include "canunit.h"

class CanUnitSPO : public CanUnit
{
private:
    void process1(const CanMessage &msg);
    /// указатель на объект
    static CanUnitSPO* _self;
protected:
    CanUnitSPO( QObject* parent = 0);
public:
    static CanUnitSPO* instance();


};

#endif // CANUNITSPO_H
