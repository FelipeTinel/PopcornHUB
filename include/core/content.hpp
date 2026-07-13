#pragma once

#include <iostream>
#include <string>

#include "genre.hpp"
#include "type.hpp"

template <typename T>
class Content {

    private:

        static int next_id;

        int id, year;
        std::string title;
        Type type;
        Genre genre;
        long views;
        float rating;
        int rating_count;
        double score;
        

    public:

        Content();
        Content (std::string title, Type type, Genre genre, int year, long views, float rating);
        Content(int id, std::string title, Type type, Genre genre, int year, long views, float rating, int rating_count);

        int get_id() const;
        std::string get_title() const;
        Type get_type() const;
        Genre get_genre() const;
        int get_year() const;
        long get_views() const;
        float get_rating() const;
        int get_rating_count() const;
        double get_score() const;

        void set_title(std::string title);
        void set_type(Type type);
        void set_genre(Genre gere);
        void set_year(int year);
        void add_views(long views);
        void set_rating(float rating);
        void add_rating (float new_rating);
        void set_score(double score);

};