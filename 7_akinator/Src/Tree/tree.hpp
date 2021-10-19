#ifndef TREE
#define TREE

//--------------------------------------------------

#include "settings.hpp"

//--------------------------------------------------

enum class TreeDumpMode : int 
{
	DEBUG,
	RELEASE,
};

//--------------------------------------------------

class NodeTree
{
    public:

        std::string data_   = nullptr;
        NodeTree*   parent_ = nullptr;
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
 
        NodeTree() = delete;

        //!

        NodeTree(const std::string& data, NodeTree* parent) :
            data_   {data},
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

        void fill_akinator_tree();
        void fill_akinator_base();

        void create_tree_from_buf (const char* buffer_data);
            
        bool tree_empty() const;
        bool clear (NodeTree* clr_node);

        void graph (const TreeDumpMode mode);

        void print_dump_tree  (                         const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree (const TreeDumpMode mode, const NodeTree* const prnt_node, std::ofstream& output);

    public:

        AkinatorTree () = delete;
        AkinatorTree (const std::string& path_base);
       ~AkinatorTree ();

        void dump (const TreeDumpMode mode, const std::string& file_path = "./txt/dump_tree.txt");

};

//--------------------------------------------------

#endif //TREE