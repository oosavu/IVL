#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QList>
#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QSGSimpleTextureNode>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QList>
#include <cmath>
#include <QTime>
#include <QThread>
#include "graphnode.h"
#include "canmessage.h"
#include "qtquick2applicationviewer.h"


#define PIX_IN_MM 3.2;

class GraphNode;

extern QtQuick2ApplicationViewer* viewer;

struct GraphNodeRenderParams
{
    QOpenGLBuffer* m_vbo_x;
    QOpenGLBuffer* m_vbo_y;
    QSGTexture *m_texture;
    QSGTexture *m_texture_axes;
    QSGTexture *m_texture_data;
    QOpenGLFramebufferObject *m_fbo;
    QOpenGLFramebufferObject *m_fbo_axes;
    QOpenGLFramebufferObject *m_fbo_data;
    int m_num;
    float m_offset;
    int m_x_pixels;
    qint32 m_mm_in_sec;
    float m_prevVal;
    bool m_needInitVBOs;
    bool m_isNeedRender;
    GraphNodeRenderParams();
    QList<float> m_valuesBuffer;
    QMutex m_mutex;
};

class Renderer : public QObject
{
    Q_OBJECT

    QMap<GraphNode*, GraphNodeRenderParams*> nodeMap;

    QOpenGLShaderProgram* m_program;
    QOpenGLShaderProgram* m_programFullTexture;
    QOpenGLShaderProgram* m_programFullTextureGaus;
    QOpenGLBuffer* m_vbo_FullTextureVert;
    QOpenGLBuffer* m_vbo_FullTextureTexCords;
    int m_fpsCount;
    bool m_needInitShader;
    int msec_from_last_render;

    static Renderer* _self;
    explicit Renderer(QObject *parent = 0);

    QTime m_time_from_prev_render;
    QTimer timer;
    QTimer renderTimer;


public:
    static Renderer* instance();


    void addGraphNode(GraphNode* node, qint32 velosity);

    void renderNode(GraphNode* node);

    void addFlowValue(qint16 _flow);
    void addVolumeValue(quint16 _volume);
    void addPressureValue(quint16 _pressure);


public slots:
    void renderAll();
private slots:
    void timerSlot();
    void renderTimerSlot();

};

#endif // RENDERER_H
