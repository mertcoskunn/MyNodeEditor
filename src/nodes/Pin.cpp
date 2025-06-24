#include "Pin.h"
#include <QDebug>


Pin::Pin(int type, QGraphicsItem* parent)
    :QGraphicsItem(parent)
{
    drawTrianglePin();
    pinType = type;
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

QPointF Pin::getTriangleCenter() const
{
    if (pinPolygon.size() != 3) return QPointF(0, 0);
    return (pinPolygon[0] + pinPolygon[1] + pinPolygon[2]) / 3.0;
}

void Pin::hoverEnterEvent(QGraphicsSceneHoverEvent *) 
{
        pinColor = Qt::yellow;
        update();
}

void Pin::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    pinColor = Qt::cyan;
    update();
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();

    QPointF startPos = mapToScene(boundingRect().center());

    tempLine = new QGraphicsLineItem(QLineF(startPos, startPos));
    tempLine->setPen(QPen(Qt::black, 2));
    scene()->addItem(tempLine);
}

void Pin::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();

    if (!tempLine)
        return; 

    QList<QGraphicsItem*> itemsUnderCursor = scene()->items(event->scenePos());

    for (QGraphicsItem* item : itemsUnderCursor) {
        Pin* tempPin = qgraphicsitem_cast<Pin*>(item);
        if(tempPin && (tempPin != this))
        {
            pinColor= Qt::green;
            update();
        }
    }

    QPointF startPos = tempLine->line().p1();
    QPointF currentPos = event->scenePos();

    tempLine->setLine(QLineF(startPos, currentPos));
}

void Pin::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();

    if(!tempLine)
        return;
    
    QList<QGraphicsItem*> itemsUnderCursor = scene()->items(event->scenePos());
    bool temp = false;

    for (QGraphicsItem* item : itemsUnderCursor) 
    {
        if (!(item->type() == Pin::Type))
            continue;
        
        Pin* tempPin = qgraphicsitem_cast<Pin*>(item);
        
        if((tempPin == nullptr) || (tempPin == this))
            continue;

        if(tempPin->parentItem() == this->parentItem())
            continue;

        if(tempPin->getPinType() == pinType)
            continue;

        ConnectionLine* line = new ConnectionLine(this, tempPin);
                    
        setLine(line);
        scene()->addItem(line); 
        scene()->removeItem(tempLine);
        delete tempLine;
        tempLine = nullptr;
        temp = true;
        break;
    }

    if(!temp)
    {
        scene()->removeItem(tempLine);
        delete tempLine;
        tempLine = nullptr;
    }
}

void Pin::drawTrianglePin()
{
    pinPolygon << QPointF(width/2,0)
               << QPointF(-width/2, -height/2)
               << QPointF(-width/2, height/2);
}

