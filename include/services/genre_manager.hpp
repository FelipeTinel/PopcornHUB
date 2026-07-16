#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "data_manager.hpp"
#include "core/genre.hpp"
#include "containers/doubly_linked_list.hpp"

class GenreManager : public DataManager<Genre> {

    private:

        // Método auxiliar para formatar a linha no arquivo
        void Genre_frame(std::ofstream & file, const Genre & genre);

    public: 

        // Construtor passando o caminho do arquivo para o DataManager
        GenreManager(const std::string & data_file) : DataManager<Genre>(data_file) {}

        // Implementação dos métodos herdados da classe abstrata DataManager
        void save_data(const DoublyLinkedList<Genre> & list) override;
        void load_data(DoublyLinkedList<Genre> & list) override;

};