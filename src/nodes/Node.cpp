#include "Node.h"
#include <QDebug>
#include "ConnectionLine.h"

Node::Node() : nodeColor("#09122C"), headerColor("#872341")
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF Node::boundingRect() const {
    return QRectF(-10, -10, 120, minHeaderHeight+minBodyHeight);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {

    QRectF fullRect = boundingRect();

    QRectF headerRect(fullRect.left(), fullRect.top(), fullRect.width(), minHeaderHeight);

    QRectF bodyRect = QRectF(fullRect.left(), fullRect.top() + minHeaderHeight, fullRect.width(), fullRect.height() - minHeaderHeight);

    painter->setPen(Qt::black);
    painter->setBrush(nodeColor);
    painter->drawRoundedRect(fullRect, 10, 10);

    painter->setBrush(headerColor);
    painter->setPen(Qt::black);

    painter->drawRect(headerRect);  

   
    painter->setPen(Qt::white);
    painter->drawText(headerRect, Qt::AlignCenter, getNodeName());
}

void Node::addInputExecutionPin()
{
    QRectF rect = boundingRect();
    ExecutionPin* inputPin = new ExecutionPin(Pin::Direction::Input, this);
    
    QPointF leftUpperCorner(rect.left(), rect.center().y() - rect.height()/2);
    leftUpperCorner.setX((inputPin->boundingRect().width()/2) + leftUpperCorner.x());
    leftUpperCorner.setY((inputPin->boundingRect().height()/2) + leftUpperCorner.y() + minHeaderHeight + 3);
    inputPin->setPos(leftUpperCorner);
    inputExecPin = inputPin;
}

void Node::addOutputExecutionPin()
{
    QRectF rect = boundingRect();
    ExecutionPin* outputPin = new ExecutionPin(Pin::Direction::Output, this);
    QPointF rightUpperCorner(rect.right(), rect.center().y() - rect.height()/2);
    rightUpperCorner.setX(rightUpperCorner.x() - (outputPin->boundingRect().width()/2));
    rightUpperCorner.setY((outputPin->boundingRect().height()/2) + rightUpperCorner.y() + minHeaderHeight + 3);
    outputPin->setPos(rightUpperCorner);
    outputExecPin = outputPin;
}

void Node::addInputPins(const std::vector<QString>& names, const std::vector<DataType>& types)
{
    const int spacing = 20;
    QRectF rect = boundingRect();
    
    QPointF startPos;
    if (inputExecPin) {
        
        startPos = inputExecPin->pos();
        startPos.setY(startPos.y() + inputExecPin->boundingRect().height() + 5);
       
    } else {
        
        startPos = QPointF(rect.left(), rect.top());
        startPos.setX(startPos.x() + 10); 
        startPos.setY(startPos.y() + minHeaderHeight + 10);
        
    }

    for (int i = 0; i < types.size(); ++i)
    {
        DataPin* pin = new DataPin(names[i], types[i], 5.0f, Pin::Direction::Input, this);        
        qreal x = startPos.x();
        qreal y = startPos.y() + i * spacing;

        pin->setPos(x, y);
        inputPins.push_back(pin);

        QGraphicsTextItem* label = new QGraphicsTextItem(names[i], this);
        label->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
        label->setDefaultTextColor(Qt::white); 
        label->setPos(x + pin->boundingRect().width() + 0.1, y - label->boundingRect().height() / 2);
    }
}

void Node::addOutputPins(const std::vector<QString>& names, const std::vector<DataType>& types)
{
    const int spacing = 20;
    QRectF rect = boundingRect();

    QPointF startPos;
    if (outputExecPin) {
        startPos = outputExecPin->pos();
        startPos.setY(startPos.y() + outputExecPin->boundingRect().height() + 5);
    } else {
        startPos = QPointF(rect.right(), rect.top());
        startPos.setX(startPos.x() - 10); 
        startPos.setY(startPos.y() + minHeaderHeight + 10); 
    }

    for (int i = 0; i < types.size(); ++i)
    {
        DataPin* pin = new DataPin(names[i], types[i], 0.0f, Pin::Direction::Output, this);        
        qreal x = startPos.x();
        qreal y = startPos.y() + i * spacing;

        pin->setPos(x, y);
        outputPins.push_back(pin);

        QGraphicsTextItem* label = new QGraphicsTextItem(names[i], this);
        label->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
        label->setDefaultTextColor(Qt::white); 
        label->setPos(x - pin->boundingRect().width() - label->boundingRect().width(), y - label->boundingRect().height() / 2);
    }
}


void Node::drawHeader()
{
    getNodeName(); 
}

 
    

