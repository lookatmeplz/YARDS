//
// Created by user on 2019-07-28.
//

#include "parser.h"
#include <iterator>
#include <sstream>
#include <algorithm>
#include <map>
#include <iostream>

namespace cmd {

using namespace std;

/**
 * parse the query
 * @param cmd query to parsed
 * @return instruction type, arguments
 */
tuple<ParserResultType , vector<shared_ptr<DataObject>>> Parser::parse(string cmd) {
    map<char, char>m;
    m.insert(make_pair('\'', '\''));
    m.insert(make_pair('\"', '\"'));
    m.insert(make_pair('{', '}'));
    m.insert(make_pair('[', ']'));
    m.insert(make_pair('(', ')'));

    vector<string> wordsVector;
    int begin = 0;
    int end = 0;

    for (int i=0; i<cmd.size(); i++) {
        char token;
        if (cmd[i] == '\'' || cmd[i] == '\"' || cmd[i] == '{' || cmd[i] == '[' || cmd[i] == '(') {
            token = m[cmd[i]];
            begin = i;
            for (int j=i+1; j<cmd.size(); j++) {
                if (cmd[j] == token) {
                    end = j-begin+1;
                    wordsVector.push_back(cmd.substr(begin, end));
                    begin += end;
                    i = j;
                    break;
                }
            }
        } else if (cmd[i] != ' ') {
            begin = i;
            for (int j=i+1; j<cmd.size(); j++) {
                if (cmd[j] == ' ') {
                    i = j;
                    break;
                }
                end = j-begin+1;
            }
            wordsVector.push_back(cmd.substr(begin, end));
            begin += end;
        }
    }

    ParserResultType op;
    vector<shared_ptr<DataObject>> desc;

    transform(wordsVector[0].begin(), wordsVector[0].end(), wordsVector[0].begin(), ::tolower);
    if (wordsVector[0] == "set") {
        op = SET;
        desc.push_back(createData(wordsVector[1]));
        desc.push_back(createData(wordsVector[2]));
    }

    return make_tuple(op, desc);
}

/**
 * create data object for the type
 * @param raw data to be created as an object
 * @return data object for raw
 */
shared_ptr<DataObject> Parser::createData(string raw) {
    shared_ptr<DataObject> data;

    DataType dt;
    switch (maybeType(raw[0])) {
        case STRING:
            if (isString(raw)) {
                data = make_shared<DataString>(raw);
            }
            break;
        case INTEGER:
            if (isInt(raw)) {
                data = make_shared<DataInt>(std::strtol(raw.c_str(), 0, 10));
            } else if (isFloat(raw)) {
                data = make_shared<DataFloat>(std::strtod(raw.c_str(), 0));
            }
            break;
        case BOOLEAN:
            if (isBool(raw)) {
                if (raw[1] == 'T' || raw[1] == 't') {
                    data = DataBoolean::True;
                } else if (raw[1] == 'F' || raw[1] == 'f') {
                    data = DataBoolean::False;
                }
            }
        case DICT:
            if (isDict(raw)) {
                // TODO: create dict object
            }
        case LIST:
            if (isList(raw)) {
                // TODO: create list object
            }
        case TUPLE:
            if (isTuple(raw)) {
                // TODO: create tuple object
            }
    }

    return data;
}

/**
 * classify types
 * @param ch the first character
 * @return possible data type
 */
DataType Parser::maybeType(char ch) {
    if (ch == '\'' || ch == '\"') {
        return STRING;
    } else if (ch == '{') {
        return DICT;
    } else if (ch == '[') {
        return LIST;
    } else if (ch == '(') {
        return TUPLE;
    } else if (ch == '/') {
        return BOOLEAN;
    } else {
        return INTEGER;
    }
}

/**
 * valid string check
 * @param raw data
 * @return is valid
 */
bool Parser::isString(string raw) {
    char token;

    if (raw[0] == '\'' || raw[0] == '\"') {
        token = raw[0];
    } else {
        return false;
    }

    for (int i=1; i<raw.size()-1; i++) {
        if (raw[i] == token) {
            if (raw[i-1] != '\\') {
                return false;
            }
        }
    }

    return true;
}

/**
 * valid integer check
 * @param raw data
 * @return is valid
 */
bool Parser::isInt(string raw) {
    for (char i : raw) {
        if (!isdigit(i)) {
            return false;
        }
    }

    return true;
}

/**
 * valid float check
 * @param raw data
 * @return is valid
 */
bool Parser::isFloat(string raw) {
    bool dot = false;

    for (int i=0; i<raw.size(); i++) {
        if (!isdigit(raw[i])) {
            if (i>0 && raw[i] == '.' && !dot) {
                dot = true;
                continue;
            } else {
                return false;
            }
        }
    }

    return true;
}

/**
 * valid boolean check
 * @param raw data
 * @return is valid
 */
bool Parser::isBool(string raw) {
    if (raw.size() != 2) {
        return false;
    }

    if (raw[0] == '/') {
        if (raw[1] == 'T' || raw[1] == 't' || raw[1] == 'F' || raw[1] == 'f') {
            return true;
        }
    }

    return false;
}

/**
 * valid dictionary check
 * @param raw data
 * @return is valid
 */
bool Parser::isDict(string raw) {
    if (raw.front() != '{' || raw.back() != '}') {
        return false;
    }

    // TODO: check valid dict format
}

/**
 * valid list check
 * @param raw data
 * @return is valid
 */
bool Parser::isList(std::string raw) {
    if (raw.front() != '[' || raw.back() != ']') {
        return false;
    }

    // TODO: check valid list format
}

/**
 * valid tuple check
 * @param raw data
 * @return is valid
 */
bool Parser::isTuple(std::string raw) {
    if (raw.front() != '(' || raw.back() != ')') {
        return false;
    }

    // TODO: check valid tuple format
}

} // end of namespace cmd