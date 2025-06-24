#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QPolygonF>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsLineItem>
#include "ConnectionLine.h"

class Pin: public  QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    Pin(int type, QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    float getWidth(){ return width; };
    float getHeight(){ return height; };
    int getPinType(){ return pinType; };
    ConnectionLine* getLine(){ return connectionLine; };
    void setLine(ConnectionLine* line){ connectionLine = line; }; 
    QPointF getTriangleCenter() const;

    int type() const override { return Type; }; 

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QPolygonF pinPolygon;
    QColor pinColor;
    float width = 20.0;
    float height = 20.0;

    ConnectionLine* connectionLine = nullptr;
    QGraphicsLineItem* tempLine = nullptr;

    void drawTrianglePin();
    void drawCirclePin(); 

    int pinType = 0; //0 input, 1 output;

};