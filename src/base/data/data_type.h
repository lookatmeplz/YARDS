//
// Created by user on 2019-07-16.
//

#ifndef YARDS_DATA_TYPE_H
#define YARDS_DATA_TYPE_H

namespace base {
enum DataType {
    // Primitive Data Type
    INTEGER,
    FLOAT,
    BOOLEAN,
    STRING,

    // Atomic Type
    ATOMIC_INTEGER,
    ATOMIC_FLOAT,
    ATOMIC_BOOLEAN,

    // Structure
    LIST,
    TUPLE,
    DICT,
}; // end of enum DataType

int get_obj_size(DataType type);

} // end of namespace base

#endif //YARDS_DATA_TYPE_H
