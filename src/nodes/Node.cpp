#include "Node.h"
#include <QDebug>
#include "ConnectionLine.h"
#include "../core/DataType.h"

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

void Node::addInputExecutionPin(int n)
{
    ExecutionPin* inputPin = new ExecutionPin(Pin::Direction::Input, this);
    
    inputPin->setPos(getFirstInputPinPos());
    lastInputPinPos = getFirstInputPinPos(); 
    inputExecPin = inputPin;
}

void Node::addOutputExecutionPin(int n )
{
    lastOutputPinPos = getFirstOutputPinPos();

    for(int i=0; i<n; i++){
        ExecutionPin* outputPin = new ExecutionPin(Pin::Direction::Output, this);
        
        outputPin->setPos(lastOutputPinPos);
        lastOutputPinPos.setY(lastOutputPinPos.y() + 3 + (outputPin->boundingRect().height()));
        outputExecPin = outputPin; 
        outputExecutionPins.push_back(outputPin); 
    }
    
}

void Node::addInputPins(const std::vector<QString>& names, const std::vector<DataType>& types)
{
    const int spacing = 20;
    QRectF rect = boundingRect();
    
    QPointF startPos = lastInputPinPos;
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
        DataPin *pin; 
        if(types[i] == DataType::Boolean){
            pin = new DataPin(names[i], types[i], false, Pin::Direction::Input, this);
        }else{
            pin = new DataPin(names[i], types[i], 5.0f, Pin::Direction::Input, this);
        }
        
        qreal x = lastInputPinPos.x();
        qreal y = lastInputPinPos.y() + spacing;

        pin->setPos(x, y);
        inputPins.push_back(pin);
        lastInputPinPos = QPointF(x, y);

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

    
    if (!outputExecPin) {
        lastOutputPinPos = getFirstOutputPinPos();
    }

    for (int i = 0; i < types.size(); ++i)
    {
        DataPin* pin = new DataPin(names[i], types[i], 0.0f, Pin::Direction::Output, this);        
        lastOutputPinPos.setY(lastOutputPinPos.y() + spacing);

        pin->setPos(lastOutputPinPos);
        outputPins.push_back(pin);

        QGraphicsTextItem* label = new QGraphicsTextItem(names[i], this);
        label->setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
        label->setDefaultTextColor(Qt::white); 
        label->setPos(lastOutputPinPos.x() - pin->boundingRect().width() - label->boundingRect().width(), lastOutputPinPos.y() - label->boundingRect().height() / 2);
    }
}


void Node::drawHeader()
{
    getNodeName(); 
}

QPointF Node::getFirstInputPinPos()
{
    QRectF rect = boundingRect();
    QPointF leftUpperCorner(rect.left(), rect.center().y() - rect.height()/2);
    leftUpperCorner.setX(10 + leftUpperCorner.x());
    leftUpperCorner.setY(10 + leftUpperCorner.y() + minHeaderHeight + 3);

    return leftUpperCorner;
}

QPointF Node::getFirstOutputPinPos()
{
    QRectF rect = boundingRect();
    QPointF rightUpperCorner(rect.right(), rect.center().y() - rect.height()/2);
    rightUpperCorner.setX(rightUpperCorner.x() - 10);
    rightUpperCorner.setY(10 + rightUpperCorner.y() + minHeaderHeight + 3);

    return rightUpperCorner;
}

