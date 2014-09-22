#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H

#include <QtQuick/QQuickFramebufferObject>
#include <QTimer>
#include "graphrenderer.h"

class GraphObject : public QQuickFramebufferObject
{
    Q_OBJECT

    QTimer updateTimer;

public:
    explicit GraphObject(QQuickItem *parent = 0);
    Renderer *createRenderer() const;

signals:

public slots:
    void updateTimerEvent();
};

#endif // GRAPHOBJECT_H
