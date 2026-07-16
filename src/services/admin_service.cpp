#include "services/admin_service.hpp"

AdminService::AdminService(DoublyLinkedList<Content> & contents): contents(contents) {}

Content * AdminService::add_content(const std::string & title, Type type, Genre::Value genre, int year, long views, float rating) {

    Content new_content(title, type, genre, year, views, rating);
    contents.insert(new_content);

    return &contents.get_head()->info; // insert() sempre poe no head da lista
}

bool AdminService::edit_content(int id, const std::string & title, Type type, Genre::Value genre, int year, long views, float rating) {

    Content * target = contents.search(id);
    if (target == nullptr) return false;

    target->set_title(title);
    target->set_type(type);
    target->set_genre(genre);
    target->set_year(year);
    target->set_views(views);
    target->set_rating(rating);

    return true;
}

bool AdminService::remove_content(int id) {

    if (contents.search(id) == nullptr) return false;

    contents.pop(id);
    return true;
}