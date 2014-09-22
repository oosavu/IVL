#ifndef KEYBOARDSIMULATOR_H
#define KEYBOARDSIMULATOR_H

#include <QObject>
#include <QDebug>
#include "QKeyEvent"
#include "QGuiApplication"
#include "QQuickWindow"
#include "QQuickItem"

class KeyboardSimulator : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void simulateKeyPressEvent(int key, QString text = QString(),
                                                   Qt::KeyboardModifier modifiers = Qt::NoModifier,
                                                   bool autorepeat = false)
    {
        QKeyEvent event1 = QKeyEvent(QKeyEvent::KeyPress, key, modifiers, text, autorepeat);
        QKeyEvent event2 = QKeyEvent(QKeyEvent::KeyRelease, key, modifiers, text, autorepeat);

        QQuickItem * receiver = qobject_cast<QQuickItem *>(QGuiApplication::focusObject());

        if (!receiver)
        { qDebug() << "simulateKeyPressEvent(): " "GuiApplication::focusObject() is 0 or not a QQuickItem."; return; }

        receiver->window()->sendEvent(receiver, &event1);
        receiver->window()->sendEvent(receiver, &event2);
    }
    explicit KeyboardSimulator(QObject *parent = 0);

signals:

public slots:

};

#endif // KEYBOARDSIMULATOR_H

