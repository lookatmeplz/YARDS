//
// Created by user on 2019-07-16.
//

#include "dictionary.h"

namespace base {

const int Dictionary::DEFAULT_SIZE = 16;

Dictionary::Dictionary(int _s)
  : _size(_s),
    _count(0) {

    auto deleter = [](unique_ptr<Node>* p){delete[] p;};
    shared_ptr<unique_ptr<Node>> d(new unique_ptr<Node>[_size], deleter);
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
                case INTEGER: {
                    auto *p1 = static_cast<DataInt *>(cur->key().get());
                    auto *p2 = static_cast<DataInt *>(_key.get());
                    if (p1->value() == p2->value())
                        return cur;

                    break;
                }
                case FLOAT: {
                    auto *p1 = static_cast<DataFloat *>(cur->key().get());
                    auto *p2 = static_cast<DataFloat *>(_key.get());
                    if (p1->value() == p2->value())
                        return cur;

                    break;
                }
                case BOOLEAN:{
                    auto *p1 = static_cast<DataBoolean *>(cur->key().get());
                    auto *p2 = static_cast<DataBoolean *>(_key.get());
                    if (p1->value() == p2->value())
                        return cur;

                    break;
                }
                case STRING:{
                    auto *p1 = static_cast<DataString *>(cur->key().get());
                    auto *p2 = static_cast<DataString *>(_key.get());
                    if (p1->value() == p2->value())
                        return cur;

                    break;
                }
                case LIST:
                case DICT:
                    return nullptr;
                case TUPLE: {
                    auto *p1 = static_cast<Tuple *>(cur->key().get());
                    auto *p2 = static_cast<Tuple *>(_key.get());
                    int len = p1->size();
                    if (len != p2->size())
                        continue;
                    for (int i = 0; i < len; ++i) {
                        // TODO: Should check Tuple
                    }
                    break;
                }
            }
        }
        cur = cur->next();
    }

    return nullptr;
}

/**
 * Set key-value in dictionary
 * @param _key key mapped value
 * @param _val value to store
 * @return value to check
 */
shared_ptr<DataObject> Dictionary::set(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val) {
    if (_count >= 0.8 * _size)
        resize(2*_size);

    int index = _key->hash() % _size;

    if (!dict.get()[index]) {
        unique_ptr<Node> ptr(new Node(_key, _val));
        dict.get()[index] = std::move(ptr);
        ++_count;

        return _val;
    }

    Node * cur = has_same_key(_key, index);
    if (cur) {
        cur->set_val(_val);
        return _val;
    }

    unique_ptr<Node> ptr(new Node(_key, _val));

    dict.get()[index]->set_prev(ptr.get());
    ptr->set_next(std::move(dict.get()[index]));
    dict.get()[index] = std::move(ptr);
    ++_count;

    return _val;
}

/**
 * Append key-value in dictionary if value is already in dictionary it wrapped by list
 * @param _key key mapped value
 * @param _val value to store
 * @return value to check
 */
shared_ptr<DataObject> Dictionary::append(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val) {
    if (_count >= 0.8 * _size)
        resize(2*_size);

    int index = _key->hash() % _size;

    if (!dict.get()[index]) {
        unique_ptr<Node> ptr(new Node(_key, _val));
        dict.get()[index] = std::move(ptr);
        ++_count;

        return _val;
    }

    Node * cur = has_same_key(_key, index);
    if (cur) {
        if (cur->val()->type() == LIST) {
            auto *list = static_cast<List *>(cur->val().get());
            list->append(_val);
        } else {
            shared_ptr<List> p(new List());
            p->append(cur->val());
            p->append(_val);
            cur->set_val(p);
        }

        return cur->val();
    }

    unique_ptr<Node> ptr(new Node(_key, _val));

    dict.get()[index]->set_prev(ptr.get());
    ptr->set_next(std::move(dict.get()[index]));
    dict.get()[index] = std::move(ptr);
    ++_count;

    return _val;
}

/**
 * Get value of dictionary with same key
 * @param _key key to get in dictionary
 * @return value in dictionary
 */
shared_ptr<DataObject> Dictionary::get(const shared_ptr<DataObject>& _key) {
    int index = _key->hash() % _size;

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
    if (_count < 0.2 * _size)
        resize(_size/2);

    int index = _key->hash() % _size;
    shared_ptr<DataObject> ptr;

    if (dict.get()[index]) {
        Node * cur = has_same_key(_key, index);
        if (cur) {
            Node* prev = cur->prev();
            if (prev) {
                cur->next()->set_prev(prev);
                prev->set_next(cur->del());
            } else
                dict.get()[index] = cur->del();

            return cur->val();
        }
    }

    return ptr;
}

/**
 * Resize dictionary
 * @param _size size for resize
 */
void Dictionary::resize(int _s) {
    auto deleter = [](unique_ptr<Node> *p) {delete[] p;};
    shared_ptr<unique_ptr<Node>> d(new unique_ptr<Node>[_s], deleter);

    if (d) {
        for (int i = 0; i < _size; ++i) {
            while (dict.get()[i]) {
                int new_index = dict.get()[i]->key()->hash() % _s;
                if (!d.get()[new_index]) {
                    d.get()[new_index] = std::move(dict.get()[i]);
                    dict.get()[i] = d.get()[new_index]->del();
                } else {
                    unique_ptr<Node> ptr = std::move(dict.get()[i]);
                    d.get()[new_index]->set_prev(ptr.get());
                    dict.get()[i] = ptr->del();
                    ptr->set_next(std::move(d.get()[new_index]));
                    d.get()[new_index] = std::move(ptr);
                }
            }
        }

        for (int i = 0; i < _s; ++i)
            if (d.get()[i])
                d.get()[i]->set_prev(nullptr);
        
        dict = std::move(d);
        _size = _s;
    }
}

int Dictionary::hash() {
    return -1;
}

DataType Dictionary::type() {
    return DICT;
}

std::string Dictionary::str() {
    std::string str = "{";
    for (int i = 0; i < _size; ++i) {
        Node * cur = dict.get()[i].get();
        while (cur) {
            str += cur->key()->str();
            str += ": ";
            str += cur->val()->str();
            str += ", ";
            cur = cur->next();
        }
    }
    str += "}";
    return str;
}

int Dictionary::size() {
    return _size;
}

int Dictionary::count() {
    return _count;
}

shared_ptr<Node*> Dictionary::get_all() {
    auto deleter = [](Node** p){delete[] p;};
    shared_ptr<Node*> d(new Node*[_count], deleter);
    int index = 0;
    for (int i = 0; i < _size; ++i) {
        Node * cur = dict.get()[i].get();
        while (cur) {
            d.get()[index++] = cur;
            cur = cur->next();
        }
    }
    return d;
}


} // end of namespace base
