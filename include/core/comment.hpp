#pragma once

#include <iostream>
#include <string>

class Comment {

    private:

        static int next_id;

        int id, content_id, user_id;
        std::string text;

    public:    
    
        Comment ();
        Comment (int _content_id, int _user_id, std::string _text);
        Comment (int id, int _content_id, int _user_id, std::string _text);


        int get_id () const;
        int get_content_id () const;
        int get_user_id () const;
        std::string get_comment () const;
        
        void set_comment (std::string new_comment);

};