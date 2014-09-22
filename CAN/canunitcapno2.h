#ifndef CANUNITCAPNO2_H
#define CANUNITCAPNO2_H

#include "canunit.h"

class CanUnitCapno2 : public CanUnit
{
private:
     void process_ID_STATUS_CAPNO2(const CanMessage &msg);
     void process_ID_WAVE_CAPNO2(const CanMessage &msg);
     void process_ID_DATA_CAPNO2(const CanMessage &msg);
     void process_ID_VERSION_CAPNO2(const CanMessage &msg);

    /// указатель на объект
    static CanUnitCapno2* _self;
protected:
    CanUnitCapno2( QObject* parent = 0);
public:
    static CanUnitCapno2* instance();


};

#endif // CANUNITCAPNO2_H
