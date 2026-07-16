#include <iostream>

#include "services/interaction_service.hpp"

InteractionService::InteractionService(AuthService& auth, DoublyLinkedList<Comment>& comments): 
    
    auth_service(auth), 
    global_comments(comments),
    rated_head(nullptr)
    
{}

InteractionService::~InteractionService() {

    RatedNode * current = rated_head;

    while (current != nullptr) {
        RatedNode * next = current->next;
        delete current;
        current = next;
    }
}

void InteractionService::seed_watch_history(const DoublyLinkedList<Content> & contents) {

    Node<Content> * node = contents.get_head();
    while (node != nullptr) {

        long views = node->info.get_views();
        if (views > 0) {
            WatchedEntry entry(node->info.get_id(), node->info.get_title(),
                                node->info.get_type(), node->info.get_genre(), views);
            watch_history.insert_sorted(entry, watched_desc);
        }

        node = node->next;
    }
}

void InteractionService::watch_content(Content& content) {

    content.add_views(1);

    //procura se ja existe uma entrada pra esse conteudo no historico.
    WatchedEntry * existing = watch_history.search(content.get_id());

    if (existing != nullptr) {
        //ja existe: precisamos tirar da lista, incrementar e reinserir
        //ordenado, porque a posicao dele pode ter mudado.
        WatchedEntry updated(*existing);
        updated.add_watch();
        watch_history.pop(content.get_id());
        watch_history.insert_sorted(updated, watched_desc);
    } else {
        //primeira vez que esse conteudo e assistido.
        WatchedEntry new_entry(content.get_id(), content.get_title(), content.get_type(), content.get_genre(), 1);
        watch_history.insert_sorted(new_entry, watched_desc);
    }
}

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

bool InteractionService::has_rated(int user_id, int content_id) const {

    RatedNode * current = rated_head;

    while (current != nullptr) {
        if (current->user_id == user_id && current->content_id == content_id) return true;
        current = current->next;
    }

    return false;
}

bool InteractionService::rate_content(Content & content, float new_note) {
    
    if (!auth_service.is_logged_in()) return false;

    int user_id = auth_service.get_current_user()->get_id();
    int content_id = content.get_id();

    if (has_rated(user_id, content_id)) return false;

    content.add_rating(new_note);

    RatedNode * new_node = new RatedNode{user_id, content_id, rated_head};
    rated_head = new_node;

    return true;
}