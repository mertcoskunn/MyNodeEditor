#include "Node.h"
#include <QDebug>

Node::Node()
{
    setFlags(ItemIsMovable | ItemIsSelectable);
    setAcceptHoverEvents(true);
}


QRectF Node::boundingRect() const {
    return QRectF(-10, -10, 120, 80);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(Qt::black);
    painter->setBrush(isSelected() ? Qt::yellow : Qt::lightGray);
    painter->drawRect(boundingRect());
}
