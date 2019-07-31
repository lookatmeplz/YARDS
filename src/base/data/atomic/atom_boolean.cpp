//
// Created by user on 2019-07-29.
//

#include "atom_boolean.h"
namespace base {

AtomicBoolean::AtomicBoolean(int _val) {
    val.store(_val != 0);
}

AtomicBoolean::~AtomicBoolean() = default;

int AtomicBoolean::hash() {
    return val*17;
}

int AtomicBoolean::value() {
    return val;
}

DataType AtomicBoolean::type() {
    return ATOMIC_BOOLEAN;
}

std::string AtomicBoolean::str() {
    return std::to_string(val);
}

} // end of namespace base
