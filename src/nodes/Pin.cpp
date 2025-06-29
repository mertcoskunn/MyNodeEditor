#include "Pin.h"
#include <QDebug>
#include "ConnectionLine.h"


Pin::Pin(PinType type, Direction direction, QGraphicsItem* parent)
    :QGraphicsObject(parent), m_pinType(type), m_direction(direction)
{
    pinColor = Qt::cyan;
    setAcceptHoverEvents(true); 
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

    if(m_pinType == Pin::PinType::Exectution && connectionLine)
    {
        scene()->removeItem(connectionLine);  
        connectionLine = nullptr; 
    }

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
        
        if(tempPin->getPinType() != m_pinType)
            continue;

        if(tempPin->getDirection() == m_direction)
            continue;

        ConnectionLine* line = new ConnectionLine(this, tempPin);
                    
        if(tempPin->getLine())
            scene()->removeItem(tempPin->getLine());
            tempPin->setLine(nullptr);
        
        setLine(line);
        tempPin->setLine(line);
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

