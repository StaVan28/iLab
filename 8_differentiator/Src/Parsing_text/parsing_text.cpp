#include "parsing_text.h"

//-----------

namespace Differenciator
{

TextDiff::TextDiff (const std::string& path_base) :
    buf_tokens_ {START_NUM_TOKENS}
{
    assert (this);

    create_buffer_data   (path_base);
    create_buffer_tokens ();
}

//----------

TextDiff::~TextDiff()
{
    assert (this);

    delete [] buf_data_;
}

//----------

void TextDiff::num_symbols_in_file (FILE* diff_base)
{
    std::size_t start_value = ftell (diff_base);
    fseek (diff_base, 0, SEEK_END);

    num_symbols_ = ftell (diff_base);
    fseek (diff_base, start_value, SEEK_SET);
}

//----------

void TextDiff::create_buffer_data (const std::string& path_base)
{
    FILE*   diff_base = fopen (path_base.c_str(), "rb");
    assert (diff_base);

    num_symbols_in_file (diff_base);

    buf_data_ = new char [num_symbols_ + 1] {};

    fread (buf_data_, sizeof (char), num_symbols_, diff_base);  

    fclose (diff_base);
}

//----------

void TextDiff::create_buffer_tokens()
{
    std::size_t i_data = 0;
    const char* symb   = buf_data_;

    while (*symb != '\0')
    {
        if (strchr ("+-*/^()", *symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);

            buf_tokens_.push (symb, TokenType::OPER);
            symb++;
        }
        else if (isdigit (*symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);
            
            buf_tokens_.push (symb, TokenType::NUMB);

            symb++;
            while (symb - buf_data_ < num_symbols_ && isdigit (*symb))
                symb++;

        }
        else if (isalpha (*symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);

            buf_tokens_.push (symb, TokenType::VARB);

            symb++;
            while (symb - buf_data_ < num_symbols_ && isalpha (*symb))
                symb++;

        }
        else
        {
            symb++;
        }
    }


    return;
}

//----------

const char* TextDiff::get_buffer_data() const
{
    return buf_data_;
}

//----------

std::size_t TextDiff::get_num_symbols() const
{
    return num_symbols_;
}

//----------

BufTokens::BufTokens (std::size_t num_tokens) :
    num_tokens_ {num_tokens}
{
    buf_tokens_ = new TokenDiff [num_tokens_] {};
}

//----------

BufTokens::~BufTokens ()
{
    dump(PATH_BUF_TOKENS_DUMP);

    delete [] buf_tokens_;
    buf_tokens_ = nullptr;
}

//----------

bool BufTokens::push (const char* symb, TokenType type)
{
    if (length_ == num_tokens_)
        resize ();

    buf_tokens_[length_].type_ = type;

    switch (buf_tokens_[length_].type_)
    {
        case TokenType::NUMB: buf_tokens_[length_].value_numb_ = strtol (symb, NULL, 10);
                              break;

        case TokenType::VARB: buf_tokens_[length_].value_varb_ = *symb;
                              break;

        case TokenType::OPER: buf_tokens_[length_].value_oper_ = *symb;
                              break;

        default:             printf("ERROR! Type: %d\n", buf_tokens_[length_].type_);
                             break;
    }

    length_++;

    return true;
}

//----------

bool BufTokens::resize ()
{
    std::size_t new_num_tokens = 2 * num_tokens_;
    TokenDiff*  new_buf_tokens = new TokenDiff [new_num_tokens];
    
    std::copy_n (buf_tokens_, new_num_tokens, new_buf_tokens);

    delete [] buf_tokens_;
    num_tokens_ = new_num_tokens;
    buf_tokens_ = new_buf_tokens;

    return true; 
}

//----------

TokenDiff& BufTokens::operator[] (const int indx)
{
    return buf_tokens_[indx];
}

//----------

const TokenDiff& BufTokens::operator[] (const int indx) const
{
    return buf_tokens_[indx];
}

//----------

void BufTokens::dump (const char* path_dump) const
{
    FILE*   dump_BufTokens = fopen (path_dump, "wb");
    assert (dump_BufTokens);

    fprintf (dump_BufTokens, "        >-- BufToken dump --<  \n"
                             "    | num_tokens_ = %d,\n"
                             "    | length_     = %d \n"
                                                    "\n", num_tokens_, length_);

    for (std::size_t i = 0; i < length_; i++)
    {
        fprintf (dump_BufTokens, "(%-3d) ", i + 1);
        buf_tokens_[i].print_data (dump_BufTokens);
    }

    fprintf (dump_BufTokens, "\n");

    fclose (dump_BufTokens);
}

//----------

}; // namespace Differenciator

