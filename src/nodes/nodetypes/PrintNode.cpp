#include "PrintNode.h"



PrintNode::PrintNode() : Node()
{
    addInputExecutionPin();
    addOutputExecutionPin();
    setupPins();
    
}



void PrintNode::setupPins()
{

    std::vector<QString> inputNames = {
        "x",
    };

    std::vector<DataType> inputs = {
        DataType::Float
    };

    std::vector<DataPin::VariantType> inputDefaults = {
        ""
    };

    addInputPins(inputNames, inputs, inputDefaults);
}


void PrintNode::executeImpl()
{
    auto val1 = inputPins[0]->getValue();
   
    if (std::holds_alternative<float>(val1))
    {
        float result = std::get<float>(val1); 
        qDebug()<< result; 
    }
    
}

