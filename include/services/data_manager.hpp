#pragma once

#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class DataManager {

    protected:

        std::string data_file;

        template <typename U> 
        void file_frame (std::ofstream & file, U info) { file << info << ";"; }

    public:

        explicit DataManager (const std::string & data_file): data_file(data_file) {}

        virtual void save_data(const T & data) = 0;
        virtual T * load_data(int id) = 0;

        virtual ~ DataManager() = default;

};