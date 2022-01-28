#include "lexical_analysis.h"

//-----------

namespace Differenciator
{

TextDiff::TextDiff (const std::string& path_base)
{
    assert (this);

    num_symbols_ = num_symbols_in_file (path_base);
    buf_data_    = new char [num_symbols_ + 1] {};

    create_buffer_data  (path_base);
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

void BufNodes::create_buffer_nodes()
{
    std::size_t i_data      = 0;
    std::size_t num_symbols = source_text_.get_num_symbols ();

    const char* symb        = source_text_.get_buffer_data ();
    const char* start_symb  = symb;

    while (*symb != '\0')
    {
        if (strchr ("+-*/^()", *symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);

            push (symb, NodeType::OPER);
            symb++;
        }
        else if (isdigit (*symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);
            
            push (symb, NodeType::NUMB);

            symb++;
            while (symb - start_symb < num_symbols && isdigit (*symb))
                symb++;

        }
        else if (isalpha (*symb))
        {
            //printf ("buf_data_[indx] = %c\n", buf_data_[i_data]);

            push (symb, NodeType::VARB);

            symb++;
            while (symb - start_symb < num_symbols && isalpha (*symb))
                symb++;

        }
        else
        {
            symb++;
        }
    }

    push (symb, NodeType::NONE);

    return;
}

//----------

BufNodes::BufNodes (const std::string& path_base, std::size_t max_nodes) :
    source_text_ {path_base},
    max_nodes_   {max_nodes}
{
    buf_nodes_ = new NodeDiff [max_nodes_] {};
}

//----------

BufNodes::~BufNodes ()
{
    dump (PATH_BUF_NODES_DUMP);

    delete [] buf_nodes_;
    buf_nodes_ = nullptr;
}

//----------

bool BufNodes::push (const char* symb, NodeType type)
{
    if (length_ == max_nodes_)
        resize ();

    buf_nodes_[length_].type_ = type;

    switch (buf_nodes_[length_].type_)
    {
        case NodeType::NUMB: buf_nodes_[length_].value_numb_ = strtol (symb, NULL, 10);
                             break;

        case NodeType::VARB: buf_nodes_[length_].value_varb_ = *symb;
                             break;

        case NodeType::OPER: buf_nodes_[length_].value_oper_ = *symb;
                             break;

        case NodeType::NONE: break;

        default:             printf("ERROR! Type: %d\n", (int) buf_nodes_[length_].type_);
                             break;
    }

    length_++;

    return true;
}

//----------

bool BufNodes::resize ()
{
    std::size_t new_max_nodes = 2 * max_nodes_;
    NodeDiff*   new_buf_nodes = new NodeDiff [new_max_nodes];
    
    std::copy_n (buf_nodes_, new_max_nodes, new_buf_nodes);

    delete [] buf_nodes_;
    max_nodes_ = new_max_nodes;
    buf_nodes_ = new_buf_nodes;

    return true; 
}

//----------

NodeDiff& BufNodes::operator[] (const int indx)
{
    return buf_nodes_[indx];
}

//----------

const NodeDiff& BufNodes::operator[] (const int indx) const
{
    return buf_nodes_[indx];
}

//----------

void BufNodes::dump (const std::string& path_dump) const
{
    FILE*   dump_BufNodes = fopen (path_dump.c_str(), "wb");
    assert (dump_BufNodes);

    fprintf (dump_BufNodes, "        >-- BufNodes dump --<  \n"
                            "    | max_nodes_ = %ld,\n"
                            "    | length_    = %ld \n"
                                                   "\n", max_nodes_, length_);

    for (std::size_t i = 0; i < length_; i++)
    {
        fprintf (dump_BufNodes, "(%-3ld) ", i + 1);
        buf_nodes_[i].print_data (dump_BufNodes);
    }

    fprintf (dump_BufNodes, "\n");

    fclose (dump_BufNodes);
    dump_BufNodes = nullptr;
}

//----------

}; // namespace Differenciator

