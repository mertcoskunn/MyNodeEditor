#pragma once 
#include "../Pin.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>

class ExecutionPin : public Pin
{

public:
    ExecutionPin(Pin::Direction direction, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
}; 