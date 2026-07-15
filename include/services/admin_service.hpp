#pragma once

#include <string>

#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"
#include "core/type.hpp"
#include "core/genre.hpp"

class AdminService {

    private:

        DoublyLinkedList<Content> & contents;

    public:

        explicit AdminService(DoublyLinkedList<Content> & contents);

        Content * add_content(const std::string & title, Type type, Genre genre, int year, long views, float rating);
        bool edit_content(int id, const std::string & title, Type type, Genre genre, int year, long views, float rating);
        bool remove_content(int id);
};