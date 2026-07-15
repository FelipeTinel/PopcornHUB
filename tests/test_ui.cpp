#include "ui/window.hpp"
#include "services/auth_service.hpp"
#include "services/interaction_service.hpp"
#include "services/content_manager.hpp"
#include "services/user_manager.hpp"
#include "services/comment_manager.hpp"
#include "containers/doubly_linked_list.hpp"
#include "services/admin_service.hpp"
#include "core/user.hpp"
#include "core/content.hpp"
#include "core/comment.hpp"
#include "core/type.hpp"
#include "core/genre.hpp"

int main() {

    DoublyLinkedList<User> users;
    DoublyLinkedList<Content> contents;
    DoublyLinkedList<Comment> comments;

    UserManager user_manager{"..tests/data/user_test.txt"};
    ContentManager content_manager{"../tests/data/content_test.txt"};
    CommentManager comment_manager{"../tests/data/comment_test.txt"};

    user_manager.load_data(users);
    content_manager.load_data(contents);
    comment_manager.load_data(comments);

    if (contents.get_head() == nullptr) {

        Content c1{"Interstellar", Type::MOVIE, Genre::SCIENCE_FICTION, 2014, 950000, 4.9f};
        Content c2{"Minecraft", Type::MOVIE, Genre::ACTION, 2025, 950000, 5.0f};

        contents.insert(c1);
        contents.insert(c2);
    }

    AuthService auth(users);
    InteractionService interaction(auth, comments);
    AdminService content_admin(contents);

    Window window(auth, interaction, content_admin, contents, comments);
    window.run();

    content_manager.save_data(contents);
    comment_manager.save_data(comments);
    user_manager.save_data(users);

    return 0;
}