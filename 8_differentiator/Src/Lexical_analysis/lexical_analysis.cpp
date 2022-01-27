#include "lexical_analysis.h"

//-----------

namespace Differenciator
{

TextDiff::TextDiff (const std::string& path_base) :
    buf_nodes_ {START_MAX_NODES}
{
    assert (this);

    num_symbols_ = num_symbols_in_file (path_base);
    buf_data_    = new char [num_symbols_ + 1] {};

    create_buffer_data  (path_base);
    create_buffer_nodes ();
}

//----------

TextDiff::~TextDiff()
{
    assert (this);

    delete [] buf_data_;
    buf_data_ = nullptr;
}

//----------

std::size_t TextDiff::num_symbols_in_file (const std::string& path_base)
{
    FILE*   diff_base = fopen (path_base.c_str(), "rb");
    assert (diff_base);

    std::size_t start_value = ftell (diff_base);
    fseek (diff_base, 0, SEEK_END);

    std::size_t num_symbols = ftell (diff_base);
    fseek (diff_base, start_value, SEEK_SET);

    fclose (diff_base);
    diff_base = nullptr;

    return num_symbols;
}

//----------

void TextDiff::create_buffer_data (const std::string& path_base)
{
    FILE*   diff_base = fopen (path_base.c_str(), "rb");
    assert (diff_base);

    fread (buf_data_, sizeof (char), num_symbols_, diff_base);  

    fclose (diff_base);
    diff_base = nullptr;
}

//----------

void TextDiff::create_buffer_nodes()
{
    std::size_t i_data = 0;
    const char* symb   = buf_data_;

    while (*symb != '\0')
    {
        if (strchr ("+-*/^()", *symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);

            buf_nodes_.push (symb, NodeType::OPER);
            symb++;
        }
        else if (isdigit (*symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);
            
            buf_nodes_.push (symb, NodeType::NUMB);

            symb++;
            while (symb - buf_data_ < num_symbols_ && isdigit (*symb))
                symb++;

        }
        else if (isalpha (*symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);

            buf_nodes_.push (symb, NodeType::VARB);

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

BufNodes::BufNodes (std::size_t max_lexems) :
    max_lexems_ {max_lexems}
{
    buf_lexems_ = new NodeDiff [max_lexems_] {};
}

//----------

BufNodes::~BufNodes ()
{
    dump (PATH_BUF_NODES_DUMP);

    delete [] buf_lexems_;
    buf_lexems_ = nullptr;
}

//----------

bool BufNodes::push (const char* symb, NodeType type)
{
    if (length_ == max_lexems_)
        resize ();

    buf_lexems_[length_].type_ = type;

    switch (buf_lexems_[length_].type_)
    {
        case NodeType::NUMB: buf_lexems_[length_].value_numb_ = strtol (symb, NULL, 10);
                             break;

        case NodeType::VARB: buf_lexems_[length_].value_varb_ = *symb;
                             break;

        case NodeType::OPER: buf_lexems_[length_].value_oper_ = *symb;
                             break;

        default:             printf("ERROR! Type: %d\n", (int) buf_lexems_[length_].type_);
                             break;
    }

    length_++;

    return true;
}

//----------

bool BufNodes::resize ()
{
    std::size_t new_max_lexems = 2 * max_lexems_;
    NodeDiff*   new_buf_lexems = new NodeDiff [new_max_lexems];
    
    std::copy_n (buf_lexems_, new_max_lexems, new_buf_lexems);

    delete [] buf_lexems_;
    max_lexems_ = new_max_lexems;
    buf_lexems_ = new_buf_lexems;

    return true; 
}

//----------

NodeDiff& BufNodes::operator[] (const int indx)
{
    return buf_lexems_[indx];
}

//----------

const NodeDiff& BufNodes::operator[] (const int indx) const
{
    return buf_lexems_[indx];
}

//----------

void BufNodes::dump (const char* path_dump) const
{
    FILE*   dump_BufNodes = fopen (path_dump, "wb");
    assert (dump_BufNodes);

    fprintf (dump_BufNodes, "        >-- BufNodes dump --<  \n"
                            "    | max_nodes_ = %ld,\n"
                            "    | length_    = %ld \n"
                                                   "\n", max_lexems_, length_);

    for (std::size_t i = 0; i < length_; i++)
    {
        fprintf (dump_BufNodes, "(%-3ld) ", i + 1);
        buf_lexems_[i].print_data (dump_BufNodes);
    }

    fprintf (dump_BufNodes, "\n");

    fclose (dump_BufNodes);
    dump_BufNodes = nullptr;
}

//----------

}; // namespace Differenciator

