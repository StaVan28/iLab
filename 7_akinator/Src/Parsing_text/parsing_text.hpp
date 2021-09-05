#ifndef PARSING_TEXT
#define PARSING_TEXT

//--------------------------------------------------

#include "settings.hpp"

//--------------------------------------------------

class Text
{
    private:

        char*  buffer_data_ = nullptr;
        size_t num_symbols_ = 0;

        void num_symbols_in_file(FILE* akin_base);
        void create_buffer(const std::string path_base);

    public:

        Text() = delete;
        Text(const std::string path_base);
       ~Text();
};

//--------------------------------------------------

#endif //PARSING_TEXT
