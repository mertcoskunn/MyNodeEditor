#pragma once

#include "../Node.h"



class SubtractionNode : public Node
{
public:
    SubtractionNode();

    void setupPins() override;
    QString getNodeName() const override { return "Subtract"; };

protected:
    void executeImpl() override;

};