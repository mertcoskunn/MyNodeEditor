#pragma once

#include "../Node.h"


class PrintNode : public Node
{
public: 
    PrintNode();

    void setupPins() override;
    void execute() override;
    QString getNodeName() const override { return "Print"; }; 
};