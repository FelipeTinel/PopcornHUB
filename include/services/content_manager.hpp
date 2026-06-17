#include <iostream>
#include <fstream>
#include <string>

#include "data_manager.hpp"

class ContentManager : public DataManager<Content> {

    private:

        void content_frame (std::ofstream & file, Content & content);

    public:

        ContentManager (std::string & data_file) : DataManager(data_file) {}

        void write_data(Content & content) override;
        void update_data (int id, Content & content) override;
        void remove_data(int id) override;
        Content * get_data(int id) override;


};