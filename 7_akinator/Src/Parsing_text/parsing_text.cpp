//--------------------------------------------------

#include "parsing_text.hpp"

//--------------------------------------------------

Text::Text(const std::string path_base)
{
    assert(this);

    create_buffer(path_base);
}

//----------

Text::~Text()
{
    assert(this);

    free(buffer_data_);
    
}

//----------

void Text::num_symbols_in_file(FILE* akin_base)
{
    std::size_t start_value = ftell(akin_base);
    fseek(akin_base, 0, SEEK_END);

    num_symbols_ = ftell(akin_base);
    fseek(akin_base, start_value, SEEK_SET);
}

//----------

void Text::create_buffer(const std::string path_base)
{
    FILE* akin_base = fopen(path_base.c_str(), "rb");
    assert(akin_base);

    num_symbols_in_file(akin_base);

    buffer_data_ = (char*) calloc(num_symbols_ + 1, sizeof(char));
    assert(buffer_data_);

    fread(buffer_data_, sizeof(char), num_symbols_, akin_base);

    fclose(akin_base);
}

//----------

const char* Text::get_buffer_data() const
{
    return buffer_data_;
}

//----------

std::size_t Text::get_num_symbols() const
{
    return num_symbols_;
}


//--------------------------------------------------
