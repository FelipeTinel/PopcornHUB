#include "services/genre_manager.hpp"
#include <sstream>

void GenreManager::Genre_frame(std::ofstream & file, const Genre & genre) {
    file_frame(file, genre.get_id());
    file_frame(file, genre.get_name());
    
    // Salva o enum como inteiro
    file_frame(file, static_cast<int>(genre.get_value()));
    
    // Formato especial para a lista de subgêneros: {sub1,sub2,sub3,}
    file << "{";
    Node<std::string>* sub = genre.get_subgenres().get_head();
    while (sub != nullptr) {
        file << sub->info << ",";
        sub = sub->next;
    }
    file << "}";
    file << "\n";
}

void GenreManager::save_data(const DoublyLinkedList<Genre> & list) {
    std::ofstream file(data_file);
    if (!file.is_open()) return;

    Node<Genre> * pointer = list.get_head();
    while (pointer != nullptr) {
        Genre_frame(file, pointer->info);
        pointer = pointer->next;
    }
    file.close();
}

void GenreManager::load_data(DoublyLinkedList<Genre> & list) {
    std::ifstream file(data_file);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string field;

        // ID
        std::getline(ss, field, ';');
        int id = std::stoi(field);

        // Nome
        std::string name;
        std::getline(ss, name, ';');

        // Enum (pulamos a leitura direta do enum pois o ID já o define)
        std::getline(ss, field, ';'); 

        // Subgêneros
        std::getline(ss, field, '{');
        std::string sub_content;
        std::getline(ss, sub_content, '}');
        
        DoublyLinkedList<std::string> subgenres_list;
        std::stringstream ss_subs(sub_content);
        std::string sub;
        while (std::getline(ss_subs, sub, ',')) {
            if (!sub.empty()) subgenres_list.insert(sub);
        }

        // Criar o objeto, adicionar à lista passada e à global
        Genre new_genre(id, name, subgenres_list);
        list.insert(new_genre);
        Genre::addGenre(new_genre); 
    }
    file.close();
}