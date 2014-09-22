#include "associatedparameter.h"


AssociatedParameter::AssociatedParameter(qint32 initValue, qint32 initMinValue, qint32 initMaxValue,bool initAvilability, QString initName, QObject *parent):
    QObject(parent)
{
    m_errorLevel = APErrorNo    ;
    m_value      = initValue    ;
    m_minValue   = initMinValue ;
    m_maxValue   = initMaxValue ;
    m_name       = initName     ;
    m_avilability = initAvilability;
}

void AssociatedParameter::printState()
{
    qDebug()<<m_name<<". min:"<<getMinValue()<<" curr:"<<getValue()<<"  max:"<<getMaxValue()<<"  el:"<<getErrorLevel()<<"  av:"<<getAvilability();
}

void AssociatedParameter::checkErrorLevel()
{
    if(getAvilability() == false)
    {
        setErrorLevel(APErrorNo);
    }
    else if(getValue() < getMinValue() || getValue() > getMaxValue())
    {
        setErrorLevel(APError2);
    }
    else
    {
        setErrorLevel(APErrorNo);
    }

}

void AssociatedParameter::setErrorLevel(AssociatedParameter::associatedErrorLevels arg)
{
    if (m_errorLevel != arg) {
        m_errorLevel = arg;
        emit errorLevelChanged(arg);
    }
}

void AssociatedParameter::setAvilability(bool arg)
{
    if (m_avilability != arg) {
        m_avilability = arg;
        emit avilabilityChanged(arg);
    }
    checkErrorLevel();
}

void AssociatedParameter::setValue(qint32 arg)
{
    if (m_value != arg) {
        m_value = arg;
        emit valueChanged(arg);
    }
    checkErrorLevel();
}

void AssociatedParameter::setMinValue(qint32 arg)
{
    if (m_minValue != arg) {
        m_minValue = arg;
        emit minValueChanged(arg);
    }
    checkErrorLevel();
}

void AssociatedParameter::setMaxValue(qint32 arg)
{
    if (m_maxValue != arg) {
        m_maxValue = arg;
        emit maxValueChanged(arg);
    }
    checkErrorLevel();
}

