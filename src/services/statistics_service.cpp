#include "services/statistics_service.hpp"

long StatisticsService::get_total_views(const DoublyLinkedList<Content> & contents) {

    long total = 0;
    Node<Content> * node = contents.get_head();

    while (node != nullptr) {
        total += node->info.get_views();
        node = node->next;
    }

    return total;
}

Content * StatisticsService::get_most_watched_by_type(const DoublyLinkedList<Content> & contents, Type type) {

    Content * best = nullptr;
    Node<Content> * node = contents.get_head();

    while (node != nullptr) {
        if (node->info.get_type() == type) {
            if (best == nullptr || node->info.get_views() > best->get_views()) best = &node->info;
        }
        node = node->next;
    }

    return best;
}

Content * StatisticsService::get_most_watched_by_genre(const DoublyLinkedList<Content> & contents, Genre::Value genre) {

    Content * best = nullptr;
    Node<Content> * node = contents.get_head();

    while (node != nullptr) {
        if (node->info.get_genre() == genre) {
            if (best == nullptr || node->info.get_views() > best->get_views()) best = &node->info;
        }
        node = node->next;
    }

    return best;
}
