#include <qmath.h>
#include "graphrenderer.h"



GraphRenderer::GraphRenderer(): QQuickFramebufferObject::Renderer()
{


    m_num = 0;
    m_x_pixels = 600;//this->framebufferObject()->width();

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vert.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/frag.fsh");
    m_program->bindAttributeLocation("x_index", 0);
    m_program->bindAttributeLocation("y_coord", 1);
    m_program->link();

    m_programFullTexture = new QOpenGLShaderProgram();
    m_programFullTexture->addShaderFromSourceFile( QOpenGLShader::Vertex, ":/vertFullTexture.vsh");
    m_programFullTexture->addShaderFromSourceFile( QOpenGLShader::Fragment, ":/fragFullTexture.fsh");
    m_programFullTexture->bindAttributeLocation("coord", 0);
    m_programFullTexture->bindAttributeLocation("texCoord", 1);
    m_programFullTexture->link();

    float * values_y = new float[m_x_pixels];
    float * values_x = new float[m_x_pixels];
    for (int i = 0; i < m_x_pixels; i++)
    {
        values_y[i] = 0.5*qSin(2.0*3.14*i/float(m_x_pixels));
        values_x[i] = i;
    }
    m_vbo_y = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo_y->setUsagePattern( QOpenGLBuffer::DynamicDraw );
    m_vbo_y->create();
    m_vbo_y->bind();
    m_vbo_y->allocate(m_x_pixels * sizeof(float));
    m_vbo_y->write(0,values_y,m_x_pixels * sizeof(float));
    m_vbo_y->release();
    m_vbo_x = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo_x->setUsagePattern( QOpenGLBuffer::DynamicDraw );
    m_vbo_x->create();
    m_vbo_x->bind();
    m_vbo_x->allocate(m_x_pixels * sizeof(float));
    m_vbo_x->write(0,values_x,m_x_pixels * sizeof(float));
    m_vbo_x->release();


}

void GraphRenderer::render()
{
    m_num++;
    if(m_num > m_x_pixels) m_num = 0;

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    //glLineWidth(1);
    m_program->bind();
    m_vbo_x->bind();
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 1, 0);
    m_program->enableAttributeArray(0);
    m_vbo_x->release();
    m_vbo_y->bind();
    m_program->setAttributeBuffer(1, GL_FLOAT, 0, 1, 0);
    m_program->enableAttributeArray(1);
    m_vbo_y->release();
    m_program->setUniformValue("buff_size", float( m_x_pixels-1));
    m_program->setUniformValue("pos", float( m_num/*+m_offset*/));
    glDrawArrays( GL_LINE_STRIP/*GL_LINE_STRIP*/, 0, m_num );
    glDrawArrays( GL_LINE_STRIP/*GL_TRIANGLE_STRIPGL_LINE_STRIP*/, m_num+2, m_x_pixels - m_num-2);
    m_program->release();


   // update();
}

QOpenGLFramebufferObject *GraphRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    //format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}
