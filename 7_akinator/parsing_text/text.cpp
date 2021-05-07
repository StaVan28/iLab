
#include "text.h"

//-----------------------------------------------------------------------------

AkinatorText::AkinatorText()
{
    assert(this);

    printf("!\n!!\n!!!\n!!!!\n Attention! This class didn't work with basic constructor," \
           " plz use AkinatorText(const std::string base_path)\n!!!!\n!!!\n!!\n!\n");
}

//-----------------------------------------------------------------------------

AkinatorText::AkinatorText(const std::string base_path)
{
    assert(this);

    FILE* base_file = fopen(base_path.c_str(), "rb");
    assert(base_file);

    num_symbols_ = num_symbols_in_file(base_file);

    buffer_data_ = new char[num_symbols_ + 1];
    assert(buffer_data_);

    fread(buffer_data_, sizeof(char), num_symbols_, base_file);

    fclose(base_file);
}


//-----------------------------------------------------------------------------

AkinatorText::~AkinatorText()
{
    assert(this);

    if (buffer_data_)
    {
        delete [] buffer_data_;
        buffer_data_ = nullptr;
    }
}

//-----------------------------------------------------------------------------

std::size_t AkinatorText::num_symbols_in_file(FILE* base_file) const noexcept
{
    assert(this);
    assert(base_file);

    std::size_t start_value     = ftell(base_file);
    fseek(base_file, 0, SEEK_END);

    std::size_t tmp_num_symbols = ftell(base_file);
    fseek(base_file, start_value, SEEK_SET);

    return tmp_num_symbols;
}

//-----------------------------------------------------------------------------

std::size_t AkinatorText::num_symbols() const noexcept
{
    return num_symbols_;
}

//-----------------------------------------------------------------------------

char* AkinatorText::buffer_data() const noexcept
{
    return buffer_data_;
}