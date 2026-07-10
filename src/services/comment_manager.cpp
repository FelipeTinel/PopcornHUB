#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "containers/doubly_linked_list.hpp"
#include "services/comment_manager.hpp"
#include "core/comment.hpp"

void CommentManager::comment_frame (std::ofstream & file, const Comment & comment) {

    file_frame(file, comment.get_id());
    file_frame(file, comment.get_content_id());
    file_frame(file, comment.get_user_id());
    file_frame(file, comment.get_comment());
    file << "\n";

}

void CommentManager::save_data (const DoublyLinkedList<Comment> & list) {

    std::ofstream file(data_file);

    if (!file.is_open()) return;

    Node<Comment> * pointer = list.get_head();
    
    while (pointer != nullptr) {

        comment_frame(file, pointer->info);
        pointer = pointer->next;

    }

    file.close();

}

void CommentManager::load_data (DoublyLinkedList<Comment> & list) {

    std::ifstream file(data_file);
    if (!file.is_open()) {
        std::cout << "Arquivo não encontrado." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;

        std::getline(ss, field, ';');
        int id = std::stoi(field);

        std::getline(ss, field, ';');
        int content_id = std::stoi(field);

        std::getline(ss, field, ';');
        int user_id = std::stoi(field);

        std::string text;
        std::getline(ss, text, ';');

        Comment comment(id, content_id, user_id, text);
        list.insert(comment);
    }

    file.close();

}