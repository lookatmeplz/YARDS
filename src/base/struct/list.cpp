//
// Created by user on 2019-07-26.
//

#include "list.h"

namespace base {
const int List::DEFAULT_SIZE = 16;

List::List(int _size)
  : size(_size),
    count(0) {

    auto deleter = [](shared_ptr<DataObject>* p){delete[] p;};
    shared_ptr<shared_ptr<DataObject>> l(new shared_ptr<DataObject>[size], deleter);
    list = std::move(l);
}

List::List() : List(DEFAULT_SIZE) {}

List::~List() = default;

shared_ptr<DataObject> List::set(int index, const shared_ptr<DataObject> &_val) {
    if (index >= count)
        return nullptr;

    list.get()[index] = _val;
    return list.get()[index];
}

shared_ptr<DataObject> List::append(const shared_ptr<DataObject> &_val) {
    if (count >= size)
        resize(2*size);

    list.get()[count++] = _val;
    ++count;

    return _val;
}

shared_ptr<DataObject> List::get(int index) {
    if (index >= count)
        return nullptr;

    return list.get()[index];
}

shared_ptr<DataObject> List::del(int index) {
    if (index >= count)
        return nullptr;

    shared_ptr<DataObject> ptr = std::move(list.get()[index]);
    for (int i = index+1; i < size; ++i)
        list.get()[i-1] = std::move(list.get()[i]);
    --count;

    if (count < size/4)
        resize(size/2);
    return ptr;
}

void List::resize(int _size) {
    auto deleter = [](shared_ptr<DataObject> *p) {delete[] p;};
    shared_ptr<shared_ptr<DataObject>> l(new shared_ptr<DataObject>[_size], deleter);

    int min = _size <= count ? _size : count;
    if (l) {
        for (int i = 0; i < min; ++i)
            l.get()[i] = std::move(list.get()[i]);

        list = std::move(l);
        size = _size;
    }
}

int List::hash() {
    return -1;
}

base::DataType List::type() {
    return LIST;
}

std::string List::str() {
    std::string str = "[";
    for (int i = 0; i < count; ++i) {
        str += list.get()[i]->str();
        str += ", ";
    }
    str += "]";
    return str;
}

}
