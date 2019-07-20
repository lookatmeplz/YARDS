#include <utility>

#include <utility>

//
// Created by 김혁진 on 2019-07-20.
//

#include "node.h"

namespace base {
Node::Node(shared_ptr<DataObject> _key, shared_ptr<DataObject> _val)
        : _key(std::move(_key)),
          _val(std::move(_val)),
          _prev(nullptr) {}

Node::~Node() {
    while (_next) {
        _next = std::move(_next->_next);
    }
}

shared_ptr<DataObject> Node::key() {
    return _key;
}

shared_ptr<DataObject> Node::val() {
    return _val;
}

void Node::set_next(unique_ptr<Node>& next) {
    _next->_prev = this;
    _next = std::move(next);
}

void Node::set_val(shared_ptr<DataObject> val) {
    _val = std::move(val);
}

Node* Node::prev() {
    return _prev;
}

Node* Node::next() {
    return _next.get();
}

void Node::del_next() {
    _next = std::move(_next->_next);
}

}