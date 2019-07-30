//
// Created by user on 2019-07-28.
//

#ifndef YARDS_PARSER_H
#define YARDS_PARSER_H

#include <tuple>
#include <vector>
#include <memory>
#include <map>
#include "../base/data/data_object.h"
#include "../base/data/data_string.h"
#include "../base/data/data_int.h"
#include "../base/data/data_float.h"
#include "../base/data/data_boolean.h"
#include "../base/struct/dictionary.h"
#include "../base/struct/list.h"
#include "../base/struct/tuple.h"
#include "parser_result.h"

namespace cmd {

using namespace std;
using namespace base;

namespace Parser {
    static map<char, char> m;

    void init();
    tuple<ParserResultType , vector<shared_ptr<DataObject>>> parse(string cmd);
    shared_ptr<DataObject> createData(string raw);
    DataType maybeType(char ch);
    bool isString(string raw);
    bool isInt(const string& raw);
    bool isFloat(string raw);
    bool isBool(string raw);
    bool isDict(string raw);
    bool isList(string raw);
    bool isTuple(string raw);
};

} // end of namespace cmd

#endif //YARDS_PARSER_H
