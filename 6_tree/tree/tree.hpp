
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

#include "settings.h"

//-----------------------------------------------------------------------------

class NodeTree
{
    public:

        std::string data_   = nullptr; 
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
        NodeTree*   parent_ = nullptr;
};
    
//!

class Tree
{
    private:

        std::string name_ = nullptr;
        NodeTree*   root_ = nullptr;

        void graph(Mode mode);

        void print_dump_tree (                 const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree(const Mode mode, const NodeTree* const prnt_node, std::ofstream& output);

        void insert(const NodeTree* const insrt_node, const std::string data);

    public:

        Tree();
        Tree(const std::string name);

       ~Tree();

        void insert(const std::string data);
    
        void dump(const Mode mode, const std::string file_path = "./txt/dump_tree.txt");
};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED