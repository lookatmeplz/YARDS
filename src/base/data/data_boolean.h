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
    static shared_ptr<DataBoolean> const True;
    static shared_ptr<DataBoolean> const False;
    ~DataBoolean() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;
    int value();

}; // end of class DataBoolean
} // end of namespace base

#endif //YARDS_DATA_BOOLEAN_H
