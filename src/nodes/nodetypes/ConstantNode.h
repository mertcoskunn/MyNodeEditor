#pragma once

#include "../Node.h"
#include <QLineEdit>
#include <QGraphicsProxyWidget>


class ConstantNode : public Node
{
public: 
    ConstantNode();

    void setupPins() override;
    void execute() override;
    QString getNodeName() const override { return "Constant"; };

private:    
    void setupInputBox();
    QLineEdit* inputBox = nullptr;
    QGraphicsProxyWidget* proxy = nullptr;

    QString pinName = ""; 
};