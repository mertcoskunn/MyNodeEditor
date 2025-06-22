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


private:
    QColor nodeColor;
    Pin* inputExecPin;
    Pin* outputExecPin;
};