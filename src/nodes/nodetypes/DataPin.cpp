#include "DataPin.h"

DataPin::DataPin(int defaultVal, Pin::Direction direction, QGraphicsItem* parent)
    : Pin(Pin::PinType::Data, direction, parent)
{
    setValue(defaultVal); 
}

void DataPin::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
        painter->setBrush(Qt::blue);
        painter->drawEllipse(QPointF(0, 0), 10, 10);
}

QRectF DataPin::boundingRect() const 
{ 
    return QRectF(-10, -10, 20, 20); 
}