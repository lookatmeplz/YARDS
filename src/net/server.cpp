//
// Created by user on 2019-07-22.
//

#include "server.h"

#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <thread>
#include <unistd.h>

#define MAX_BUF_SIZE 0x1000

namespace net {

using namespace cmd;

const std::string Server::DEFAULT_IP_ADDR = "127.0.0.1";
const int Server::DEFAULT_PORT = 5001;

/**
 * set server
 * @param ip set to server ip
 * @param port set to server port
 */
Server::Server(std::string ip, int port)
  : serv_ip(std::move(ip)),
    serv_port(port),
    is_run(false) {
}

/**
 * set manager
 * @param m set to manager
 */
void Server::setMngr(cmd::Mngr *m) {
    mngr = m;
}

/**
 * start server
 * accept client and handle using thread
 */
void Server::start() {
    create();

    int csock = 0;

    std::vector<std::unique_ptr<std::thread>> threads;

    do {
        if ((csock = getAccept()) != -1) {
            threads.emplace_back(new std::thread(socketHandler, this, csock));
        }
    } while ( is_run );
}

/**
 * stop server
 */
void Server::stop() {
    close(serv_sock);
    is_run = false;
}

/**
 * get state of server
 * @return running state
 */
bool Server::isRun() {
    return is_run;
}

/**
 * Create server
 */
void Server::create() {
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    serv_addr.sin_addr.s_addr = inet_addr(serv_ip.c_str()); //INADDR_ANY;

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (serv_sock == -1) {
        std::cerr << "socket() Error!" << std::endl;
        exit(1);
    }

    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        std::cerr << "bind() Error!" << std::endl;
        exit(1);
    }

    if (listen(serv_sock, SOMAXCONN) == -1) {
        std::cerr << "listen() Error!" << std::endl;
        exit(1);
    }

    is_run = true;
    std::cout << "Done." << std::endl;
}

/**
 * connect with client
 */
int Server::getAccept() {
    socklen_t size;
    int accept_sock = accept(serv_sock, (sockaddr*)&clnt_addr, &size);
    printf("IP : %s, Port : %d\n", inet_ntoa(clnt_addr.sin_addr), clnt_addr.sin_port);
    return accept_sock;
}

/**
 * recv and process requests from clients
 * @param csock client socket
 */
void Server::socketHandler(Server *server, int csock) {
    shared_ptr<User> u = make_shared<User>(csock);
    do {
        std::vector<char> buffer(MAX_BUF_SIZE);
        std::string rcv;

        int recv_len = 0;
        if ((recv_len = recv(csock, &buffer[0], buffer.size(), 0)) == -1) {
            printf("recv() Error, disconnect Client fd %d\n", csock);
            break;
        }

        if (recv_len == 0) continue;

        rcv.append( buffer.cbegin(), buffer.cbegin()+recv_len );

        server->mngr->queryHandler(u, rcv);

        // TODO: send the result of query

    } while ( server->isRun() );

    close(csock);
}

} // end of namespace net