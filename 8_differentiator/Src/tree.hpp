
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

enum class NodeType : int
{
    NONE,
    OPER,
    NUMB,
    VARB,
};

//-----------------------------------------------------------------------------

class NodeTree
{
    public:

        NodeType type_;
        char     value_oper_;
        long     value_numb_;
        char     value_varb_;

        std::string data_;
        NodeTree*   parent_ = nullptr;
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
 
        NodeTree ()
        {}

        //!

        template <typename T>
        NodeTree (NodeType type, T value, const std::string& data) :
            type_ {type},
            data_ {data}
        {
            switch (type)
            {
                case NodeType::NUMB: value_numb_ = value;
                                     break;

                case NodeType::VARB: value_varb_ = value;
                                     break;

                case NodeType::OPER: value_oper_ = value;
                                     break;

                default:             printf("ERROR! Type:\n");
                                     break;
            }
        }

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


       Text& deep_copy (const Text&);
};
   
//!

class Tree
{
    private:

        void graph (const Mode mode);

        void print_dump_tree  (                 const NodeTree* const prnt_node, std::ofstream& output);
        void print_graph_tree (const Mode mode, const NodeTree* const prnt_node, std::ofstream& output);

    public:

        std::string name_ = nullptr;
        NodeTree*   root_ = nullptr;
        std::size_t size_ = 0;

        Tree();
        Tree(const std::string& name);

       ~Tree();
    
        void dump(const Mode mode, const std::string& file_path = "./txt/dump_tree.txt");

};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED