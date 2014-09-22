#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QOpenGLContext>
#include <QQuickItem>
#include "graphnode.h"
#include "renderer.h"
#include "directGraphics/lfbctrl.h"

class GraphItem : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qint32 velosity READ getVelosity WRITE setvelosity NOTIFY velosityChanged)

    QTimer timer;
    int fpsCount;

    qint32 m_velosity;

    LFBINFO *lbfInfo;

public:
    explicit GraphItem(QQuickItem *parent = 0);


qint32 getVelosity() const
{
    return m_velosity;
}

public slots:
void setvelosity(qint32 arg)
{
    if (m_velosity != arg) {
        m_velosity = arg;
        emit velosityChanged(arg);
    }
}

signals:
void velosityChanged(qint32 arg);

private slots:
    void timerSlot();


protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data);
    
};

#endif // GRAPHITEM_H
