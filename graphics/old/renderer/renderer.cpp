#include "renderer.h"
#include <qmath.h>
#include <QPainter>
#include <QOpenGLPaintDevice>

Renderer* Renderer::_self = 0;

GraphNodeRenderParams::GraphNodeRenderParams()
{
    m_needInitVBOs = true;
    m_num = 0;
    m_offset = 0;
}

Renderer::Renderer(QObject *parent) :
    QObject(parent),
    m_program(NULL)
{
    m_fpsCount = 0;
    msec_from_last_render = 0;
    m_needInitShader = true;
    connect(viewer, SIGNAL(beforeRendering()), this, SLOT(renderAll()), Qt::DirectConnection);
    m_time_from_prev_render.start();

    renderTimer.setInterval(50);
    renderTimer.setSingleShot(false);
    //renderTimer.moveToThread(QThread::currentThread());
    connect(&renderTimer, SIGNAL(timeout()),this, SLOT(renderTimerSlot()));
    //renderTimer.start();

    timer.setInterval(1000);
    timer.setSingleShot(false);
    connect(&timer, SIGNAL(timeout()),this, SLOT(timerSlot()));
    timer.start();
}

void Renderer::timerSlot()
{
    qDebug()<<"renderer fps count: "<<QString::number(m_fpsCount);
    m_fpsCount=0;
}

void Renderer::renderTimerSlot()
{
        viewer->update();
}

Renderer *Renderer::instance()
{
    if(!_self)
    {
        _self = new Renderer();
    }
    return _self;
}

void Renderer::addGraphNode(GraphNode *node, qint32 velosity)
{
    GraphNodeRenderParams* params = new GraphNodeRenderParams();
    params->m_mm_in_sec = velosity;
    nodeMap[node] = params;
    //qDebug()<<"m_num="<< QString::number(params->m_num)<<"; m_offset"<< QString::number(params->m_offset);

}

void Renderer::renderAll()
{


    msec_from_last_render = m_time_from_prev_render.restart();

    if(m_needInitShader)
    {
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

        m_programFullTextureGaus = new QOpenGLShaderProgram();
        m_programFullTextureGaus->addShaderFromSourceFile( QOpenGLShader::Vertex, ":/vertFullTexture.vsh");
        m_programFullTextureGaus->addShaderFromSourceFile( QOpenGLShader::Fragment, ":/fragDataToFrame.fsh");
        m_programFullTextureGaus->bindAttributeLocation("coord", 0);
        m_programFullTextureGaus->bindAttributeLocation("texCoord", 1);
        m_programFullTextureGaus->link();


        float* coordFon = new float[12];
        coordFon[0]= -1.0; coordFon[1]= -1.0;
        coordFon[2]= -1.0;  coordFon[3]= 1.0;
        coordFon[4]= 1.0; coordFon[5]= -1.0;
        coordFon[6]= -1.0;  coordFon[7]= 1.0;
        coordFon[8]= 1.0; coordFon[9]= -1.0;
        coordFon[10]= 1.0;  coordFon[11]= 1.0;
        m_vbo_FullTextureVert = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vbo_FullTextureVert->setUsagePattern( QOpenGLBuffer::DynamicDraw );
        m_vbo_FullTextureVert->create();
        m_vbo_FullTextureVert->bind();
        m_vbo_FullTextureVert->allocate(12 * sizeof(float));
        m_vbo_FullTextureVert->write(0,coordFon,12 * sizeof(float));
        m_vbo_FullTextureVert->release();

        float* coordTexture = new float[12];
        coordTexture[0]= 0.0; coordTexture[1]= 1.0;
        coordTexture[2]= 0.0;  coordTexture[3]= 0.0;
        coordTexture[4]= 1.0; coordTexture[5]= 1.0;
        coordTexture[6]= 0.0;  coordTexture[7]= 0.0;
        coordTexture[8]= 1.0; coordTexture[9]= 1.0;
        coordTexture[10]= 1.0; coordTexture[11]= 0.0;
        m_vbo_FullTextureTexCords = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_vbo_FullTextureTexCords->setUsagePattern( QOpenGLBuffer::DynamicDraw );
        m_vbo_FullTextureTexCords->create();
        m_vbo_FullTextureTexCords->bind();
        m_vbo_FullTextureTexCords->allocate(12 * sizeof(float));
        m_vbo_FullTextureTexCords->write(0,coordTexture,12 * sizeof(float));
        m_vbo_FullTextureTexCords->release();

        m_needInitShader = false;
    }

    QTime testerTime;
    testerTime.start();
    QList<float> m_nums;
    //qDebug()<<nodeMap.values().at(0)->m_valuesBuffer.size();
    foreach(GraphNode* node, nodeMap.keys())
    {
        float before = float(nodeMap[node]->m_num+ nodeMap[node]->m_offset);
        renderNode(node);
        m_nums.append(float(nodeMap[node]->m_num+ nodeMap[node]->m_offset)-before);
    }

    //qDebug()<<"msflrr: "<<msec_from_last_render<<". torn: "<<QString::number(testerTime.elapsed())<<". pixinstep: "<<m_nums;

    viewer->update();
    m_fpsCount++;

}


