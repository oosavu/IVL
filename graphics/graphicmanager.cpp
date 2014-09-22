#include "graphicmanager.h"
#include "qmath.h"

GraphicManager* GraphicManager::_self = 0;


bool GraphicManager::openFBImage()
{
#ifndef DESKTOP_LINUX
    struct fb_fix_screeninfo fixinfo;
    struct fb_var_screeninfo varinfo;

    int fd=open("/dev/fb1",O_RDWR);
    if(fd==-1)
      {qDebug("Unable to open frame buffer\n");return false;}
    //get the fixed screen info
    if(ioctl(fd,FBIOGET_FSCREENINFO, &fixinfo))
      {qDebug("Unable to get fixed screen info\n");return false;}
    //get the variable screen info
    if(ioctl(fd,FBIOGET_VSCREENINFO, &varinfo))
      {qDebug("Unable to get variable screen info\n");return false;}
    //map the framebuffer into memory
    unsigned int *framebuffer=(unsigned int *)mmap(0,fixinfo.smem_len,PROT_WRITE,MAP_SHARED,fd,0);
    if(framebuffer==MAP_FAILED)
      {qDebug("Unable to map frame buffer\n");return(-1);}
    lfbInfo.fb=framebuffer;
    lfbInfo.width=varinfo.xres;
    lfbInfo.height=varinfo.yres;
    lfbInfo.bytes_per_line=fixinfo.line_length;
    lfbInfo.fbdev=fd;
    *framebuffer=0;
    fbImage = new QImage((uchar*)(lfbInfo.fb),1024,768,1024*4,QImage::Format_ARGB32);
#else
    qDebug()<<"ERROR: GRAPHIC NOT DISPLAYED!!!";
    fbImage = new QImage(1024,768,QImage::Format_ARGB32);
#endif

    fbPainter = new QPainter(fbImage);
    fbPainter->setPen(Qt::blue);
    fbPainter->setFont(QFont("Arial", 30));
    fbPainter->fillRect(0,0,1024,768,QColor::fromRgb(0,0,0,0));
    //fbPainter->drawText(300,300,"from 666 to asdfsdf77");
    fbPainter->end();
    return true;
}

