#pragma once

#include <iostream>
#include <string>

#include "genre.hpp"
#include "type.hpp"
class Content {

    private:

        std::string title;
        Type type;
        Genre genre;
        int year;
        long views;
        float rating;

    public:

        Content (std::string t, Type ty, Genre g, int y, long v, float r):

            title(t),
            type(ty),
            genre(g),
            year(y),
            views(v),
            rating(r)

        {}

};