//
// Created by user on 2019-07-22.
//

#ifndef YARDS_SERVER_H
#define YARDS_SERVER_H

#include <netinet/in.h>
#include <string>

namespace net {

class Server {
protected:
    bool is_run;
    int serv_sock;
    sockaddr_in serv_addr, clnt_addr;
    int serv_port;
    std::string serv_ip;

    static const std::string DEFAULT_IP_ADDR;
    static const int DEFAULT_PORT;

    void create();
    int getAccept();
    static void socketHandler(Server *server, int csock);

public:
    explicit Server(std::string ip=DEFAULT_IP_ADDR, int port=DEFAULT_PORT);
    void start();
    void stop();
    bool isRun();
}; // end of class Server
} // end of namespace net

#endif //YARDS_SERVER_H
