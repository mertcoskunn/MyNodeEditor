#pragma once

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QPolygonF>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsLineItem>
#include <QObject>

class ConnectionLine;
class Node; 

class Pin: public  QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };
    enum class Direction { Input, Output};
    Q_ENUM(Direction)

    // burası opsiyonel olabilirr
    enum class PinType { Exectution, Data};
    Q_ENUM(PinType)

    Pin(QString name, PinType type, Direction direction, QGraphicsItem* parent = nullptr );
    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override = 0;


    Direction getDirection(){ return m_direction; };
    PinType getPinType(){ return m_pinType; };
    virtual void setLine(ConnectionLine* line){ connectionLine = line; }; 
    ConnectionLine* getLine(){ return connectionLine; };
    int type() const override { return Type; }; 
    Node* getOwner(){return owner;};
    QString getName() const {return pinName;};
    void setId(QString id); 
    QString getId(){return pinId;}; 
    
    QGraphicsTextItem* drawPinName(); 

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    PinType m_pinType;
    Direction m_direction;
    

private:
    QColor pinColor;
    QString pinName = "";
    QString pinId = "";
    ConnectionLine* connectionLine = nullptr;
    QGraphicsLineItem* tempLine = nullptr;
    Node* owner = nullptr; 
};