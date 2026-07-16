#pragma once

#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"
#include "core/type.hpp"
#include "core/genre.hpp"

// Acumula contadores sobre as recomendacoes geradas ao longo da execucao
// (uma "rodada" = uma chamada de register_recommendation, tipicamente uma
// vez por questionario respondido).
class Statistics {

    private:

        int type_counts[TYPE_COUNT];
        int genre_counts[GENRE_COUNT]; // indice 0 nao e usado (Genre::Value comeca em 1)
        int total_recommendations;

    public:

        Statistics();

        void register_recommendation(const DoublyLinkedList<Content> & recommended);

        int get_total_recommendations() const;

        Type get_most_recommended_type() const;
        Type get_least_recommended_type() const;

        Genre::Value get_most_recommended_genre() const;
        Genre::Value get_least_recommended_genre() const;

};
