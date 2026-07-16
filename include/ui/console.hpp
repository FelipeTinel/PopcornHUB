#pragma once

#include <iostream>
#include <string>

#include "core/comment.hpp"
#include "core/user.hpp"
#include "core/content.hpp"
#include "core/type.hpp"
#include "core/genre.hpp"
#include "core/watched_entry.hpp"
#include "services/auth_service.hpp"
#include "services/interaction_service.hpp"
#include "services/admin_service.hpp"
#include "services/statistics_service.hpp"
#include "containers/doubly_linked_list.hpp"
#include "containers/binary_tree.hpp"
#include "ui/ansi.hpp"

enum class ConsoleScreen {
    PROFILE_CHOOSE,
    LOGIN,
    QUESTIONARY,
    RECOMMENDATIONS,
    USER_DASHBOARD,
    CONTENT_DETAIL,
    ADMIN_DASHBOARD,
    WATCH_HISTORY,
    STATISTICS,
    EXIT
};

class Console {

    private:

        static const int PAGE_SIZE = 5;

        ConsoleScreen actual_screen;

        AuthService & auth_service;
        InteractionService & interaction_service;
        AdminService & content_admin_service;
        DoublyLinkedList<Content> & contents;
        DoublyLinkedList<Comment> & comments;
        DoublyLinkedList<Genre> & genres;

        Content * selected_content;

        BinaryTree genre_tree;
        NodeTree * current_tree_node;
        Genre::Value chosen_genre;
        DoublyLinkedList<Content> recommended;

        StatisticsService statistics;

        int user_page;
        int admin_page;

        const char * genre_to_string(Genre::Value g);
        const char * type_to_string(Type t);
        const char * rating_color(float rating);
        void print_watched_entry_line(const WatchedEntry & entry, int position);

        int read_int(const std::string & prompt);
        float read_float(const std::string & prompt);
        std::string read_line(const std::string & prompt);

        int count_contents() const;
        Node<Content> * get_page_start(int page) const;
        void print_content_line(const Content & content);

        void render_profile_choose();
        void render_login();
        void render_questionary();
        void render_recommendations();
        void build_recommendations();
        void render_user_dashboard();
        void render_content_detail();
        void render_admin_dashboard();
        void render_admin_formulary(bool editing);
        void render_watch_history();
        void render_statistics();

    public:

        Console(AuthService & auth, InteractionService & interaction, AdminService & content_admin,
                DoublyLinkedList<Content> & contents, DoublyLinkedList<Comment> & comments,
                DoublyLinkedList<Genre> & genres);

        void run();

};