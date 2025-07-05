#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include "Pin.h"
#include "pintypes/DataPin.h"
#include "pintypes/ExecutionPin.h"

class Node :public QGraphicsItem 
{
      
public:
    Node();

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    //void execute(); 

    ExecutionPin* getInputExecutionPin(){return inputExecPin;};
    ExecutionPin* getOutputExecutionPin(){return outputExecPin;};

    virtual void setupPins() = 0; 
    virtual void execute() {return;};
    virtual QString getNodeName() const { return "" ;};
    virtual void setNodeColor() const {return;};
    virtual void setHeaderColor() const {return;}; 

protected:
    void addInputExecutionPin();
    void addOutputExecutionPin();
    void addInputPins(const std::vector<QString>& names, const std::vector<DataType>& types);
    void addOutputPins(const std::vector<QString>& names, const std::vector<DataType>& types);
    void drawHeader(); 

    std::vector<DataPin*> inputPins;
    std::vector<DataPin*> outputPins;

private:
    QColor nodeColor;
    QColor headerColor; 
    ExecutionPin* inputExecPin = nullptr;
    ExecutionPin* outputExecPin = nullptr;

    float minHeaderHeight = 20.0f;
    float minBodyHeight = 80.0f;
};