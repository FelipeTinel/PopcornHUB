#pragma once

#include <iostream>
#include <string>

#include "core/comment.hpp"
#include "core/user.hpp"
#include "core/content.hpp"
#include "core/type.hpp"
#include "core/genre.hpp"
#include "services/auth_service.hpp"
#include "services/interaction_service.hpp"
#include "services/admin_service.hpp"
#include "containers/doubly_linked_list.hpp"
#include "ui/ansi.hpp"

enum class ConsoleScreen {
    PROFILE_CHOOSE,
    LOGIN,
    USER_DASHBOARD,
    CONTENT_DETAIL,
    ADMIN_DASHBOARD,
    EXIT
};

class Console {

    private:

        // Quantos itens sao mostrados por pagina nas listagens de catalogo.
        static const int PAGE_SIZE = 8;

        ConsoleScreen actual_screen;

        AuthService & auth_service;
        InteractionService & interaction_service;
        AdminService & content_admin_service;
        DoublyLinkedList<Content> & contents;
        DoublyLinkedList<Comment> & comments;

        Content * selected_content;

        // Pagina atual de cada listagem (uma para o usuario, outra para o admin,
        // ja que cada uma pode estar em uma pagina diferente).
        int user_page;
        int admin_page;

        const char * genre_to_string(Genre g);
        const char * type_to_string(Type t);
        const char * rating_color(float rating);

        int read_int(const std::string & prompt);
        float read_float(const std::string & prompt);
        std::string read_line(const std::string & prompt);

        int count_contents() const;
        Node<Content> * get_page_start(int page) const;
        void print_content_line(const Content & content);

        void render_profile_choose();
        void render_login();
        void render_user_dashboard();
        void render_content_detail();
        void render_admin_dashboard();
        void render_admin_formulary(bool editing);

    public:

        Console(AuthService & auth, InteractionService & interaction, AdminService & content_admin,
                DoublyLinkedList<Content> & contents, DoublyLinkedList<Comment> & comments);

        void run();

};
