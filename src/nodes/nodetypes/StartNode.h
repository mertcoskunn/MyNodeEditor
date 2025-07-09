#pragma once

#include "../Node.h"


class StartNode : public Node
{
public: 
    StartNode();

    void setupPins() override;
    QString getNodeName() const override { return "Start"; };

protected:
    void executeImpl() override;
};