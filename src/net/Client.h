//
// Created by user on 2019-07-22.
//

#ifndef YARDS_CLIENT_H
#define YARDS_CLIENT_H

#include <cygwin/in.h>
#include <string>

namespace net {

class Client {
protected:
    int sock;
    sockaddr_in clnt_addr;
    std::string serv_ip;
    int serv_port;
    bool is_conn;

    static const std::string DEFAULT_IP_ADDR;
    static const int DEFAULT_PORT;

public:
    explicit Client(std::string ip=DEFAULT_IP_ADDR, int port=DEFAULT_PORT);
    bool conn();
    std::string query(std::string command);
}; // end of class client
} // end of namespace net

#endif //YARDS_CLIENT_H
