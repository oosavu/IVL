#ifndef GRAPHICLOOP_H
#define GRAPHICLOOP_H
#include "graphicobject.h"

class GraphicLoop : public GraphicObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 maxPositiveValX READ getMaxPositiveValX WRITE setMaxPositiveValX NOTIFY maxPositiveValXChanged)
    Q_PROPERTY(qint32 maxNegativeValX READ getMaxNegativeValX WRITE setMaxNegativeValX NOTIFY maxNegativeValXChanged)
    Q_PROPERTY(qint32 maxPositiveValY READ getMaxPositiveValY WRITE setMaxPositiveValY NOTIFY maxPositiveValYChanged)
    Q_PROPERTY(qint32 maxNegativeValY READ getMaxNegativeValY WRITE setMaxNegativeValY NOTIFY maxNegativeValYChanged)


public:
    GraphicLoop();

    QList<qint32> maxLimitsX;
    QList<qint32> maxLimitsY;
    qint32 prevXpix;
    qint32 prevYpix;
    qint32 nextCircleMinX;
    qint32 nextCircleMaxX;
    qint32 nextCircleMinY;
    qint32 nextCircleMaxY;

    qint32 getMaxPositiveValX() const
    {
        return m_maxPositiveValX;
    }
    qint32 getMaxNegativeValX() const
    {
        return m_maxNegativeValX;
    }
    qint32 getMaxPositiveValY() const
    {
        return m_maxPositiveValY;
    }
    qint32 getMaxNegativeValY() const
    {
        return m_maxNegativeValY;
    }

public slots:
    void setMaxPositiveValX(qint32 arg)
    {
        if (m_maxPositiveValX != arg) {
            m_maxPositiveValX = arg;
            emit maxPositiveValXChanged(arg);
        }
    }
    void setMaxNegativeValX(qint32 arg)
    {
        if (m_maxNegativeValX != arg) {
            m_maxNegativeValX = arg;
            emit maxNegativeValXChanged(arg);
        }
    }

    void setMaxPositiveValY(qint32 arg)
    {
        if (m_maxPositiveValY != arg) {
            m_maxPositiveValY = arg;
            emit maxPositiveValYChanged(arg);
        }
    }

    void setMaxNegativeValY(qint32 arg)
    {
        if (m_maxNegativeValY != arg) {
            m_maxNegativeValY = arg;
            emit maxNegativeValYChanged(arg);
        }
    }

signals:
    void maxPositiveValXChanged(qint32 arg);
    void maxNegativeValXChanged(qint32 arg);
    void maxPositiveValYChanged(qint32 arg);
    void maxNegativeValYChanged(qint32 arg);

private:
    qint32 m_maxPositiveValX;
    qint32 m_maxNegativeValX;
    qint32 m_maxPositiveValY;
    qint32 m_maxNegativeValY;
};

#endif // GRAPHICLOOP_H
