//
// Created by user on 2019-07-29.
//

#ifndef YARDS_ATOM_BOOLEAN_H
#define YARDS_ATOM_BOOLEAN_H

#include <atomic>
#include "../data_object.h"

namespace base {
using namespace std;
class AtomicBoolean : public DataObject {
private:
    atomic<bool> val;
public:
    explicit AtomicBoolean(int _val);
    ~AtomicBoolean() override;
    int hash() override;
    base::DataType type() override;
    std::string str() override;

    int value();
    // Todo: Should be implemented not op
}; // end of class AtomicBoolean
} // end of namespace base

#endif //YARDS_ATOM_BOOLEAN_H
