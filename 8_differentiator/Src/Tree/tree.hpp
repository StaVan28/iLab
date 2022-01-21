
#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "node_diff.h"

//-----------------------------------------------------------------------------

enum class Mode : int 
{
    DEBUG,
    RELEASE,
};

//-----------------------------------------------------------------------------

namespace Differenciator
{

class NodeTree
{
    public:

        NodeType type_;
        char     value_oper_;
        long     value_numb_;
        char     value_varb_;

        NodeTree* parent_ = nullptr;
        NodeTree* left_   = nullptr;
        NodeTree* right_  = nullptr;
 
        NodeTree ()
        {}

        //!

        template <typename T>
        NodeTree (NodeType type, T value, NodeTree* parent = nullptr, 
                                          NodeTree* left   = nullptr, NodeTree* right = nullptr) :
            type_   {type},
            parent_ {parent},
            left_   {left},
            right_  {right}
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

        explicit NodeTree (NodeTree* parent) :
            parent_ {parent}
        {}

        //!

       ~NodeTree ()
       {}

       //!

       void print_data   (const NodeTree* const prnt_node, FILE* dump) const;
       void choose_param (const NodeTree* const prnt_node, FILE* dump) const;
};
   
//!

class Tree
{
    private:

        const NodeTree* const print_graph_tree (const Mode mode, const NodeTree* const prnt_node, FILE* dump);

    public:

        std::string name_;
        NodeTree*   root_;
        std::size_t size_;

        Tree();
        Tree(const std::string& name);

       ~Tree();
    
        void dump (Mode mode, const char* path_name_without_end = "./Txt/dump_tree");
};

int vssystem (const char* command, ...) __attribute__((format(printf, 1, 2)));

}; // using namespace Differenciator


//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED