//
// Created by user on 2019-07-29.
//

#ifndef YARDS_ATOM_FLOAT_H
#define YARDS_ATOM_FLOAT_H

#include <atomic>
#include "../data_object.h"

namespace base {
using namespace std;
class AtomicFloat : public DataObject {
private:
    atomic<float> val;
public:
    explicit AtomicFloat(float _val);
    ~AtomicFloat() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    float value();

}; // end of class AtomicFloat
} // end of namespace base

#endif //YARDS_ATOM_FLOAT_H
