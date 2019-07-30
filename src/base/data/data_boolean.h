//
// Created by user on 2019-07-22.
//

#ifndef YARDS_DATA_BOOLEAN_H
#define YARDS_DATA_BOOLEAN_H
#include "data_object.h"

namespace base {
using namespace std;
class DataBoolean : public DataObject {
private:
    explicit DataBoolean(int _val);
    enum Type{
        FALSE = 0,
        TRUE = 1
    };

    Type val;
public:
    static const shared_ptr<DataBoolean> True;
    static const shared_ptr<DataBoolean> False;
    ~DataBoolean() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;
    int value();

    shared_ptr<const DataBoolean> not_op();
}; // end of class DataBoolean
} // end of namespace base

#endif //YARDS_DATA_BOOLEAN_H
