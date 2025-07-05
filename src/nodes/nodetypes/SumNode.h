#pragma once

#include "../Node.h"



class SumNode : public Node
{
public:
    SumNode();

    void setupPins() override;
    void execute() override; 
    QString getNodeName() const override { return "Sum"; }; 

};