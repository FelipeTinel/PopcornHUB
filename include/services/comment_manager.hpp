#pragma once

#include <iostream>
#include <fstream>

#include "data_manager.hpp"
#include "core/comment.hpp"
#include "containers/doubly_linked_list.hpp"

class CommentManager : DataManager<Comment> {

    private:

        void comment_frame(std::ofstream & file, const Comment  & comment);

    public: 

        CommentManager (const std::string  & data_file) : DataManager<Comment>(data_file) {}

        void save_data(const DoublyLinkedList<Comment> & list) override;
        void load_data(DoublyLinkedList<Comment> & list) override;

};