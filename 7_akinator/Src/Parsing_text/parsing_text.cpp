//--------------------------------------------------

#include "parsing_text.hpp"

//--------------------------------------------------

Text::Text (const std::string& path_base)
{
    assert (this);

    create_buffer_data   (path_base);
    create_buffer_lexems ();
}

//----------

Text::~Text()
{
    assert (this);

    delete [] buf_data_;
    delete [] buf_lexems_;
}

//----------

void Text::num_symbols_in_file (FILE* akin_base)
{
    std::size_t start_value = ftell (akin_base);
    fseek (akin_base, 0, SEEK_END);

    num_symbols_ = ftell (akin_base);
    fseek (akin_base, start_value, SEEK_SET);
}

//----------

void Text::create_buffer_data (const std::string& path_base)
{
    FILE* akin_base = fopen (path_base.c_str(), "rb");
    assert (akin_base);

    num_symbols_in_file (akin_base);

    printf ("num_symbols_ = %zu\n", num_symbols_);
    buf_data_ = new char[num_symbols_ + 1] {};

    fread (buf_data_, sizeof(char), num_symbols_, akin_base);

    fclose (akin_base);
}
//----------

std::size_t Text::num_lexems_in_buf()
{
    std::size_t indx       = 0;
    std::size_t num_lexems = 0;

    while (buf_data_[indx] != '\0')
    {
        if (buf_data_[indx] == '?' ||
            buf_data_[indx] == '@' ||
            buf_data_[indx] == '<' ||
            buf_data_[indx] == '>' ||
            buf_data_[indx] == 'V'   )
        {
            num_lexems++;
        }

        indx++;
    }


    return num_lexems;
}

//----------

void Text::create_buffer_lexems()
{
    num_lexems_ = num_lexems_in_buf();
    buf_lexems_ = new Token[num_lexems_] {};

    for (int i = 0; i < num_symbols_; i++)
    {
        while (i < num_symbols_ &&  isspace (buf_data_[i]))
            i++;

        int begin = i;

        while (i < num_symbols_ && !isspace (buf_data_[i]))
            i++;

        int end        = i;
        buf_data_[end] = '\0';

        printf("FOUND:\n");
        printf("begin = %d, end = %d, end - begin = %d, ", begin, end, end - begin);
        printf("buf_data_ + begin = {%s}\n\n", buf_data_ + begin);

        if      (buf_data_[begin] == '?' ||
                 buf_data_[begin] == '@'   )
        {
            buf_lexems_->type       = TokenType::STRING;
            buf_lexems_->value_str  = buf_data_ + begin + 1;

            printf("TOKEN: STRING, "
                   "buf_lexems_->value_str  = {%s}\n", buf_lexems_->value_str.c_str());
        }
        else if (buf_data_[begin] == '>' ||
                 buf_data_[begin] == '<' ||
                 buf_data_[begin] == 'V'   )
        {
            buf_lexems_->type       = TokenType::OPER;
            buf_lexems_->value_oper = *(buf_data_ + begin);

            printf("TOKEN: OPER, "
                   "buf_lexems_->value_oper = {%c}\n", buf_lexems_->value_oper);
        }
        else
        {
            printf("OLO, REBYAT U VAS KAKBE SYNTX ERROR! AT POSITION [%d]\n", i);
            printf("symb = %c[%d]\n", *(buf_data_ + i), *(buf_data_ + i));
        }
    }
}

//----------

void Text::skip_space (char* buf_data_, std::size_t* indx_buf)
{
    while (!isspace (buf_data_[*indx_buf]))
        (*indx_buf)++;

    buf_data_[*indx_buf] = '\0';   
}

//----------

const char* Text::get_buffer_data() const
{
    return buf_data_;
}

//----------

std::size_t Text::get_num_symbols() const
{
    return num_symbols_;
}


//--------------------------------------------------