GraphicManager::GraphicManager() :
    QObject(0)
{
    if(openFBImage()) qDebug()<<"fb Image opened";
    else qDebug()<<"ERROR: fbImage not opened!!!";

    QList<qint32> limitsP;
    QList<qint32> limitsV;
    QList<qint32> limitsF;
    QList<qint32> limitsCO2perc;
    QList<qint32> limitsCO2mm;

    limitsP.append(200  );
    limitsP.append(400  );
    limitsP.append(600  );
    limitsP.append(800  );
    limitsP.append(1000 );
    limitsP.append(1500 );
    limitsP.append(2000 );
    limitsP.append(10000);
    limitsV.append(100  );
    limitsV.append(200  );
    limitsV.append(500  );
    limitsV.append(1000 );
    limitsV.append(2000 );
    limitsV.append(5000 );
    limitsV.append(10000);
    limitsF.append(100  );
    limitsF.append(250  );
    limitsF.append(500  );
    limitsF.append(1000 );
    limitsF.append(2000 );
    limitsF.append(4000 );
    limitsF.append(10000);
    limitsCO2perc.append(1000);
    limitsCO2mm.append(800);

    graphP      = new GraphicLine();
    graphP->maxLimits = limitsP;
    graphP->setMaxNegativeVal(-200);
    graphP->setMaxPositiveVal(200 );
    graphP->setColor(QColor::fromRgb(255,255,0));

    graphV      = new GraphicLine();
    graphV->maxLimits = limitsV;
    graphV->setMaxNegativeVal(0);
    graphV->setMaxPositiveVal(100);
    graphV->setColor(QColor::fromRgb(255,0,255));

    graphF      = new GraphicLine();
    graphF->maxLimits = limitsF;
    graphF->setMaxNegativeVal(-100);
    graphF->setMaxPositiveVal(100);
    graphF->setColor(QColor::fromRgb(0,255,255));

    graphFiCO2mm      = new GraphicLine();
    graphFiCO2mm->maxLimits = limitsCO2mm;
    graphFiCO2mm->setMaxNegativeVal(0);
    graphFiCO2mm->setMaxPositiveVal(20);
    graphFiCO2mm->setColor(QColor::fromRgb(88,255,00));

    graphFiCO2pers      = new GraphicLine();
    graphFiCO2pers->maxLimits = limitsCO2perc;
    graphFiCO2pers->setMaxNegativeVal(0);
    graphFiCO2pers->setMaxPositiveVal(100);
    graphFiCO2pers->setColor(QColor::fromRgb(88,255,140));


    graphLoopPV = new GraphicLoop();
    graphLoopPV->maxLimitsX = limitsP;
    graphLoopPV->maxLimitsY = limitsV;
    graphLoopPV->setColor(QColor::fromRgb(255,0,0));

    graphLoopFV = new GraphicLoop();
    graphLoopFV->maxLimitsX = limitsF;
    graphLoopFV->maxLimitsY = limitsV;
    graphLoopFV->setColor(QColor::fromRgb(0,255,0));

    graphLoopFP = new GraphicLoop();
    graphLoopFP->maxLimitsX = limitsF;
    graphLoopFP->maxLimitsY = limitsP;
    graphLoopFP->setColor(QColor::fromRgb(0,0,255));

    //graphFiO2   = new GraphicObject();

    maxLineX = 100;
    currLineX = 0;
    isNeededRefreshLoops = false;
    paintLineAtCircleEnd(graphP);
    paintLineAtCircleEnd(graphV);
    paintLineAtCircleEnd(graphF);
    paintLineAtCircleEnd(graphFiCO2mm);
    paintLineAtCircleEnd(graphFiCO2pers);


    graphTimer.moveToThread(&graphThread);
    connect(&graphTimer,SIGNAL(timeout()), SLOT(timerSlot()), Qt::DirectConnection);
    graphTimer.setSingleShot(false);
    graphTimer.setInterval(30);
    QMetaObject::invokeMethod(&graphTimer, "start", Qt::QueuedConnection);
    graphThread.start();
    //graphTimer.start();
}

void GraphicManager::paintLineStep(GraphicLine *gl, QVarLengthArray<qint16, 1024> *data)
{
    if(data->size() == 0) data->append(0);
    qint16 currMax = data->at(0);
    qint16 currMin = data->at(0);
    foreach (qint16 currValue, *data)
    {
       if (currValue > currMax) currMax = currValue;
       if (currValue < currMin) currMin = currValue;
    }

    if(gl->nextCircleMax < currMax) gl->nextCircleMax = currMax;
    if(gl->nextCircleMin > currMin) gl->nextCircleMin = currMin;

    if(currMax> gl->getMaxPositiveVal()) currMax = gl->getMaxPositiveVal();
    if(currMin> gl->getMaxPositiveVal()) currMin = gl->getMaxPositiveVal();
    if(currMax< gl->getMaxNegativeVal()) currMax = gl->getMaxNegativeVal();
    if(currMin< gl->getMaxNegativeVal()) currMin = gl->getMaxNegativeVal();

    if(double((qAbs(gl->getMaxPositiveVal()) + qAbs(gl->getMaxNegativeVal()))) <= 0) qDebug()<<"scale coef  error";
    double scaleCoef = gl->getHeight()/double((qAbs(gl->getMaxPositiveVal()) + qAbs(gl->getMaxNegativeVal())));
    int negativePixels = scaleCoef*qAbs(gl->getMaxNegativeVal());
    int maxPixels = scaleCoef* currMax;
    int minPixels = scaleCoef* currMin;
    int startZeroPixel = gl->getY() + gl->getHeight() - negativePixels;
    fbPainter->setPen(QColor::fromRgb(0,0,0,255));
    fbPainter->drawLine(gl->getX() + (currLineX+1)%maxLineX,
                      gl->getY(),
                      gl->getX() + (currLineX+1)%maxLineX,
                      gl->getY()+ gl->getHeight()
                );
    fbPainter->setPen(QColor::fromRgb(gl->getColor().red()/2,gl->getColor().green()/2,gl->getColor().blue()/2));
    fbPainter->drawLine(gl->getX() + currLineX,
                      startZeroPixel ,
                      gl->getX() + currLineX,
                      startZeroPixel - minPixels
                );

    fbPainter->setPen(gl->getColor());
    fbPainter->drawLine(gl->getX() + currLineX,
                      startZeroPixel - minPixels,
                      gl->getX() + currLineX,
                      startZeroPixel - maxPixels
                );
}

