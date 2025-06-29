#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include "Pin.h"
#include "nodetypes/DataPin.h"
#include "nodetypes/ExecutionPin.h"





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

    ExecutionPin* getInputExecutionPin(){return inputExecPin;};
    ExecutionPin* getOutputExecutionPin(){return outputExecPin;};
    
    //virtual void execute() = 0;

private:
    QColor nodeColor;
    ExecutionPin* inputExecPin;
    ExecutionPin* outputExecPin;

    std::vector<DataPin*> inputPins;
    std::vector<DataPin*> outputPins;
};