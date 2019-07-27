//
// Created by user on 2019-07-22.
//

#include "client.h"

#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <unistd.h>

#define MAX_BUF_SIZE 0x1000

namespace net {

const std::string Client::DEFAULT_IP_ADDR = "127.0.0.1";
const int Client::DEFAULT_PORT = 5001;

/**
 * set client
 * @param ip set to server ip
 * @param port set to server port
 */
Client::Client(std::string ip, int port)
  : serv_ip(std::move(ip)),
    serv_port(port),
    is_conn(false) {

}

/**
 * connect to server
 * @return connection successful
 */
bool Client::conn() {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == -1) {
        std::cerr << "socket() Error!" << std::endl;
        return false;
    }

    clnt_addr.sin_family = AF_INET;
    clnt_addr.sin_addr.s_addr = inet_addr(serv_ip.c_str());
    clnt_addr.sin_port = htons(serv_port);

    if (connect(sock, (struct sockaddr *) &clnt_addr, sizeof(clnt_addr)) == -1) {
        std::cerr << "connect() Error!" << std::endl;
        return false;
    }

    is_conn = true;

    return true;
}

void Client::disconn() {
    is_conn = false;
    close(sock);
}

bool Client::isConn() {
    return is_conn;
}

/**
 * query to db
 * @param command query to request to db
 * @return result of query
 */
std::string Client::query(std::string command) {
    if (!is_conn) {
        return std::string("Server connection is required.");
    }

    if (send(sock, command.c_str(), command.size(), 0) == -1) {
        return std::string("send() Error!");
    }

    std::vector<char> buffer(MAX_BUF_SIZE);
    std::string rcv;

    int recv_len = 0;
    if ((recv_len = recv(sock, &buffer[0], buffer.size(), 0)) == -1) {
        return std::string("recv() Error!");
    }

    rcv.append( buffer.begin(), buffer.begin()+recv_len );

    return rcv;
}

} // end of namespace net