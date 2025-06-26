#include "Node.h"
#include <QDebug>

Node::Node() : nodeColor("#471396")
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);

    addExecutionPins();
    addInputPins();
    addOutputPins();

     
}

QRectF Node::boundingRect() const {
    return QRectF(-10, -10, 120, 80);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(Qt::black);
    painter->setBrush( nodeColor);
    painter->drawRoundedRect(boundingRect(), 10, 10);
}

void Node::addExecutionPins()
{
    QRectF rect = boundingRect();
    Pin* inputPin = new Pin(Pin::PinType::Exectution, Pin::Direction::Input, this);
    
    QPointF leftUpperCorner(rect.left(), rect.center().y() - rect.height()/2);
    leftUpperCorner.setX((inputPin->getWidth()/2) + leftUpperCorner.x());
    leftUpperCorner.setY((inputPin->getHeight()/2) + leftUpperCorner.y());
    inputPin->setPos(leftUpperCorner);
    inputExecPin = inputPin;

    Pin* outputPin = new Pin(Pin::PinType::Exectution, Pin::Direction::Output, this);
    QPointF rightUpperCorner(rect.right(), rect.center().y() - rect.height()/2);
    rightUpperCorner.setX(rightUpperCorner.x() - (outputPin->getWidth()/2));
    rightUpperCorner.setY((outputPin->getHeight()/2) + rightUpperCorner.y());
    outputPin->setPos(rightUpperCorner);
    outputExecPin = outputPin;
}


/// Bu bitmedi devam ettttttttt, for loop yanlış
void Node::addInputPins()
{
    QRectF rect = boundingRect();
    float topMargin = 25.0f;

    Pin* tempPin = new Pin(Pin::PinType::Data, Pin::Direction::Input, this);
    QPointF leftUpperCorner(rect.left(), rect.center().y() - rect.height()/2);
    leftUpperCorner.setX((tempPin->getWidth()/2) + leftUpperCorner.x());
    leftUpperCorner.setY((tempPin->getHeight()/2) + leftUpperCorner.y() + topMargin);
    tempPin->setPos(leftUpperCorner);
    //leftUpperCorner.setX((tempPin->getWidth()/2) + leftUpperCorner.x());
    //leftUpperCorner.setY((tempPin->getHeight()/2) + leftUpperCorner.y());
    inputPins.push_back(tempPin); 


    for(int i=0; i<2; i++)
    {
        Pin* tempPin = new Pin(Pin::PinType::Data, Pin::Direction::Input, this);
        leftUpperCorner.setY(leftUpperCorner.y() + topMargin);
        tempPin->setPos(leftUpperCorner);
        inputPins.push_back(tempPin);
    }

}

void Node::addOutputPins()
{
    QRectF rect = boundingRect();
    float topMargin = 25.0f;

    Pin* tempPin = new Pin(Pin::PinType::Data, Pin::Direction::Output, this);
    QPointF rightUpperCorner(rect.right(), rect.center().y() - rect.height()/2);
    rightUpperCorner.setX(rightUpperCorner.x()-(tempPin->getWidth()/2));
    rightUpperCorner.setY((tempPin->getHeight()/2) + rightUpperCorner.y() + topMargin);
    tempPin->setPos(rightUpperCorner);
    outputPins.push_back(tempPin);
    //leftUpperCorner.setX((tempPin->getWidth()/2) + leftUpperCorner.x());
    //leftUpperCorner.setY((tempPin->getHeight()/2) + leftUpperCorner.y());
    
    for(int i=0; i<2; i++)
    {
        Pin* tempPin = new Pin(Pin::PinType::Data, Pin::Direction::Output, this);
        rightUpperCorner.setY(rightUpperCorner.y() + topMargin);
        tempPin->setPos(rightUpperCorner);
        outputPins.push_back(tempPin);
    }

}

void Node::execute()
{

    for (int i=0; i<inputPins.size(); i++) {

        outputPins[i]->setValue(inputPins[i]->getValue()*2);
        if(outputPins[i]->getLine())
            outputPins[i]->getLine()->getNextPin()->setValue(outputPins[i]->getValue());
        
        qDebug() <<  outputPins[i]->getValue();
    }
    
}
