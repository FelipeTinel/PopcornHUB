#pragma once

#include <iostream>
#include <string>

#include "genre.hpp"
#include "type.hpp"

class Content {

    private:

        static int next_id;

        int id, year;
        std::string title;
        Type type;
        Genre::Value genre;
        std::string subgenre; //opcional optamos por usar para refinar recomendacoes de genero
        long views;
        float rating;
        int rating_count;
        

    public:

        Content();
        Content (std::string title, Type type, Genre::Value genre, int year, long views, float rating, std::string subgenre = "");
        Content(int id, std::string title, Type type, Genre::Value genre, int year, long views, float rating, int rating_count, std::string subgenre = "");

        int get_id() const;
        std::string get_title() const;
        Type get_type() const;
        Genre::Value get_genre() const;
        std::string get_subgenre() const;
        int get_year() const;
        long get_views() const;
        float get_rating() const;
        int get_rating_count() const;

        void set_title(std::string title);
        void set_type(Type type);
        void set_genre(Genre::Value gere);
        void set_subgenre(std::string subgenre);
        void set_year(int year);
        void add_views(long views);
        void set_views(long views);
        void set_rating(float rating);
        void add_rating (float new_rating);

};

bool content_rating_desc(const Content &a, const Content &b);