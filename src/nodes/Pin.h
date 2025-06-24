#pragma once

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygonF>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsLineItem>
#include <QObject>
#include "ConnectionLine.h"

class Pin: public  QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };
    enum class Direction { Input, Output};
    Q_ENUM(Direction)

    enum class PinType { Exectution, Data};
    Q_ENUM(PinType)

    Pin( PinType type, Direction direction, QGraphicsItem* parent = nullptr );
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    float getWidth(){ return width; };
    float getHeight(){ return height; };
    //int getPinType(){ return pinType; };
    //PinType get
    Direction getDirection(){ return m_direction; };
    PinType getPinType(){ return m_pinType; }; 

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

    Direction m_direction;
    PinType m_pinType; 

};