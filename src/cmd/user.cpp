//
// Created by user on 2019-07-28.
//

#include "user.h"

namespace cmd {

/**
 * set user
 * @param fd client fd
 */
User::User(int fd) {
    user_fd = fd;
}

/**
 * set db to be used by user
 * @param name selected db name
 */
void User::setDB(std::string name) {
    db_name = name;
}

} // end of namespace cmd