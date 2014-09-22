#ifndef GRAPHRENDERER_H
#define GRAPHRENDERER_H

#include <QtQuick/QQuickFramebufferObject>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtQuick/QQuickWindow>
#include <QOpenGLBuffer>

#include <qsgsimpletexturenode.h>


class GraphRenderer : public QQuickFramebufferObject::Renderer
{
//    QOpenGLFramebufferObject *m_fbo_axes;
    QOpenGLShaderProgram* m_program;
    QOpenGLShaderProgram* m_programFullTexture;
//    QOpenGLBuffer* m_vbo_FullTextureVert;
//    QOpenGLBuffer* m_vbo_FullTextureTexCords;
    QOpenGLBuffer* m_vbo_x;
    QOpenGLBuffer* m_vbo_y;
    int m_num;
    float m_offset;
    int m_x_pixels;
    qint32 m_mm_in_sec;


public:
    GraphRenderer();
    void render();
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size);

};

#endif
