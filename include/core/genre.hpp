#pragma once

#include <iostream>

class Genre {

    //esta classe vai ler uma lista de generos static e vai criar objetos do tipo Genre, 
    //cada genero vai ter uma lista de subgeneros próprios
    //que serão usados para criar perguntas na  arvore binaria.

    private:
    
    static DoublyLinkedList<Genre> genres; //inicializada com dados dos arquivos de genero
    
    std::string name;
    DoublyLinkedList<std::string> subgenres; //inicializada com dados dos arquivos de subgenero

    public:
    Genre(){
        
        //neste construtor, ele vai inicializar os objetos generos, 
        //e os subgeneros de cada genero, 
        //a partir de um arquivo de texto que contem os generos e subgeneros.

    };
};


//generos atuais
//ACTION,
//COMEDY,
//ROMANCE,
//HORROR,
//SUSPENSE,
//DRAMA,
//SCIENCE_FICTION,
//SLICE_OF_LIFE,