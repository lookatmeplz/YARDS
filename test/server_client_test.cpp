//
// Created by user on 2019-07-27.
//

#include <thread>
#include "gtest/gtest.h"

#include "../src/net/server.h"
#include "../src/net/client.h"

namespace {
using namespace std;
using namespace net;

TEST(ServerClientTest, server_test) {
    Server *s = new Server();

    std::vector<std::unique_ptr<std::thread>> threads;
    threads.emplace_back(new std::thread([s]{ s->start(); }));

    sleep(1);

    EXPECT_EQ(s->isRun(), true);

    s->stop();
    sleep(1);

    EXPECT_EQ(s->isRun(), false);

    threads[0]->join();
    delete s;
}

TEST(ServerClientTest, client_test) {
    Server *s = new Server();

    std::vector<std::unique_ptr<std::thread>> threads;
    threads.emplace_back(new std::thread([s]{ s->start(); }));

    sleep(1);
    EXPECT_EQ(s->isRun(), true);

    Client *c = new Client();
    c->conn();
    EXPECT_EQ(c->isConn(), true);

    c->disconn();
    EXPECT_EQ(c->isConn(), false);

    s->stop();

    threads[0]->join();
    delete s;
    delete c;
}

}