#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <QColor>
#include <QObject>
#include <QDebug>
//class GraphicManager;

class GraphicObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 x READ getX  WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qint32 y READ getY  WRITE setY NOTIFY yChanged)
    Q_PROPERTY(qint32 width READ getWidth  WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qint32 height READ getHeight  WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool isOn READ getIsOn  WRITE setIsOn NOTIFY isOnChanged)
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    qint32 m_x;
    qint32 m_y;
    qint32 m_width;
    qint32 m_height;
    bool m_isOn;
    QColor m_color;

public:
    explicit GraphicObject(QObject *parent = 0);
    ~GraphicObject();

    qint32 getX() const{    return m_x;}
    qint32 getY() const{    return m_y;}
    qint32 getWidth() const{    return m_width;}
    qint32 getHeight() const{    return m_height;}
    bool getIsOn() const  {    return m_isOn;}
    Q_INVOKABLE void setState(bool _isOn, qint32 _x, qint32 _y, qint32 _w, qint32 _h);
    QColor getColor() const{return m_color;}

signals:

    void xChanged(qint32 arg);
    void yChanged(qint32 arg);
    void widthChanged(qint32 arg);
    void heightChanged(qint32 arg);
    void isOnChanged(bool arg);
    void colorChanged(QColor arg);

public slots:

    void setX(qint32 arg)
    {
        if (m_x != arg) {
            m_x = arg;
            emit xChanged(arg);
        }
    }
    void setY(qint32 arg)
    {
        if (m_y != arg) {
            m_y = arg;
            emit yChanged(arg);
        }
    }
    void setWidth(qint32 arg)
    {
        if (m_width != arg) {
            m_width = arg;
            emit widthChanged(arg);
        }
    }
    void setHeight(qint32 arg)
    {
        if (m_height != arg) {
            m_height = arg;
            emit heightChanged(arg);
        }
    }

    void setIsOn(bool arg)
    {
        if (m_isOn != arg) {
            m_isOn = arg;
            emit isOnChanged(arg);
        }
    }
    void setColor(QColor arg)
    {
        if (m_color != arg) {
            m_color = arg;
            emit colorChanged(arg);
        }
    }
};

#endif // GRAPHICOBJECT_H
