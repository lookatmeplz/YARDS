//
// Created by user on 2019-07-24.
//
#include "gtest/gtest.h"

#include "../src/base/node.h"
#include "../src/base/data/data_int.h"

namespace {
using namespace std;
using namespace base;

TEST(LinkedListTest, Init) {
    shared_ptr<DataInt> k(new DataInt(37));
    shared_ptr<DataInt> v(new DataInt(17));
    unique_ptr<Node> node(new Node(k, v));

    EXPECT_EQ(node->key(), k);
    EXPECT_EQ(node->val(), v);
}

TEST(LinkedListTest, Append) {
    shared_ptr<DataObject> k(new DataInt(1));
    shared_ptr<DataObject> k2(new DataInt(2));

    shared_ptr<DataObject> v(new DataInt(3));
    shared_ptr<DataObject> v2(new DataInt(4));

    unique_ptr<Node> node(new Node(k, v));
    unique_ptr<Node> node2(new Node(k2, v2));

    node2->set_prev(node.get());
    node->set_next(std::move(node2));

    DataInt* key = static_cast<DataInt*>(node->key().get());
    DataInt* val = static_cast<DataInt*>(node->val().get());

    EXPECT_EQ(key->value(), 1);
    EXPECT_EQ(val->value(), 3);

    key = static_cast<DataInt*>(node->next()->key().get());
    val = static_cast<DataInt*>(node->next()->val().get());

    EXPECT_EQ(key->value(), 2);
    EXPECT_EQ(val->value(), 4);
}

}
