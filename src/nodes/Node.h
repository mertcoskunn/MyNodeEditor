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
    void setActiveOutputExecutionPin(ExecutionPin* pin){ outputExecPin = pin; }; 

    virtual void setupPins() = 0; 
    void execute() {executeImpl(); setDirty(false);};
    virtual QString getNodeName() const { return "" ;};
    virtual void setNodeColor() const {return;};
    virtual void setHeaderColor() const {return;};

    bool isDirty() const {return dirty;};
    void setDirty(bool val) {dirty = val;};
    
     
protected:
    void addInputExecutionPin(int n = 1);
    void addOutputExecutionPin(int n = 1);
    void addInputPins(const std::vector<QString>& names, const std::vector<DataType>& types);
    void addOutputPins(const std::vector<QString>& names, const std::vector<DataType>& types);
    void drawHeader();
    
    virtual void executeImpl() = 0;

    void setActiveOutputExecnODE();

    QPointF getFirstInputPinPos();
    QPointF getFirstOutputPinPos();

    std::vector<ExecutionPin*> inputExecutionPins;
    std::vector<ExecutionPin*> outputExecutionPins;

    std::vector<DataPin*> inputPins;
    std::vector<DataPin*> outputPins;

private:
    QColor nodeColor;
    QColor headerColor; 
    ExecutionPin* inputExecPin = nullptr;
    ExecutionPin* outputExecPin = nullptr;

    float minHeaderHeight = 20.0f;
    float minBodyHeight = 80.0f;

    QPointF lastInputPinPos;
    QPointF lastOutputPinPos;
    bool dirty = true; 
};