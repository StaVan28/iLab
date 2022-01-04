#include "diff.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

NodeTree* Diff::diff (const NodeTree* input)
{
    if (input->type_ == TokenType::NUMB)
    {
        NodeTree* ret = new NodeTree (TokenType::NUMB, 0);
        return    ret;
    }

    if (input->type_ == TokenType::VARB)
    {
        NodeTree* ret = new NodeTree (TokenType::NUMB, 1);
        return    ret;
    }

    if (input->type_ == TokenType::OPER)
    {
        if (input->value_oper_ == '+' || input->value_oper_ == '-')
        {
            NodeTree* ret = new NodeTree (TokenType::OPER, input->value_varb_);

            ret->left_  = diff (input->left_);
            ret->right_ = diff (input->right_);

            return ret;
        }

        if (input->value_oper_ == '*')
        {
            NodeTree* ret   = new NodeTree (TokenType::OPER, '+');
            NodeTree* ret_l = new NodeTree (TokenType::OPER, '*', ret, nullptr, nullptr);
            NodeTree* ret_r = new NodeTree (TokenType::OPER, '*', ret, nullptr, nullptr);

            ret->left_  = ret_l;
            ret->right_ = ret_r;

            ret_l->left_  = copy (input->left_);
            ret_l->right_ = diff (input->right_);
            ret_r->left_  = diff (input->left_);
            ret_r->right_ = copy (input->right_);

            return ret;
        }
    }

    printf ("EEEEEEEEEEEEEERORR!! diff() in diff.cpp\n");
    return nullptr;
}

//-----------------------------------------------------------------------------

NodeTree* Diff::copy (const NodeTree* node)
{
    NodeTree* new_node = new NodeTree (*node);

    if (node->left_)  new_node->left_  = copy (node->left_);
    if (node->right_) new_node->right_ = copy (node->right_);

    return new_node;
}

};

//-----------------------------------------------------------------------------