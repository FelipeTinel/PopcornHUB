#include <iostream>
#include <string>
#include <fstream>

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
    // TODO: Implementar a lógica para remover o conteúdo do arquivo usando o ID
    std::cout << "Removendo dado com ID: " << id << std::endl;
}

Content* ContentManager::get_data(int id) {
    // TODO: Implementar a lógica para buscar no arquivo e retornar o ponteiro do objeto
    std::cout << "Buscando dado com ID: " << id << std::endl;
    
    // Retornando nullptr temporariamente apenas para o código compilar e linkar
    return nullptr; 
}

