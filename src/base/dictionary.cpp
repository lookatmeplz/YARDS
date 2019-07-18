#include <memory>

//
// Created by user on 2019-07-16.
//

#include "dictionary.h"

namespace base {

const int Dictionary::DEFAULT_SIZE = 16;

Dictionary::Dictionary(int _size)
  : size(_size),
    count(0) {

    auto deleter = [](shared_ptr<DataObject>* p){delete[] p;};
    shared_ptr<shared_ptr<DataObject>> k(new shared_ptr<DataObject>[size], deleter);
    shared_ptr<shared_ptr<DataObject>> v(new shared_ptr<DataObject>[size], deleter);
    key = k;
    val = v;
}

Dictionary::~Dictionary() = default;

Dictionary::Dictionary() : Dictionary(DEFAULT_SIZE) {}

/**
 * Check _key has same key in dictionary
 * @param _key key to check
 * @param index index of dictionary
 * @return whether _key has same key or not
 */
bool Dictionary::has_same_key(const shared_ptr<DataObject> &_key, int index) {
    if (key.get()[index]->type() == _key->type()) {
        switch (key.get()[index]->type()) {
            case INTEGER:
                auto* p1 = static_cast<DataInt *>(key.get()[index].get());
                auto* p2 = static_cast<DataInt *>(_key.get());
                if (p1->value() == p2->value()) {
                    return true;
                }
                break;
        }
    }

    return false;
}

shared_ptr<DataObject> Dictionary::set(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val) {
    int index = _key->hash() % size;

    if (!key.get()[index] || has_same_key(_key, index)) {
        key.get()[index] = _key;
        val.get()[index] = _val;
        return _val;
    }

    // TODO : Need to save when conflict occur
    return nullptr;
}

shared_ptr<DataObject> Dictionary::add(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val) {
    int index = _key->hash() % size;

    if (!key.get()[index]) {
        key.get()[index] = _key;
        val.get()[index] = _val;
        return _val;
    }

    // TODO : Add value to List
    return nullptr;
}

/**
 * Get value of dictionary with same key
 * @param _key key to get in dictionary
 * @return value in dictionary
 */
shared_ptr<DataObject> Dictionary::get(const shared_ptr<DataObject>& _key) {
    int index = _key->hash() % size;

    if (key.get()[index] && has_same_key(_key, index))
        return val.get()[index];

    return nullptr;
}

/**
 * Delete key-value that matches the key in dictionary
 * @param _key key to delete in dictionary
 * @return value in dictionary
 */
shared_ptr<DataObject> Dictionary::del(const shared_ptr<DataObject>& _key) {
    int index = _key->hash() % size;
    shared_ptr<DataObject> ptr;

    if (key.get()[index] && has_same_key(_key, index)) {
        ptr = val.get()[index];
        key.get()[index] = nullptr;
        val.get()[index] = nullptr;
    }
    return ptr;
}

void Dictionary::resize() {
    // TODO: Should be implemented !
}

} // end of namespace base
