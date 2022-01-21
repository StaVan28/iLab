#include "diff.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

NodeTree* Diff::diff (const NodeTree* input)
{
    if (input->type_ == NodeType::NUMB)
    {
        NodeTree* ret = new NodeTree (NodeType::NUMB, 0);
        return    ret;
    }

    if (input->type_ == NodeType::VARB)
    {
        NodeTree* ret = new NodeTree (NodeType::NUMB, 1);
        return    ret;
    }

    if (input->type_ == NodeType::OPER)
    {
        if (input->value_oper_ == '+' || input->value_oper_ == '-')
        {
            NodeTree* ret = new NodeTree (NodeType::OPER, input->value_varb_);

            ret->left_  = diff (input->left_);
            ret->right_ = diff (input->right_);

            return ret;
        }

        if (input->value_oper_ == '*')
        {
            NodeTree* ret   = new NodeTree (NodeType::OPER, '+');
            NodeTree* ret_l = new NodeTree (NodeType::OPER, '*', ret, nullptr, nullptr);
            NodeTree* ret_r = new NodeTree (NodeType::OPER, '*', ret, nullptr, nullptr);

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

//-----------------------------------------------------------------------------

void NodeDiff::print_data (FILE* dump) const
{
    assert (dump);

    switch (type_)
    {
        case NodeType::NUMB: fprintf (dump, " NUMB -- {%ld}\n" , value_numb_);
                              break;

        case NodeType::VARB: fprintf (dump, " VARB -- {%c}\n"  , value_varb_);
                              break;

        case NodeType::OPER: fprintf (dump, " OPER -- {%c}\n"  , value_oper_);
                              break;

        default:              printf  ("ERROR! Type: %d\n", type_);
                              break;
    }

}

//-----------------------------------------------------------------------------

}; // namespace Differenciator