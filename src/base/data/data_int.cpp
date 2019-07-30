//
// Created by user on 2019-07-17.
//

#include "data_int.h"

namespace base {

DataInt::DataInt(int _val)
  : val(_val) {}

DataInt::~DataInt() = default;;

int DataInt::hash() {
    int hash = val*97;
    return hash >= 0 ? hash : -hash;
}

int DataInt::value() {
    return val;
}

DataType DataInt::type() {
    return INTEGER;
}

std::string DataInt::str() {
    return std::to_string(val);
}

}  // end of namespace base
