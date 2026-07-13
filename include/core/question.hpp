#pragma once

#include <iostream>
#include <string>

#include "genre.hpp"
#include "type.hpp"

template <typename T>
class Question {

    private:

        static int next_id;

        int id;

        bool is_genre_question = true;

        std::string question;

        Genre genre;

        

    public:

        Question();
        Question(std::string question, Genre genre, bool is_genre_question);

        Question(std::string question, Genre genre);

        std::string get_question() const;
        Type get_type() const;
        Genre get_genre() const;

        void set_question(std::string question);
        void set_answer(std::string answer);
        void set_type(Type type);
        void set_genre(Genre genre);

};