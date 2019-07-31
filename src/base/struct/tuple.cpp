//
// Created by user on 2019-07-26.
//

#include "tuple.h"

namespace base {

Tuple::Tuple(shared_ptr<shared_ptr<DataObject>> _tuple, int _s)
  : _size(_s) {
    tuple = std::move(_tuple);
}

Tuple::~Tuple() = default;

int Tuple::hash() {
    int hash = 0;
    for (int i = 0; i < _size; ++i) {
        int t = tuple.get()[i]->hash();
        if (t < 0)
            return -1;

        hash += t * 191;
    }

    return hash;
}

base::DataType Tuple::type() {
    return TUPLE;
}

std::string Tuple::str() {
    std::string str = "(";
    for (int i = 0; i < _size; ++i) {
        str += tuple.get()[i]->str();
        str += ", ";
    }
    str += ")";
    return str;
}

shared_ptr<DataObject> Tuple::get(int index) {
    if (index >= _size)
        return nullptr;

    return tuple.get()[index];
}

int Tuple::size() {
    return _size;
}

} // end of namespace base
