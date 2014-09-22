#include <QtGui/QGuiApplication>
#include <QDebug>
#include <QtQml>
#include "qtquick2applicationviewer.h"

//#include "CAN/socketcandevice.h"
#include "CAN/emulationcandevice.h"

//#include "alarms/alarmmanager.h"
#include "options/optionsmanager.h"
#include "events/eventmanager.h"
#include "ventmode/ventmodemanager.h"
#include "i18n/translationmanager.h"
#include "keyboardSimulator/keyboardsimulator.h"
#include "canmanager.h"
#include "regimemanager.h"
#include "graphics/graphicmanager.h"

QMutex guiMutex;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //Создание структуры объектов

    //CanDevice* canDevice = SocketCanDevice::instance();
    CanDevice* canDevice = EmulationCanDevice::instance();
    canDevice->registerCanUnit(CanUnitCapno1::instance());
    canDevice->registerCanUnit(CanUnitCapno2::instance());
    canDevice->registerCanUnit(CanUnitPower::instance());
    canDevice->registerCanUnit(CanUnitSPO::instance());
    canDevice->registerCanUnit(CanUnitKIVL::instance());
    canDevice->registerCanUnit(CanUnitMix::instance());

    RegimeManager::instance();
    CanManager::instance();
    EventManager::instance();
    GraphicManager::instance();
    OptionsManager::instance();

    VentModeManager::instance();
    TranslationManager::instance();
    QObject::connect(canDevice,SIGNAL(canDeviceModeChanged(CanDevice::canDeviceModes)),
                     RegimeManager::instance(), SLOT(slotCanDeviceMode(CanDevice::canDeviceModes)));

    //Регистрация перечислений для QML
    qmlRegisterUncreatableType<CanUnitMix>("CppImport", 1, 0, "CanUnitMix", "NOT MAY CREATE");
    qmlRegisterUncreatableType<CanUnitKIVL>("CppImport", 1, 0, "CanUnitKIVL", "NOT MAY CREATE");
    qmlRegisterUncreatableType<MeasureParameter>("CppImport", 1, 0, "MeasureParameter", "NOT MAY CREATE");
    qmlRegisterUncreatableType<TunningParameter>("CppImport", 1, 0, "TunningParameter", "NOT MAY CREATE");
    qmlRegisterUncreatableType<AssociatedParameter>("CppImport", 1, 0, "AssociatedParameter", "NOT MAY CREATE");
    qmlRegisterUncreatableType<EventIDs>("CppImport", 1, 0, "EventIDs", "NOT MAY CREATE");
    qmlRegisterUncreatableType<EventTypes>("CppImport", 1, 0, "EventTypes", "NOT MAY CREATE");
    qmlRegisterUncreatableType<CanUnitPower>("CppImport", 1, 0, "CanUnitPower", "NOT MAY CREATE");
    qmlRegisterUncreatableType<CanUnit>("CppImport", 1, 0, "CanUnit", "NOT MAY CREATE");
    qmlRegisterUncreatableType<RegimeManager>("CppImport", 1, 0, "RegimeManager", "NOT MAY CREATE");
    qmlRegisterUncreatableType<VentModeManager>("CppImport", 1, 0, "VentModeManager", "NOT MAY CREATE");

    //Создание представления и контекста QML
    QtQuick2ApplicationViewer viewer;
    QQmlContext* ctx = viewer.rootContext();


    //регистрация объектов для QML
    ctx->setContextProperty("keySim",         new KeyboardSimulator());
    ctx->setContextProperty("tm",             TranslationManager::instance());
    ctx->setContextProperty("regimeManager",  RegimeManager::instance());
    ctx->setContextProperty("canUnitMix",     CanUnitMix::instance());
    ctx->setContextProperty("canUnitKIVL",    CanUnitKIVL::instance());
    ctx->setContextProperty("canUnitPower",   CanUnitPower::instance());    
    ctx->setContextProperty("eventManager",   EventManager::instance());
    ctx->setContextProperty("ventModeManager",VentModeManager::instance());
    ctx->setContextProperty("graphicManager", GraphicManager::instance());
    ctx->setContextProperty("canManager",     CanManager::instance());
    CanUnitKIVL::instance()->bindContext(ctx);
    CanUnitCapno1::instance()->bindContext(ctx);
    VentModeManager::instance()->bindContext(ctx);
    GraphicManager::instance()->bindContext(ctx);
    OptionsManager::instance()->bindContext(ctx);


    viewer.setMainQmlFile(QStringLiteral("qml/BaseIVL2/main.qml"));
    viewer.setWidth(1024);
    viewer.setHeight(768);
    viewer.setColor(QColor::fromRgb(0,0,0,0)/*Qt::transparent*/);
    viewer.showExpanded();

    canDevice->startInit();
    return app.exec();
}