void GraphicManager::paintLineAtCircleEnd(GraphicLine *gl)
{
    qint32 appendedMax = 0;
    qint32 trueMax = gl->nextCircleMax;
    if(gl == graphF) trueMax = qMax(qAbs(gl->nextCircleMax),qAbs(gl->nextCircleMin));

    foreach(qint32 val, gl->maxLimits)
    {
        appendedMax = val;
        if(trueMax < val) break;
    }
    if(appendedMax != gl->getMaxPositiveVal())clearGraphObject(gl);

    if(gl == graphP)
    {
        gl->setMaxNegativeVal(-200);
        gl->setMaxPositiveVal(appendedMax);
    }
    else if(gl == graphV || gl == graphFiCO2mm || gl == graphFiCO2pers)
    {
        gl->setMaxNegativeVal(0);
        gl->setMaxPositiveVal(appendedMax);
    }
    else if(gl == graphF)
    {
       // qDebug()<<"Flow:"<< appendedMax << " " << trueMax;
        gl->setMaxNegativeVal(-appendedMax);
        gl->setMaxPositiveVal(appendedMax);
    }
    gl->nextCircleMax = 0;
    gl->nextCircleMin = 0;

}

void GraphicManager::paintLoopStep(GraphicLoop *gLoop, QVarLengthArray<qint16, 1024> *dataX, QVarLengthArray<qint16, 1024> *dataY)
{
    if(dataX->size() == 0) dataX->append(0);
    if(dataY->size() == 0) dataY->append(0);

    qint16 currX = 0;
    qint16 currY = 0;
    foreach (qint16 currValueX, *dataX){ currX += currValueX; }
    currX = currX/dataX->size();
    foreach (qint16 currValueY, *dataY){ currY += currValueY; }
    currY = currY/dataY->size();

    if(gLoop->nextCircleMaxX < currX) gLoop->nextCircleMaxX = currX;
    if(gLoop->nextCircleMinX > currX) gLoop->nextCircleMinX = currX;
    if(gLoop->nextCircleMaxY < currY) gLoop->nextCircleMaxY = currY;
    if(gLoop->nextCircleMinY > currY) gLoop->nextCircleMinY = currY;

    if(currX > gLoop->getMaxPositiveValX()) currX = gLoop->getMaxPositiveValX();
    if(currY > gLoop->getMaxPositiveValY()) currY = gLoop->getMaxPositiveValY();
    if(currX < gLoop->getMaxNegativeValX()) currX = gLoop->getMaxNegativeValX();
    if(currY < gLoop->getMaxNegativeValY()) currY = gLoop->getMaxNegativeValY();

    double scaleCoefX = gLoop->getWidth()  / double((qAbs(gLoop->getMaxPositiveValX()) + qAbs(gLoop->getMaxNegativeValX())));
    double scaleCoefY = gLoop->getHeight() / double((qAbs(gLoop->getMaxPositiveValY()) + qAbs(gLoop->getMaxNegativeValY())));


    int currXPix = scaleCoefX* (currX - gLoop->getMaxNegativeValX());
    int currYPix = scaleCoefY* (currY - gLoop->getMaxNegativeValY());

    fbPainter->setPen(QColor::fromRgb(gLoop->getColor().red(),gLoop->getColor().green(),gLoop->getColor().blue()));
    fbPainter->drawLine(gLoop->getX() + gLoop->prevXpix,
                      gLoop->getY() + gLoop->getHeight() - gLoop->prevYpix ,
                      gLoop->getX() + currXPix,
                      gLoop->getY() + gLoop->getHeight() - currYPix
                );
    gLoop->prevXpix = currXPix;
    gLoop->prevYpix = currYPix;
}