void Renderer::renderNode(GraphNode *node)
{
    GraphNodeRenderParams* params = nodeMap[node];
    QSize size = node->rect().size().toSize();
    //QSize doubleSize(size.width()*2, size.height()*2);
    QSize doubleSize(size.width(), size.height());

    //if(!params->m_isNeedRender) return;

    if(params->m_needInitVBOs)
    {
        params->m_x_pixels = size.width()+1;

        params->m_fbo = new QOpenGLFramebufferObject(size);
        params->m_texture = viewer->createTextureFromId(params->m_fbo->texture(), size);
        params->m_fbo_axes =  new QOpenGLFramebufferObject(size);
        params->m_texture_axes = viewer->createTextureFromId(params->m_fbo_axes->texture(), size);
        params->m_fbo_data =  new QOpenGLFramebufferObject(doubleSize);
        params->m_texture_data = viewer->createTextureFromId(params->m_fbo_data->texture(), doubleSize);

        float * values_y = new float[params->m_x_pixels];
        float * values_x = new float[params->m_x_pixels];
        for (int i = 0; i < params->m_x_pixels; i++)
        {
            values_y[i] = 0.5*qSin(2.0*3.14*i/float(params->m_x_pixels));
            values_x[i] = i;
        }
        params->m_vbo_y = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        params->m_vbo_y->setUsagePattern( QOpenGLBuffer::DynamicDraw );
        params->m_vbo_y->create();
        params->m_vbo_y->bind();
        params->m_vbo_y->allocate(params->m_x_pixels * sizeof(float));
        params->m_vbo_y->write(0,values_y,params->m_x_pixels * sizeof(float));
        params->m_vbo_y->release();
        params->m_vbo_x = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        params->m_vbo_x->setUsagePattern( QOpenGLBuffer::DynamicDraw );
        params->m_vbo_x->create();
        params->m_vbo_x->bind();
        params->m_vbo_x->allocate(params->m_x_pixels * sizeof(float));
        params->m_vbo_x->write(0,values_x,params->m_x_pixels * sizeof(float));
        params->m_vbo_x->release();

        params->m_fbo_axes->bind();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        QOpenGLPaintDevice device(size);
        QPainter _painter;
        _painter.begin(&device);
        //_painter.fillRect(0.0,0.0,size.width(),size.height(),QColor::fromRgbF(0.5,0.5,0.5,0.2));
        _painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
        _painter.setPen(QPen(Qt::white, 1));
        _painter.setBrush(Qt::red);
        //_painter.drawEllipse(size.width()/2.0, size.height()/2.0, size.width()/3.0, size.height()/3.0 );
//        _painter.drawLine(size.width()/10, size.height()/10, size.width()/10, size.height()*9/10);
//        _painter.drawLine(size.width()/10, size.height()/2, size.width()*9/10, size.height()/2);
        //_painter.drawPoint(10,10);
        _painter.drawText(10,10,"10-10");
        _painter.drawText(size.width()-10.0,10,"wid-10");
        _painter.drawText(10,size.height()-10.0,"10-hei");
        _painter.drawText(size.width()-10.0,size.height()*9.0/10.0,"wid-hei");
        _painter.end();
        params->m_fbo_axes->release();

        node->setTexture(params->m_texture_data);
        //static_cast<QSGSimpleTextureNode*>(node->firstChild())->setTexture(params->m_texture);

        params->m_needInitVBOs = false;

        params->m_prevVal = 0;
        params->m_offset = 0;
    }

    double need_pixels_d = msec_from_last_render * PIX_IN_MM;
    need_pixels_d = need_pixels_d * params->m_mm_in_sec/1000.0;
   // if(need_pixels_d<1.0) return;
    params->m_offset += need_pixels_d;
//    if(params->m_offset > params->m_x_pixels)  params->m_offset = params->m_offset - params->m_x_pixels;

    params->m_mutex.lock();
    while(params->m_offset > 1.0)
    {
//        params->m_prevVal += 0.04;
//        float nextVal = 0.8*qSin(params->m_prevVal);

        float nextVal = 0.9;
        if(params->m_valuesBuffer.size() != 0)
        {
            nextVal = params->m_valuesBuffer.last();
            //params->m_valuesBuffer.removeFirst();
        }


        params->m_vbo_y->bind();
            params->m_vbo_y->write((params->m_num) * sizeof(float) ,&nextVal,sizeof(float));
            params->m_num++;
            if(params->m_num == params->m_x_pixels)
            {
                params->m_num = 1;
                params->m_vbo_y->write(0 ,&nextVal,sizeof(float));
            }
        params->m_vbo_y->release();
        params->m_offset-=1.0;
    }
    params->m_valuesBuffer.clear();
    params->m_mutex.unlock();


    params->m_fbo_data->bind();
        glViewport(0, 0, doubleSize.width(), doubleSize.height());
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(1);
        m_program->bind();
        params->m_vbo_x->bind();
        m_program->setAttributeBuffer(0, GL_FLOAT, 0, 1, 0);
        m_program->enableAttributeArray(0);
        params->m_vbo_x->release();
        params->m_vbo_y->bind();
        m_program->setAttributeBuffer(1, GL_FLOAT, 0, 1, 0);
        m_program->enableAttributeArray(1);
        params->m_vbo_y->release();
        m_program->setUniformValue("buff_size", float( params->m_x_pixels-1));
        m_program->setUniformValue("pos", float( params->m_num/*+params->m_offset*/));
        glDrawArrays( GL_LINE_STRIP/*GL_LINE_STRIP*/, 0, params->m_num );
        glDrawArrays( GL_LINE_STRIP/*GL_TRIANGLE_STRIPGL_LINE_STRIP*/, params->m_num+2, params->m_x_pixels - params->m_num-2);
        m_program->release();

        m_programFullTexture->bind();
        m_vbo_FullTextureVert->bind();
        m_programFullTexture->setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
        m_programFullTexture->enableAttributeArray(0);
        m_vbo_FullTextureVert->release();
        m_vbo_FullTextureTexCords->bind();
        m_programFullTexture->setAttributeBuffer(1, GL_FLOAT, 0, 2, 0);
        m_programFullTexture->enableAttributeArray(1);
        m_vbo_FullTextureTexCords->release();
        glBindTexture( GL_TEXTURE_2D, params->m_fbo_axes->texture());
        glDrawArrays( GL_TRIANGLES, 0, 6);
        m_programFullTexture->release();

    params->m_fbo_data->release();


//    params->m_fbo->bind();
//        glViewport(0, 0, size.width(), size.height());
//        glClear(GL_COLOR_BUFFER_BIT);



//        m_programFullTextureGaus->bind();
//        m_vbo_FullTextureVert->bind();
//        m_programFullTextureGaus->setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
//        m_programFullTextureGaus->enableAttributeArray(0);
//        m_vbo_FullTextureVert->release();
//        m_vbo_FullTextureTexCords->bind();
//        m_programFullTextureGaus->setAttributeBuffer(1, GL_FLOAT, 0, 2, 0);
//        m_programFullTextureGaus->enableAttributeArray(1);
//        m_vbo_FullTextureTexCords->release();
////        m_programFullTextureGaus->setUniformValue("w_pix",float(1.0/float( doubleSize.width())));
////        m_programFullTextureGaus->setUniformValue("h_pix",float(1.0/float( doubleSize.height())));
//        glBindTexture( GL_TEXTURE_2D, params->m_fbo_data->texture());
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glDrawArrays( GL_TRIANGLES, 0, 6);
//        m_programFullTextureGaus->release();

//    params->m_fbo->bindDefault();


}

void Renderer::addFlowValue(qint16 _flow)
{
    nodeMap.values().at(0)->m_mutex.lock();
    nodeMap.values().at(0)->m_valuesBuffer.append(float(_flow)/256.0);
    nodeMap.values().at(0)->m_mutex.unlock();
}

void Renderer::addVolumeValue(quint16 _volume)
{
    nodeMap.values().at(1)->m_mutex.lock();
    nodeMap.values().at(1)->m_valuesBuffer.append(float(_volume)/256.0);
    nodeMap.values().at(1)->m_mutex.unlock();
}

void Renderer::addPressureValue(quint16 _pressure)
{
    nodeMap.values().at(2)->m_mutex.lock();
    nodeMap.values().at(2)->m_valuesBuffer.append(float(_pressure)/256.0);
    nodeMap.values().at(2)->m_mutex.unlock();
}


