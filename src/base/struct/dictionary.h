//
// Created by user on 2019-07-16.
//

#ifndef YARDS_DICTIONARY_H
#define YARDS_DICTIONARY_H

#include "../data/data_object.h"
#include "../data/data_int.h"
#include "../data/data_float.h"
#include "../data/data_string.h"
#include "../data/data_boolean.h"

#include "node.h"

namespace base {

using std::shared_ptr;
using std::unique_ptr;

class Dictionary : public DataObject {
private:
    static const int DEFAULT_SIZE;

    int size;
    int count;

    shared_ptr<unique_ptr<Node>> dict;

    Node* has_same_key(const shared_ptr<DataObject> &_key, int index);
    void resize(int _size);

public:
    explicit Dictionary(int _size);
    Dictionary();
    ~Dictionary() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    shared_ptr<DataObject> set(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val);
    shared_ptr<DataObject> append(const shared_ptr<DataObject>& _key, const shared_ptr<DataObject>& _val);
    shared_ptr<DataObject> get(const shared_ptr<DataObject>& _key);
    shared_ptr<DataObject> del(const shared_ptr<DataObject>& _key);

}; // end of class Dictionary
} // end of namespace base


#endif //YARDS_DICTIONARY_H
