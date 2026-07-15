#pragma once

#include <iostream>
#include <string>

#include <containers/doubly_linked_list.hpp>
#include <core/user.hpp>

class AuthService {

    private:

        DoublyLinkedList<User> & user_list;
        User * current_user;

        User * find_by_name (const std::string & username);

    public:

        AuthService(DoublyLinkedList<User> & global_list);

        bool register_user(const std::string& username, const std::string& password);
        bool login_user(const std::string& username, const std::string& password);

        void logout();

        bool is_logged_in() const { return current_user != nullptr; }
        User * get_current_user() const { return current_user; }
        User * find_by_id(int id) const;


};