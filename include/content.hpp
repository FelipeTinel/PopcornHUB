#pragma once

#include <iostream>
#include <string>

class Content {

    std::string title, type, gender;
    int year;
    long views;
    Content * next, * previous;

    public:

        Content (std::string t, std::string ty, std::string gen, int y)
        {

            title = t;
            type = ty;
            gender = gen;
            year = y;
            next = nullptr;
            previous = nullptr;

        }

};