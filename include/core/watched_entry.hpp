#pragma once

#include <string>

#include "type.hpp"
#include "genre.hpp"

// Representa uma entrada no ranking de "mais assistidos" (historico global,
// nao por usuario - contabiliza views de todo mundo pro mesmo conteudo).
class WatchedEntry {

    private:

        int id;
        std::string title;
        Type type;
        Genre::Value genre;
        long watch_count;

    public:

        WatchedEntry(); // usado pelo DoublyLinkedList::pop quando o id nao e encontrado
        WatchedEntry(int id, std::string title, Type type, Genre::Value genre, long watch_count);

        int get_id() const;
        std::string get_title() const;
        Type get_type() const;
        Genre::Value get_genre() const;
        long get_watch_count() const;

        void add_watch();

};

bool watched_desc(const WatchedEntry &a, const WatchedEntry &b);
