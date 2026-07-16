
#pragma once

#include <iostream>
#include <string>
#include "genre.hpp"
#include "containers/doubly_linked_list.hpp"

class Question {
    private:
        bool is_genre_question;
        std::string question_text;
        Genre genre; // Usado apenas se is_genre_question for true

    public:
        // Construtor para perguntas de Gênero (ex: "Você gosta de Ação?")
        Question(const Genre& g, bool is_genre);

        // Construtor para pergunta de um único Subgênero (ex: "Você gosta de Superhero?")
        Question(const std::string& sub, bool is_genre);

        // Construtor para comparação de Subgêneros (ex: "Você prefere X ou Y?")
        Question(const std::string& sub1, const std::string& sub2, bool is_genre);

        std::string get_question() const;
        Genre get_genre() const;

        void set_bool(bool is_genre);
        void set_question(std::string question);
        void set_genre(const Genre& g);
};
