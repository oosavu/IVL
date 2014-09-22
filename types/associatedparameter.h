#ifndef ASSOCIATEDPARAMETER_H
#define ASSOCIATEDPARAMETER_H

#include <QObject>
#include <QDebug>

class AssociatedParameter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(associatedErrorLevels errorLevel READ getErrorLevel WRITE setErrorLevel NOTIFY errorLevelChanged)
    Q_PROPERTY(bool avilability READ getAvilability WRITE setAvilability NOTIFY avilabilityChanged)
    Q_PROPERTY(qint32 value     READ getValue       WRITE setValue       NOTIFY valueChanged)
    Q_PROPERTY(qint32 minValue  READ getMinValue    WRITE setMinValue    NOTIFY minValueChanged)
    Q_PROPERTY(qint32 maxValue  READ getMaxValue    WRITE setMaxValue    NOTIFY maxValueChanged)
    Q_ENUMS(associatedErrorLevels)
public:
    /// перечисление уровней ошибки
    enum associatedErrorLevels{
        APErrorNo = 0,    ///< нет ошибки
        APError1,         ///< ошибка 1
        APError2          ///< ошибка 2
    };
    explicit AssociatedParameter(qint32 initValue = 10,qint32 initMinValue = 0,
                                 qint32 initMaxValue = 20,bool initAvilability = true,QString initName = "noname",QObject *parent = 0);

    associatedErrorLevels getErrorLevel() const { return m_errorLevel;  }
    bool getAvilability()                 const { return m_avilability; }
    qint32 getValue()                     const { return m_value;       }
    qint32 getMinValue()                  const { return m_minValue;    }
    qint32 getMaxValue()                  const { return m_maxValue;    }

    void printState();

private:
    associatedErrorLevels m_errorLevel;
    bool m_avilability;
    qint32 m_value;
    qint32 m_minValue;
    qint32 m_maxValue;
    QString m_name;

    void checkErrorLevel();

signals:

    void errorLevelChanged(associatedErrorLevels arg);
    void avilabilityChanged(bool arg);
    void valueChanged(qint32 arg);
    void minValueChanged(qint32 arg);
    void maxValueChanged(qint32 arg);

public slots:

    void setErrorLevel(associatedErrorLevels arg);
    void setAvilability(bool arg);
    void setValue(qint32 arg);
    void setMinValue(qint32 arg);
    void setMaxValue(qint32 arg);
};

#endif // ASSOCIATEDPARAMETER_H
