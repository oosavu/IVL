#ifndef OPTIONSMANAGER_H
#define OPTIONSMANAGER_H

#include <QObject>
#include <QQmlContext>
#include "../types/parametersTypes.h"

class OptionsManager : public QObject
{
    Q_OBJECT

public:
    static OptionsManager* instance();

    void bindContext(QQmlContext* ctx);

    TunningParameter* optCapnoBO    ;
    TunningParameter* optCapnoPT    ;
    TunningParameter* optFastOxy    ;
    TunningParameter* optBiSTEP     ;
    TunningParameter* optNIV        ;
    TunningParameter* optAPRV       ;
    TunningParameter* optNebul      ;
    TunningParameter* optSpO2       ;
    TunningParameter* optLungMassage;
    TunningParameter* optCombinedIVL;
    TunningParameter* optISV        ;
    TunningParameter* optIPPV       ;
    TunningParameter* optPreOxy     ;
    TunningParameter* optFickSens   ;
    TunningParameter* optVolCapno   ;
    TunningParameter* optNeonat     ;
    TunningParameter* optWireless   ;
    TunningParameter* optSCM        ;
    TunningParameter* optPCV_VG     ;
    TunningParameter* optSanat      ;
    TunningParameter* optAlvRecrMan ;
    TunningParameter* optSIMV_DC    ;

private:
    static OptionsManager* _self;
    explicit OptionsManager(QObject *parent = 0);



signals:

public slots:

};

#endif // OPTIONSMANAGER_H
