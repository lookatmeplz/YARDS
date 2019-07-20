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

    auto deleter = [](unique_ptr<Node>* p){delete[] p;};
    shared_ptr<unique_ptr<Node>> d(new unique_ptr<Node>[size], deleter);
    dict = std::move(d);
}

Dictionary::~Dictionary() = default;

Dictionary::Dictionary() : Dictionary(DEFAULT_SIZE) {}

/**
 * Check _key has same key in dictionary
 * @param _key key to check
 * @param index index of dictionary
 * @return whether _key has same key or not
 */
Node* Dictionary::has_same_key(const shared_ptr<DataObject> &_key, int index) {
    Node * cur = dict.get()[index].get();
    while (cur) {
        if (cur->key()->type() == _key->type()) {
            switch (cur->key()->type()) {
                case INTEGER:
                    auto* p1 = static_cast<DataInt *>(cur->key().get());
                    auto* p2 = static_cast<DataInt *>(_key.get());
                    if (p1->value() == p2->value()) {
                        return cur;
                    }
                    break;
            }
        }
        cur = cur->next();
    }

    return nullptr;
}

/**
 * Set key-value in dictionary
 * @param _key
 * @param _val
 * @return
 */
shared_ptr<DataObject> Dictionary::set(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val) {
    int index = _key->hash() % size;

    if (!dict.get()[index]) {
        std::unique_ptr<Node> ptr(new Node(_key, _val));
        dict.get()[index] = std::move(ptr);
        ++count;

        return _val;
    }

    Node * cur = has_same_key(_key, index);
    if (cur) {
        cur->set_val(_val);
        return _val;
    }

    std::unique_ptr<Node> ptr(new Node(_key, _val));
    ptr->set_next(dict.get()[index]);
    dict.get()[index] = std::move(ptr);
    ++count;

    return _val;
}

shared_ptr<DataObject> Dictionary::add(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val) {
    int index = _key->hash() % size;

    if (!dict.get()[index]) {
        std::unique_ptr<Node> ptr(new Node(_key, _val));
        dict.get()[index] = std::move(ptr);
        ++count;

        return _val;
    }

    Node * cur = has_same_key(_key, index);
    if (cur) {
        // TODO : Add value to List
        return nullptr;
    }

    std::unique_ptr<Node> ptr(new Node(_key, _val));
    ptr->set_next(dict.get()[index]);
    dict.get()[index] = std::move(ptr);
    ++count;

    return _val;
}

/**
 * Get value of dictionary with same key
 * @param _key key to get in dictionary
 * @return value in dictionary
 */
shared_ptr<DataObject> Dictionary::get(const shared_ptr<DataObject>& _key) {
    int index = _key->hash() % size;

    if (dict.get()[index]) {
        Node * cur = has_same_key(_key, index);
        if (cur)
            return cur->val();
    }

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

    if (dict.get()[index]) {
        Node * cur = has_same_key(_key, index);
        if (cur) {
            return cur->val();
        }
    }

    return ptr;
}

void Dictionary::resize() {
    // TODO: Should be implemented !
}

} // end of namespace base
