//
// Created by user on 2019-07-31.
//

#include "data_type.h"

namespace base {

int get_obj_size(DataType type) {
    switch (type) {
        case INTEGER:
        case FLOAT:
        case STRING:
        case ATOMIC_INTEGER:
        case ATOMIC_FLOAT:
        case ATOMIC_BOOLEAN:
            return 16 - 8; // -8 is VTable Size
        case BOOLEAN:
            return sizeof(int); // 0 or 1 (int)
        case LIST:
        case TUPLE:
        case DICT:
            return 32 - 8; // -8 is VTable Size
        default:
            return 0;
    }
}

}
