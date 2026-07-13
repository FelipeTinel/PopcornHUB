#include <iostream>

#include "containers/node.hpp"
#include "services/auth_service.hpp"
#include "containers/doubly_linked_list.hpp"
#include "services/user_manager.hpp"

AuthService::AuthService (DoublyLinkedList<User> & global_list): user_list(global_list), current_user(nullptr) {}

User * AuthService::find_by_name(const std::string & username) {
    
    Node<User> * temp = user_list.get_head();

    while (temp != nullptr) {

        if (temp->info.get_name() == username) return & (temp->info);

        temp = temp->next;

    }

    return nullptr; 
}

bool AuthService::register_user(const std::string & username, const std::string & password) {
    
    if (find_by_name(username) != nullptr) return false;
    
    User new_user(username, password);
    user_list.insert(new_user);
    return true;

}

bool AuthService::login_user(const std::string & username, const std::string & password) {
    
    User * user = find_by_name(username);
    
    if (user != nullptr && user->get_password() == password) {
        current_user = user;
        return true;
    }

    return false;
}

void AuthService::logout() { current_user = nullptr; }