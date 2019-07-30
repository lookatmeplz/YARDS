//
// Created by user on 2019-07-28.
//

#include "gtest/gtest.h"
#include "../src/cmd/parser.h"
#include "../src/cmd/parser_result.h"
#include <vector>
#include <tuple>

namespace {

using namespace std;
using namespace cmd;

TEST(ParserTest, parser_test) {
    tuple<ParserResultType , vector<shared_ptr<DataObject>>> re;
    re = Parser::parse("set 'key' 'asdf d'");

    EXPECT_EQ(get<0>(re), SET);
    EXPECT_EQ(get<1>(re)[0].get()->str(), "'key'");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "'asdf d'");

    re = Parser::parse("set 1231 0");

    EXPECT_EQ(get<1>(re)[0].get()->str(), "1231");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "0");

    re = Parser::parse("set 0.215 42.0");

    EXPECT_EQ(get<1>(re)[0].get()->str(), "0.215000");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "42.000000");

    re = Parser::parse("set /T /F");

    EXPECT_EQ(get<1>(re)[0].get()->str(), "True");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "False");
}

}