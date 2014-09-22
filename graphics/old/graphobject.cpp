#include "graphobject.h"

GraphObject::GraphObject(QQuickItem *parent):
    QQuickFramebufferObject(parent)
{
//    setFlag(QQuickItem::ItemClipsChildrenToShape,true);
//    setClip(true);

    updateTimer.setSingleShot(false);
    updateTimer.setInterval(16);
    QObject::connect(&updateTimer,SIGNAL(timeout()),this,SLOT(updateTimerEvent()));
    updateTimer.start();

}

QQuickFramebufferObject::Renderer *GraphObject::createRenderer() const
{
    return new GraphRenderer();
}



void GraphObject::updateTimerEvent()
{
    update();
}
