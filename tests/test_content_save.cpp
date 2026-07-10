#include <iostream>

#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"
#include "services/content_manager.hpp"
#include "core/user.hpp"
#include "services/user_manager.hpp"
#include "core/comment.hpp"
#include "services/comment_manager.hpp"

int main () {

    DoublyLinkedList<Content> ctlist;
    DoublyLinkedList<User> ulist;
    DoublyLinkedList<Comment> cmlist;

    ContentManager ctmanager{"../tests/data/content_test.txt"};
    UserManager umanager{"../tests/data/user_test.txt"};
    CommentManager cmmanager{"../tests/data/comment_test.txt"};

    Content content1{"Interstellar", Type::MOVIE, Genre::SCIENCE_FICTION, 2014, 950000, 4.9};
    Content content2{"Minecraft", Type::MOVIE, Genre::ACTION, 2025, 950000, 5.0};
    Content content3{"Duna parte 3", Type::MOVIE, Genre::ACTION, 2010, 950000, 0.5};

    User user1 {"Felipe", "123"};
    User user2 {"Marcelo", "456"};
    User user3 {"Janderson", "789"};

    Comment comment1 {1, 1, "Cara que filme bosta"};
    Comment comment2 {2, 2, "Aaaaaaiiii eu amo minecraft o filmeee"};

    ulist.insert(user1);
    ulist.insert(user2);
    ulist.insert(user3);

    cmlist.insert(comment1);
    cmlist.insert(comment2);

    ctlist.insert(content1);
    ctlist.insert(content2);
    ctlist.insert(content3);

    ctmanager.save_data(ctlist);

    umanager.save_data(ulist);

    cmmanager.save_data(cmlist);

    content2 = ctlist.pop(2);

    ctmanager.save_data(ctlist);

}