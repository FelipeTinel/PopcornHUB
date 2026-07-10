#include <iostream>

#include "containers/doubly_linked_list.hpp"
#include "core/content.hpp"
#include "services/content_manager.hpp"

int main () {

    DoublyLinkedList<Content> list;
    ContentManager manager{"../tests/data/content_test.txt"};

    Content content1{"Interstellar", Type::MOVIE, Genre::SCIENCE_FICTION, 2014, 950000, 4.9};
    Content content2{"Minecraft", Type::MOVIE, Genre::ACTION, 2025, 950000, 5.0};
    Content content3{"Duna parte 3", Type::MOVIE, Genre::ACTION, 2010, 950000, 0.5};

    list.insert(content1);
    list.insert(content2);
    list.insert(content3);

    manager.save_data(list);

    content2 = list.pop(2);

    manager.save_data(list);

}