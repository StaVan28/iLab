
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

   ~NodeTree() 
    {
        left_   = nullptr;
        right_  = nullptr;
        parent_ = nullptr;
    }

};
    
//!

class Tree
{
    private:

        std::string name_ = nullptr;
        NodeTree*   root_ = nullptr;
        std::size_t size_ = 0;

        void graph(const Mode mode);

        void print_dump_tree (                 const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree(const Mode mode, const NodeTree* const prnt_node, std::ofstream& output);

        bool insert(NodeTree* const insrt_node, const std::string data);
        bool remove(NodeTree* const srch_node,  const std::string rmv_data);

        bool find_max(const NodeTree* const max_node, std::string ret_data) const;
        bool find_min(const NodeTree* const min_node, std::string ret_data) const;

        bool clear(NodeTree* clr_node);

    public:

        Tree();
        Tree(const std::string name);

       ~Tree();

        bool insert(const std::string data);
        bool remove(const std::string data);

        bool find_max(std::string ret_data) const;
        bool find_min(std::string ret_data) const;

        bool clear();

        bool empty() const noexcept;
        bool size()  const noexcept;
    
        void dump(const Mode mode, const std::string file_path = "./txt/dump_tree.txt");
};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED