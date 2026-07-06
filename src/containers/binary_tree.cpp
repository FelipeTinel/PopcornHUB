#include <iostream>
#include <string>

#include "containers/binary_tree.hpp"

void BinaryTree::insert(std::string info) {
    if(root == nullptr) {
        root = new NodeTree();
        root->question = info;
    } else {
        NodeTree* current = root;
        while(true) {
            if(info < current->question) {
                if(current->left == nullptr) {
                    current->left = new NodeTree();
                    current->left->question = info;
                    break;
                } else {
                    current = current->left;
                }
            } else if(info > current->question) {
                if(current->right == nullptr) {
                    current->right = new NodeTree();
                    current->right->question = info;
                    break;
                } else {
                    current = current->right;
                }
            } else {
                break;
            }
        }
    }
}

bool BinaryTree::search(std::string info) {
    NodeTree* current = root;
    while(current != nullptr) {
        if(info < current->question) {
            current = current->left;
        } else if(info > current->question) {
            current = current->right;
        } else {
            return true; 
        }
    }
    return false; 
}

static NodeTree* remove_helper(NodeTree* node, const std::string& info) {
    if (node == nullptr) return nullptr;
    if (info < node->question) {
        node->left = remove_helper(node->left, info);
    } else if (info > node->question) {
        node->right = remove_helper(node->right, info);
    } else {
        if (node->left == nullptr) {
            NodeTree* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            NodeTree* temp = node->left;
            delete node;
            return temp;
        }
        NodeTree* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        node->question = temp->question;
        node->content = temp->content;
        node->right = remove_helper(node->right, temp->question);
    }
    return node;
}

void BinaryTree::remove(std::string info) {
    root = remove_helper(root, info);
}