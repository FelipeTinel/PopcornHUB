#pragma once

#include <iostream>
#include <string>

#include "node2.hpp"

template <typename T>
class BinaryTree {

    private:

        Node2<T> * root;

    public:
    
        BinaryTree (): root(nullptr) {}

    
        void insert(T info);
        bool search (T info);
        void remove (T info);

};