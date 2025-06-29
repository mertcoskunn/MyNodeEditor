#include "ExecutionPin.h"


ExecutionPin::ExecutionPin(Pin::Direction direction, QGraphicsItem* parent)
    : Pin(Pin::PinType::Exectution, direction, parent)
{
   
}

void ExecutionPin::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
        QPolygonF triangle;
        triangle << QPointF(10, 0)
                 << QPointF(-10, -10)
                 << QPointF(-10, 10);
        painter->setBrush(Qt::darkGreen);
        painter->drawPolygon(triangle);
}

QRectF ExecutionPin::boundingRect() const 
{ 
    return QRectF(-10, -10, 20, 20); 
}