#include "ConnectionLine.h"
#include "Pin.h"

ConnectionLine::ConnectionLine(Pin* from, Pin* to)
    : startPin(from), endPin(to)
{
    setPen(QPen(Qt::darkGreen, 2));
    updateLine();
    
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ConnectionLine::updateLine);
    timer->start(16);
}


void ConnectionLine::updateLine() {
    if (startPin && endPin) {
        
        QPointF p1 = startPin->mapToScene(startPin->getTriangleCenter());
        QPointF p2 = endPin->mapToScene(endPin->getTriangleCenter());
        
        setLine(QLineF(p1, p2));
    }
}