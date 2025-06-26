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
#include "Node.h"

class Pin: public  QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };
    enum class Direction { Input, Output};
    Q_ENUM(Direction)

    // burası opsiyonel olabilirr
    enum class PinType { Exectution, Data};
    Q_ENUM(PinType)

    Pin( PinType type, Direction direction, QGraphicsItem* parent = nullptr );
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;


    float getWidth(){ return width; };
    float getHeight(){ return height; };
   
    
    
    Direction getDirection(){ return m_direction; };
    PinType getPinType(){ return m_pinType; };
    void setLine(ConnectionLine* line){ connectionLine = line; }; 
    ConnectionLine* getLine(){ return connectionLine; };
    int type() const override { return Type; }; 
    
    //data pine özel
    float getValue(){ return value; };
    void setValue(float v){ value = v; }; 

    
    
    QPointF getTriangleCenter() const;

    

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

    float value = 3.0f; 

    ConnectionLine* connectionLine = nullptr;
    QGraphicsLineItem* tempLine = nullptr;

    void drawTrianglePin();

    Direction m_direction;
    PinType m_pinType;

    

};