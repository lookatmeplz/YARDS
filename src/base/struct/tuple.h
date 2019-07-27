//
// Created by user on 2019-07-26.
//

#ifndef YARDS_TUPLE_H
#define YARDS_TUPLE_H

#include "../data/data_object.h"

namespace base {
using std::shared_ptr;
using std::unique_ptr;
class Tuple : public DataObject {
private:
    int size;
    shared_ptr<unique_ptr<DataObject>> tuple;

public:
    explicit Tuple(shared_ptr<unique_ptr<DataObject>>& _tuple, int _size);
    ~Tuple() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;
}; // end of class Tuple
} // end of namespace base

#endif //YARDS_TUPLE_H
