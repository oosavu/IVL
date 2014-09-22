#include "tunningparameter.h"

TunningParameter::TunningParameter(qint32 initValue, qint32 initMinValue, qint32 initMaxValue, QString initName, QObject *parent) :
    QObject(parent)
{
    m_errorLevel = TPErrorNo;
    m_currValue = initValue;
    m_trueValue = initValue;
    m_minValue = initMinValue;
    m_maxValue = initMaxValue;
    m_name = initName;
}

void TunningParameter::acceptValue()
{
    m_trueValue = m_currValue;
    emit trueValueChanged(m_trueValue);
}

void TunningParameter::restoreValue()
{
    if(m_currValue != m_trueValue){
        m_currValue = m_trueValue;
        emit currValueChanged(m_currValue);
    }
}

void TunningParameter::printState()
{
    qDebug()<<m_name<<". min:"<<getMinValue()<<" curr:"<<getCurrValue()<<"  max:"<<getMaxValue()<<"  el:"<<getErrorLevel();
}

void TunningParameter::setErrorLevel(TunningParameter::tunningErrorLevels arg)
{
    if (m_errorLevel != arg) {
        m_errorLevel = arg;
        emit errorLevelChanged(arg);
    }
}

void TunningParameter::attemptSetCurrValue(qint32 arg)
{
    if (m_currValue != arg) {
        if(arg <= m_maxValue)
        {
            if(arg >= m_minValue)
            {
                m_currValue = arg;
                emit currValueChanged(m_currValue);
            }
            else if (m_currValue != m_minValue)
            {
                m_currValue = m_minValue;
                emit currValueChanged(m_currValue);
            }
        }
        else if (m_currValue != m_maxValue)
        {
            m_currValue = m_maxValue;
            emit currValueChanged(m_currValue);
        }
    }
}

void TunningParameter::setMinValue(qint32 arg)
{
    if (m_minValue != arg) {
        m_minValue = arg;
        if(m_currValue<m_minValue)
        {
            m_currValue = m_minValue;
            emit currValueChanged(m_currValue);
            m_trueValue = m_currValue;
            emit trueValueChanged(m_trueValue);
        }
        emit minValueChanged(arg);
    }
}

void TunningParameter::setMaxValue(qint32 arg)
{
    if (m_maxValue != arg) {
        m_maxValue = arg;
        if(m_currValue>m_maxValue)
        {
            m_currValue = m_maxValue;
            emit currValueChanged(m_currValue);
            m_trueValue = m_currValue;
            emit trueValueChanged(m_trueValue);
        }
        emit maxValueChanged(arg);
    }
}