void GraphicManager::paintLoopAtCircleEnd(GraphicLoop *gLoop)
{
    qint32 appendedMaxX = 0;
    qint32 appendedMaxY = 0;
    qint32 trueMaxX = gLoop->nextCircleMaxX;
    qint32 trueMaxY = gLoop->nextCircleMaxY;

    if(gLoop == graphLoopFP || gLoop == graphLoopFV ) trueMaxX = qMax(qAbs(gLoop->nextCircleMaxX),qAbs(gLoop->nextCircleMinX));

//    if(gLoop == graphLoopFP || gLoop == graphLoopFV ) trueMaxX = qMax(qAbs(gLoop->nextCircleMax),qAbs(gLoop->nextCircleMin));

    foreach(qint32 val, gLoop->maxLimitsX)
    {
        appendedMaxX = val;
        if(trueMaxX < val) break;
    }
    foreach(qint32 val, gLoop->maxLimitsY)
    {
        appendedMaxY = val;
        if(trueMaxY < val) break;
    }

    if(gLoop->getIsOn()) clearGraphObject(gLoop);
//    if(gLoop->getIsOn())
//    {
//        fbPainter->begin(fbImage);
//        fbPainter->fillRect(gLoop->getX(),gLoop->getY(),gLoop->getWidth(),gLoop->getHeight(),QColor::fromRgb(50,50,0));
//        fbPainter->end();
//    }

    if(gLoop == graphLoopPV)
    {
        gLoop->setMaxNegativeValX(-appendedMaxX/10.0);
        gLoop->setMaxPositiveValX(appendedMaxX);
        gLoop->setMaxNegativeValY(-appendedMaxY/10.0);
        gLoop->setMaxPositiveValY(appendedMaxY);
    }

    if(gLoop == graphLoopFP)
    {
        gLoop->setMaxNegativeValX(-appendedMaxX);
        gLoop->setMaxPositiveValX(appendedMaxX);
        gLoop->setMaxNegativeValY(-appendedMaxY/10.0);
        gLoop->setMaxPositiveValY(appendedMaxY);
    }

    if(gLoop == graphLoopFV)
    {
        gLoop->setMaxNegativeValX(-appendedMaxX);
        gLoop->setMaxPositiveValX(appendedMaxX);
        gLoop->setMaxNegativeValY(-appendedMaxY/10.0);
        gLoop->setMaxPositiveValY(appendedMaxY);
    }
    gLoop->nextCircleMaxX = 0;
    gLoop->nextCircleMinX = 0;
    gLoop->nextCircleMaxY = 0;
    gLoop->nextCircleMinY = 0;

}

void GraphicManager::clearGraphObject(GraphicObject *go)
{
    //QMutexLocker locker(&mutex);
    fbPainter->begin(fbImage);
    fbPainter->fillRect(go->getX()-1,go->getY()-1,go->getWidth()+2,go->getHeight()+2,QColor::fromRgb(0,0,0));
    fbPainter->end();
}


GraphicManager *GraphicManager::instance()
{
    if(!_self)
    {
        _self = new GraphicManager();
    }
    return _self;
}

void GraphicManager::stopAll()
{
    QMutexLocker locker(&mutex);
    graphP->setIsOn(false);
    graphV->setIsOn(false);
    graphF->setIsOn(false);
    graphLoopFP->setIsOn(false);
    graphLoopFV->setIsOn(false);
    graphLoopPV->setIsOn(false);
    graphFiCO2mm->setIsOn(false);
    graphFiCO2pers->setIsOn(false);
}

