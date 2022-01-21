
#ifndef PARSING_TREE_H_INCLUDED
#define PARSING_TREE_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "node_diff.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

class BufNodes
{
    private:

        NodeDiff*   buf_nodes_ = nullptr;
        std::size_t max_nodes_ = 0;
        std::size_t length_    = 0;

        bool resize ();

    public:

        BufNodes (std::size_t max_nodes = START_MAX_NODES);
       ~BufNodes ();

        NodeDiff&       operator[] (const int indx);
        const NodeDiff& operator[] (const int indx) const;

        bool push (const char* symb, NodeType type);
        void dump (const char* path_dump = PATH_BUF_NODES_DUMP) const;

}; // class BufNodes

//!

class TextDiff
{
    private:

        std::size_t num_symbols_ = 0;
        char*       buf_data_    = nullptr;

        std::size_t num_symbols_in_file (const std::string& path_base);
        void        create_buffer_data  (const std::string& path_base);


    public:

        BufNodes buf_nodes_;

        TextDiff () = delete;
        TextDiff (const std::string& path_base);
       ~TextDiff ();

        const char* get_buffer_data () const;
        std::size_t get_num_symbols () const;
       
        void create_buffer_nodes ();
}; // class TextDiff

}; // namespace Differenciator


//-----------------------------------------------------------------------------

#endif // PARSING_TREE_H_INCLUDED

