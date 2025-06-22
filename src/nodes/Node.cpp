#include "Node.h"
#include <QDebug>

Node::Node() : nodeColor("#471396")
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);

    Pin* inputPin = new Pin(this);
    QRectF inputRect = boundingRect();
    QPointF leftCenter(inputRect.left(), inputRect.center().y());
    leftCenter.setX((inputPin->getWidth()/2) + leftCenter.x());
    inputPin->setPos(leftCenter);
    inputExecPin = inputPin;

    Pin* outputPin = new Pin(this);
    QRectF outputRect = boundingRect();
    QPointF rightCenter(outputRect.right(), outputRect.center().y());
    rightCenter.setX(rightCenter.x() - (outputPin->getWidth()/2));
    outputPin->setPos(rightCenter);
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
