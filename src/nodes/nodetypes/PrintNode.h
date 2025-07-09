#pragma once

#include "../Node.h"


class PrintNode : public Node
{
public: 
    PrintNode();

    void setupPins() override;
    QString getNodeName() const override { return "Print"; };

protected:
    void executeImpl() override;
};