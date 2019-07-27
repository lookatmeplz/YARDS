//
// Created by user on 2019-07-22.
//

#ifndef YARDS_DATA_STRING_H
#define YARDS_DATA_STRING_H

#include "data_object.h"

namespace base {
class DataString : public DataObject {
private:
    std::string val;
public:
    explicit DataString(std::string _val);
    ~DataString() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    std::string value();

}; // end of class DataString
} // end of namespace base

#endif //YARDS_DATA_STRING_H
