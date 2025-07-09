#pragma once

#include "../../Node.h"



class DivisionNode : public Node
{
public:
    DivisionNode();

    void setupPins() override;
    QString getNodeName() const override { return "Division"; };

protected:
    void executeImpl() override;

};