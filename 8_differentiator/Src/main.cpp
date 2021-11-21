#include "tree.hpp"

//-----------------------------------------------------------------------------

NodeTree* diff (const NodeTree* input_node);

NodeTree* copy (const NodeTree*  copy_node);

//-----------------------------------------------------------------------------

int main ()
{
    NodeTree n1 (NodeType::OPER, '*',  "*");
    NodeTree n2 (NodeType::VARB, 'x',  "x");
    NodeTree n3 (NodeType::NUMB,  28, "28");

    n1.left_  = &n2;
    n1.right_ = &n3;

    Tree my_tree("name");
    my_tree.root_ = &n1;
    my_tree.dump(Mode::DEBUG, "./dump.txt");

    NodeTree* dif_node = diff (my_tree.root_);

    Tree my_tree_dif("name diff");
    my_tree_dif.root_ = dif_node;
    my_tree_dif.dump(Mode::DEBUG, "./dump_dif.txt");


    return 0;
}

//-----------------------------------------------------------------------------

NodeTree* diff (const NodeTree* input)
{
    if (input->type_ == NodeType::NUMB)
    {
        NodeTree* ret = new NodeTree (NodeType::NUMB, 0, "0");
        return    ret;
    }

    if (input->type_ == NodeType::VARB)
    {
        NodeTree* ret = new NodeTree (NodeType::NUMB, 1, "1");
        return    ret;
    }

    if (input->type_ == NodeType::OPER)
    {
        if (input->value_oper_ == '+' || input->value_oper_ == '-')
        {
            NodeTree* ret = new NodeTree (NodeType::OPER, input->value_varb_, input->data_);

            ret->left_  = diff (input->left_);
            ret->right_ = diff (input->right_);

            return ret;
        }

        if (input->value_oper_ == '*')
        {
            NodeTree* ret   = new NodeTree (NodeType::OPER, '+', "+");
            NodeTree* ret_l = new NodeTree (NodeType::OPER, '*', "*");
            NodeTree* ret_r = new NodeTree (NodeType::OPER, '*', "*");

            ret->left_  = ret_l;
            ret->right_ = ret_r;

            ret_l->left_  = input->left_;
            ret_l->right_ = diff (input->right_);
            ret_r->left_  = diff (input->left_);
            ret_r->right_ = input->right_;

            return ret;
        }

        if (input->value_oper_ == '^')
        {
            NodeTree* ret       = new NodeTree (NodeType::OPER, '+', "+");
            NodeTree* ret_left  = new NodeTree (NodeType::OPER, '*', "*");
            NodeTree* ret_right = new NodeTree (NodeType::OPER, '*', "*");            
        }
    }

    printf ("EEEEEEEEEEEEEERORR lol\n");
    return nullptr;
}

//-----------------------------------------------------------------------------

NodeTree* copy (NodeTree* copy)
{
    NodeTree* new_copy = new NodeTree (copy);
}

//-----------------------------------------------------------------------------
