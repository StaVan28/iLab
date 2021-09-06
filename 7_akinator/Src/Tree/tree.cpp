//--------------------------------------------------

#include "parsing_text.hpp"
#include "tree.hpp"

//--------------------------------------------------

AkinatorTree::AkinatorTree(const std::string path_base) :
    path_base_ {path_base}
{
    assert(this);

    fill_akinator_tree();
}

//---------

AkinatorTree::~AkinatorTree()
{
    assert(this);
    
    clear(root_);

    root_ = 0;
    size_ = 0;
}

//---------

void AkinatorTree::fill_akinator_tree()
{
    Text parser_base(path_base_);
    
    create_tree(parser_base.get_buffer_data());
}

//---------

void AkinatorTree::fill_akinator_base()
{

}

//---------

void AkinatorTree::create_tree(const char* buf_data)
{
    NodeTree*   tmp_prnt_node = root_;
    std::size_t indx_buf      = 0;

    while ()
    {
        while (isspace(buf_data[indx_buf]))
            indx_buf++;

        if (buf_data[indx_buf] == '?')
        {
            indx_buf++;

            if (tree_empty())
            {
                root_ = new NodeTree(buf_data, nullptr);
                size_++;

                tmp_prnt_node = root_;
            }
            else
            { 

            }
        }
}

//---------

bool AkinatorTree::tree_empty() const
{
    return size_ == EMPTY;
}

//---------

bool AkinatorTree::clear(NodeTree* clr_node)
{
    if (tree_empty())
        return false;

    if (clr_node->left_ != nullptr)
        clear(clr_node->left_);

    if (clr_node->right_ != nullptr)
        clear(clr_node->right_);

    delete clr_node;
    return true;
}

//--------------------------------------------------
