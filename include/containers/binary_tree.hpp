#pragma once

#include <iostream>
#include <string>

#include "node_tree.hpp"
class BinaryTree {

    private:

        NodeTree * root;

    public:
    
        BinaryTree (): root(nullptr) {}

        void insert(std::string info);
        bool search (std::string info);
        void remove (std::string info);

};