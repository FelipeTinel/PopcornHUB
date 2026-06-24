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
        Genre genre;
        long views;
        float rating;

    public:

        Content (std::string title, Type type, Genre genre, int year, long views, float rating);

        int get_id() const;
        std::string get_title() const;
        Type get_type() const;
        Genre get_genre() const;
        int get_year() const;
        long get_views() const;
        float get_rating() const;

        void set_title(std::string title);
        void set_type(Type type);
        void set_genre(Genre gere);
        void set_year(int year);
        void add_views(long views);
        void set_rating(float rating);

};