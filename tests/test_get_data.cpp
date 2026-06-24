#include <iostream>
#include <fstream>

#include "services/content_manager.hpp"
#include "core/content.hpp"
#include "core/genre.hpp"
#include "core/type.hpp"

int main () {

    ContentManager c_manager{"../tests/data/content_test.txt"};

    Content * content = c_manager.get_data(1);

    if (content != nullptr) { 
        std::cout << content->get_title() << std::endl;
    } else {
        std::cerr << "Não foi possível encotrar o conteúdo" << std::endl;
    }

}