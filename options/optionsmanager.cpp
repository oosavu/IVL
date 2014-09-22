#include "optionsmanager.h"

OptionsManager* OptionsManager::_self = 0;

OptionsManager *OptionsManager::instance()
{
    if(_self == 0)
        _self = new OptionsManager();
    return _self;
}

void OptionsManager::bindContext(QQmlContext *ctx)
{
    ctx->setContextProperty("optCapnoBO"    , optCapnoBO    );
    ctx->setContextProperty("optCapnoPT"    , optCapnoPT    );
    ctx->setContextProperty("optFastOxy"    , optFastOxy    );
    ctx->setContextProperty("optBiSTEP"     , optBiSTEP     );
    ctx->setContextProperty("optNIV"        , optNIV        );
    ctx->setContextProperty("optAPRV"       , optAPRV       );
    ctx->setContextProperty("optNebul"      , optNebul      );
    ctx->setContextProperty("optSpO2"       , optSpO2       );
    ctx->setContextProperty("optLungMassage", optLungMassage);
    ctx->setContextProperty("optCombinedIVL", optCombinedIVL);
    ctx->setContextProperty("optISV"        , optISV        );
    ctx->setContextProperty("optIPPV"       , optIPPV       );
    ctx->setContextProperty("optPreOxy"     , optPreOxy     );
    ctx->setContextProperty("optFickSens"   , optFickSens   );
    ctx->setContextProperty("optVolCapno"   , optVolCapno   );
    ctx->setContextProperty("optNeonat"     , optNeonat     );
    ctx->setContextProperty("optWireless"   , optWireless   );
    ctx->setContextProperty("optSCM"        , optSCM        );
    ctx->setContextProperty("optPCV_VG"     , optPCV_VG     );
    ctx->setContextProperty("optSanat"      , optSanat      );
    ctx->setContextProperty("optAlvRecrMan" , optAlvRecrMan );
    ctx->setContextProperty("optSIMV_DC"    , optSIMV_DC    );
}

OptionsManager::OptionsManager(QObject *parent) :
    QObject(parent)
{
    optCapnoBO     = new TunningParameter(1,0,1);
    optCapnoPT     = new TunningParameter(1,0,1);
    optFastOxy     = new TunningParameter(1,0,1);
    optBiSTEP      = new TunningParameter(1,0,1);
    optNIV         = new TunningParameter(1,0,1);
    optAPRV        = new TunningParameter(1,0,1);
    optNebul       = new TunningParameter(1,0,1);
    optSpO2        = new TunningParameter(1,0,1);
    optLungMassage = new TunningParameter(1,0,1);
    optCombinedIVL = new TunningParameter(1,0,1);
    optISV         = new TunningParameter(1,0,1);
    optIPPV        = new TunningParameter(1,0,1);
    optPreOxy      = new TunningParameter(1,0,1);
    optFickSens    = new TunningParameter(1,0,1);
    optVolCapno    = new TunningParameter(1,0,1);
    optNeonat      = new TunningParameter(1,0,1);
    optWireless    = new TunningParameter(1,0,1);
    optSCM         = new TunningParameter(1,0,1);
    optPCV_VG      = new TunningParameter(1,0,1);
    optSanat       = new TunningParameter(1,0,1);
    optAlvRecrMan  = new TunningParameter(1,0,1);
    optSIMV_DC     = new TunningParameter(1,0,1);

}
