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
    ~ConnectionLine();

    Pin* getNextPin(){return endPin;};
    Pin* getStartPin(){return startPin;}; 

public slots:
    void updateLine();

private:
    Pin* startPin = nullptr;
    Pin* endPin = nullptr;
};