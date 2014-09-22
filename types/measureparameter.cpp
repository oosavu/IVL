#include "measureparameter.h"


MeasureParameter::MeasureParameter(qint32 startValue, bool startAvilability, QObject *parent):
    QObject(parent)
{
    m_value = startValue;
    m_avilability = startAvilability;
    m_errorLevel = MErrorNo;
}

void MeasureParameter::setErrorLevel(MeasureParameter::measureErrorLevels arg)
{
    QMutexLocker locker(&guiMutex);
    if (m_errorLevel != arg) {
        m_errorLevel = arg;
        emit errorLevelChanged(arg);
    }
}

void MeasureParameter::setValue(qint32 arg)
{
    QMutexLocker locker(&guiMutex);
    if (m_value != arg) {
        m_value = arg;
        emit valueChanged(arg);
    }
}

void MeasureParameter::setAvilability(bool arg)
{
    QMutexLocker locker(&guiMutex);
    if (m_avilability != arg) {
        m_avilability = arg;
        emit avilabilityChanged(arg);
    }
}


