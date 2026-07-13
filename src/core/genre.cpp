#include <iostream>

#include "core/genre.hpp"

class Genre {

    //esta classe vai ler uma lista de generos static e vai criar objetos do tipo Genre, 
    //cada genero vai ter uma lista de subgeneros próprios
    //que serão usados para criar perguntas na  arvore binaria.
    
    public:
    Genre(){
    Node<Genre>* current = allGenres.get_head();

    while (current != nullptr) {
        // Aqui você tem acesso ao objeto Genre
        Genre& g = current->info;
        
        std::cout << "Processando genero: " << g.get_name() << std::endl;
        
        // Processar os subgêneros deste gênero
        Node<Subgenre>* subCurrent = g.subgenres.get_head();
    while (subCurrent != nullptr) {
        std::cout << " - Subgenero: " << subCurrent->info.get_name() << std::endl;
        subCurrent = subCurrent->next;
    }

    // Avança para o próximo
    current = current->next;
}
        //neste construtor, ele vai inicializar os objetos generos, 
        //e os subgeneros de cada genero, 
        //a partir de um arquivo de texto que contem os generos e subgeneros.

    };


};