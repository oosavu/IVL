#ifndef MEASUREPARAMETER_H
#define MEASUREPARAMETER_H

#include <QObject>
#include <QDebug>
#include <QMutexLocker>

extern QMutex guiMutex;

class MeasureParameter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(measureErrorLevels errorLevel READ getErrorLevel WRITE setErrorLevel NOTIFY errorLevelChanged)
    Q_PROPERTY(qint32 value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(bool avilability READ getAvilability WRITE setAvilability NOTIFY avilabilityChanged)
    Q_ENUMS(measureErrorLevels)

public:
    enum measureErrorLevels{
        MErrorNo = 0,    ///< нет ошибки
        MError1,         ///< ошибка 1
        MError2          ///< ошибка 2
    };

    explicit MeasureParameter(qint32 startValue = 23,bool startAvilability = true,QObject* parent = 0);

    measureErrorLevels getErrorLevel()  const    {   QMutexLocker locker(&guiMutex);     return m_errorLevel;      }
    qint32 getValue()                   const    {   QMutexLocker locker(&guiMutex);     return m_value;           }
    bool getAvilability()               const    {   QMutexLocker locker(&guiMutex);     return m_avilability;     }

private:
    measureErrorLevels m_errorLevel;
    qint32 m_value;
    bool m_avilability;

signals:
    void errorLevelChanged(measureErrorLevels arg);
    void valueChanged(qint32 arg);
    void avilabilityChanged(bool arg);

public slots:

void setErrorLevel(measureErrorLevels arg);
void setValue(qint32 arg);
void setAvilability(bool arg);
};

#endif // MEASUREPARAMETER_H
