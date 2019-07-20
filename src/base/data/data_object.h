//
// Created by user on 2019-07-16.
//

#ifndef YARDS_DATA_OBJECT_H
#define YARDS_DATA_OBJECT_H
#include <string>

#include "data_type.h"

namespace base {
class DataObject {
public:
    virtual ~DataObject() = default;
    virtual int hash() = 0;
    virtual base::DataType type() = 0;
    virtual std::string str() = 0;
};
}  // end of namespace base

#endif //YARDS_DATA_OBJECT_H
