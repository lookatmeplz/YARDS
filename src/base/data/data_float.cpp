//
// Created by user on 2019-07-22.
//

#include "data_float.h"

namespace base {

DataFloat::DataFloat(float _val)
        : val(_val) {}

DataFloat::~DataFloat() = default;;

int DataFloat::hash() {
    return (int)val*37;
}

float DataFloat::value() {
    return val;
}

DataType DataFloat::type() {
    return FLOAT;
}

std::string DataFloat::str() {
    return std::to_string(val);
}

}  // end of namespace base
