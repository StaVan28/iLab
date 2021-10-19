#ifndef TREE
#define TREE

//--------------------------------------------------

#include "settings.hpp"
#include "parsing_text.hpp"

//--------------------------------------------------

enum class TreeDumpMode : int 
{
	DEBUG,
	RELEASE,
};

//!

enum class TreeDirection : int
{
    LEFT,
    RIGHT,
};

//--------------------------------------------------

class NodeTree
{
    public:

        std::string data_;
        NodeTree*   parent_ = nullptr;
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
 
        NodeTree()
        {}

        //!

        NodeTree (const std::string& data, NodeTree* parent) :
            data_   {data},
            parent_ {parent}
        {}

        //!

        explicit NodeTree (NodeTree* parent) :
            parent_ {parent}
        {}

        //!

       ~NodeTree()
       {}
};

//--------------------------------------------------

class AkinatorTree
{
    private:

        NodeTree*   root_      = nullptr; 
        std::string path_base_ = nullptr;
        std::size_t size_      = 0;

        void fill_akinator_tree ();
        void fill_akinator_base ();

        void      create_tree_from_buf (const char* buffer_data);
        NodeTree* fill_recurce_tree    (Token* buf_lexems, std::size_t* num_lexem);
        void      print_recursive_base (FILE* base_tree, NodeTree* cur_node, std::size_t num_tabs);

        bool tree_empty () const;
        bool clear (NodeTree* clr_node);

        void graph (const TreeDumpMode mode);

        void print_dump_tree  (                         const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree (const TreeDumpMode mode, const NodeTree* const prnt_node, std::ofstream& output);

        NodeTree* walk (const NodeTree* cur_node, TreeDirection direct) const;

    public:

        AkinatorTree () = delete;
        AkinatorTree (const std::string& path_base);
       ~AkinatorTree ();

        void dump (const TreeDumpMode mode, const std::string& file_path = "./Txt/dump_tree.txt");

};

//--------------------------------------------------

#endif //TREE