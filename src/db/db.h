//
// Created by user on 2019-07-31.
//

#ifndef YARDS_DB_H
#define YARDS_DB_H

#include <string>
#include <fstream>

#include "../base/data/atomic/atom_boolean.h"
#include "../base/data/atomic/atom_int.h"
#include "../base/data/atomic/atom_float.h"
#include "../base/data/data_object.h"
#include "../base/data/data_int.h"
#include "../base/data/data_float.h"
#include "../base/data/data_string.h"
#include "../base/data/data_boolean.h"

#include "../base/struct/list.h"
#include "../base/struct/tuple.h"
#include "../base/struct/node.h"
#include "../base/struct/dictionary.h"


namespace db {
using namespace std;
using namespace base;

void dump(shared_ptr<DataObject> object);
void serialize(ofstream& out, shared_ptr<DataObject>& object);
shared_ptr<DataObject> deserialize(ifstream& in);
shared_ptr<DataObject> load(string name);

}

#endif //YARDS_DB_H
