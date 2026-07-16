#include "core/genre.hpp"

// Inicialização da lista estática global
DoublyLinkedList<Genre> Genre::genres_list;

// Construtor padrão
Genre::Genre() : id(0), name(""), subgenres_list() {}

// Construtor completo
Genre::Genre(int i, std::string n, DoublyLinkedList<std::string> sg_list) 
    : id(i), name(n), subgenres_list(sg_list) {}

// Adiciona um subgênero ao objeto específico
void Genre::addSubgenre(const std::string& s) { 
    subgenres_list.insert(s); 
} 

// Adiciona um objeto Genre à lista global (usado para inicialização ou carregamento)
void Genre::addGenre(const Genre& g) { 
    genres_list.insert(g); 
}

// Getters
int Genre::get_id() const { 
    return id; 
}

std::string Genre::get_name() const { 
    return name; 
}

DoublyLinkedList<std::string> Genre::get_subgenres() const { 
    return subgenres_list; 
}

DoublyLinkedList<Genre>& Genre::get_genres_list() { 
    return genres_list; 
}