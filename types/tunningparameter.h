#ifndef TUNNINGPARAMETER_H
#define TUNNINGPARAMETER_H

#include <QObject>
#include <QDebug>

class TunningParameter : public QObject
{
    Q_OBJECT
    /// свойство уровня ошибки
    Q_PROPERTY(tunningErrorLevels errorLevel READ getErrorLevel WRITE setErrorLevel NOTIFY errorLevelChanged)
    /// свойство текущего редактируемого значения
    Q_PROPERTY(qint32 currValue READ getCurrValue WRITE attemptSetCurrValue NOTIFY currValueChanged)
    /// свойство "истинного" значения
    Q_PROPERTY(qint32 trueValue READ getTrueValue NOTIFY trueValueChanged)
    /// свойство минимального значения
    Q_PROPERTY(qint32 minValue READ getMinValue WRITE setMinValue NOTIFY minValueChanged)
    /// свойство максимального значения
    Q_PROPERTY(qint32 maxValue READ getMaxValue WRITE setMaxValue NOTIFY maxValueChanged)

    Q_ENUMS(tunningErrorLevels)
public:

    /// перечисление уровней ошибки
    enum tunningErrorLevels{
        TPErrorNo = 0,    ///< нет ошибки
        TPError1,         ///< ошибка 1
        TPError2          ///< ошибка 2
    };
    explicit TunningParameter(qint32 initValue = 10,qint32 initMinValue = 0,
                              qint32 initMaxValue = 20,QString initName = "noname",QObject *parent = 0);

    Q_INVOKABLE void acceptValue();
    Q_INVOKABLE void restoreValue();
    tunningErrorLevels getErrorLevel() const    {        return m_errorLevel;    }
    qint32 getCurrValue() const                 {        return m_currValue ;    }
    qint32 getTrueValue() const                 {        return m_trueValue ;    }
    qint32 getMinValue() const                  {        return m_minValue  ;    }
    qint32 getMaxValue() const                  {        return m_maxValue  ;    }

    void printState();


private:
    tunningErrorLevels m_errorLevel;
    qint32 m_currValue;
    qint32 m_trueValue;
    qint32 m_minValue;
    qint32 m_maxValue;
    QString m_name;

signals:

    void errorLevelChanged(tunningErrorLevels arg);

    void currValueChanged(qint32 arg);

    void trueValueChanged(qint32 arg);

    void minValueChanged(qint32 arg);

    void maxValueChanged(qint32 arg);

public slots:

    void setErrorLevel(tunningErrorLevels arg);
    void attemptSetCurrValue(qint32 arg);
    void setMinValue(qint32 arg);
    void setMaxValue(qint32 arg);

};

#endif // TUNNINGPARAMETER_H
