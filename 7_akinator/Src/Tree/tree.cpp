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
    
    create_tree_from_buf(parser_base.get_buffer_data());
}

//---------

void AkinatorTree::fill_akinator_base()
{

}

//---------

void AkinatorTree::create_tree_from_buf(const char* buf_data)
{
    NodeTree*   tmp_new_node  = nullptr;
    NodeTree*   tmp_prnt_node = nullptr;
    std::size_t indx_buf      = 0;

    indx_buf++;

    tmp_new_node = new NodeTree(buf_data, nullptr);
    size_++;

    root_         = tmp_new_node;
    tmp_prnt_node = tmp_new_node;

    while (!isspace(buf_data[indx_buf]))
        indx_buf++;

    while (buf_data[indx_buf] != '\0')
    {
        while (isspace(buf_data[indx_buf]))
            indx_buf++;

        if (buf_data[indx_buf] == '<')
        {
            indx_buf++;

            while (isspace(buf_data[indx_buf]))
                indx_buf++;

            indx_buf++;

            tmp_new_node = new NodeTree(buf_data, nullptr);
            size_++;

            while (!isspace(buf_data[indx_buf]))
                indx_buf++;

            tmp_new_node->parent_ = tmp_prnt_node;
            tmp_prnt_node->left_  = tmp_new_node;

            tmp_prnt_node = tmp_new_node;
        }

        if (buf_data[indx_buf] == '>')
        {
            indx_buf++;

            while (isspace(buf_data[indx_buf]))
                indx_buf++;

            indx_buf++;

            tmp_new_node = new NodeTree(buf_data, nullptr);
            size_++;

            while (!isspace(buf_data[indx_buf]))
                indx_buf++;

            tmp_new_node->parent_ = tmp_prnt_node;
            tmp_prnt_node->right_ = tmp_new_node;

            tmp_prnt_node = tmp_new_node;
        }

        if (buf_data[indx_buf] == 'V')
        {
            indx_buf++;

            tmp_prnt_node = tmp_prnt_node->parent_;
        }
    }
}

//---------

void AkinatorTree::create_root_node(NodeTree* tmp_new_node, NodeTree* tmp_prnt_node, const char* buf_data, std::size_t indx_buf)
{
    indx_buf++;

    tmp_new_node = new NodeTree(buf_data, nullptr);
    size_++;

    root_         = tmp_new_node;
    tmp_prnt_node = tmp_new_node;

    while (!isspace(buf_data[indx_buf]))
        indx_buf++;
}

//---------

void AkinatorTree::skip_delimiters(const char* buf_data, std::size_t indx_buf)
{
    indx_buf++;

    while (isspace(buf_data[indx_buf]))
        indx_buf++;

    indx_buf++;
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
