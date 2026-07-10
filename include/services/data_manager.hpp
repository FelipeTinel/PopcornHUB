#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "containers/doubly_linked_list.hpp"
#include "containers/node.hpp"
template<typename T>
class DataManager {

    protected:

        std::string data_file;
 
        template <typename U>
        void file_frame (std::ofstream & file, U info) { file << info << ";"; }

    public:

        explicit DataManager (const std::string & data_file): data_file(data_file) {}

        virtual void save_data(const DoublyLinkedList<T> & list) = 0;
        virtual Node<T> * load_data() = 0;
    
        virtual ~ DataManager() = default;

};