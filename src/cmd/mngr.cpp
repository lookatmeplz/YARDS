//
// Created by user on 2019-07-28.
//

#include <string>
#include "mngr.h"

namespace cmd {

/**
 * set manager
 */
Mngr::Mngr() {
    dod = new Dictionary();
}

/**
 * set dict of db
 * @param d set to dict of db
 */
void Mngr::setDod(Dictionary *d) {
    dod = d;
}

/**
 * parse and execute query
 * @param u user who requested the query
 * @param cmd query to execute
 */
void Mngr::queryHandler(shared_ptr<User> u, std::string cmd) {

    tuple<ParserResultType , vector<shared_ptr<DataObject>>> re = Parser::parse(cmd);
    // TODO: handle the parse result
}

} // end of namespace cmd