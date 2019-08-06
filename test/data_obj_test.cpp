//
// Created by user on 2019-08-06.
//
#include "gtest/gtest.h"

#include "../src/base/struct/node.h"
#include "../src/base/data/data_int.h"
#include "../src/base/data/data_float.h"
#include "../src/base/data/data_string.h"


namespace {
using namespace std;
using namespace base;

TEST(DataObjectTest, IntegerValue) {
    DataInt dataInt(5);
    EXPECT_EQ(dataInt.value(), 5);
}

TEST(DataObjectTest, IntegerType) {
    DataInt dataInt(5);
    EXPECT_EQ(dataInt.type(), DataType::INTEGER);
}

TEST(DataObjectTest, IntegerString) {
    DataInt dataInt(5);
    EXPECT_EQ(dataInt.str(), "5");
}

TEST(DataObjectTest, IntegerHash) {
    DataInt dataInt(5);
    EXPECT_EQ(dataInt.hash(), 97*5);
}

TEST(DataObjectTest, IntegerSet) {
    DataInt dataInt(5);
    dataInt.set(197);
    EXPECT_EQ(dataInt.value(), 197);
}

TEST(DataObjectTest, IntegerAdd) {
    DataInt dataInt(5);
    dataInt.add(197);
    EXPECT_EQ(dataInt.value(), 5+197);
}

TEST(DataObjectTest, IntegerMult) {
    DataInt dataInt(5);
    dataInt.mul(13);
    EXPECT_EQ(dataInt.value(), 5*13);
}

TEST(DataObjectTest, FloatValue) {
    DataFloat dataFloat(3.14);
    EXPECT_FLOAT_EQ(dataFloat.value(), 3.14);
}

TEST(DataObjectTest, FloatType) {
    DataFloat dataFloat(3.14);
    EXPECT_EQ(dataFloat.type(), DataType::FLOAT);
}

TEST(DataObjectTest, FloatString) {
    DataFloat dataFloat(3.14);
    EXPECT_EQ(dataFloat.str(), "3.140000");
}

TEST(DataObjectTest, FloatHash) {
    DataFloat dataFloat(3.14);
    EXPECT_EQ(dataFloat.hash(), (int)(37*3.14));
}

TEST(DataObjectTest, FloatSet) {
    DataFloat dataFloat(3.14);
    dataFloat.set(12.28);
        EXPECT_FLOAT_EQ(dataFloat.value(), 12.28);
}

TEST(DataObjectTest, FloatAdd) {
    DataFloat dataFloat(3.14);
    dataFloat.add(0.001592);
    EXPECT_FLOAT_EQ(dataFloat.value(), 3.141592);
}

TEST(DataObjectTest, FloatMult) {
    DataFloat dataFloat(3.14);
    dataFloat.mul(2);
    EXPECT_FLOAT_EQ(dataFloat.value(), 2*3.14);
}

TEST(DataObjectTest, StringValue) {
    DataString dataString("Hello YARD!!");
    EXPECT_EQ(dataString.value(), "Hello YARD!!");
}

TEST(DataObjectTest, StringType) {
    DataString dataString("Hello YARD!!");
    EXPECT_EQ(dataString.type(), DataType::STRING);
}

TEST(DataObjectTest, StringHash) {
    DataString dataString("Hello YARD!!");
    EXPECT_EQ(dataString.hash(), 1237707711);
}

TEST(DataObjectTest, StringStr) {
    DataString dataString("Hello YARD!!");
    EXPECT_EQ(dataString.str(), "Hello YARD!!");
}

TEST(DataObjectTest, StringStrValue) {
    DataString dataString("Hello YARD!!");
    EXPECT_EQ(dataString.str(), dataString.value());
}

TEST(DataObjectTest, StringSet) {
    DataString dataString("Hello YARD!!");
    dataString.set("Bye Bye YARD!!");
    EXPECT_EQ(dataString.str(), "Bye Bye YARD!!");
}

}