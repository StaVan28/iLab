
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
        NodeDiff*   buf_nodes_;
        std::size_t max_nodes_;
        std::size_t length_;

        bool resize ();

    public:

        BufNodes () = delete;
        BufNodes (const std::string& path_base, std::size_t max_nodes);
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

}; // namespace Differenciator


//-----------------------------------------------------------------------------

#endif // LEXICAL_ANALYSIS_H_INCLUDED

