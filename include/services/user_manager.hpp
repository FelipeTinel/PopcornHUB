#pragma once

#include <iostream>
#include <fstream>

#include "data_manager.hpp"
#include "core/user.hpp"
#include "containers/doubly_linked_list.hpp"

class UserManager : DataManager<User> {

    private:

        void user_frame(std::ofstream & file, const User  & user);

    public: 

        UserManager (const std::string  & data_file) : DataManager<User>(data_file) {}

        void save_data(const DoublyLinkedList<User> & list) override;
        void load_data(DoublyLinkedList<User> & list) override;

};