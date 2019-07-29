//
// Created by user on 2019-07-29.
//

#ifndef YARDS_ATOM_INT_H
#define YARDS_ATOM_INT_H

#include <atomic>
#include "../data_object.h"

namespace base {
using namespace std;
class AtomicInt : public DataObject {
private:
    atomic<int> val;
public:
    explicit AtomicInt(int _val);
    ~AtomicInt() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    int value();

}; // end of class AtomicInt
} // end of namespace base

#endif //YARDS_ATOM_INT_H
