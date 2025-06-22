#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>


class Node : public QGraphicsItem 
{
public:
    Node();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

};