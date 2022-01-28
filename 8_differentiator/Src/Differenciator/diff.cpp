#include "diff.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

//!

Diff::Diff (const std::string& source_text)
{

}

//-----------------------------------------------------------------------------

Diff::~Diff ()
{

}

//-----------------------------------------------------------------------------

NodeDiff* Diff::diff (const NodeDiff* input)
{
    if (input->type_ == NodeType::NUMB)
    {
        NodeDiff* ret = new NodeDiff (NodeType::NUMB, 0);
        return    ret;
    }

    if (input->type_ == NodeType::VARB)
    {
        NodeDiff* ret = new NodeDiff (NodeType::NUMB, 1);
        return    ret;
    }

    if (input->type_ == NodeType::OPER)
    {
        if (input->value_oper_ == '+' || input->value_oper_ == '-')
        {
            NodeDiff* ret = new NodeDiff (NodeType::OPER, input->value_varb_);

            ret->left_  = diff (input->left_);
            ret->right_ = diff (input->right_);

            return ret;
        }

        if (input->value_oper_ == '*')
        {
            NodeDiff* ret   = new NodeDiff (NodeType::OPER, '+');
            NodeDiff* ret_l = new NodeDiff (NodeType::OPER, '*', ret, nullptr, nullptr);
            NodeDiff* ret_r = new NodeDiff (NodeType::OPER, '*', ret, nullptr, nullptr);

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

NodeDiff* Diff::copy (const NodeDiff* node)
{
    NodeDiff* new_node = new NodeDiff (*node);

    if (node->left_)  new_node->left_  = copy (node->left_);
    if (node->right_) new_node->right_ = copy (node->right_);

    return new_node;
}


//-----------------------------------------------------------------------------

}; // namespace Differenciator