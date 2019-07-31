//
// Created by user on 2019-07-28.
//

#include "parser.h"
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace cmd {

using namespace std;

void parser::init() {
    m.insert(make_pair('\'', '\''));
    m.insert(make_pair('\"', '\"'));
    m.insert(make_pair('{', '}'));
    m.insert(make_pair('[', ']'));
    m.insert(make_pair('(', ')'));
}

/**
 * parse the query
 * @param cmd query to parsed
 * @return instruction type, arguments
 */
tuple<ParserResultType, vector<shared_ptr<DataObject>>> parser::parse(const string& cmd, char sep) {
    ParserResultType op;
    vector<shared_ptr<DataObject>> desc;
    vector<string> wordsVector = std::move(parseWithSep(cmd, sep));

    transform(wordsVector[0].begin(), wordsVector[0].end(), wordsVector[0].begin(), ::tolower);
    if (wordsVector[0] == "set") {
        if (wordsVector.size() != 3) {
            op = ERR;
        } else {
            op = SET;
            desc.push_back(createData(wordsVector[1]));
            desc.push_back(createData(wordsVector[2]));
        }
    } else {
        op = ERR;
    }

    return make_tuple(op, desc);
}

/**
 * parse the query with seperator
 * @param cmd query to parsed
 * @param sep seperator
 * @return seperated strings
 */
vector<string> parser::parseWithSep(const string& cmd, char sep) {
    vector<string> wordsVector;
    int begin = 0;
    int end = 0;

    for (int i=0; i<cmd.size(); i++) {
        char token;
        if (cmd[i] == '\'' || cmd[i] == '\"') {
            token = m[cmd[i]];
            if (end == 0) {
                begin = i;
                end = 1;
            }
            for (int j=i+1; j<cmd.size(); j++) {
                if (cmd[j] == token && cmd[j-1] != '\\') {
                    end = j-begin+1;
                    i = j;
                    break;
                }
            }
        } else if (cmd[i] == '{' || cmd[i] == '[' || cmd[i] == '(') {
            int cnt = 1;
            token = m[cmd[i]];
            if (end == 0) {
                begin = i;
                end = 1;
            }
            for (int j=i+1; j<cmd.size(); j++) {
                if (cmd[j] == token) {
                    cnt -= 1;
                    if (cnt == 0) {
                        end = j - begin + 1;
                        i = j;
                        break;
                    } else if (cnt < 0) {
                        vector<string> err;
                        return err;
                    }
                } else if (cmd[j] == cmd[i]) {
                    cnt += 1;
                }
            }
        } else if (cmd[i] == ' ' && end == 0) {
            continue;
        } else if (cmd[i] != sep) {
            if (end == 0) {
                begin = i;
                end = 1;
            }
            for (int j=i+1; j<cmd.size(); j++) {
                if (cmd[j] == sep) {
                    for (int k=begin; k<end; k++) {
                        if (cmd[k] == ' ') {
                            begin += 1;
                        } else {
                            break;
                        }
                    }
                    for (int k=begin+end-1; k>=begin; k--) {
                        if (cmd[k] == ' ') {
                            end -= 1;
                        } else {
                            break;
                        }
                    }
                    wordsVector.push_back(cmd.substr(begin, end));
                    end = 0;
                    i = j;
                    break;
                }
                end = j-begin+1;
            }
        } else if (cmd[i] == sep && end > 0) {
            for (int k=begin; k<end; k++) {
                if (cmd[k] == ' ') {
                    begin += 1;
                } else {
                    break;
                }
            }
            for (int k=begin+end-1; k>=begin; k--) {
                if (cmd[k] == ' ') {
                    end -= 1;
                } else {
                    break;
                }
            }
            wordsVector.push_back(cmd.substr(begin, end));
            end = 0;
        }
    }

    if (end > 0) {
        for (int k=begin; k<end; k++) {
            if (cmd[k] == ' ') {
                begin += 1;
            } else {
                break;
            }
        }
        for (int k=begin+end-1; k>=begin; k--) {
            if (cmd[k] == ' ') {
                end -= 1;
            } else {
                break;
            }
        }
        wordsVector.push_back(cmd.substr(begin, end));
    }

    return wordsVector;
}

/**
 * create data object for the type
 * @param raw data to be created as an object
 * @return data object for raw
 */
shared_ptr<DataObject> parser::createData(string raw) {

    switch (maybeType(raw[0])) {
        case STRING:
            if (isString(raw)) {
                shared_ptr<DataString> str_data = make_shared<DataString>(raw);
                return str_data;
            }
            break;
        case INTEGER:
            if (isInt(raw)) {
                shared_ptr<DataInt> int_data;
                int_data = make_shared<DataInt>(std::strtol(raw.c_str(), nullptr, 10));
                return int_data;
            } else if (isFloat(raw)) {
                shared_ptr<DataFloat> float_data;
                float_data = make_shared<DataFloat>(std::strtod(raw.c_str(), nullptr));
                return float_data;
            }
            break;
        case BOOLEAN:
            if (isBool(raw)) {
                shared_ptr<DataBoolean> bool_data;
                if (raw[1] == 'T' || raw[1] == 't') {
                    bool_data = DataBoolean::True;
                } else if (raw[1] == 'F' || raw[1] == 'f') {
                    bool_data = DataBoolean::False;
                }
                return bool_data;
            }
            break;
        case DICT:
            if (isDict(raw)) {
                shared_ptr<Dictionary> dict = make_shared<Dictionary>();
                raw = raw.substr(1, raw.size()-2);
                vector<string> blocks = parseWithSep(raw, ',');
                for (auto & block : blocks) {
                    vector<string> kv = parseWithSep(block, ':');
                    if (kv.size() != 2) {
                        return nullptr;
                    }
                    shared_ptr<DataObject> key = createData(kv[0]);
                    shared_ptr<DataObject> val = createData(kv[1]);
                    dict->set(key, val);
                }
                return dict;
            }
            break;
        case LIST:
            if (isList(raw)) {
                shared_ptr<List> list = make_shared<List>();
                raw = raw.substr(1, raw.size()-2);
                vector<string> blocks = parseWithSep(raw, ',');
                for (auto & block : blocks) {
                    list->append(createData(block));
                }
                return list;
            }
            break;
        case TUPLE:
            if (isTuple(raw)) {
                raw = raw.substr(1, raw.size()-2);
                vector<string> blocks = parseWithSep(raw, ',');
                shared_ptr<List> list = make_shared<List>();
                for (auto & block : blocks) {
                    list->append(createData(block));
                }
                shared_ptr<Tuple> tuple = make_shared<Tuple>(list->get(), list->size());
                return tuple;
            }
            break;
    }

    return nullptr;
}

/**
 * classify types
 * @param ch the first character
 * @return possible data type
 */
DataType parser::maybeType(char ch) {
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
bool parser::isString(string raw) {
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
bool parser::isInt(const string& raw) {
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
bool parser::isFloat(string raw) {
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
bool parser::isBool(string raw) {
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
bool parser::isDict(string raw) {
    if (raw.front() != '{' || raw.back() != '}') {
        return false;
    }

    return true;
}

/**
 * valid list check
 * @param raw data
 * @return is valid
 */
bool parser::isList(std::string raw) {
    if (raw.front() != '[' || raw.back() != ']') {
        return false;
    }

    return true;
}

/**
 * valid tuple check
 * @param raw data
 * @return is valid
 */
bool parser::isTuple(std::string raw) {
    if (raw.front() != '(' || raw.back() != ')') {
        return false;
    }

    return true;
}

} // end of namespace cmd
