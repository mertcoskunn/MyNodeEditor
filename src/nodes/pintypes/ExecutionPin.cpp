#include "ExecutionPin.h"


ExecutionPin::ExecutionPin(Pin::Direction direction, QGraphicsItem* parent)
    : Pin(Pin::PinType::Exectution, direction, parent), pinColor("#FFFFFF")
{
   
}

void ExecutionPin::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
        QPolygonF triangle;
        triangle << QPointF(10, 0)
                 << QPointF(-10, -10)
                 << QPointF(-10, 10);
        painter->setBrush(pinColor);
        painter->drawPolygon(triangle);
}

QRectF ExecutionPin::boundingRect() const 
{ 
    return QRectF(-10, -10, 20, 20); 
}