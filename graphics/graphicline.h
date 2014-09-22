#ifndef GRAPHICLINE_H
#define GRAPHICLINE_H
#include "graphicobject.h"
class GraphicLine : public GraphicObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 maxPositiveVal READ getMaxPositiveVal WRITE setMaxPositiveVal NOTIFY maxPositiveValChanged)
    Q_PROPERTY(qint32 maxNegativeVal READ getMaxNegativeVal WRITE setMaxNegativeVal NOTIFY maxNegativeValChanged)

public:
    GraphicLine();

    QList<qint32> maxLimits;
    qint32 prevMin;
    qint32 prevMax;
    qint32 nextCircleMin;
    qint32 nextCircleMax;

    qint32 getMaxPositiveVal() const
    {
        return m_maxPositiveVal;
    }

    qint32 getMaxNegativeVal() const
    {
        return m_maxNegativeVal;
    }

public slots:

    void setMaxPositiveVal(qint32 arg)
    {
        //qDebug()<<"smp "<<arg;
        if (m_maxPositiveVal != arg) {
            if(m_maxNegativeVal >= m_maxPositiveVal)
            {
                m_maxNegativeVal = -10;
                emit maxNegativeValChanged(-10);
            }
            m_maxPositiveVal = arg;
            emit maxPositiveValChanged(arg);
        }
    }

    void setMaxNegativeVal(qint32 arg)
    {
        if (m_maxNegativeVal != arg) {
            if(m_maxNegativeVal >= m_maxPositiveVal)
            {
                m_maxPositiveVal = 10;
                emit maxPositiveValChanged(10);
            }
            m_maxNegativeVal = arg;

            emit maxNegativeValChanged(arg);
        }
    }

signals:
    void NullPositionChanged(qint32 arg);

    void maxPositiveValChanged(qint32 arg);

    void maxNegativeValChanged(qint32 arg);

private:
    qint32 m_maxPositiveVal;
    qint32 m_maxNegativeVal;
};

#endif // GRAPHICLINE_H
