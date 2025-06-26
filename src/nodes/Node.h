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
    
    void addExecutionPins();
    void addInputPins();
    void addOutputPins();

    void execute(); 

    Pin* getOutputExecutionPin(){return outputExecPin;};
    //virtual void execute() = 0;

private:
    QColor nodeColor;
    Pin* inputExecPin;
    Pin* outputExecPin;

    std::vector<Pin*> inputPins;
    std::vector<Pin*> outputPins;
};