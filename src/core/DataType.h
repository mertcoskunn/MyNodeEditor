#pragma once

#include <QString>

enum class DataType {
    Integer,
    Float,
    Boolean,
    String
};


inline QString dataTypeToString(DataType type)
{
    switch(type) {
        case DataType::Integer : return "Integer";
        case DataType::Float : return "Float";
        case DataType::Boolean : return "Boolean";
        case DataType::String :  return "String";
    }
    return "Unknown"; 
}
