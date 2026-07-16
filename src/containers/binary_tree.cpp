#include "containers/binary_tree.hpp"

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    destroy_tree(root);
}

void BinaryTree::destroy_tree(NodeTree* node) {
    if (node == nullptr) return;

    destroy_tree(node->yes);
    destroy_tree(node->no);

    delete node->question; // libera a Question alocada em build_genre_nodes/build_subgenre_nodes
    delete node;            // result_list (DoublyLinkedList) se libera sozinha aqui, via seu proprio destrutor
}

void BinaryTree::build_tree(DoublyLinkedList<Genre>& genreList) {
    root = build_genre_nodes(genreList.get_head());
}



NodeTree* BinaryTree::build_genre_nodes(Node<Genre>* current) {
    if (current == nullptr) return nullptr;
    NodeTree* node = new NodeTree();
    DoublyLinkedList<std::string> priorityList;
    node->question = new Question(current->info, true);

    //importante!! get_subgenres() retorna a lista POR VALOR (uma copia). Precisa ficar guardada numa variavel nomeada, senao o temporario e destruido no fim da expressao e o get_head() usado abaixo vira um ponteiro invalido

    DoublyLinkedList<std::string> subgenres = current->info.get_subgenres();
    node->yes = build_subgenre_nodes(subgenres.get_head(), priorityList, 0);
    node->no = build_genre_nodes(current->next);
    return node;
}

NodeTree* BinaryTree::build_subgenre_nodes(Node<std::string>* currentSub, DoublyLinkedList<std::string>& priorityList, int contPriority) {
    if (currentSub == nullptr) {
        return create_result_node(priorityList); // Passa a lista acumulada para a folha
    }

    NodeTree* node = new NodeTree();
    if (priorityList.get_head() == nullptr) {
        node->question = new Question(currentSub->info, false);
    } else {
        std::string compareTarget = get_element_at(priorityList, contPriority);
        node->question = new Question(compareTarget, currentSub->info, false);
    }

    node->yes = process_yes_branch(currentSub, priorityList, contPriority);
    node->no = process_no_branch(currentSub, priorityList, contPriority);
    return node;
}

NodeTree* BinaryTree::process_yes_branch(Node<std::string>* currentSub, DoublyLinkedList<std::string>& priorityList, int /*contPriority*/) {
    DoublyLinkedList<std::string> newList = priorityList; 
    newList.insert(currentSub->info);
    return build_subgenre_nodes(currentSub->next, newList, 0);
}

NodeTree* BinaryTree::process_no_branch(Node<std::string>* currentSub, DoublyLinkedList<std::string>& priorityList, int contPriority) {
    if (contPriority + 1 < priorityList.size()) {
        return build_subgenre_nodes(currentSub, priorityList, contPriority + 1);
    } else {
        return build_subgenre_nodes(currentSub->next, priorityList, 0);
    }
}

NodeTree* BinaryTree::create_result_node(DoublyLinkedList<std::string>& finalList) {
    NodeTree* resultNode = new NodeTree();
    resultNode->question = nullptr; 
    resultNode->yes = nullptr;
    resultNode->no = nullptr;
    resultNode->result_list = finalList; // Salva o estado final para a API acessar[cite: 1]
    return resultNode;
}

std::string BinaryTree::get_element_at(DoublyLinkedList<std::string>& list, int index) {
    Node<std::string>* temp = list.get_head();
    int count = 0;
    while (temp != nullptr && count < index) {
        temp = temp->next;
        count++;
    }
    return (temp != nullptr) ? temp->info : ""; 
}

//metodos de navegação:

NodeTree* BinaryTree::navigate_yes(NodeTree* current) {
    if (current != nullptr && current->yes != nullptr) {
        return current->yes;
    }
    return current; // Se não houver ramo, permanece no nó atual (ou retorna null)
}

NodeTree* BinaryTree::navigate_no(NodeTree* current) {
    if (current != nullptr && current->no != nullptr) {
        return current->no;
    }
    return current;
}