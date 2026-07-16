#include "ui/console.hpp"
#include "services/auth_service.hpp"
#include "services/interaction_service.hpp"
#include "services/content_manager.hpp"
#include "services/user_manager.hpp"
#include "services/comment_manager.hpp"
#include "services/genre_manager.hpp"
#include "containers/doubly_linked_list.hpp"
#include "services/admin_service.hpp"
#include "core/user.hpp"
#include "core/content.hpp"
#include "core/comment.hpp"
#include "core/genre.hpp"
#include "core/type.hpp"

int main() {

    DoublyLinkedList<User> users;
    DoublyLinkedList<Content> contents;
    DoublyLinkedList<Comment> comments;
    DoublyLinkedList<Genre> genres;

    // Arquivos persistentes reais do projeto (pasta data/), diferente dos
    // arquivos de teste usados em tests/test_ui.cpp.
    UserManager user_manager{"../data/users_data.txt"};
    ContentManager content_manager{"../data/contents_data.txt"};
    CommentManager comment_manager{"../data/comments_data.txt"};
    GenreManager genre_manager{"../data/genres_data.txt"};

    user_manager.load_data(users);
    content_manager.load_data(contents);
    comment_manager.load_data(comments);
    genre_manager.load_data(genres);

    if (contents.get_head() == nullptr) {

        Content c1{"Interstellar", Type::MOVIE, Genre::SCIENCE_FICTION, 2014, 950000, 4.9f};
        Content c2{"Minecraft", Type::MOVIE, Genre::ACTION, 2025, 950000, 5.0f};

        contents.insert(c1);
        contents.insert(c2);
    }

    // O arquivo data/genres_data.txt ainda nao existe (ou esta vazio) na primeira
    // execucao do projeto. Sem generos cadastrados, a BinaryTree do questionario
    // fica com root == nullptr e a tela QUESTIONARY pula direto pro catalogo.
    // Por isso semeamos aqui os generos padrao, assim como ja e feito com contents.
    if (genres.get_head() == nullptr) {

        DoublyLinkedList<std::string> subs_action;
        subs_action.insert("Luta");
        subs_action.insert("Veiculos");
        subs_action.insert("Guerra");

        DoublyLinkedList<std::string> subs_comedy;
        subs_comedy.insert("Romantica");
        subs_comedy.insert("Pastelao");
        subs_comedy.insert("Satira");

        DoublyLinkedList<std::string> subs_romance;
        subs_romance.insert("Epoca");
        subs_romance.insert("Familiar");
        subs_romance.insert("Drama");

        DoublyLinkedList<std::string> subs_horror;
        subs_horror.insert("Slasher");
        subs_horror.insert("Sobrenatural");
        subs_horror.insert("Psicologico");

        DoublyLinkedList<std::string> subs_suspense;
        subs_suspense.insert("Policial");
        subs_suspense.insert("Thriller");
        subs_suspense.insert("Misterio");

        DoublyLinkedList<std::string> subs_drama;
        subs_drama.insert("Biografico");
        subs_drama.insert("Familiar");
        subs_drama.insert("Social");

        DoublyLinkedList<std::string> subs_scifi;
        subs_scifi.insert("Espacial");
        subs_scifi.insert("Distopia");
        subs_scifi.insert("Viagem no Tempo");

        DoublyLinkedList<std::string> subs_slice;
        subs_slice.insert("Escolar");
        subs_slice.insert("Cotidiano");
        subs_slice.insert("Coming of Age");

        Genre g1(Genre::ACTION,          "Acao",              subs_action);
        Genre g2(Genre::COMEDY,          "Comedia",           subs_comedy);
        Genre g3(Genre::ROMANCE,         "Romance",           subs_romance);
        Genre g4(Genre::HORROR,          "Terror",            subs_horror);
        Genre g5(Genre::SUSPENSE,        "Suspense",          subs_suspense);
        Genre g6(Genre::DRAMA,           "Drama",             subs_drama);
        Genre g7(Genre::SCIENCE_FICTION, "Ficcao Cientifica", subs_scifi);
        Genre g8(Genre::SLICE_OF_LIFE,   "Slice of Life",     subs_slice);

        genres.insert(g1);
        genres.insert(g2);
        genres.insert(g3);
        genres.insert(g4);
        genres.insert(g5);
        genres.insert(g6);
        genres.insert(g7);
        genres.insert(g8);

        Genre::addGenre(g1);
        Genre::addGenre(g2);
        Genre::addGenre(g3);
        Genre::addGenre(g4);
        Genre::addGenre(g5);
        Genre::addGenre(g6);
        Genre::addGenre(g7);
        Genre::addGenre(g8);
    }

    AuthService auth(users);
    InteractionService interaction(auth, comments);
    AdminService content_admin(contents);

    Console console(auth, interaction, content_admin, contents, comments, genres);
    console.run();

    content_manager.save_data(contents);
    comment_manager.save_data(comments);
    user_manager.save_data(users);
    genre_manager.save_data(genres);

    return 0;
}