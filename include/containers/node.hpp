#pragma once

#include <iostream>

template <typename T>
struct Node {

    T info;
    Node * next, * previous;

    Node(const T &_info): info(_info), next(nullptr), previous(nullptr) {}
};

