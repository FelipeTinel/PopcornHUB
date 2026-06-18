#include <iostream>
#include <fstream>
#include <string>

#include "data_manager.hpp"
#include "core/content.hpp"

class ContentManager : public DataManager<Content> {

    private:

        void content_frame (std::ofstream & file, const Content & content);

    public:

        explicit ContentManager (const std::string & data_file) : DataManager(data_file) {}

        void write_data(const Content & content) override;
        void update_data (int id, const Content & content) override;
        void remove_data(int id) override;
        Content * get_data(int id) override;


};