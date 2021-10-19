//--------------------------------------------------

#include "parsing_text.hpp"

//--------------------------------------------------

Text::Text (const std::string& path_base)
{
    assert (this);

    create_buffer_data (path_base);
}

//----------

Text::~Text()
{
    assert (this);

    delete [] buf_data_;
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
            buf_data_[indx] == '>'   )
        {
            num_lexems++;
        }

        indx++;
    }


    return num_lexems;
}

//----------

Token* Text::create_buffer_lexems()
{
    std::size_t num_lexems = num_lexems_in_buf();
    Token*      buf_lexems = new Token[num_lexems + 1] {};
    std::size_t cur_lex    = 0;


    for (int i = 0; i < num_symbols_; i++)
    {
        while (i < num_symbols_ &&  isspace (buf_data_[i]))
            i++;

        int begin = i;

        while (i < num_symbols_ && !isspace (buf_data_[i]))
            i++;

        int end        = i;
        buf_data_[end] = '\0';
/*
        printf("FOUND:\n");
        printf("begin = %d, end = %d, end - begin = %d, ", begin, end, end - begin);
        printf("buf_data_ + begin = {%s}\n\n", buf_data_ + begin);
*/
        if      (buf_data_[begin] == '?' ||
                 buf_data_[begin] == '@'   )
        {

            buf_lexems[cur_lex].type = (buf_data_[begin] == '?') ? (TokenType::QUESTION) : (TokenType::ANSWER);
            buf_lexems[cur_lex].value_str  = buf_data_ + begin + 1;
            cur_lex++;
/*
            printf("TOKEN: STRING, "
                   "buf_lexems_->value_str  = {%s}\n", buf_lexems->value_str.c_str());
*/      }
        else if (buf_data_[begin] == '>' ||
                 buf_data_[begin] == '<'   )
        {
            buf_lexems[cur_lex].type       = TokenType::OPER;
            buf_lexems[cur_lex].value_oper = *(buf_data_ + begin);
            cur_lex++;

//          printf("TOKEN: OPER, "
//                 "buf_lexems_->value_oper = {%c}\n", buf_lexems->value_oper);
        }
        else
        {
            printf("OLO, REBYAT U VAS KAKBE SYNTX ERROR! AT POSITION [%d]\n", i);
            printf("symb = %c[%d]\n", *(buf_data_ + i), *(buf_data_ + i));
        }
    }

    return buf_lexems;
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
