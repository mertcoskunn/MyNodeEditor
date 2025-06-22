#include "Pin.h"


Pin::Pin(QGraphicsItem* parent)
    :QGraphicsItem(parent)
{
    pinPolygon << QPointF(width/2,0)
                  << QPointF(-width/2, -height/2)
                  << QPointF(-width/2, height/2);

    pinColor = Qt::cyan;
    setAcceptHoverEvents(true); 
}


QRectF Pin::boundingRect() const
{
    return pinPolygon.boundingRect();
}

void Pin::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
        painter->setBrush(pinColor);
        painter->setPen(Qt::black);
        painter->drawPolygon(pinPolygon);
}