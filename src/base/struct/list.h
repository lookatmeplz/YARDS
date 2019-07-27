//
// Created by user on 2019-07-26.
//

#ifndef YARDS_LIST_H
#define YARDS_LIST_H

#include "../data/data_object.h"

namespace base {
using std::shared_ptr;
using std::unique_ptr;
class List : public DataObject {
private:
    static const int DEFAULT_SIZE;

    int size;
    int count;

    shared_ptr<shared_ptr<DataObject>> list;

    void resize(int _size);

public:
    explicit List(int _size);
    List();
    ~List() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    shared_ptr<DataObject> set(int index, const shared_ptr<DataObject>& _val);
    shared_ptr<DataObject> append(const shared_ptr<DataObject>& _val);
    shared_ptr<DataObject> get(int index);
    shared_ptr<DataObject> del(int index);

}; // end of class List
} // end of namespace base

#endif //YARDS_LIST_H
