#include "syntactic_analysis.h"

//-----------

namespace Differenciator
{

//------

Parser::Parser () :
    buf_nodes_   {DEFAULT_SOURCE_TEXT, START_MAX_NODES},
    syntax_tree_ {DEFAULT_TREE_NAME},
    i_node_      {0}
{
    buf_nodes_.dump (PATH_BUF_NODES_DUMP);
    syntax_tree_.root_ = get_expr ();
}

//------

Parser::~Parser ()
{
    syntax_tree_.dump (Mode::DEBUG,   DEFAULT_TREE_DUMP_PATH);
    syntax_tree_.dump (Mode::RELEASE, DEFAULT_TREE_DUMP_PATH);
}

//------

NodeDiff* Parser::get_expr ()
{
        if (buf_nodes_[i_node_].type_ == NodeType::OPER)
    {
        if (buf_nodes_[i_node_].value_oper_ == '+' ||
            buf_nodes_[i_node_].value_oper_ == '-')
        {
            i_node_++;
        }
    }
    
    if (buf_nodes_[i_node_].type_ == NodeType::NONE)
        return nullptr;

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
    }

    NodeDiff* rt_node = get_expr ();

    if (rt_node == nullptr)
        return lt_node;

    op_node->left_  = lt_node;
    op_node->right_ = rt_node;

    lt_node->parent_ = op_node;
    rt_node->parent_ = op_node;

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
    NodeDiff* ret_num_node = nullptr;

    if (buf_nodes_[i_node_].type_ == NodeType::NUMB)
    {
        ret_num_node = &(buf_nodes_[i_node_]);
        i_node_++;
    }

    return ret_num_node;
}

}; // namespace Differenciator

