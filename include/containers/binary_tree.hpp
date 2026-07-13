#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "node_tree.hpp"

#include "genre.hpp"
#include "type.hpp"

template <typename T>
class BinaryTree {

    private:

        NodeTree * root;

        std::vector<std::string> subgenres_priority;

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
        void answer(); //seleciona uma resposta pra pergunta, e vai rodar o código de priorização de vetor, e vai jogar o proximo nó da arvore
        void priority_order();// é chamado pelo answer pra arrumar o vetor de prioridades.

        NodeTree* get_root() const { return root; }
        void set_root(NodeTree* new_root) { root = new_root; }

};