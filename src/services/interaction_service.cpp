#include <iostream>

#include "services/interaction_service.hpp"

InteractionService::InteractionService(AuthService& auth, DoublyLinkedList<Comment>& comments): 
    
    auth_service(auth), 
    global_comments(comments) 
    
{}

void InteractionService::watch_content(Content& content) { content.add_views(1); }

bool InteractionService::add_comment_to_content(Content& content, const std::string& text) {

    if (auth_service.is_logged_in()) {
        
        int user_id = auth_service.get_current_user()->get_id();
        int content_id = content.get_id();

        Comment new_comment(content_id, user_id, text);

        global_comments.insert(new_comment);

        return true;
    
    }
    
    return false;
}

bool InteractionService::rate_content(Content & content, float new_note) {
    
    if (auth_service.is_logged_in()) {
        
        content.add_rating(new_note); 
        return true;

    }

    return false;
}