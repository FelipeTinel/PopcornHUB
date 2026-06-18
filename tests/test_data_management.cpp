#include <iostream>
#include <fstream>

#include "services/content_manager.hpp"
#include "core/content.hpp"
#include "core/genre.hpp"
#include "core/type.hpp"

int main () {

    Content content{"Interstellar", Type::MOVIE, Genre::SCIENCE_FICTION, 2014, 950000, 4.9};
    ContentManager content_manager{"../tests/data/content_test.txt"};

    content_manager.write_data(content);

}