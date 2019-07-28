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
    shared_ptr<Server> s(new Server());

    EXPECT_EQ(s->isRun(), false);
}

TEST(ServerClientTest, client_test) {
    shared_ptr<Server> s(new Server());
    unique_ptr<Client> c(new Client);

    EXPECT_EQ(s->isRun(), false);
    EXPECT_EQ(c->isConn(), false);
}

}