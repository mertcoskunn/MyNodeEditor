#pragma once

#include "../Node.h"



class MultiplyNode : public Node
{
public:
    MultiplyNode();

    void setupPins() override;
    QString getNodeName() const override { return "Multiply"; };

protected:
    void executeImpl() override;

};