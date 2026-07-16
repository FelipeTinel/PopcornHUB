
#include "core/question.hpp"

Question::Question(const Genre& g, bool is_genre) 
    : is_genre_question(is_genre), genre(g) {
    if (is_genre_question) {
        question_text = "voce gosta de " + genre.get_name() + "?";
    }
}

Question::Question(const std::string& sub, bool is_genre)
    : is_genre_question(is_genre) {
    if (!is_genre_question) {
        question_text = "Voce gosta de " + sub + "?";
    }
}

Question::Question(const std::string& sub1, const std::string& sub2, bool is_genre) 
    : is_genre_question(is_genre) {
    if (!is_genre_question) {
        question_text = "Voce ja mostrou interesse em " + sub1 + ". Voce tambem curte " + sub2 + "?";
    }
}

std::string Question::get_question() const {
    return question_text;
}

Genre Question::get_genre() const {
    return genre;
}

void Question::set_bool(bool is_genre) {
    is_genre_question = is_genre;
}

void Question::set_question(std::string q) {
    question_text = q;
}

void Question::set_genre(const Genre& g) {
    genre = g;
}

bool Question::is_genre() const {
    return is_genre_question;
}