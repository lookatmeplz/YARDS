//
// Created by 김혁진 on 2019-07-20.
//

#ifndef YARDS_NODE_H
#define YARDS_NODE_H

#include "data/data_object.h"

namespace base {

using std::shared_ptr;
using std::unique_ptr;

class Node {
private:
    Node* _prev;
    unique_ptr<Node> _next;
    shared_ptr<DataObject> _key;
    shared_ptr<DataObject> _val;
public:
    explicit Node(shared_ptr <DataObject> _key, shared_ptr <DataObject> _val);
    ~Node();

    shared_ptr<DataObject> key();
    shared_ptr<DataObject> val();
    Node* prev();
    Node* next();

    void set_val(shared_ptr<DataObject> val);
    void set_next(unique_ptr<Node> _next);
    unique_ptr<Node> del();
};
}

#endif //YARDS_NODE_H
