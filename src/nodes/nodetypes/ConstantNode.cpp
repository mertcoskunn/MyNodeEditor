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

    std::vector<DataPin::VariantType> inputDefaults = {
        0.0f
    };

    std::vector<QString> outputNames = {
        "" 
    };

    std::vector<DataType> outputTypes = {
        DataType::Float
    };

    std::vector<DataPin::VariantType> outputDefaults = {
        0.0f
    };

    addInputPins(inputNames, inputTypes, inputDefaults); 
    addOutputPins(outputNames, outputTypes, outputDefaults); 
}

void ConstantNode::executeImpl()
{
    outputPins[0]->setValue(inputPins[0]->getValue());
}

