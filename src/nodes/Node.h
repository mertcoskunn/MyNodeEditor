#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include "Pin.h"


class Node : public QGraphicsItem 
{
public:
    Node();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    //virtual void execute() = 0;

private:
    QColor nodeColor;
    Pin* inputExecPin;
    Pin* outputExecPin;
};