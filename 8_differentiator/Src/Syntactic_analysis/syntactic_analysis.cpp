#include "syntactic_analysis.h"

//-----------

namespace Differenciator
{

//------

Parser::Parser ()
{
    i_node_ = 0;
    buf_nodes_;
    syntax_tree_;

    syntax_tree_.root_ = get_expr ();
}

//------

Parser::~Parser ()
{
    printf ("destr parser\n");

    syntax_tree_.dump (Mode::DEBUG,   "./Txt/dump");
    syntax_tree_.dump (Mode::RELEASE, "./Txt/dump");
}

//------

NodeDiff* Parser::get_expr ()
{
    NodeDiff* lt_node = get_numb ();
    NodeDiff* op_node = nullptr;

    if (buf_nodes_[i_node_].type_ == NodeType::OPER)
    {
        if (buf_nodes_[i_node_].value_oper_ == '+' ||
            buf_nodes_[i_node_].value_oper_ == '-')
        {
            op_node = &(buf_nodes_[i_node_]);
            i_node_++;
        }
        else
        {
            // other operators
        }
    }
    else if (buf_nodes_[i_node_].type_ == NodeType::NONE)
    {
        return lt_node;
    }
    else 
    {
        //error
    }

    NodeDiff* rt_node = get_expr ();

    lt_node->parent_ = op_node;
    rt_node->parent_ = op_node;

    op_node->left_   = lt_node;
    op_node->right_  = rt_node;

    return op_node;
}

//------

NodeDiff* Parser::get_term ()
{
    return nullptr;
}

//------

NodeDiff* Parser::get_prnt ()
{
    return nullptr;
}
//------

NodeDiff* Parser::get_numb ()
{
    printf ("i_node = %ld\n\n", i_node_);
    printf ("buf = %p\n\n", &buf_nodes_);

    if (buf_nodes_[i_node_].type_ == NodeType::NUMB)
    {
        NodeDiff* ret_node = &(buf_nodes_[i_node_]);
        i_node_++;

        return ret_node;
    }
    else
    {
        // error
    }

    return nullptr;
}

}; // namespace Differenciator

