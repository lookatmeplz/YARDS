//
// Created by user on 2019-07-28.
//

#ifndef YARDS_PARSER_RESULT_H
#define YARDS_PARSER_RESULT_H

namespace cmd {

enum ParserResultType{
    ERR,
    USE,
    SET,
    GET,
    DEL,
    ADD,
    SUB,
    MUL,
    DIV,
    APND,
    L2T,
};

} // end of namespace cmd

#endif //YARDS_PARSER_RESULT_H
