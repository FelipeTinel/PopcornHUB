#include <iostream>

#include "core/comment.hpp"

int Comment::next_id = 1;

Comment::Comment (): id(0), content_id(0), user_id(0), text("") {}

Comment::Comment(int _content_id, int _user_id, std::string _text): id(next_id++), content_id(_content_id), user_id(_user_id), text(_text) {}

Comment::Comment(int id, int _content_id, int _user_id, std::string _text): id(id), content_id(_content_id), user_id(_user_id), text(_text) 
{
    if (id >= next_id) next_id += 1;
}

int Comment::get_id () const { return id; }
int Comment::get_content_id () const { return content_id; }
int Comment::get_user_id () const { return user_id; }
std::string Comment::get_comment () const { return text; };
        
void Comment::set_comment (std::string new_comment) { text = new_comment; }