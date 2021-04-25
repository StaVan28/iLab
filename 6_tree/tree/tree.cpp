
#include "tree.hpp"

//-----------------------------------------------------------------------------

Tree::Tree() :
    name_(UNKNOWN_NAME)
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::Tree(std::string name) :
    name_(name)
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::~Tree()
{
    // destruct root_
    root_ = nullptr;
}

//-----------------------------------------------------------------------------

void Tree::dump(std::string file_path)
{
    std::ofstream dump(file_path);
    assert(dump);

    dump << std::endl << "******************************************************" << std::endl;

    dump << "\t\t"        << return_current_time_and_date() << std::endl;
    dump << "\t\t\tTree:" << std::endl                      << std::endl;


    dump << "Tree (OK) [" << this << "] \"" << name_ << "\" {" << std::endl;

    print_dump_tree(root_, dump);

    dump << "}" << std::endl;


    dump << std::endl << "******************************************************" << std::endl;

    dump.close();

    graph();
}

//-----------------------------------------------------------------------------

void Tree::print_dump_tree(NodeTree* prnt_node, std::ofstream& output)
{
    if (prnt_node == nullptr)
        return;

    output <<   "data = {" << prnt_node->data_   << "}"
           <<   "left = {" << prnt_node->left_   << "}"
           <<  "right = {" << prnt_node->right_  << "}"
           << "parent = {" << prnt_node->parent_ << "}" << std::endl;

    if (prnt_node->right_ != nullptr)
        print_dump_tree(prnt_node->right_, output);

    if (prnt_node->left_  != nullptr)
        print_dump_tree(prnt_node->left_,  output);
}

//-----------------------------------------------------------------------------

void Tree::graph()
{

}


