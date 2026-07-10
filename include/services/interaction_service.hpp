#pragma once

#include <iostream>

#include "services/auth_service.hpp"
#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"
#include "core/comment.hpp"

class InteractionService {

    private:
        
        AuthService & auth_service;             
        DoublyLinkedList<Comment> & global_comments;

    public:

        InteractionService(AuthService & auth, DoublyLinkedList<Comment> & comments);

        void watch_content(Content & content);
        bool add_comment_to_content(Content& content, const std::string & text);
        void rate_content(Content & content);
};