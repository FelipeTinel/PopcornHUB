#include "services/statistics.hpp"

Statistics::Statistics(): total_recommendations(0) {
    for (int i = 0; i < TYPE_COUNT; i++) type_counts[i] = 0;
    for (int i = 0; i < GENRE_COUNT; i++) genre_counts[i] = 0;
}

void Statistics::register_recommendation(const DoublyLinkedList<Content> & recommended) {

    Node<Content> * node = recommended.get_head();
    if (node == nullptr) return; // rodada sem nenhuma recomendacao nao conta

    while (node != nullptr) {
        type_counts[static_cast<int>(node->info.get_type())]++;
        genre_counts[static_cast<int>(node->info.get_genre())]++;
        node = node->next;
    }

    total_recommendations++;
}

int Statistics::get_total_recommendations() const { return total_recommendations; }

Type Statistics::get_most_recommended_type() const {

    int best = 0;
    for (int i = 1; i < TYPE_COUNT; i++) {
        if (type_counts[i] > type_counts[best]) best = i;
    }
    return static_cast<Type>(best);
}

Type Statistics::get_least_recommended_type() const {

    int worst = 0;
    for (int i = 1; i < TYPE_COUNT; i++) {
        if (type_counts[i] < type_counts[worst]) worst = i;
    }
    return static_cast<Type>(worst);
}

Genre::Value Statistics::get_most_recommended_genre() const {

    int best = 1;
    for (int i = 2; i < GENRE_COUNT; i++) {
        if (genre_counts[i] > genre_counts[best]) best = i;
    }
    return static_cast<Genre::Value>(best);
}

Genre::Value Statistics::get_least_recommended_genre() const {

    int worst = 1;
    for (int i = 2; i < GENRE_COUNT; i++) {
        if (genre_counts[i] < genre_counts[worst]) worst = i;
    }
    return static_cast<Genre::Value>(worst);
}
