//
// Created by user on 2019-07-22.
//

#ifndef YARDS_DATA_FLOAT_H
#define YARDS_DATA_FLOAT_H

#include "data_object.h"

namespace base {
class DataFloat : public DataObject {
private:
    float val;
public:
    explicit DataFloat(float _val);
    ~DataFloat() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    float value();

    float set(float _val);

    float add(float _val);
    float mul(float _val);

}; // end of class DataFloat
} // end of namespace base

#endif //YARDS_DATA_FLOAT_H
