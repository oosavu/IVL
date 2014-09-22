#ifndef EMULATIONCANDEVICE_H
#define EMULATIONCANDEVICE_H

#include <QDebug>
#include "candevice.h"

class EmulationCanDevice : public CanDevice
{
    Q_OBJECT
protected:
    EmulationCanDevice(QObject *parent = 0);
public:
    /// определение метода получения ссылки на объект
    static CanDevice* instance();
    void sendMessage(const CanMessage& msg);
    void startInit();


};

#endif // EMULATIONCANDEVICE_H
