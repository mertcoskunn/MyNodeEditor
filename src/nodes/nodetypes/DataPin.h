#pragma once 
#include "../Pin.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>

class DataPin : public Pin
{
public :
    DataPin(int defaultVal, Pin::Direction direction, QGraphicsItem* parent = nullptr);
    
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override; 
    float getValue(){ return value; };
    void setValue(float v){ value = v; }; 

private:
    float value; 
};