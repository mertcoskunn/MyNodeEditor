#include "Node.h"
#include <QDebug>

Node::Node() : nodeColor("#471396")
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);

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

QRectF Node::boundingRect() const {
    return QRectF(-10, -10, 120, 80);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(Qt::black);
    painter->setBrush( nodeColor);
    painter->drawRoundedRect(boundingRect(), 10, 10);
}
