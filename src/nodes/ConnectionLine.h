#pragma once

#include <QGraphicsLineItem>
#include <QObject>
#include <QTimer>

class Pin;

class ConnectionLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    ConnectionLine(Pin* from, Pin* to);

public slots:
    void updateLine();

private:
    Pin* startPin = nullptr;
    Pin* endPin = nullptr;
};