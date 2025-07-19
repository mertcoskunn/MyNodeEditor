#include "Node.h"
#include <QDebug>
#include "ConnectionLine.h"
#include "../core/DataType.h"

int Node::nextId = 0;


Node::Node() : id(nextId++), nodeColor("#09122C"), headerColor("#872341")
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);
}

QRectF Node::boundingRect() const {
    return QRectF(-10, -10, 150, minHeaderHeight+minBodyHeight);
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
    lastInputPinPos = getFirstInputPinPos();
    QString pinId = QString("%1_%2_%3_%4").arg(getId()).arg("execution").arg("input").arg(0);
    ExecutionPin* inputPin = new ExecutionPin("", Pin::Direction::Input, this);
    inputPin->setId(pinId);
    inputPin->setPos(lastInputPinPos);
    inputExecPin = inputPin;
    inputExecutionPins.push_back(inputExecPin);

    for(int i=1; i<n; i++){
        QString pinId = QString("%1_%2_%3_%4").arg(getId()).arg("execution").arg("input").arg(i);
        ExecutionPin* inputPin = new ExecutionPin("", Pin::Direction::Input, this);
        inputPin->setId(pinId);
        lastInputPinPos.setY(lastInputPinPos.y() + 3 + (inputPin->boundingRect().height()));
        inputPin->setPos(lastInputPinPos);
        inputExecPin = inputPin; 
        inputExecutionPins.push_back(inputPin); 
    }
}

void Node::addOutputExecutionPin(int n )
{
    lastOutputPinPos = getFirstOutputPinPos();
    QString pinId = QString("%1_%2_%3_%4").arg(getId()).arg("execution").arg("output").arg(0);
    ExecutionPin* outputPin = new ExecutionPin("", Pin::Direction::Output, this);
    outputPin->setId(pinId);
    outputPin->setPos(lastOutputPinPos);
    outputExecPin = outputPin; 
    outputExecutionPins.push_back(outputPin);

    for(int i=1; i<n; i++){
        QString pinId = QString("%1_%2_%3_%4").arg(getId()).arg("execution").arg("output").arg(i);
        ExecutionPin* outputPin = new ExecutionPin("", Pin::Direction::Output, this);
        outputPin->setId(pinId);
        lastOutputPinPos.setY(lastOutputPinPos.y() + 3 + (outputPin->boundingRect().height()));
        outputPin->setPos(lastOutputPinPos);
        outputExecPin = outputPin; 
        outputExecutionPins.push_back(outputPin); 
    }
    
}

void Node::addInputPins(const std::vector<QString>& names, const std::vector<DataType>& types, const std::vector<DataPin::VariantType>& defaultVals)
{
    const int spacing = 20;
    QRectF rect = boundingRect();
    
    QPointF startPos = lastInputPinPos;
    if (!inputExecPin) {
        lastInputPinPos = getFirstInputPinPos();   
    } 
    
    for (int i = 0; i < types.size(); ++i)
    {
        QString pinId = QString("%1_%2_%3_%4").arg(getId()).arg("data").arg("input").arg(i);
        DataPin* pin = new DataPin(names[i], types[i], defaultVals[i], Pin::Direction::Input, this);
        pin->setId(pinId);         
        lastInputPinPos.setY(lastInputPinPos.y() + spacing);
        pin->setPos(lastInputPinPos);
        inputPins.push_back(pin);
    }
}

void Node::addOutputPins(const std::vector<QString>& names, const std::vector<DataType>& types, const std::vector<DataPin::VariantType>& defaultVals)
{
    const int spacing = 20;
    QRectF rect = boundingRect();

    
    if (!outputExecPin) {
        lastOutputPinPos = getFirstOutputPinPos();
    }

    for (int i = 0; i < types.size(); ++i)
    {
        QString pinId = QString("%1_%2_%3_%4").arg(getId()).arg("data").arg("output").arg(i);
        DataPin* pin = new DataPin(names[i], types[i], defaultVals[i], Pin::Direction::Output, this); 
        pin->setId(pinId);        
        lastOutputPinPos.setY(lastOutputPinPos.y() + spacing);
        pin->setPos(lastOutputPinPos);
        outputPins.push_back(pin);
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

std::vector<Pin*> Node::getAllPins() const {

    std::vector<Pin*> allPins;
    allPins.insert(allPins.end(), inputExecutionPins.begin(), inputExecutionPins.end());
    allPins.insert(allPins.end(), outputExecutionPins.begin(), outputExecutionPins.end());
    allPins.insert(allPins.end(), inputPins.begin(), inputPins.end());
    allPins.insert(allPins.end(), outputPins.begin(), outputPins.end());

    return allPins;
}


std::vector<Pin*> Node::getInputPins() const {

    std::vector<Pin*> inputs;
    inputs.insert(inputs.end(), inputExecutionPins.begin(), inputExecutionPins.end());
    inputs.insert(inputs.end(), inputPins.begin(), inputPins.end());

    return inputs;
}


std::vector<Pin*> Node::getOutputPins() const {

    std::vector<Pin*> outputs;
    outputs.insert(outputs.end(), outputExecutionPins.begin(), outputExecutionPins.end());
    outputs.insert(outputs.end(), outputPins.begin(), outputPins.end());

    return outputs;
}
