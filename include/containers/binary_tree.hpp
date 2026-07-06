#pragma once

#include <iostream>
#include <string>

#include "node_tree.hpp"
class BinaryTree {

    private:

        NodeTree * root;

        void destroy(NodeTree* node) {
            if (node != nullptr) {
                destroy(node->left);
                destroy(node->right);
                delete node;
            }
        }

    public:
    
        BinaryTree (): root(nullptr) {}
        ~BinaryTree() { destroy(root); }

        void insert(std::string info);
        bool search (std::string info);
        void remove (std::string info);

        NodeTree* get_root() const { return root; }
        void set_root(NodeTree* new_root) { root = new_root; }

};