#pragma once
#include "core/question.hpp"
#include "containers/doubly_linked_list.hpp"

struct NodeTree {
    Question* question;
    NodeTree* yes;
    NodeTree* no;
    DoublyLinkedList<std::string> result_list; // Armazena o resultado final na folha
};

class BinaryTree {
    private:
        NodeTree* root;
        std::string get_element_at(DoublyLinkedList<std::string>& list, int index);
        NodeTree* create_result_node(DoublyLinkedList<std::string>& finalList); // Atualizado para receber a lista
        void destroy_tree(NodeTree* node); // Libera recursivamente os nos e as Questions alocadas

    public:
        BinaryTree();
        ~BinaryTree();
        void build_tree(DoublyLinkedList<Genre>& genreList);
        NodeTree* build_genre_nodes(Node<Genre>* current);
        NodeTree* build_subgenre_nodes(Node<std::string>* currentSub, DoublyLinkedList<std::string>& priorityList, int contPriority);
        NodeTree* process_yes_branch(Node<std::string>* currentSub, DoublyLinkedList<std::string>& priorityList, int contPriority);
        NodeTree* process_no_branch(Node<std::string>* currentSub, DoublyLinkedList<std::string>& priorityList, int contPriority);
        NodeTree* navigate_yes(NodeTree* current); // navega pra no
        NodeTree* navigate_no(NodeTree* current); // navega pra sim

        NodeTree* get_root() const { return root; } // pega a raiz da arvore
};
