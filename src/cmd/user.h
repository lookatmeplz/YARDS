//
// Created by user on 2019-07-28.
//

#ifndef YARDS_USER_H
#define YARDS_USER_H

#include <string>

namespace cmd {

class User {
private:
    int user_fd;
    std::string db_name;

public:
    User(int fd);
    void setDB(std::string name);
};

} // end of namespace cmd

#endif //YARDS_USER_H
