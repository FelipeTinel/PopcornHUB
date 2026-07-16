#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "containers/doubly_linked_list.hpp"
#include "services/content_manager.hpp"
#include "core/content.hpp"

void ContentManager::content_frame (std::ofstream & file, const Content & content) {

    file_frame(file, content.get_id());
    file_frame(file, content.get_title());
    file_frame(file, static_cast<int>(content.get_type()));
    file_frame(file, static_cast<int>(content.get_genre()));
    file_frame(file, content.get_year());
    file_frame(file, content.get_views());
    file_frame(file, content.get_rating());
    file_frame(file, content.get_rating_count());
    file << "\n";

}

void ContentManager::save_data (const DoublyLinkedList<Content> & list) {

    std::ofstream file(data_file);

    if (!file.is_open()) return;

    Node<Content> * pointer = list.get_head();
    
    while (pointer != nullptr) {

        content_frame(file, pointer->info);
        pointer = pointer->next;

    }

    file.close();

}

void ContentManager::load_data(DoublyLinkedList<Content> & list) {
    
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

        std::string title;
        std::getline(ss, title, ';');

        std::getline(ss, field, ';');
        Type type = static_cast<Type>(std::stoi(field));

        std::getline(ss, field, ';');
        Genre::Value genre = static_cast<Genre::Value>(std::stoi(field));

        std::getline(ss, field, ';');
        int year = std::stoi(field);

        std::getline(ss, field, ';');
        long views = std::stol(field);

        std::getline(ss, field, ';');
        float rating = std::stof(field);

        std::getline(ss, field, ';');
        int rating_count = std::stoi(field);

        Content content(id, title, type, genre, year, views, rating, rating_count);
        list.insert(content);
    }

    file.close();
}
