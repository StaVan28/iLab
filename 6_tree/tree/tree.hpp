
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

    explicit NodeTree(const std::string data, NodeTree* parent) :
        data_   {data},
        left_   {},
        right_  {},
        parent_ {parent}
    {}
};
    
//!

class Tree
{
    private:

        std::string name_ = nullptr;
        NodeTree*   root_ = nullptr;
        std::size_t size_ = 0;

        void graph(Mode mode);

        void print_dump_tree (                 const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree(const Mode mode, const NodeTree* const prnt_node, std::ofstream& output);

        bool insert(NodeTree* const insrt_node, const std::string data);
        bool remove(NodeTree* const insrt_node, const std::string data);

        bool find_max(const NodeTree* const max_node, std::string ret_data);
        bool find_min(const NodeTree* const min_node, std::string ret_data);

    public:

        Tree();
        Tree(const std::string name);

       ~Tree();

        bool insert(const std::string data);
        bool remove(const std::string data);

        bool find_max(std::string ret_data);
        bool find_min(std::string ret_data);
    
        void dump(const Mode mode, const std::string file_path = "./txt/dump_tree.txt");
};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED