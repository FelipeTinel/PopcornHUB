#pragma once

#include <iostream>
#include <string>

class User {

    private:

        static int next_id;

        int id;
        std::string name;
        std::string password;

    public:

        User ();
        User (std::string _name, std::string _password);
        User (int id, std::string _name, std::string password);

        int get_id() const;
        std::string get_name() const;
        std::string get_password() const;

        void set_name(std::string new_name);
        void set_password(std::string new_password);

};