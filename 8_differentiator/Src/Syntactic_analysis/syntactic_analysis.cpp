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
    NodeDiff* op_node = nullptr;
    NodeDiff* lt_node = nullptr;
    NodeDiff* rt_node = nullptr;

    bool sign_flag = 0; 

    if (buf_nodes_[i_node_].type_ == NodeType::OPER)
    {
        if (buf_nodes_[i_node_].value_oper_ == '+')
        {
            i_node_++;
            sign_flag += 0;
        }
        else if (buf_nodes_[i_node_].value_oper_ == '-')
        {
            i_node_++;
            sign_flag += 1;
        }
        else
        {
            // error
        }
    }
    
    if (buf_nodes_[i_node_].type_ == NodeType::NONE)
    {
        return nullptr;
    }
    else
    {
        //error
    }

    lt_node = get_numb (sign_flag);

    if (buf_nodes_[i_node_].type_ == NodeType::OPER)
    {
        if (buf_nodes_[i_node_].value_oper_ = '+')
        {
            op_node = &(buf_nodes_[i_node_]);
            i_node_++;
        }
        else if (buf_nodes_[i_node_].value_oper_ = '-')
        {
            op_node = &(buf_nodes_[i_node_]);
            i_node_++;
        }
        else
        {
            // error
        }
    }

    rt_node = get_expr ();

    if (rt_node == nullptr)
    {
        return lt_node;
    }

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

NodeDiff* Parser::get_numb (bool sign_flag)
{
    NodeDiff* num_node = nullptr;

    if (buf_nodes_[i_node_].type_ == NodeType::NUMB)
    {
        num_node = &(buf_nodes_[i_node_]);
        i_node_++;
    
        if (sign_flag)
            num_node->value_numb_ = -num_node->value_numb_;
    }

    return num_node;
}

}; // namespace Differenciator

