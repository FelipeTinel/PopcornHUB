#include <iostream>

#include "core/user.hpp"

int User::next_id = 1;

User::User (): id(0), name(""), password("") {}

User::User(std::string _name, std::string _password): id(next_id++), name(_name), password(_password) {}

User::User(int id, std::string _name, std::string _password): id(id), name(_name), password(_password) 
{
    if (id >= next_id) next_id += 1;
}

int User::get_id () const { return id; }
std::string User::get_name () const { return name; }
std::string User::get_password () const { return password; }

void User::set_name (std::string new_name) { name = new_name; }
void User::set_password (std::string new_password) { password = new_password; }

