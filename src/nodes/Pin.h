#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QPolygonF>
#include <QColor>

class Pin: public  QGraphicsItem
{
public:
    Pin(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    float getWidth(){ return width; };
    float getHeight(){ return height; };

private:
    QPolygonF pinPolygon;
    QColor pinColor;
    float width = 20.0;
    float height = 20.0; 
};