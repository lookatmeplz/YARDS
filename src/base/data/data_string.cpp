//
// Created by user on 2019-07-22.
//

#include "data_string.h"

namespace base {

DataString::DataString(std::string _val)
        : val(std::move(_val)) {}

DataString::~DataString() = default;;

int DataString::hash() {
    int hash = 0;
    for (char& c : val) {
        hash += hash * 31 + c;
    }
    return hash >= 0 ? hash : -hash;
}

std::string DataString::value() {
    return val;
}

DataType DataString::type() {
    return STRING;
}

std::string DataString::str() {
    return val;
}

}  // end of namespace base
