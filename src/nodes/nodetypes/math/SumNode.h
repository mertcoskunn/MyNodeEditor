#pragma once

#include "../../Node.h"



class SumNode : public Node
{
public:
    SumNode();

    void setupPins() override;
    QString getNodeName() const override { return "Sum"; };

protected:
    void executeImpl() override;

};