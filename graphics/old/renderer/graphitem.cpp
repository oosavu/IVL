#include "graphitem.h"
#include <QSGFlatColorMaterial>
#include <QSGSimpleRectNode>

#define OPENGL_RENDERING

GraphItem::GraphItem(QQuickItem *parent) :
    QQuickItem(parent)
{
    fpsCount = 0;
    setFlag(ItemHasContents, true);
    setSmooth(false);
    timer.setInterval(1000);
    timer.setSingleShot(false);

#ifdef OPENGL_RENDERING
    connect(&timer, SIGNAL(timeout()),this, SLOT(timerSlot()));
    timer.start();
#else
    lfbInit();
    lfbFillAll(0);
#endif
    m_velosity = 40;

}

void GraphItem::timerSlot()
{
    qDebug()<<"item fps count: "<<QString::number(fpsCount);
    fpsCount=0;
    //this->update();
}

QSGNode *GraphItem::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *data)
{

#ifndef OPENGL_RENDERING
    testDraw(QColor::fromRgb(127,0,200));
#endif

    if (oldNode != NULL)
    {
        return oldNode;
    }
    GraphNode *node = new GraphNode(/*window(), this, m_isUpdated*/);
 //   node->appendChildNode(new QSGSimpleTextureNode());
    node->setRect(boundingRect());
#ifdef OPENGL_RENDERING
    Renderer::instance()->addGraphNode(node,m_velosity);
#endif

    return node;
}

