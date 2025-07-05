#pragma once

#include "../Node.h"


class StartNode : public Node
{
public: 
    StartNode();

    void setupPins() override;
    void execute() override;
    QString getNodeName() const override { return "Start"; }; 
};