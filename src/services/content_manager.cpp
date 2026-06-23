#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
    file << "\n";

}

void ContentManager::write_data (const Content & content) {

    std::ofstream write_file(data_file, std::ios::app);

    if (write_file.is_open()) {
        
        content_frame(write_file, content);
        write_file.close();

    } else {
        std::cout << "Erro, arquivo não encontrado." << std::endl;
    }

}

void ContentManager::update_data (int id, const Content & content) {

    std::ofstream update_file(data_file);

    if (update_file.is_open()) {

        content_frame(update_file, content);
        update_file.close();

    } else {
        std::cout << "Erro, não foi possível atualizar o conteúdo" << std::endl;
    }

}

void ContentManager::remove_data(int id) {
    std::cout << "Removendo dado com ID: " << id << std::endl;
}

Content * ContentManager::get_data(int id) {
    
    std::ifstream read_content (data_file);
    
    std::string search_id;

    if (!read_content.is_open()) {
        std::cerr << "Arquivo não encontrado" << std::endl;
    } else {

        while (std::getline(read_content, search_id)) {
            
            std::stringstream ss(search_id);
            std::string camp;
            
            if (std::getline(ss, camp, ';')) {
                
                int actual_id = std::stoi(camp);
                
                if (actual_id == id) {
                    
                    std::string title, str_type, str_genre, str_year, str_views, str_rating;
                    
                    std::getline(ss, title, ';');
                    std::getline(ss, str_type, ';');
                    std::getline(ss, str_genre, ';');
                    std::getline(ss, str_year, ';');
                    std::getline(ss, str_views, ';');
                    std::getline(ss, str_rating, ';');
    
                    Type type = static_cast<Type>(std::stoi(str_type));
                    Genre genre = static_cast<Genre>(std::stoi(str_genre));
                    int year = std::stoi(str_year);
                    long views = std::stol(str_views);
                    float rating = std::stof(str_rating);
    
                    return new Content(title, type, genre, year, views, rating);
    
                }
            } 
        }
        
    }
    
    return nullptr; 
}

