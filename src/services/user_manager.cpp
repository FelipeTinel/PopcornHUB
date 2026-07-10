#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "containers/doubly_linked_list.hpp"
#include "services/user_manager.hpp"
#include "core/user.hpp"

void UserManager::user_frame (std::ofstream & file, const User & user) {

    file_frame(file, user.get_id());
    file_frame(file, user.get_name());
    file_frame(file, user.get_password());
    file << "\n";

}

void UserManager::save_data (const DoublyLinkedList<User> & list) {

    std::ofstream file(data_file);

    if (!file.is_open()) return;

    Node<User> * pointer = list.get_head();
    
    while (pointer != nullptr) {

        user_frame(file, pointer->info);
        pointer = pointer->next;

    }

    file.close();

}

void UserManager::load_data (DoublyLinkedList<User> & list) {

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

        std::string name;
        std::getline(ss, name, ';');

        std::string password;
        std::getline(ss, password, ';');

        User user(id, name, password);
        list.insert(user);
    }

    file.close();

}