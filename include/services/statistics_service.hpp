#pragma once

#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"
#include "core/type.hpp"
#include "core/genre.hpp"

// Metodos estaticos que calculam metricas direto sobre o catalogo (contents),
// sem precisar guardar estado proprio.
class StatisticsService {

    public:

        static long get_total_views(const DoublyLinkedList<Content> & contents);

        static Content * get_most_watched_by_type(const DoublyLinkedList<Content> & contents, Type type);
        static Content * get_most_watched_by_genre(const DoublyLinkedList<Content> & contents, Genre::Value genre);

};
