#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QSGSimpleTextureNode>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include <cmath>

#include <QTimer>

#include "graphitem.h"
class GraphItem;

class GraphNode : public QObject, public QSGSimpleTextureNode
{
    Q_OBJECT
public:
    explicit GraphNode();
    //~GraphNode();

};

#endif // GRAPHNODE_H
