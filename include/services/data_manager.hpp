#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "containers/doubly_linked_list.hpp"

template<typename T>
class DataManager {

    protected:

        std::string data_file;
        DoublyLinkedList main_list;
 
        template <typename U>
        void file_frame (std::ofstream & file, U info) { file << info << ";"; }

    public:

        explicit DataManager (const std::string & data_file): data_file(data_file) {}

        virtual void save_data() = 0;
        virtual void load_data() = 0;

        virtual DoublyLinkedList get_list() { return main_list; }

        virtual ~ DataManager() = default;

};