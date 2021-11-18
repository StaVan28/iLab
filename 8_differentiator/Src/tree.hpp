
#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iostream> 
#include <fstream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

//-----------------------------------------------------------------------------

enum class Mode : int 
{
    DEBUG,
    RELEASE,
};

//-----------------------------------------------------------------------------

class NodeTree
{
    public:

        std::string data_;
        NodeTree*   parent_ = nullptr;
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
 
        NodeTree ()
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

       ~NodeTree ()
       {}
};
   
//!

class Tree
{
    private:

        std::string name_ = nullptr;
        NodeTree*   root_ = nullptr;
        std::size_t size_ = 0;

        void graph (const Mode mode);

        void print_dump_tree  (                 const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree (const Mode mode, const NodeTree* const prnt_node, std::ofstream& output);

    public:

        Tree();
        Tree(const std::string& name);

       ~Tree();
    
        void dump(const Mode mode, const std::string& file_path = "./txt/dump_tree.txt");
};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED