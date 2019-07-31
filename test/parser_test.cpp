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
    parser::init();

    tuple<ParserResultType , vector<shared_ptr<DataObject>>> re;
    re = parser::parse("set 'key' 'asdf d'", ' ');

    EXPECT_EQ(get<0>(re), SET);
    EXPECT_EQ(get<1>(re)[0].get()->str(), "'key'");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "'asdf d'");

    re = parser::parse("set 1231 0", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "1231");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "0");

    re = parser::parse("set 0.215 42.0", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "0.215000");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "42.000000");

    re = parser::parse("set /T /F", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "True");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "False");
}

TEST(ParserTest, struct_test) {
    parser::init();

    tuple<ParserResultType , vector<shared_ptr<DataObject>>> re;
    re = parser::parse("set 'k' {'asdf': {'dd dd': 123}}", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "'k'");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "{'asdf': {'dd dd': 123, }, }");

    re = parser::parse("set 'k' {'asdf': {/T : {0.1213 : /F}    }}", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "'k'");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "{'asdf': {True: {0.121300: False, }, }, }");

    re = parser::parse("set 'k' ['a', 1, 0.123 , 'dddd', /F ]", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "'k'");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "['a', 1, 0.123000, 'dddd', False, ]");

    re = parser::parse("set 'k' ({'k1':'v1', 3:456}, [1,2, {/T:/F}], ('a',1.2, 0.234))", ' ');

    EXPECT_EQ(get<1>(re)[0].get()->str(), "'k'");
    EXPECT_EQ(get<1>(re)[1].get()->str(), "({3: 456, 'k1': 'v1', }, [1, 2, {True: False, }, ], ('a', 1.200000, 0.234000, ), )");
}

}
