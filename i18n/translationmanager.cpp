#include "translationmanager.h"
#include <QDebug>

TranslationManager* TranslationManager::_self = 0;

TranslationManager::TranslationManager(QObject *parent) :
    QObject(parent)
{

    translatorEN = new QTranslator(this);
    translatorEN->load(":/en.qm"); //TODO относительные пути
    translatorRU = new QTranslator(this);
    translatorRU->load(":/ru.qm");
    setLanguage(Rus);

}

TranslationManager *TranslationManager::instance()
{
    if (_self == 0)
        _self = new TranslationManager();
    return _self;
}

void TranslationManager::setLanguage(TranslationManager::languages arg)
{
    if(arg == Rus)
    {
        QGuiApplication::instance()->installTranslator(translatorRU);
    }
    else if(arg == Eng)
    {
        QGuiApplication::instance()->installTranslator(translatorEN);
    }
    emit languageChanged();
}
