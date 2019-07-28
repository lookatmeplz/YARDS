//
// Created by user on 2019-07-28.
//

#ifndef YARDS_MNGR_H
#define YARDS_MNGR_H

#include "../base/struct/dictionary.h"
#include "parser.h"
#include "user.h"
#include "parser_result.h"

namespace cmd {

using namespace base;

class Mngr {

private:
    Dictionary *dod;

public:
    Mngr();
    void setDod(Dictionary *d);
    void queryHandler(shared_ptr<User> u, std::string);
};

} // end of namespace cmd


#endif //YARDS_MNGR_H
