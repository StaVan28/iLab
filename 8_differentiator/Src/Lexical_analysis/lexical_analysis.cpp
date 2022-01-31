#include "lexical_analysis.h"

//-----------

namespace Differenciator
{

//-----------

TextDiff::TextDiff ()
{}

//-----------

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

BufNodes::BufNodes () :
    source_text_ {DEFAULT_SOURCE_TEXT},
    buf_lexems_  {nullptr}, 
    max_lexems_  {START_MAX_NODES},
    length_      {0}
{
    buf_lexems_ = new NodeDiff [max_lexems_] {};

    create_buffer_nodes ();
}

//----------

BufNodes::BufNodes (const std::string& source_text, std::size_t max_lexems) :
    source_text_ {source_text},
    buf_lexems_  {nullptr}, 
    max_lexems_  {max_lexems},
    length_      {0}
{
    buf_lexems_ = new NodeDiff [max_lexems_] {};

    create_buffer_nodes ();
}

//----------

BufNodes::~BufNodes ()
{
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

        case NodeType::NONE: break;

        default:             printf("ERROR! Type: %d\n", (int) buf_lexems_[length_].type_);
                             break;
    }

    length_++;

    return true;
}

//----------

void BufNodes::create_buffer_nodes ()
{
    std::size_t num_symbols = source_text_.get_num_symbols ();
    const char* start_symb  = source_text_.get_buffer_data ();
    const char* symb        = start_symb;

    int minus_cntr = 0;

    while (isspace (*symb))
        symb++;

    while (*symb == '-' || *symb == '+')
    {
        if (*symb == '-')
            minus_cntr++;

        symb++;
        while (symb - start_symb < num_symbols && isspace (*symb))
            symb++;
    }

    if (isdigit (*symb))
    {
        push (symb, NodeType::NUMB);

        if (is_odd (minus_cntr))
        {
            length_--;
            buf_lexems_[length_].value_numb_ = -buf_lexems_[length_].value_numb_;
            length_++;
        }

        while (symb - start_symb < num_symbols && isdigit (*symb))
            symb++;
    }

    while (*symb != '\0')
    {
        if (strchr ("+-", *symb))
        {
            int minus_cntr = 0;

            while (isspace (*symb))
                symb++;

            while (*symb == '-' || *symb == '+')
            {
                if (*symb == '-')
                    minus_cntr++;

                symb++;
                while (symb - start_symb < num_symbols && isspace (*symb))
                    symb++;
            }

            if (is_odd (minus_cntr))
                push ("-", NodeType::OPER);
            else
                push ("+", NodeType::OPER);
        }
        else if (strchr ("*/^()", *symb))
        {
            push (symb, NodeType::OPER);
            symb++;
        }
        else if (isdigit (*symb))
        {
            push (symb, NodeType::NUMB);

            while (symb - start_symb < num_symbols && isdigit (*symb))
                symb++;

        }
        else if (isalpha (*symb))
        {
            push (symb, NodeType::VARB);

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

void BufNodes::dump (const std::string& path_dump) const
{
    FILE*   dump_BufNodes = fopen (path_dump.c_str (), "wb");
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

void NodeDiff::print_data (FILE* dump) const
{
    assert (dump);

    switch (type_)
    {
        case NodeType::NUMB:    fprintf (dump, " NUMB -- {%ld}\n" , value_numb_);
                                break;

        case NodeType::VARB:    fprintf (dump, " VARB -- {%c}\n"  , value_varb_);
                                break;

        case NodeType::OPER:    fprintf (dump, " OPER -- {%c}\n"  , value_oper_);
                                break;

        case NodeType::NONE:    fprintf (dump, " NONE\n");
                                break;

        default:                printf  ("ERROR! Type: %d\n", (int) type_);
                                break;
    }
}

//----------

const std::size_t BufNodes::get_length () const
{
    return length_;
}

//----------

bool is_odd (int numb)
{
    return numb % 2;
}

//----------

int minus_counter (const char** symb, const char* start_symb, std::size_t num_symbols)
{
    int tmp_minus_counter = 0;

    while (isspace (**symb))
        *symb++;

    while (**symb == '-' || **symb == '+')
    {
        if (**symb == '-')
            tmp_minus_counter++;

        *symb++;
        while (*symb - start_symb < num_symbols && isspace (**symb))
            *symb++;
    }

    return tmp_minus_counter;
}

}; // namespace Differenciator

