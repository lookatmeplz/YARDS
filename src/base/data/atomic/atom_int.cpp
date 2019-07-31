//
// Created by user on 2019-07-29.
//

#include "atom_int.h"

namespace base {

AtomicInt::AtomicInt(int _val) {
    val.store(_val);
}

AtomicInt::~AtomicInt() = default;

int AtomicInt::hash() {
    int hash = val*97;
    return hash >= 0 ? hash : -hash;
}

int AtomicInt::value() {
    return val;
}

DataType AtomicInt::type() {
    return ATOMIC_INTEGER;
}

std::string AtomicInt::str() {
    return std::to_string(val);
}

int AtomicInt::set(int _val) {
    val.store(_val);
    return val;
}

int AtomicInt::add(int _val) {
    val.fetch_add(_val);
    return val;
}

} // end of namespace base
