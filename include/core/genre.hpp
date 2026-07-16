#pragma once

#include <iostream>
#include <string>
#include "containers/doubly_linked_list.hpp"

class Genre {
    public:
        // Mantemos o enum para que Content e outros serviços continuem funcionando
        enum Value {
            ACTION = 1,
            COMEDY = 2,
            ROMANCE = 3,
            HORROR = 4,
            SUSPENSE = 5,
            DRAMA = 6,
            SCIENCE_FICTION = 7,
            SLICE_OF_LIFE = 8
        };

    private:
        int id;
        std::string name;
        DoublyLinkedList<std::string> subgenres_list;
        
        // Mantemos a lista global para busca de metadados
        static DoublyLinkedList<Genre> genres_list;

    public:
        Genre(); // Construtor padrão
        // Construtor para inicializar com dados completos
        Genre(int id, std::string name, DoublyLinkedList<std::string> subgenres_list);

        // Métodos de manipulação
        void addSubgenre(const std::string& s);
        static void addGenre(const Genre& g);

        // Getters
        int get_id() const;
        std::string get_name() const;
        
        // Retorna o enum associado a este objeto
        Value get_value() const { return static_cast<Value>(id); }
        
        DoublyLinkedList<std::string> get_subgenres() const;
        static DoublyLinkedList<Genre>& get_genres_list();
};

// Values vao de 1 (ACTION) a 8 (SLICE_OF_LIFE); +1 pra usar como limite de loop (g < GENRE_COUNT)
const int GENRE_COUNT = 9;