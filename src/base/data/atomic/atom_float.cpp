//
// Created by user on 2019-07-29.
//

#include "atom_float.h"

namespace base {

AtomicFloat::AtomicFloat(float _val) {
    val.store(_val);
}

AtomicFloat::~AtomicFloat() = default;;

int AtomicFloat::hash() {
    return (int)val*37;
}

float AtomicFloat::value() {
    return val;
}

DataType AtomicFloat::type() {
    return ATOMIC_FLOAT;
}

std::string AtomicFloat::str() {
    return std::to_string(val);
}

float AtomicFloat::set(float _val) {
    val = _val;
    return val;
}

}  // end of namespace base