void GraphicManager::startAll()
{
    QMutexLocker locker(&mutex);
    clearScreen();
    currLineX = 0;
    maxLineX = 0;
    if(graphV->getIsOn()) maxLineX = graphV->getWidth();
    if(graphP->getIsOn()) maxLineX = graphP->getWidth();
    if(graphF->getIsOn()) maxLineX = graphF->getWidth();
    if(graphFiCO2mm->getIsOn()) maxLineX = graphFiCO2mm->getWidth();
    if(graphFiCO2pers->getIsOn()) maxLineX = graphFiCO2pers->getWidth();
    if(maxLineX == 0)
    {
//        qDebug()<<"maxLineX = 0 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11111111111111111111!!!!!!!!!1111111!1";
//        qDebug()<<graphV->getWidth()<< " " << graphP->getWidth() << " " << graphF->getWidth();
        maxLineX = 1;
    }
}

void GraphicManager::clearScreen()
{
    fbPainter->begin(fbImage);
    fbPainter->fillRect(0,0,1024,768,QColor::fromRgb(0,0,0));
    fbPainter->end();
}

void GraphicManager::bindContext(QQmlContext *ctx)
{
    ctx->setContextProperty("graphP"     , graphP   );
    ctx->setContextProperty("graphV"     , graphV   );
    ctx->setContextProperty("graphF"     , graphF   );
    ctx->setContextProperty("loopPV"     , graphLoopPV);
    ctx->setContextProperty("loopFV"     , graphLoopFV);
    ctx->setContextProperty("loopFP"     , graphLoopFP);
    ctx->setContextProperty("graphFiCO2mm"   ,  graphFiCO2mm    ) ;
    ctx->setContextProperty("graphFiCO2pers"  , graphFiCO2pers );
}


void GraphicManager::timerSlot()
{
    QMutexLocker locker(&mutex);

    fbPainter->begin(fbImage);
    fbPainter->setPen(Qt::white);

        mutexData.lock();
        if(graphP->getIsOn())         paintLineStep(graphP, &dataP);
        if(graphV->getIsOn())         paintLineStep(graphV, &dataV);
        if(graphF->getIsOn())         paintLineStep(graphF, &dataF);
        if(graphFiCO2mm->getIsOn())   paintLineStep(graphFiCO2mm  , &dataCO2mm  );
        if(graphFiCO2pers->getIsOn()) paintLineStep(graphFiCO2pers, &dataCO2perc);
        if(graphLoopPV->getIsOn())    paintLoopStep(graphLoopPV, &dataP,&dataV);
        if(graphLoopFV->getIsOn())    paintLoopStep(graphLoopFV, &dataF,&dataV);
        if(graphLoopFP->getIsOn())    paintLoopStep(graphLoopFP, &dataF,&dataP);
        dataP.clear();
        dataV.clear();
        dataF.clear();
        dataCO2perc.clear();
        dataCO2mm.clear();
        mutexData.unlock();

    fbPainter->end();

    currLineX+=1;

    if(isNeededRefreshLoops)
    {
        isNeededRefreshLoops = false;
        paintLoopAtCircleEnd(graphLoopPV);
        paintLoopAtCircleEnd(graphLoopFP);
        paintLoopAtCircleEnd(graphLoopFV);
    }

    if(currLineX>= maxLineX)
    {
        currLineX = 0;
        paintLineAtCircleEnd(graphP);
        paintLineAtCircleEnd(graphV);
        paintLineAtCircleEnd(graphF);
        paintLineAtCircleEnd(graphFiCO2mm  );
        paintLineAtCircleEnd(graphFiCO2pers);
    }
}

void GraphicManager::addPVFData(qint16 _p, qint16 _v, qint16 _f)
{
    mutexData.lock();
    if(dataP.count()<50) dataP.append(_p);
    else qDebug()<< "graph data full";
    if(dataV.count()<50) dataV.append(_v);
    if(dataF.count()<50) dataF.append(_f);
    mutexData.unlock();
}

void GraphicManager::addCapnoData(qint16 _co2_mm, qint16 _co2_perc)
{
    mutexData.lock();
    if(dataCO2perc.count()<50) dataCO2perc.append(_co2_perc);
    if(dataCO2mm.count()<50) dataCO2mm.append(_co2_mm);
    else qDebug()<< dataCO2perc.size();
    mutexData.unlock();
}


