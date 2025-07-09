#pragma once

#include "../Node.h"


class BranchNode : public Node
{
public: 
    BranchNode();

    void setupPins() override;
    QString getNodeName() const override { return "Branch"; };

protected:
    void executeImpl() override;
};