#include <iostream>
#include <string>

#include "containers/binary_tree.hpp"

void BinaryTree::insert(std::string info) {
    if(root == nullptr) {
        root = new NodeTree();
        root->content.info = info;
        root->left = nullptr;
        root->right = nullptr;
    } else {
        NodeTree* current = root;
        while(true) {
            if(info < current->content.info) {
                if(current->left == nullptr) {
                    current->left = new NodeTree();
                    current->left->content.info = info;
                    current->left->left = nullptr;
                    current->left->right = nullptr;
                    break;
                } else {
                    current = current->left;
                }
            } else if(info > current->content.info) {
                if(current->right == nullptr) {
                    current->right = new NodeTree();
                    current->right->content.info = info;
                    current->right->left = nullptr;
                    current->right->right = nullptr;
                    break;
                } else {
                    current = current->right;
                }
            } else {
                // If the info is equal, we can choose to ignore it or handle duplicates
                // For this implementation, we will ignore duplicates
                break;
            }

        }
    }
}

bool BinaryTree::search(std::string info) {

    

}

void BinaryTree::remove(std::string info) {

    

}