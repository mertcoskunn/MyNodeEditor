#include "ConstantNode.h"


ConstantNode::ConstantNode() : Node()
{
    setupPins();
}



void ConstantNode::setupPins()
{

    std::vector<QString> inputNames = {
        "" 
    };

    std::vector<DataType> inputTypes = {
        DataType::Float    
    };

    std::vector<QString> outputNames = {
        "" 
    };

    std::vector<DataType> outputTypes = {
        DataType::Float
    };
    addInputPins(inputNames, inputTypes); 
    addOutputPins(outputNames, outputTypes); 
}

void ConstantNode::executeImpl()
{
    qDebug() << "constant node execute calisti";
    outputPins[0]->setValue(inputPins[0]->getValue());
}

