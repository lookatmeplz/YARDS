//
// Created by user on 2019-07-17.
//

#ifndef YARDS_DATA_INT_H
#define YARDS_DATA_INT_H

#include "data_object.h"

namespace base {
class DataInt : public DataObject {
private:
    int val;
    const base::DataType _type;
public:
    explicit DataInt(int _val);
    ~DataInt() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    int value();

}; // end of class DataInt
} // end of namespace base

#endif //YARDS_DATA_INT_H
