
#ifndef LEXICAL_ANALYSIS_H_INCLUDED
#define LEXICAL_ANALYSIS_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "node_diff.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

class TextDiff
{
    private:

        std::size_t num_symbols_ = 0;
        char*       buf_data_    = nullptr;

        std::size_t num_symbols_in_file (const std::string& path_base);
        void        create_buffer_data  (const std::string& path_base);

    public:

        TextDiff ();
        TextDiff (const std::string& path_base);
       ~TextDiff ();

        TextDiff             (const TextDiff& other) = delete;
        TextDiff& operator = (const TextDiff& other) = delete;

        TextDiff             (TextDiff&& that) = delete;
        TextDiff& operator = (TextDiff&& that) = delete;

        const char* get_buffer_data () const;
        std::size_t get_num_symbols () const;
       
}; // class TextDiff

//!

class BufNodes
{
    private:

        TextDiff    source_text_; 
        NodeDiff*   buf_lexems_;
        std::size_t max_lexems_;
        std::size_t length_;

        bool resize ();

    public:

        BufNodes ();
        BufNodes (const std::string& source_text, std::size_t max_lexems);
       ~BufNodes ();

        BufNodes             (const BufNodes& other) = delete;
        BufNodes& operator = (const BufNodes& other) = delete;

        BufNodes             (BufNodes&& that) = delete;
        BufNodes& operator = (BufNodes&& that) = delete;

        NodeDiff&       operator[] (const int indx);
        const NodeDiff& operator[] (const int indx) const;

        void create_buffer_nodes ();

        bool push (const char* symb, NodeType type);
        void dump (const std::string& path_dump = PATH_BUF_NODES_DUMP) const;

}; // class BufNodes

bool is_odd (int numb);

int  minus_counter (const char** symb, const char* start_symb, std::size_t num_symbols);

}; // namespace Differenciator


//-----------------------------------------------------------------------------

#endif // LEXICAL_ANALYSIS_H_INCLUDED

