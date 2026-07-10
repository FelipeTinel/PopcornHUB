#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "data_manager.hpp"
#include "core/content.hpp"
#include "containers/doubly_linked_list.hpp"

class ContentManager : public DataManager<Content> {

    private:

        void content_frame (std::ofstream & file, const Content & content);

    public:

        ContentManager (const std::string & data_file) : DataManager<Content>(data_file) {}

        void save_data(const DoublyLinkedList<Content> & list) override;
        Node<Content> * load_data() override;
        
};