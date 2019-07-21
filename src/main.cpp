//
// Created by HyeockJin Kim on 2019-07-16.
//
#include <iostream>


#include "base/node.h"

using std::shared_ptr;
using std::unique_ptr;
using namespace base;

int main() {
    auto deleter = [](unique_ptr<Node>* p){delete[] p;};
    shared_ptr<unique_ptr<Node>> d(new unique_ptr<Node>[16], deleter);
    shared_ptr<unique_ptr<Node>> dict;
    dict = std::move(d);

}
