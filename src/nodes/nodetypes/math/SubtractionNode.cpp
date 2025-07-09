#include "SubtractionNode.h"
#include "../../ConnectionLine.h"



SubtractionNode::SubtractionNode() : Node()
{
    addInputExecutionPin();
    addOutputExecutionPin();
    setupPins();
    
}

void SubtractionNode::setupPins()
{

     std::vector<QString> inputNames = {
        "a",
        "b"
    };

    std::vector<DataType> inputTypes = {
        DataType::Float,
        DataType::Float
    };

    std::vector<QString> outputNames = {
        "result"
    };

    std::vector<DataType> outputTypes = {
        DataType::Float,
    };

    addInputPins(inputNames, inputTypes);
    addOutputPins(outputNames, outputTypes); 
}

void SubtractionNode::executeImpl()
{
    auto val1 = inputPins[0]->getValue();
    auto val2 = inputPins[1]->getValue();
   
    if (std::holds_alternative<float>(val1) && std::holds_alternative<float>(val2))
    {
        float result = std::get<float>(val1) - std::get<float>(val2);
        outputPins[0]->setValue(result);
        
    }
}