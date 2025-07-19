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

    std::vector<DataType> inputTypes = {
        DataType::Boolean
    };

    std::vector<DataPin::VariantType> inputDefaults = {
        false
    };


    addInputPins(inputNames, inputTypes, inputDefaults);
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

