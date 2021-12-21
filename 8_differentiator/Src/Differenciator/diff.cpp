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

NodeTree* Diff::copy (const NodeTree* copy_node)
{
    NodeTree* new_node = nullptr;

    switch (copy_node->type_)
    {
        case TokenType::NUMB: new_node = new NodeTree (copy_node->type_, copy_node->value_numb_);
                             break;

        case TokenType::VARB: new_node = new NodeTree (copy_node->type_, copy_node->value_varb_);
                             break;

        case TokenType::OPER: new_node = new NodeTree (copy_node->type_, copy_node->value_oper_);
                             break;

        default:             printf("ERROR! Type:\n");
                             break;
    }

    if (copy_node->left_  != nullptr)
    {
        new_node->left_          = copy (copy_node->left_);
        new_node->left_->parent_ = new_node;
    }

    if (copy_node->right_ != nullptr)
    {
        new_node->right_          = copy (copy_node->right_);
        new_node->right_->parent_ = new_node;
    }

    return new_node;
}

};

//-----------------------------------------------------------------------------