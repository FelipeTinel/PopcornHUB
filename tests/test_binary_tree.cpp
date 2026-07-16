#include <iostream>
#include <cassert>
#include "containers/binary_tree.hpp"
#include "core/genre.hpp"
#include "containers/doubly_linked_list.hpp"

int count_nodes(NodeTree* node) {
    if (node == nullptr) return 0;
    return 1 + count_nodes(node->yes) + count_nodes(node->no);
}

int count_questions(NodeTree* node) {
    if (node == nullptr) return 0;
    int count = (node->question != nullptr) ? 1 : 0;
    return count + count_questions(node->yes) + count_questions(node->no);
}

int main() {
    std::cout << "=== Running BinaryTree verification tests ===" << std::endl;

    // Create subgenres for Action
    DoublyLinkedList<std::string> action_subs;
    action_subs.insert("Superhero");
    action_subs.insert("Sci-Fi Action");

    Genre action_genre(1, "Action", action_subs);

    // Create subgenres for Comedy
    DoublyLinkedList<std::string> comedy_subs;
    comedy_subs.insert("Romantic Comedy");
    comedy_subs.insert("Sitcom");

    Genre comedy_genre(2, "Comedy", comedy_subs);

    DoublyLinkedList<Genre> list;
    list.insert(comedy_genre);
    list.insert(action_genre);

    std::cout << "List size: " << list.size() << std::endl;

    BinaryTree tree;
    tree.build_tree(list);

    NodeTree* root = tree.get_root();
    assert(root != nullptr);

    std::cout << "Tree successfully built." << std::endl;

    int total_nodes = count_nodes(root);
    int total_questions = count_questions(root);
    std::cout << "Total nodes: " << total_nodes << std::endl;
    std::cout << "Total questions: " << total_questions << std::endl;

    std::cout << "Root question: " << root->question->get_question() << std::endl;

    std::cout << "=== BinaryTree verification tests completed successfully ===" << std::endl;
    return 0;
}
