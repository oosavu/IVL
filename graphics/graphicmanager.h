#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include <QObject>
#include <QMutexLocker>
#include <QList>
#include <QQmlContext>
#include <QQmlListProperty>
#include <QImage>
#include <QPainter>
#include <QThread>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <sys/mman.h>
//#include "fb.h"
#include <QDebug>
#include <QTimer>
#include <QVariantList>
#include "graphicline.h"
#include "graphicloop.h"


typedef struct _LFBINFO
{
    unsigned int *fb;
    unsigned short width;           //xres
    unsigned short height;          //yres
    unsigned int bytes_per_line;    //line_length
    int fbdev;
}LFBINFO;



class GraphicManager : public QObject
{
    Q_OBJECT

public:
    Q_ENUMS(GRAPH_TYPES)
    enum  GRAPH_TYPES{
        GRAPH_TYPE_P          = 0,
        GRAPH_TYPE_V             ,
        GRAPH_TYPE_F             ,
        GRAPH_TYPE_LOOP          ,
        GRAPH_TYPE_CO2_PERC      ,
        GRAPH_TYPE_CO2_MM        ,
    };

private:
    QThread graphThread;
    QMutex mutex;
    QMutex mutexData;

    LFBINFO lfbInfo;
    QImage *fbImage;
    QPainter* fbPainter;
    QTimer graphTimer;

    bool  openFBImage();
    explicit GraphicManager();
    static GraphicManager* _self;

    quint32 currLineX;
    quint32 maxLineX;

    //QMap<GRAPH_TYPES,GraphicObject*> goMap;
    GraphicLine*    graphP         ;
    GraphicLine*    graphV         ;
    GraphicLine*    graphF         ;
    GraphicLoop*    graphLoopPV    ;
    GraphicLoop*    graphLoopFP    ;
    GraphicLoop*    graphLoopFV    ;
    GraphicLine*    graphFiCO2pers ;
    GraphicLine*    graphFiCO2mm   ;

    QVarLengthArray<qint16, 1024> dataP;
    QVarLengthArray<qint16, 1024> dataV;
    QVarLengthArray<qint16, 1024> dataF;
    QVarLengthArray<qint16, 1024> dataCO2perc;
    QVarLengthArray<qint16, 1024> dataCO2mm;

    void paintLineStep(GraphicLine* gl, QVarLengthArray<qint16, 1024>* data);
    void paintLineAtCircleEnd(GraphicLine* gl);

    void paintLoopStep(GraphicLoop* gLoop, QVarLengthArray<qint16, 1024>* dataX, QVarLengthArray<qint16, 1024>* dataY);
    void paintLoopAtCircleEnd(GraphicLoop* gLoop);

    void clearGraphObject(GraphicObject* go);

public:

    static GraphicManager* instance();

    Q_INVOKABLE void stopAll();

    Q_INVOKABLE void startAll();

    Q_INVOKABLE void clearScreen();

    void bindContext(QQmlContext *ctx);

    bool isNeededRefreshLoops;


signals:
    void graphListChanged(QQmlListProperty<GraphicObject> arg);

private slots:
    void timerSlot();

public:
    void addPVFData(qint16 _p, qint16 _v, qint16 _f);
    void addCapnoData(qint16 _co2_mm, qint16 _co2_perc);

};


#endif // GRAPHICMANAGER_H
