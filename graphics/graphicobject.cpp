#include "graphicobject.h"
//#include "graphicmanager.h"
GraphicObject::GraphicObject(QObject *parent) :
    QObject(parent)
{
    //qDebug()<<"meCreated";
    setIsOn(false);
    setX(10);
    setY(10);
    setWidth(100);
    setHeight(100);
    setColor(QColor::fromRgb(255,255,0));
}

GraphicObject::~GraphicObject()
{
    //qDebug()<<"meDeleted";
    //GraphicManager::instance()->removeGraphicObject(this);
}

void GraphicObject::setState(bool _isOn, qint32 _x, qint32 _y, qint32 _w, qint32 _h)
{
    setIsOn(_isOn);
    setX(_x);
    setY(_y);
    setWidth(_w);
    setHeight(_h);
    //qDebug()<< _isOn << " " << _x << " " << _y << " " << _w << " " << _h;
    //qDebug()<< getIsOn() << " " << getX() << " " << getY() << " " << getWidth() << " " << getHeight();
}
