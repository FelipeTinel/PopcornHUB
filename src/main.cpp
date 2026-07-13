//arvore em levels, como se programa ?
//aqui na main serão inicializados os elementos da arvore e alguns do catálogo
//
#include "doubly_linked_list.hpp"

void main() {
    // Inicialização da árvore
    BinaryTree perguntas;

    DoublyLinkedList <Content> lista_conteudos;

    // Inicialização do catálogo
    Content filme1("Filme 1", Type::MOVIE, Genre::ACTION, 2020, 1000, 4.5f);
    Content filme2("Filme 2", Type::MOVIE, Genre::HORROR, 2020, 1000, 4.5f);
    Content filme3("Filme 3", Type::MOVIE, Genre::COMEDY, 2020, 1000, 4.5f);

    lista_conteudos.insert(filme1);
    lista_conteudos.insert(filme2);
    lista_conteudos.insert(filme3);

    // Adicionando elementos à árvore

    perguntas.insert(filme1);
    perguntas.insert(filme2);
    perguntas.insert(filme3);

    
    String entrada;
    Content Searched;

    cout << "insira elemento que deseja pesquisar: ";
    cin >> entrada;

    while (entrada == ) {
        if(entrada == perguntas.){

        }
        Searched = perguntas.search(entrada);
    }
    cout << "elemento 1: " << perguntas.search("") << endl;

    // Exibir a árvore em níveis
    perguntas.exibirEmNiveis();

    // Exibir o catálogo
    catalogo.exibirItens();
}