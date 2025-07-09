#include "BranchNode.h"



BranchNode::BranchNode() : Node()
{
    addInputExecutionPin();
    addOutputExecutionPin(2);
    setupPins();
    
}



void BranchNode::setupPins()
{

    std::vector<QString> inputNames = {
        "x",
    };

    std::vector<DataType> inputs = {
        DataType::Boolean
    };
    addInputPins(inputNames, inputs);
}


void BranchNode::executeImpl()
{
    auto val1 = inputPins[0]->getValue();
   
    if (std::holds_alternative<bool>(val1))
    {
        
        bool val = std::get<bool>(val1); 
        qDebug()<< val;
        if(val)
            setActiveOutputExecutionPin(outputExecutionPins[0]); 
        else
            setActiveOutputExecutionPin(outputExecutionPins[1]); 
    }
    
}

