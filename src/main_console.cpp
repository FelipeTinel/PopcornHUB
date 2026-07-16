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

#include <initializer_list>
#include <string>

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

    //arvore binaria precisa popular genero
    if (genres.get_head() == nullptr) {

        auto make_genre = [&genres](Genre::Value value, const std::string & name,
                                     std::initializer_list<std::string> subs) {
            DoublyLinkedList<std::string> subgenres;
            for (const std::string & s : subs) subgenres.insert(s);
            Genre g(value, name, subgenres);
            genres.insert(g);
            Genre::addGenre(g);
        };

        make_genre(Genre::ACTION,           "Acao",              {"Aventura", "Artes Marciais", "Guerra"});
        make_genre(Genre::COMEDY,           "Comedia",           {"Romantica", "Pastelao", "Satira"});
        make_genre(Genre::ROMANCE,          "Romance",           {"Drama Romantico", "Comedia Romantica"});
        make_genre(Genre::HORROR,           "Terror",            {"Slasher", "Sobrenatural", "Psicologico"});
        make_genre(Genre::SUSPENSE,         "Suspense",          {"Policial", "Thriller Psicologico"});
        make_genre(Genre::DRAMA,            "Drama",             {"Biografia", "Historico"});
        make_genre(Genre::SCIENCE_FICTION,  "Ficcao Cientifica", {"Space Opera", "Distopia", "Cyberpunk"});
        make_genre(Genre::SLICE_OF_LIFE,    "Slice of Life",     {"Escolar", "Familiar"});
    }

    AuthService auth(users);
    InteractionService interaction(auth, comments);
    AdminService content_admin(contents);

    //o historico de Mais Assistidos deve refletir o total da PLATAFORMA, nao so o que for assistido nesta sessao.

    interaction.seed_watch_history(contents);

    Console console(auth, interaction, content_admin, contents, comments, genres);
    console.run();

    content_manager.save_data(contents);
    comment_manager.save_data(comments);
    user_manager.save_data(users);
    genre_manager.save_data(genres);

    return 0;
}