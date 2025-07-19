#include "SumNode.h"
#include "../../ConnectionLine.h"



SumNode::SumNode() : Node()
{
    addInputExecutionPin();
    addOutputExecutionPin();
    setupPins();
    
}

void SumNode::setupPins()
{

     std::vector<QString> inputNames = {
        "a",
        "b"
    };

    std::vector<DataType> inputTypes = {
        DataType::Float,
        DataType::Float
    };

    std::vector<DataPin::VariantType> inputDefaults = {
        1.0f,
        1.0f 
    };

    std::vector<QString> outputNames = {
        "sum"
    };

    std::vector<DataType> outputTypes = {
        DataType::Float,
    };

    std::vector<DataPin::VariantType> outputDefaults = {
        1.0f,
    };

    addInputPins(inputNames, inputTypes, inputDefaults);
    addOutputPins(outputNames, outputTypes, outputDefaults); 
}

void SumNode::executeImpl()
{
    auto val1 = inputPins[0]->getValue();
    auto val2 = inputPins[1]->getValue();
   
    if (std::holds_alternative<float>(val1) && std::holds_alternative<float>(val2))
    {
        float result = std::get<float>(val1) + std::get<float>(val2);
        outputPins[0]->setValue(result);
        qDebug() << result; 
        qDebug() << std::get<float>(val2); 
       /*
        auto outPin = outputPins[0];
        if (outPin)
        {
            auto line = outPin->getLine();
            if (line)
            {
                Pin* nextPin = line->getNextPin();
                if (auto tempPin = dynamic_cast<DataPin*>(nextPin))
                {
                    tempPin->setValue(result);
                }
            }
        }
    */
    }
}