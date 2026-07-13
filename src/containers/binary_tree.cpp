#include <iostream>
#include <string>

#include "containers/binary_tree.hpp"

void BinaryTree::BinaryTree() {
    //inicializa a arvore binaria com as perguntas de genero e subgenero,
    for(){
        
    }
}

//insere uma nova pergunta na arvore binaria
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

void BinaryTree::answer() {
    // Implement the logic to select an answer for the question
    // and run the priority ordering code, then move to the next node in the tree.

}

void BinaryTree::priority_order() {
    // Implement the logic to reorder the subgenres_priority vector based on the answers given.
}
