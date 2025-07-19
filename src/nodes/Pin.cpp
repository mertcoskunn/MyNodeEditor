#include "Pin.h"
#include <QDebug>
#include "ConnectionLine.h"
#include "pintypes/DataPin.h"
#include "Node.h"

Pin::Pin(QString name, PinType type, Direction direction, QGraphicsItem* parent)
    :QGraphicsObject(parent), m_pinType(type), m_direction(direction)
{
    pinName = name; 
    pinColor = Qt::cyan;
    setAcceptHoverEvents(true);
    owner = dynamic_cast<Node*>(parent); 
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

        if(m_pinType == PinType::Data)
        {
            DataPin* thisDataPin = dynamic_cast<DataPin*>(this);
            DataPin* otherDataPin = dynamic_cast<DataPin*>(tempPin);

            if (!thisDataPin || !otherDataPin)
                continue;

            if (thisDataPin->getDataType() != otherDataPin->getDataType())
                continue;
        }
            
        Pin *from;
        Pin *to;
        if(getDirection() == Direction::Output)
        {
            from = this;
            to = tempPin;
        }else{
            from = tempPin;
            to = this; 
        }
        ConnectionLine* line = new ConnectionLine(from, to);
                    
        if(tempPin->getLine() && tempPin->getDirection() == Direction::Input){
            scene()->removeItem(tempPin->getLine());
            tempPin->setLine(nullptr);
        }
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

QGraphicsTextItem* Pin::drawPinName(){
    QGraphicsTextItem* label = new QGraphicsTextItem(getName(), this);
    label->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
    label->setDefaultTextColor(Qt::white);
    return label; 
}

void Pin::setId(QString id)
{
    pinId = id; 
}